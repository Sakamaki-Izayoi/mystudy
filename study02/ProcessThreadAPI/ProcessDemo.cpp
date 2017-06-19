#include "stdafx.h"

/***************��������ʵ��*************************/
#define EXE_PATH L"C:\\Users\\killvxk\\Desktop\\procexp.exe"
void TestCreateProcess()
{
	STARTUPINFO si = {};
	PROCESS_INFORMATION pi = {};
	si.cb = sizeof(si);
	BOOL isSuc = CreateProcess(
		EXE_PATH,	//�ļ�·������Ϊ�գ��ڶ�����������Ϊ��
		NULL,		//�����У���һ���ո�֮ǰ������·�����ո�֮������������
		NULL,		//Security_Attributes����ΪNULL���ʾ��Ĭ�ϰ�ȫ����
		NULL,		//�̰߳�ȫ���ԣ��㲻�����о�����Ҫ
		FALSE,		//�ӽ��̵ľ�����ɹ�ϵ
		0,			//������־��һ�㲻�á�
		NULL,		//��ΪNULLʹ�ø����̻�������
		NULL,		//��ΪNULLʹ�ø�����Ŀ¼��Ϊ��ǰĿ¼
		&si,		//STARTUPINFO����ʼ��λ�õ���Ϣ����������ΪNULL
		&pi			//�����ɹ��󷵻ص���Ϣ
	);
	WaitForSingleObject(pi.hProcess, INFINITE);	//�ȴ��ӽ��̽���
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}
/***********************************************/

/*******************��ý��̸�������******************/
typedef struct _PROCESS_INFO
{
	DWORD dwPid;
	HANDLE hProcess;
	DWORD dwProVersion;
	DWORD dwPrioClass;
	DWORD dwHandleCount;
	DWORD_PTR dwAffinityMask;
	DWORD_PTR dwSystemAffinityMask;
	SIZE_T dwWorkingSetSizeMax;
	SIZE_T dwWorkingSetSizeMin;
	LPWSTR szCmdLine;
	STARTUPINFO sti;
}PROCESS_INFO, *LPPROCESS_INFO;
//���͵ģ��Ժ�����Լ����
//
void GetProcessInfo()
{
	PROCESS_INFO pi;
	pi.hProcess = GetCurrentProcess();
	pi.dwPid = GetCurrentProcessId();
	pi.dwProVersion = GetProcessVersion(pi.dwPid);
	pi.dwPrioClass = GetPriorityClass(pi.hProcess);
	pi.dwHandleCount = GetProcessHandleCount(pi.hProcess, &pi.dwHandleCount);
	GetProcessAffinityMask(pi.hProcess, &pi.dwAffinityMask, &pi.dwSystemAffinityMask);
	GetProcessWorkingSetSize(pi.hProcess, &pi.dwWorkingSetSizeMax, &pi.dwWorkingSetSizeMin);
	pi.szCmdLine = GetCommandLine();
	GetStartupInfo(&pi.sti);
	
}
/******************************************************/

/*******************���̻�����������***********************/
void TestProcessEnvir()
{

	WCHAR value[MAX_PATH];
	ZeroMemory(value, MAX_PATH);
	GetEnvironmentVariable(L"USERNAME", value, MAX_PATH);
	printf("%ws\n", value);

	SetEnvironmentVariable(L"hama", L"hama");

	printf("========================================\n");
	LPTCH  pEvStart = GetEnvironmentStrings();
	LPWSTR pEv = (LPWSTR)pEvStart;
	do 
	{
		printf("%ws\n", pEv);
		while (*(pEv++));
	} while (*pEv);
	FreeEnvironmentStrings(pEvStart);

	

	
}
/**********************************************************/
void TestProcessDemo()
{
	//TestCreateProcess();
	//GetProcessInfo();
	TestProcessEnvir();
}