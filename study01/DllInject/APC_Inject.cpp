#include "stdafx.h"

DWORD GetMainThread(DWORD pid);// ���ĳ���̵����߳�
PVOID WriteStubEx(HANDLE h_process, LPCWSTR lpszDllFilePath);
void stub();
DWORD WINAPI stub_end();

//APCע��inject_apc_dll
using NT_QUEUE_APC_THREAD = NTSTATUS(NTAPI *)(HANDLE, PVOID, PVOID, PVOID, PVOID);//���ԣ�ɾ��NTAPI����
BOOL inject_apc_dll(DWORD dwProcessId, LPCWSTR lpszDllFilePath)
{
	auto mainThreadId = GetMainThread(dwProcessId);
	auto h_process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessId);
	if (h_process == NULL) return false;

	WCHAR szName[MAX_PATH] = { 0 };
	wcscpy_s(szName, MAX_PATH, lpszDllFilePath);
	auto h_Thread = OpenThread(THREAD_ALL_ACCESS, FALSE, mainThreadId);
	if (h_Thread == NULL) return false;

	auto NtQueueApcThread = (NT_QUEUE_APC_THREAD)GetProcAddress(GetModuleHandle(_T("ntdll.dll")), "NtQueueApcThread");
	auto mem = WriteStubEx(h_process, szName);
	NtQueueApcThread(h_Thread, mem, NULL, NULL, NULL);
	CloseHandle(h_Thread);
	CloseHandle(h_process);

	return true;
}

DWORD GetMainThread(DWORD pid)
{
	//��������С���������Ӱ�췵�ؽ��
	ULONG len = 0;
	NTSTATUS status;
	PVOID buffer;
	NTDLL::PSYSTEM_PROCESSES_INFORMATION pspi;
	//�ȴ�����һ����Ҫ�����ֽ�
	NtQuerySystemInformation(NTDLL::SystemExtendedProcessInformation, NULL, 0, &len);

	do
	{
		//Ȼ�󳤶ȼ���һ������ֵ���Լ�Ԥ����300
		len += 300;
		buffer = LocalAlloc(LMEM_FIXED, len);
		if (!buffer) return NULL;
		status = NtQuerySystemInformation(NTDLL::SystemExtendedProcessInformation, buffer, len, 0);

	} while (status != STATUS_SUCCESS);

	pspi = (NTDLL::PSYSTEM_PROCESSES_INFORMATION)buffer;

	while (pspi->NextEntryDelta)
	{
		if (pspi->UniqueProcessId == (HANDLE)pid)
		{
			DWORD threaId = reinterpret_cast<DWORD>(pspi->Threads[0].ClientId.UniqueThread);
			LocalFree(buffer);
			return threaId;
		}
		pspi = (NTDLL::PSYSTEM_PROCESSES_INFORMATION)(reinterpret_cast<ULONG>(pspi) + pspi->NextEntryDelta);
	}
	LocalFree(buffer);
	return NULL;
}

PVOID WriteStubEx(HANDLE h_process, LPCWSTR lpszDllFilePath)
{
	ULONG_PTR stublen;
	PVOID LoadLibAddr, mem;
	stublen = (ULONG_PTR)stub_end - (ULONG_PTR)stub;
	LoadLibAddr = GetProcAddress(GetModuleHandle(_T("kernel32.dll")), "LoadLibraryW");
	mem = VirtualAllocEx(h_process, NULL, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	WriteProcessMemory(h_process, mem, &LoadLibAddr, sizeof(PVOID), NULL);//��load��ַд��Ŀ�����
	WriteProcessMemory(h_process, reinterpret_cast<PVOID>(reinterpret_cast<ULONG>(mem) + 4), stub, stublen, NULL);
	WriteProcessMemory(h_process, (LPVOID)((LPBYTE)mem + 4 + stublen), lpszDllFilePath, MAX_PATH * sizeof(WCHAR), NULL);
	return (PVOID)((LPBYTE)mem + 4);
}

#pragma optimize( "", off )
__declspec(naked) void stub()
{
	__asm
	{
		pushad
		pushfd
		call start

		start :
		pop ecx
		sub ecx, 7

		lea eax, [ecx + 32]
		push eax
		call dword ptr[ecx - 4]

		popfd
		popad
		ret
	}
}

DWORD WINAPI stub_end()
{
	return 0;
}
#pragma optimize( "", on )




