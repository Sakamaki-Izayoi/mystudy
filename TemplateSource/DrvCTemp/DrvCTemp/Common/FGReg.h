#include <ntddk.h>

/*����һ��KEY*/
NTSTATUS FGCreateKey(IN PUNICODE_STRING keyPath);

/*��һ��KEY������һ������������м��ͷ�*/
NTSTATUS FGOpenKey(IN PUNICODE_STRING regPath, OUT PHANDLE phReg);

/*ɾ��һ��KEY*/
NTSTATUS FGDeleteKey(IN PUNICODE_STRING keyPath);

/*����һ��VALUEKEY,type:REG_BINARY, REG_DWORD,REG_SZ, REG_EXPAND_SZ, REG_MULTI_SZ*/
NTSTATUS FGSetValueKey(IN PUNICODE_STRING keyPath, IN ULONG type, IN PUNICODE_STRING valueName, IN PUNICODE_STRING value);

/*ɾ��һ��VALUEKEY*/
NTSTATUS FGdeleteValueKey(IN PUNICODE_STRING keyPath, PUNICODE_STRING valuename);

/*��ѯһ��DWORDֵ*/
NTSTATUS FGQueryDword(IN PUNICODE_STRING keyPath, IN PUNICODE_STRING valuename, OUT PULONG value);

/*��ѯһ��SZ,��Ҫ�Լ�����value�Ļ��壬��Ϊע�������Ƚ�С�����Զ�����º��ʵ�*/
NTSTATUS FGQuerySZ(IN PUNICODE_STRING keyPath, IN PUNICODE_STRING valuename, OUT PUNICODE_STRING value);