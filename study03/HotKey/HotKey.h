
// HotKey.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CHotKeyApp: 
// �йش����ʵ�֣������ HotKey.cpp
//

class CHotKeyApp : public CWinApp
{
public:
	CHotKeyApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CHotKeyApp theApp;