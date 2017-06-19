
// MsgWnd2Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MsgWnd2.h"
#include "MsgWnd2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//������Ϣ���򣬲���1��������Ϣ
//����Ҫ�뷢����Ϣ����Ҫһ�£����ֿ��Բ�һ��
#define WM_1 (WM_USER+1000)
// CMsgWnd2Dlg �Ի���
CMsgWnd2Dlg::CMsgWnd2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MSGWND2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMsgWnd2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMsgWnd2Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_1, &CMsgWnd2Dlg::SendWnd2Fun)//������Ϣ���򣬲���3����Ϣӳ��
END_MESSAGE_MAP()


// CMsgWnd2Dlg ��Ϣ�������

BOOL CMsgWnd2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	SetWindowText(_T("Wnd2"));
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMsgWnd2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMsgWnd2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//������Ϣ���򣬲���4����������
LRESULT CMsgWnd2Dlg::SendWnd2Fun(WPARAM wpD, LPARAM lpD)
{
	MessageBox(_T("�յ���"), _T("����"), MB_OK);
	return LRESULT();
}



