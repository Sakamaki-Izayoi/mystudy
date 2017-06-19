#include "stdafx.h"
#include <iostream>


/*****************�����ڴ�ķ�����ͷ�****************************/
void VirtualAllocAndFree()
{
	SIZE_T sizeVirtual = 0x3000;
	LPVOID lpRound = reinterpret_cast<LPVOID>(0x10000001);
	MEMORY_BASIC_INFORMATION mbi;
	auto lpAddress = VirtualAlloc(lpRound, sizeVirtual, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	CopyMemory(lpAddress, "hello", strlen("hello"));
	std::cout << "�����ַΪ��" << lpAddress << "  ";
	std::cout << "����Ϊ��" << (LPSTR)lpAddress << std::endl;;

	//��ע����Ϊ��ʼΪ10000001+size���2��ҳ��,���Բ������RegionSizeҳ���һ��
	VirtualQuery(lpAddress, &mbi, sizeof(mbi));//�鿴mbi��stateֵ 0x1000 MEM_COMMIT

	VirtualFree(lpRound, sizeVirtual, MEM_DECOMMIT);
	VirtualQuery(lpAddress, &mbi, sizeof(mbi));//�鿴mbi��stateֵ 0x2000 MEM_DECOMMIT

	VirtualFree(lpAddress, 0, MEM_RELEASE);
	VirtualQuery(lpAddress, &mbi, sizeof(mbi));//�鿴mbi��stateֵ 0x00010000 MEM_FREE
}
/*****************************************************************/

/********************�޸��ڴ�����******************************/
void VirtualProtectDemo()
{
	MEMORY_BASIC_INFORMATION mbi;
	DWORD oldPro;
	auto lpMem = VirtualAlloc(NULL, 0x1001, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	VirtualQuery(lpMem, &mbi, sizeof(mbi));

	VirtualProtect(lpMem, 0x2000, PAGE_READONLY, &oldPro);
	VirtualQuery(lpMem, &mbi, sizeof(mbi));
}
/*******************************************************/
void TestVirtualMemDemo()
{
	//VirtualAllocAndFree();
	VirtualProtectDemo();
}