// APITopic.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
void TestNtQuerySystemInfo();

int main()
{
	TestNtQuerySystemInfo();
    return 0;
}

extern void NTQSIDemo1();
extern DWORD GetMainThread(DWORD pid);
void TestNtQuerySystemInfo()
{
	NTQSIDemo1();
	DWORD dwThread = GetMainThread(2428);
}

