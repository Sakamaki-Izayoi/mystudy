// TestDLL.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

/**************************************
  ֱ��ʹ��__declspec(dllexport)��������
  
**************************************/
//#include "../TempDLL/Header.h"
//#pragma comment(lib, "../x64/Debug/TempDLL.lib")
//void TestTempDLL()
//{
//	abcd();
//	abcd(11);
//}

/**************************************
 ʹ��def�ļ�����
**************************************/
#include "../TempDLLDef/Header.h"
#pragma comment(lib, "../x64/Debug/TempDLLDef.lib")
void TestTempDLLDef()
{
	abc();
	abcd();
}


int main()
{
	//TestTempDLL();
	TestTempDLLDef();
    return 0;
}

