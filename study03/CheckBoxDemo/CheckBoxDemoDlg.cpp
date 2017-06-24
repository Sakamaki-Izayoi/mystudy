
// CheckBoxDemoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CheckBoxDemo.h"
#include "CheckBoxDemoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCheckBoxDemoDlg �Ի���



CCheckBoxDemoDlg::CCheckBoxDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CHECKBOXDEMO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCheckBoxDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_RED, m_chkRed);
	DDX_Control(pDX, IDC_CHECK_BLUE, m_chkBlue);
	DDX_Control(pDX, IDC_CHECK_GREEN, m_chkGreen);
}

BEGIN_MESSAGE_MAP(CCheckBoxDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_CHECK_RED, &CCheckBoxDemoDlg::OnBnClickedCheckRed)
	ON_BN_CLICKED(IDC_CHECK_GREEN, &CCheckBoxDemoDlg::OnBnClickedCheckGreen)
	ON_BN_CLICKED(IDC_CHECK_BLUE, &CCheckBoxDemoDlg::OnBnClickedCheckBlue)
	ON_BN_CLICKED(IDC_RADIO_RECT, &CCheckBoxDemoDlg::OnBnClickedRadioRect)
	ON_BN_CLICKED(IDC_RADIO_CIRCLE, &CCheckBoxDemoDlg::OnBnClickedRadioCircle)
END_MESSAGE_MAP()


// CCheckBoxDemoDlg ��Ϣ�������

BOOL CCheckBoxDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	m_chkRed.SetCheck(TRUE);
	static_cast<CButton *>(GetDlgItem(IDC_RADIO_RECT))->SetCheck(TRUE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CCheckBoxDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCheckBoxDemoDlg::OnPaint()
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
HCURSOR CCheckBoxDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CCheckBoxDemoDlg::OnEraseBkgnd(CDC* pDC)
{
	//����������������������Ȼ����꣬�ٷ���bRet
	auto  bRet = CDialogEx::OnEraseBkgnd(pDC);

	//��Ӻñ���������Ƿ�ѡ��
	auto nRed = m_chkRed.GetCheck() ? 255 : 0;
	auto nGreen = m_chkGreen.GetCheck() ? 255 : 0;
	auto nBlue = m_chkBlue.GetCheck() ? 255 : 0;
	COLORREF crColor = RGB(nRed, nGreen, nBlue);

	//���廭ˢ��������ɫ������PDC�Ļ�ˢ
	CBrush brush;
	brush.CreateSolidBrush(crColor);
	auto oldBrush = pDC->SelectObject(&brush);

	RECT rect = { 0, 0, 100, 100 };
	auto radioRect = (CButton *)GetDlgItem(IDC_RADIO_RECT);
	auto radioCircle = static_cast<CButton *>(GetDlgItem(IDC_RADIO_CIRCLE));
	if (radioRect->GetCheck())
	{
		pDC->Rectangle(&rect);
	}
	else if(radioCircle->GetCheck())
	{
		pDC->Ellipse(&rect);
	}

	//��ԭ�ϻ�ˢ
	pDC->SelectObject(oldBrush);
	return bRet;
}


void CCheckBoxDemoDlg::OnBnClickedCheckRed()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Invalidate();
}


void CCheckBoxDemoDlg::OnBnClickedCheckGreen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Invalidate();
}


void CCheckBoxDemoDlg::OnBnClickedCheckBlue()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Invalidate();
}


void CCheckBoxDemoDlg::OnBnClickedRadioRect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Invalidate();
}


void CCheckBoxDemoDlg::OnBnClickedRadioCircle()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Invalidate();
}
