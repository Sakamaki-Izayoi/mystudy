
// ScrollBarDemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CScrollBarDemoApp: 
// �йش����ʵ�֣������ ScrollBarDemo.cpp
//

class CScrollBarDemoApp : public CWinApp
{
public:
	CScrollBarDemoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CScrollBarDemoApp theApp;