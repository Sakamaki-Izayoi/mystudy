
// ProgressDemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CProgressDemoApp: 
// �йش����ʵ�֣������ ProgressDemo.cpp
//

class CProgressDemoApp : public CWinApp
{
public:
	CProgressDemoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CProgressDemoApp theApp;