/*!
 * \file MsgPipe.cpp
 *
 * \author FrogGod
 * \date ���� 2017
 *
 * �����ܵ�ʵ�ֽ������ݽ�����
 * �����ܵ�������ʹ��CreateNamedPipe(pszNameΪ"\\\\.\\pipe\\pipename");
 * �����ܵ��ͻ���ʹ��Createfile(pszNameΪ"\\\\servername\\pipe\\pipename");
 */

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <string>

void run_client();
void run_server();
HANDLE CreateNewPipe(LPCTSTR lpszName);
void ReadPipeData(HANDLE h_PipeHandle);
void WritePipeData(HANDLE h_PipeHandle);

#define MY_MUTEX _T("467F8B22-5984-4A21-87A3-6AC6681D32C6")
const TCHAR g_PipeReadName[] = _T("\\\\.\\pipe\\Pipe_Read_5DAC42BD-A2E0-4A5A-A2A4-CB0A3F37E9C5");
const TCHAR g_PipeWirteName[] = _T("\\\\.\\pipe\\Pipe_Write_E97B0232-7C5E-4EB1-93AF-71727E5CA4EE");

int main()
{
	auto h_Mutex = CreateMutex(NULL, FALSE, MY_MUTEX);	//�ܵ�������
	if (h_Mutex)
	{
		if (GetLastError() == ERROR_ALREADY_EXISTS)
		{
			run_client();
		}
		else
		{
			run_server();
		}
	}
    return 0;
}

void run_server()
{
	auto h_WritePipe = CreateNewPipe(g_PipeWirteName);
	std::cout << "����WritePipe OK" << std::endl;
	auto h_ReadPipe = CreateNewPipe(g_PipeReadName);
	std::cout << "����ReadPipe OK" << std::endl;
	
	while (true)
	{
		//pipe�����Ӧ�ó������
		WritePipeData(h_WritePipe);
		ReadPipeData(h_ReadPipe);
	}
}

void run_client()
{
	if (!WaitNamedPipe(g_PipeWirteName, NMPWAIT_WAIT_FOREVER))
	{
		std::cout << "Write�����ܵ�ʵ�������� ..." << std::endl;
		return;
	}
	//�ͻ��˶��Ƿ�����д
	auto h_ReadNamedPipe = CreateFile(g_PipeWirteName, GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (h_ReadNamedPipe == INVALID_HANDLE_VALUE)
	{
		std::cout << "�������ܵ�ʧ�� ..." << std::endl;
		return;
	}

	//�ȴ�READ�ڴ����������ӣ�
	Sleep(2000);

	//�ͻ���д�Ƿ�������
	if (!WaitNamedPipe(g_PipeReadName, NMPWAIT_WAIT_FOREVER))
	{
		std::cout << "Read�����ܵ�ʵ�������� ..." << std::endl;
		return;
	}
	auto h_WriteNamedPipe = CreateFile(g_PipeReadName, GENERIC_WRITE, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == h_WriteNamedPipe)
	{
		std::cout << "�������ܵ�ʧ�� ..." << std::endl;
		return;
	}
	while (true)
	{
		//pipe�ͻ���Ӧ�ó������
		ReadPipeData(h_ReadNamedPipe);
		WritePipeData(h_WriteNamedPipe);
	}
}


//************************************
// Method:    CreateNewPipe
// Returns:   ����NULL �� 0˵������ʧ��
// Parameter: LPCTSTR lpszName
//************************************
HANDLE CreateNewPipe(LPCTSTR lpszName)
{
	auto h_NamePipe = CreateNamedPipe(lpszName, PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED,
								     0, 1, 0x4000, 0x4000, 0, NULL);
	if (h_NamePipe == INVALID_HANDLE_VALUE)
	{
		std::cout << "���������ܵ�ʧ��..." << std::endl;
		return NULL;
	}
	//����¼��Եȴ��ͻ������������ܵ�
	//���¼�Ϊ�ֶ������¼����ҳ�ʼ��״̬Ϊ���ź�״̬
	auto h_Event = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (h_Event == NULL)
	{
		std::cout << "�����¼�ʧ��..." << std::endl;
		return NULL;
	}

	//���ڴ���ʱ��ʹ��FILE_FLAG_OVERLAPPED�������ڵ���cConnectNamedPipe������ovlap
	OVERLAPPED ovlap = { 0 };
	memset(&ovlap, 0, sizeof(ovlap));
	ovlap.hEvent = h_Event;

	//�ȴ��ͻ�������
	if (ConnectNamedPipe(h_NamePipe, &ovlap) == 0)
	{
		if (ERROR_IO_PENDING != GetLastError() && ERROR_PIPE_CONNECTED != GetLastError())// || ERROR_PIPE_CONNECTED != GetLastError())
		{
			CloseHandle(h_NamePipe);
			CloseHandle(h_Event);
			std::cout << "�ȴ��ͻ�������ʧ�� ..." << std::endl;
			return 0;
		}
	}

	if (WAIT_FAILED == WaitForSingleObject(h_Event, INFINITE))
	{
		CloseHandle(h_NamePipe);
		CloseHandle(h_Event);
		std::cout << "�ȴ�����ʧ��..." << std::endl;
		return 0;
	}
	CloseHandle(h_Event);
	return h_NamePipe;
}

void ReadPipeData(HANDLE h_PipeHandle)
{
	CHAR szStr[MAX_PATH * 4] = { 0 };
	DWORD dwRet = 0;
	auto ret = ReadFile(h_PipeHandle, szStr, sizeof(szStr), &dwRet, NULL);
	std::cout << "��ȡ���ݳɹ�=" << szStr << std::endl;;
}

void WritePipeData(HANDLE h_PipeHandle)
{
	std::cout << "��������:";
	auto msg = std::string();
	std::getline(std::cin, msg);
	DWORD dwRet = 0;
	WriteFile(h_PipeHandle, msg.c_str(), msg.size(), &dwRet, NULL);
}

