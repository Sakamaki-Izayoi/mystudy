
// ListControldemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CListControldemoApp: 
// �йش����ʵ�֣������ ListControldemo.cpp
//

class CListControldemoApp : public CWinApp
{
public:
	CListControldemoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CListControldemoApp theApp;