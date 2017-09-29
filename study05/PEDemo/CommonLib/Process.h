#pragma once
//#include "stdafx.h"
//���̲���
namespace usr::util
{
	class Process {
	private:
		HANDLE _ProcessHandle;
		DWORD_PTR ProcessId;
	public:
		Process() { _ProcessHandle = GetCurrentProcess(); ProcessId = GetCurrentProcessId(); };
		Process(DWORD_PTR _ProcessId) {
			ProcessId = _ProcessId;
			open_handle();
		};
		~Process() {
			if (_ProcessHandle)
			{
				ntdll::ZwClose(_ProcessHandle);
				_ProcessHandle = nullptr;
			}
		};
	public:
		Process & operator=(const Process &_Proc) 
		{
			this->_ProcessHandle = nullptr;
			this->ProcessId = _Proc.ProcessId;
			this->open_handle();
			return *this;
		}
		HANDLE get() {
			return _ProcessHandle;
		}
		void kill()
		{
			//TODO::JOB��ʽ
			//ZwCreateJobObject()
			//ZwAssignProcessToJobObject()
			//ZwTerminateJobObject()
			//ZwClose
			//�򵥴ֱ�
			if (_ProcessHandle)
			{
				ntdll::ZwTerminateProcess(_ProcessHandle,0);
			}
		}
		bool is_process64()
		{
			decltype(&IsWow64Process) _IsWow64Process;

			_IsWow64Process = (decltype(&IsWow64Process))GetProcAddress(GetModuleHandle(_T("KERNEL32")), "IsWow64Process");

			if (_IsWow64Process != NULL)
			{
				if (sizeof(void *) == 8)
				{
					// This process is 64 bit hence 64-bit OS
					BOOL processisWOW64 = FALSE;
					_IsWow64Process(_ProcessHandle, &processisWOW64);
					return processisWOW64 == FALSE;
				}
				else
				{
					// This process is 32 bit
					HANDLE this_process = GetCurrentProcess();
					BOOL iamWOW64 = FALSE;
					_IsWow64Process(this_process, &iamWOW64);
					if (iamWOW64)
					{
						// This process is 32 bit on a 64-bit OS
						BOOL processisWOW64 = FALSE;
						_IsWow64Process(_ProcessHandle, &processisWOW64);
						return processisWOW64 == TRUE;
					}
					else
					{
						// This process is 32 bit on a 32-bit OS
						return false;
					}
				}
			}
			else
			{
				// OS is old ! This process is 32 bit on a 32-bit OS
				return false;
			}
		}
	private:
		void open_handle()
		{
			get_all_privilege();
			using namespace ntdll;
			HANDLE _handle = nullptr;
			ntdll::OBJECT_ATTRIBUTES oa = {};
			ntdll::CLIENT_ID cid = {};
			cid.UniqueProcess = (HANDLE)this->ProcessId;
			InitializeObjectAttributes(&oa, nullptr, OBJ_INHERIT
				|OBJ_CASE_INSENSITIVE, nullptr,nullptr);
			auto ns = ZwOpenProcess(&_handle, PROCESS_ALL_ACCESS,
				&oa, &cid);
			if (ns<0)
			{
				DebugBreak();
			}
			_ProcessHandle = _handle;
		}
	};
}