// MemoryAPI.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


/***********�ѵĸ������**********************/
void CreateReHeapDemo()
{
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	printf("ϵͳ�ڴ�ҳ��С��0x%x\nϵͳ�������ȣ�0x%x\n", si.dwPageSize, si.dwAllocationGranularity);
	//��ʽ1����ö�
	auto h_Heap1 = HeapCreate(HEAP_NO_SERIALIZE, si.dwPageSize, si.dwPageSize * 10);
	printf("������һ���ѣ���ʼ����СΪ1ҳ�����Ϊ10ҳ\n");

	//��ʽ2����ö�
	auto h_Heap2 = GetProcessHeap();
	printf("��õ�ǰ���̵�һ����\n");

	auto h_Heap3 = HeapCreate(HEAP_NO_SERIALIZE, 0, 0);
	printf("�������������޵Ķ�\n");

	//��ʽ3����ý��������еĶ�
	HANDLE h_Heaps[10] = {};
	auto dwHeapCount = GetProcessHeaps(10, h_Heaps);
	printf("ϵͳ��һ����%d����\n", dwHeapCount);

	//�Ӷ��з����ڴ�
	auto lpMem = HeapAlloc(h_Heap1, HEAP_ZERO_MEMORY, si.dwPageSize * 3);
	auto lpMem1 = HeapAlloc(h_Heap1, HEAP_ZERO_MEMORY, si.dwPageSize);
	if (lpMem)
		printf("�ڶ��ϳɹ������ڴ棬��ʼλ����:0x%x\n", lpMem);
	memset(lpMem, 0x22, 3 * si.dwPageSize);
	memset(lpMem1, 0x33, si.dwPageSize);
	
	//���ĳ���С
	SIZE_T size = HeapSize(h_Heap1, HEAP_NO_SERIALIZE, lpMem);
	printf("lpMem��С%x\n", size);
	size = HeapSize(h_Heap1, HEAP_NO_SERIALIZE, lpMem1);
	printf("lpMem1��С%x\n", size);

	//���¶����С
	auto lpReAlloc = HeapReAlloc(h_Heap1, HEAP_ZERO_MEMORY, lpMem1, si.dwPageSize * 3);

	//�ͷŶѣ�����HeapAlloc, HeapReAlloc
	HeapFree(h_Heap1, HEAP_NO_SERIALIZE, lpMem);
	//HeapFree(h_Heap1, HEAP_NO_SERIALIZE, lpMem1);ִ����仰������Ϊ�Ѿ����·��䣬������Ҫ�ͷ���
	HeapFree(h_Heap1, HEAP_NO_SERIALIZE, lpReAlloc);
	//���ٶ�
	HeapDestroy(h_Heap1), HeapDestroy(h_Heap3);

}
/************************************************************/

void TestHeapDemo()
{
	CreateReHeapDemo();
}

