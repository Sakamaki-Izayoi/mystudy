/*!
* \file MsgFile.cpp
*
* \author FrogGod
* \date ���� 2017
*
* �ļ�ʵ�ֽ������ݽ�����
* ����Ŀ���¼�������Ϊ������һ������д�ļ���һ�����ļ���ʵ�ֽ��̼����ݽ����� 
* д�ļ��Ľ�����SetEvent֪ͨ���ļ��Ľ��̣����¶����ˡ�
*/

/************************************************************************
* �ܽ�                                                                      
* 1.��GUID����������Դ�����֣��ú���棬���Ա����ͻ
* 2.����std::string.c_str()���Խ�stringת��Ϊc�����ַ�����
* 3.����ļ���������ʹ����֮������trucate_exsiting�򿪣��Ϳ�����
* 4.c++�����û�����std::getline(std::cin, msg);
************************************************************************/

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <string>

#define LOCK_EVENT __T("{2E3A242A-B469-415A-B569-F54476075AC4}")
int main()
{
	auto msg = std::string("msg initial");
	auto h_Lock = CreateEvent(NULL, FALSE, FALSE, LOCK_EVENT);//<--Eventͬ����

	//�̳��������� h_lock || h_Lock == INVALID_HANDLE_VALUE�����ҰѺ����ȥ��
	//�����ǲ�msdn�ķ���
	if (h_Lock == NULL)
	{
		std::cout << "Create Event Error %d:" << GetLastError() << std::endl;
		return -1;
	}

	//�¼��Ѵ��ڣ�˵��֮ǰ���˴�����
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		
		while (true)
		{
			std::cout << "string from another process: ";
			WaitForSingleObject(h_Lock, INFINITE);
			auto h_File = CreateFile(_T("Share.dat"), GENERIC_READ | GENERIC_WRITE,
									0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			if (h_File == INVALID_HANDLE_VALUE)
			{
				std::cout << "Create File Error %d" << GetLastError() << std::endl;
				return -1;
			}
			DWORD dwRet;
			char str[MAX_PATH] = {};
			ReadFile(h_File, str, MAX_PATH, &dwRet, NULL);
			msg = std::string(str);
			std::cout << msg << std::endl;
			CloseHandle(h_File);

			h_File = CreateFile(_T("Share.dat"), GENERIC_READ | GENERIC_WRITE,
				0, NULL, TRUNCATE_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			CloseHandle(h_File);
		}
	}
	else//�¼������ɹ�
	{

		while (true)
		{
			DWORD dwRet = 0;
			std::cout << "input your string for another :";
			std::getline(std::cin, msg);
			auto h_File = CreateFile(_T("Share.dat"),GENERIC_READ | GENERIC_WRITE,
									0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			if (h_File == INVALID_HANDLE_VALUE)
			{
				std::cout << "Create File Error: "<< std::hex << GetLastError() << std::endl;
				return -1;
			}
			WriteFile(h_File, msg.c_str(), msg.size(), &dwRet, NULL);
			CloseHandle(h_File);
			SetEvent(h_Lock);
		}
	}

	return 0;
}

