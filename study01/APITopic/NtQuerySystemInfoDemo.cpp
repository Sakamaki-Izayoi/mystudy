#include "NtQuerySystemInfoDemo.h"
#include "stdafx.h"
using namespace std;

void NTQSIDemo1()
{
	//SystemBasicInformation��CPU����
	SYSTEM_BASIC_INFORMATION bi = {};
	auto len = sizeof(SYSTEM_BASIC_INFORMATION);
	NtQuerySystemInformation(NTDLL::SystemBasicInformation, &bi, len, 0);
	cout << "CPU������" << static_cast<int>(bi.NumberOfProcessors) << endl;
}

/************************************************************************
* �������ܣ��ҳ�������ΪlpszName�����н���pid������������ʽ����
* ����һ��Ҫ���ҵĽ�����         ����������ŷ��ص�vector
************************************************************************/
void find_process(LPCWSTR lpszName, std::vector<DWORD>& pid_list)
{
	//SystemProcessInformationö�ٽ���
	//SystemExtendedProcessInformationҲ������Ϊ��һ������
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
		if (!buffer)return;
		status = NtQuerySystemInformation(NTDLL::SystemExtendedProcessInformation, buffer, len, 0);

	} while (status != STATUS_SUCCESS);

	pspi = (NTDLL::PSYSTEM_PROCESSES_INFORMATION)buffer;
	WCHAR szName[MAX_PATH] = { 0 };

	while (pspi->NextEntryDelta)
	{
		//std::wcout << ((pspi->ImageName.Buffer == NULL) ? L"System Idle Process": pspi->ImageName.Buffer) << std::endl;
		RtlCopyMemory(szName, pspi->ImageName.Buffer, pspi->ImageName.MaximumLength);
		if (_wcsicmp(szName, lpszName) == 0)//�ҵ�
		{
			auto pid = reinterpret_cast<DWORD>(pspi->UniqueProcessId);
			if (pid != GetCurrentProcessId())
			{
				pid_list.push_back(pid);
			}
		}
		pspi = (NTDLL::PSYSTEM_PROCESSES_INFORMATION)(reinterpret_cast<ULONG>(pspi) + pspi->NextEntryDelta);
	}
	LocalFree(buffer);
}

/************************************************************************
* �������ܣ�SystemExtendedProcessInformation����ָ�����̵����߳�
* ����һ������ID
* ����ֵ���߳�id,����0ʧ��
************************************************************************/
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
