#include "stdafx.h"
#include <iostream>
using namespace std;

/*****************ȫ�ַ��䡢�ֲ�����********************/
//��32λ���Ѿ�û��ȫ�ֺ;ٰ캯�����Ҳ�������ƶ��͹̶�����
//���漰��һЩ�����Ѿ����������ˡ�����ֻҪ��ס�����÷��Ϳ����ˡ�
void TestGlobalLocalMemDemo()
{
	auto lpMem = (LPVOID)GlobalAlloc(GPTR, 1000);
	auto  str = L"this is a string";
	memcpy(lpMem, str, wcslen(str) * 2 + 2);
	auto uFlags = GlobalFlags(lpMem);
	auto sizeMem = GlobalSize(lpMem);
	printf("����Ϊ%ws, ��ַΪ:0x%Ix, ��С��0x%I64x���ڴ�����:%u\n", (LPWSTR)lpMem, lpMem,sizeMem, uFlags);
	GlobalFree(lpMem);
	
}