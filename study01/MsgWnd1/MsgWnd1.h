
// MsgWnd1.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMsgWnd1App: 
// �йش����ʵ�֣������ MsgWnd1.cpp
//

class CMsgWnd1App : public CWinApp
{
public:
	CMsgWnd1App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMsgWnd1App theApp;