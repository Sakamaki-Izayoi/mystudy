
// SpinDemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSpinDemoApp: 
// �йش����ʵ�֣������ SpinDemo.cpp
//

class CSpinDemoApp : public CWinApp
{
public:
	CSpinDemoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSpinDemoApp theApp;