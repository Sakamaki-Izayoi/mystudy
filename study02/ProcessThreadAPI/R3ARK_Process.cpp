#include "stdafx.h"


/*************EnumProcessö�ٽ���************************/
//ժ��MSDN
void PrintNameAndModules(DWORD pid)
{
	WCHAR szName[MAX_PATH] = {};
	HANDLE h_process = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);

	if (NULL != h_process)
	{
		HMODULE h_mod;//���ص���һ�����飬����������ֻ��Ҫ֪���������Զ���һ������
		DWORD cbNeed;
		if (EnumProcessModules(h_process, &h_mod, sizeof(h_mod), &cbNeed))
		{
			GetModuleBaseName(h_process, h_mod, szName, MAX_PATH);
		}
	}
	std::wcout << pid << ":" << szName << std::endl;
	CloseHandle(h_process);
}
void EnumProDemo1()
{
	// Get the list of process identifiers.
	DWORD aProcesses[1024], cbNeeded, cProcesses;
	if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
	{
		return;
	}
	// Calculate how many process identifiers were returned.
	cProcesses = cbNeeded / sizeof(DWORD);

	for (auto i = 0; i < cProcesses; i++)
	{
		if (aProcesses[i] != 0)
		{
			PrintNameAndModules(aProcesses[i]);
		}
	}
	std::cout << "һ��" << cProcesses << "������" << std::endl;
	getchar();
}
/*******************************************************/

/*************SnapShotö�ٽ���**************************/
void EnumProDemo2()
{
	PROCESSENTRY32 pe32;
	auto hProcSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);//0����ö�����н���
	if (hProcSnap == INVALID_HANDLE_VALUE)
		return;
	pe32.dwSize = sizeof(pe32);

	if (!Process32First(hProcSnap, &pe32))
		return;
	do 
	{
		std::cout << "=====================================" << std::endl;
		std::wcout << pe32.szExeFile << ":" << pe32.th32ProcessID << std::endl;
		std::cout << "�߳�����:" << pe32.cntThreads << std::endl;
		std::cout << "������:" << pe32.th32ParentProcessID <<std::endl;
		std::cout << "���ȼ�:" << pe32.pcPriClassBase << std::endl;
	} while (Process32Next(hProcSnap, &pe32));
	CloseHandle(hProcSnap);
	getchar();
}
/*******************************************************/

/*******************ͨ�����������PID*************************/
BOOL GetProcessIdByName(LPCWSTR szProName, LPDWORD lpPID)
{
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(pe32);
	auto hProcSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcSnap == INVALID_HANDLE_VALUE)
		return FALSE;
	if (!Process32First(hProcSnap, &pe32))
		return FALSE;

	do 
	{
		if (wcscmp(szProName, pe32.szExeFile) == 0)
		{
			*lpPID = pe32.th32ProcessID;
			CloseHandle(hProcSnap);
			return TRUE;
		}
	} while (Process32Next(hProcSnap, &pe32));
	CloseHandle(hProcSnap);
	return FALSE;
}
/*******************************************************/
void TestARKProcess()
{
	//EnumProDemo1();
	//EnumProDemo2();

	DWORD pid = 0;
	GetProcessIdByName(L"360Tray.exe", &pid);
}