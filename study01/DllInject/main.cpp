#include "stdafx.h"

VOID GetAllPrivilege();

//Զ���߳�ע��
extern bool inject_remote_thread(DWORD dwPid, LPCWSTR lpszDllPath);
extern BOOL inject_apc_dll(DWORD dwProcessId, LPCWSTR lpszDllFilePath);//Ŀǰ����ֵʹ��32λ
extern BOOL inject_context_dll(DWORD dwProcessId, LPCWSTR lpszDllFilePath);
int main()
{
	GetAllPrivilege();
	//inject_remote_thread(1000, L"C:\\Users\\killvxk\\Desktop\\mydll32.dll");//����
	//inject_remote_thread(5148, L"C:\\Users\\killvxk\\Desktop\\mydll64.dll");//����
	//inject_apc_dll(3984, L"C:\\Users\\killvxk\\Desktop\\mydll32.dll");//apcע����δ�ɹ���
	//inject_context_dll(3984, L"C:\\Users\\killvxk\\Desktop\\mydll32.dll");//contextע�룬�ɹ���
	
	return 0;
}


VOID GetAllPrivilege()
{
	for (USHORT i = 0; i < 0x100; i++)
	{
		BOOLEAN Old;
		RtlAdjustPrivilege(i, TRUE, FALSE, &Old);
	}
}

