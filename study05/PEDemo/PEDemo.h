
// PEDemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPEDemoApp: 
// �йش����ʵ�֣������ PEDemo.cpp
//

class CPEDemoApp : public CWinApp
{
public:
	CPEDemoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPEDemoApp theApp;