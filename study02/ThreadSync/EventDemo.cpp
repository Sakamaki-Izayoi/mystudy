#include "stdafx.h"
//frog

/**************ʹ��Event����ͬ��**********************/
CHAR szFoo[MAX_PATH] = "������";
HANDLE hEvent = NULL;
DWORD WINAPI Demo1Proc(LPVOID lpParameter)
{
	if (!WaitForSingleObject(hEvent, INFINITE))
	{
		std::cout << "�����̺߳���,���յ��¼������ˣ�����Ϊ��";
		std::cout << szFoo << std::endl;;
	}
	return 0;
}

void EventDemo1()
{
	hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	HANDLE hThread = CreateThread(NULL, 0, Demo1Proc, NULL, 0, NULL);

	CopyMemory(szFoo, "��Ҫ��������", sizeof("��Ҫ��������"));
	std::cout << "����׼�����0.5��֮��signal�¼�" << std::endl;
	Sleep(500);
	SetEvent(hEvent);
	Sleep(200);
}
/*****************************************************/

void TestEvent()
{
	EventDemo1();
}
