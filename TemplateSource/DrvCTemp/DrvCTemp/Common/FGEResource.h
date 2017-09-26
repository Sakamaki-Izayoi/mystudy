#include <ntddk.h>

typedef struct _FG_EResource_LOCK
{
	ERESOURCE m_lock;
}ELOCK;

/*��ʼ������DriverEntryִ��*/
VOID __stdcall initELock(ELOCK *lpLock);
/*ж�أ���DriverUnload��ִ��*/
VOID __stdcall deleteELock(ELOCK *lpLock);
/*����*/
VOID __stdcall eLockRead(ELOCK *lpLock);
/*д��*/
VOID __stdcall eLockWrite(ELOCK *lpLock);
/*��������*/
VOID __stdcall eLockReadStarveWriter(ELOCK *lpLock);
/*д������*/
VOID __stdcall eLockWriteStarveReader(ELOCK *lpLock);
/*����*/
VOID __stdcall eUnlock(ELOCK *lpLock);