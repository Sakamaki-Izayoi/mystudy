// WinmainConsole.cpp : ����Ӧ�ó������ڵ㡣
//
/*!
* \file WinmainConsole.cpp
*
* \author frogGod
* \date ���� 2017
*
*  WinMain����console(����̨)
*/


#include "stdafx.h"
#include <stdio.h>
#include "WinmainConsole.h"


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
	AllocConsole();
	SetConsoleTitle(L"�������");
	AttachConsole(GetCurrentProcessId());


	FILE *pFile = nullptr;
	freopen_s(&pFile, "CON", "r", stdin);
	freopen_s(&pFile, "CON", "w", stdout);
	freopen_s(&pFile, "CON", "w", stderr);
	_tprintf(L"what is this\r\n");
	MessageBox(NULL, _T("һ����ʾ"), _T("Me"), MB_OK);
    return 0;
}


