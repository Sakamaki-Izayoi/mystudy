#include "stdafx.h"
#include <iostream>
using namespace std;
void ShowSystemMemInfo()
{
	MEMORYSTATUSEX memstat;
	memstat.dwLength = sizeof(memstat);
	GlobalMemoryStatusEx(&memstat);
	cout << "�������ڴ�:" << memstat.ullTotalPhys;
	cout << " ���������ڴ�:" << memstat.ullAvailPhys;
	cout << " ʹ�ðٷֱ�:" << memstat.dwMemoryLoad << endl;;

	cout << "�ܷ�ҳ:" << memstat.ullTotalPageFile;
	cout << " ���÷�ҳ:" << memstat.ullAvailPageFile << endl;;

	cout << "�������ڴ�" << memstat.ullTotalVirtual;
	cout << " ���������ڴ�" << memstat.ullAvailVirtual << endl;
}