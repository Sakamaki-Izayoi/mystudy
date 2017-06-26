
// DateTimeDemoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DateTimeDemo.h"
#include "DateTimeDemoDlg.h"
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


// CDateTimeDemoDlg �Ի���



CDateTimeDemoDlg::CDateTimeDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DATETIMEDEMO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDateTimeDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATE_BEGIN, m_date_begin);
	DDX_Control(pDX, IDC_DATE_END, m_date_end);
	DDX_Control(pDX, IDC_EDIT_OUTPUT, m_edit_output);
}

BEGIN_MESSAGE_MAP(CDateTimeDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATE_BEGIN, &CDateTimeDemoDlg::OnDatetimechangeDateBegin)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATE_END, &CDateTimeDemoDlg::OnDatetimechangeDateEnd)
END_MESSAGE_MAP()


// CDateTimeDemoDlg ��Ϣ�������

BOOL CDateTimeDemoDlg::OnInitDialog()
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
	m_date_begin.SetFormat(L"yyyy-MM-dd HH:mm:ss");
	m_date_end.SetFormat(L"yyyy-MM-dd HH:mm:ss");



	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CDateTimeDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDateTimeDemoDlg::OnPaint()
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
HCURSOR CDateTimeDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//ʱ��ѡ����Demo
void CDateTimeDemoDlg::OnDatetimechangeDateBegin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//1.��ȡ��ǰ�¼�
	SYSTEMTIME st_begin, st_end;
	m_date_begin.GetTime(&st_begin);

	//2.��ȡ��һ���ؼ��¼�
	m_date_end.GetTime(&st_end);

	//ʹ��FILETIME����
	FILETIME ft_bein, ft_end;
	SystemTimeToFileTime(&st_begin, &ft_bein);
	SystemTimeToFileTime(&st_end, &ft_end);
	
	ULARGE_INTEGER u_begin, u_end, u_span;
	u_begin.u.HighPart = ft_bein.dwHighDateTime;
	u_begin.u.LowPart = ft_bein.dwLowDateTime;

	u_end.u.HighPart = ft_end.dwHighDateTime;
	u_end.u.LowPart = ft_end.dwLowDateTime;

	
	if (u_end.QuadPart >= u_begin.QuadPart)
	{
		u_span.QuadPart = u_end.QuadPart - u_begin.QuadPart;
	}
	else
	{
		u_span.QuadPart = u_begin.QuadPart - u_end.QuadPart;
	}
	
	
	ULONGLONG ull_second = u_span.QuadPart / 10000000;
	int n_minute = ull_second / 60;
	int n_hours = n_minute / 60;
	int n_days = n_hours / 24;
	CString strOutput;
	//strOutput.Format(L"begin:%lu, %lu\r\nend:%lu, %lu", u_begin.HighPart, u_begin.LowPart, u_end.HighPart, u_end.LowPart);
	

	strOutput.Format(L"��:%I64u\r\n����:%u\r\nСʱ:%u\r\n�죺%u", ull_second, n_minute, n_hours, n_days);

	SetDlgItemTextW(IDC_EDIT_OUTPUT, strOutput);
	*pResult = 0;
}


void CDateTimeDemoDlg::OnDatetimechangeDateEnd(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//1.��ȡ��ǰ�¼�
	SYSTEMTIME st_begin, st_end;
	m_date_begin.GetTime(&st_begin);

	//2.��ȡ��һ���ؼ��¼�
	m_date_end.GetTime(&st_end);

	//ʹ��FILETIME����
	FILETIME ft_bein, ft_end;
	SystemTimeToFileTime(&st_begin, &ft_bein);
	SystemTimeToFileTime(&st_end, &ft_end);

	ULARGE_INTEGER u_begin, u_end, u_span;
	u_begin.u.HighPart = ft_bein.dwHighDateTime;
	u_begin.u.LowPart = ft_bein.dwLowDateTime;

	u_end.u.HighPart = ft_end.dwHighDateTime;
	u_end.u.LowPart = ft_end.dwLowDateTime;


	if (u_end.QuadPart >= u_begin.QuadPart)
	{
		u_span.QuadPart = u_end.QuadPart - u_begin.QuadPart;
	}
	else
	{
		u_span.QuadPart = u_begin.QuadPart - u_end.QuadPart;
	}


	ULONGLONG ull_second = u_span.QuadPart / 10000000;
	int n_minute = ull_second / 60;
	int n_hours = n_minute / 60;
	int n_days = n_hours / 24;
	CString strOutput;
	//strOutput.Format(L"begin:%lu, %lu\r\nend:%lu, %lu", u_begin.HighPart, u_begin.LowPart, u_end.HighPart, u_end.LowPart);


	strOutput.Format(L"��:%I64u\r\n����:%u\r\nСʱ:%u\r\n�죺%u", ull_second, n_minute, n_hours, n_days);

	SetDlgItemTextW(IDC_EDIT_OUTPUT, strOutput);
	*pResult = 0;
}
