// DlgTest.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DlgTest.h"
#include "afxdialogex.h"
#include "resource.h"


// CDlgTest �Ի���

IMPLEMENT_DYNAMIC(CDlgTest, CDialogEx)

CDlgTest::CDlgTest(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLGTEST, pParent)
{

}

CDlgTest::~CDlgTest()
{
}

void CDlgTest::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgTest, CDialogEx)
END_MESSAGE_MAP()


// CDlgTest ��Ϣ�������
