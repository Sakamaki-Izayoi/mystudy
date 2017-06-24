
// ScrollBarDemoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ScrollBarDemo.h"
#include "ScrollBarDemoDlg.h"
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


// CScrollBarDemoDlg �Ի���



CScrollBarDemoDlg::CScrollBarDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SCROLLBARDEMO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CScrollBarDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SCROLLBAR, m_scroll);
}

BEGIN_MESSAGE_MAP(CScrollBarDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CScrollBarDemoDlg ��Ϣ�������

BOOL CScrollBarDemoDlg::OnInitDialog()
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
	SCROLLINFO sinfo = {};
	sinfo.cbSize = sizeof(SCROLLINFO);
	sinfo.fMask = SIF_RANGE | SIF_PAGE;
	sinfo.nMin = 0;
	sinfo.nMax = 100;
	sinfo.nPage = 10;
	m_scroll.SetScrollInfo(&sinfo);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CScrollBarDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CScrollBarDemoDlg::OnPaint()
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
HCURSOR CScrollBarDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//MFC������demo
//�� initDlg�г�ʼ�������ù�������Ϣ��
//nPos������������pos
void CScrollBarDemoDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	//
	SCROLLINFO sinfo = {};
	pScrollBar->GetScrollInfo(&sinfo);

	int newPos = sinfo.nPos;
	switch (nSBCode)
	{
	case SB_THUMBTRACK:	//�û��϶�������
		newPos = nPos;
		break;
	case SB_LINELEFT:	//��ߵİ�ť
		newPos -= 1;
		break;
	case SB_LINERIGHT:	//�ұߵİ�ť
		newPos += 1;
		break;
	case SB_PAGELEFT:	//��ҳ����
		newPos -= 10;
		break;
	case SB_PAGERIGHT:	//��ҳ����
		newPos += 10;
		break;
	default:
		break;
	}

	if (newPos > sinfo.nMax) newPos = sinfo.nMax;
	if (newPos < sinfo.nMin) newPos = sinfo.nMin;
		
	pScrollBar->SetScrollPos(newPos);//��仰ֱ�Ӷ�SCROLLINFO.nPos��������
	//����newPos��֮����������ҪŪ���߼���

	CString str;
	str.Format(L"��ǰλ�ã�%d", newPos);
	SetDlgItemTextW(IDC_STATIC_SBINDEX, str);
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
