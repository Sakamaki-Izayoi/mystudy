#include "stdafx.h"




extern void TestFileFuncDemo();
int main()
{
	TestFileFuncDemo();
	return 0;
}





/************************************************************************/
/*       C++����̨������                                                               
 * 1. C��������ȫ��locale
 * setlocale(LC_ALL, "");

 * 2. C++ ����ȫ��locale
 * std::locale::global(std::locale(""));

 * 3. ����Ϊ wcout ����һ�� locale
 * std::locale loc("");
 * std::wcout.imbue(loc);
/************************************************************************/