
// MsgWnd2.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMsgWnd2App: 
// �йش����ʵ�֣������ MsgWnd2.cpp
//

class CMsgWnd2App : public CWinApp
{
public:
	CMsgWnd2App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMsgWnd2App theApp;