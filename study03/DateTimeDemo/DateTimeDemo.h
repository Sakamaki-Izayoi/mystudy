
// DateTimeDemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDateTimeDemoApp: 
// �йش����ʵ�֣������ DateTimeDemo.cpp
//

class CDateTimeDemoApp : public CWinApp
{
public:
	CDateTimeDemoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDateTimeDemoApp theApp;