
// ComboBox_ListBox.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CComboBox_ListBoxApp: 
// �йش����ʵ�֣������ ComboBox_ListBox.cpp
//

class CComboBox_ListBoxApp : public CWinApp
{
public:
	CComboBox_ListBoxApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CComboBox_ListBoxApp theApp;