#pragma once
#include "stdafx.h"

//win2k-win7 �������� ���� ʱ�⵹��dispg1.0��
//win8-win10 �����ڴ�-->VA-->������ģ��Ķ�PTE����PDE��NX=1,pf��
//������Ҳ�̶ܹ�,���cr2==rip��
//cmp dword ptr[cr2],48513148h
//cmp qword ptr[cr2],85131481131482Eh,
//��������rip�� һ��retn��ȥ��pg��û�ˣ���û��
//������ָ�PTE����PDE��NX
namespace ddk::patchguard
{
	typedef struct _POOL_TRACKER_BIG_PAGES // 4 elements, 0x18 bytes (sizeof) 
	{
		/*0x000*/     VOID*        Va;
		/*0x008*/     ULONG32      Key;
		/*0x00C*/     ULONG32      PoolType;
		/*0x010*/     UINT64       NumberOfBytes;
	}POOL_TRACKER_BIG_PAGES, *PPOOL_TRACKER_BIG_PAGES;

	void DisPg();
	void Disable_Early();
	void dispg_new();
}