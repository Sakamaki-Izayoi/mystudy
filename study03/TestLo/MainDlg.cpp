
// MainDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MainApp.h"
#include "MainDlg.h"
#include "afxdialogex.h"
#include "CommonMFC/mfc_listview.h"

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


// CMainCDlg �Ի���



CMainCDlg::CMainCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TEMPMFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMainCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMainCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMainCDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMainCDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMainCDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_Test, &CMainCDlg::OnBnClickedTest)
	ON_BN_CLICKED(IDC_BUTTON5, &CMainCDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CMainCDlg ��Ϣ�������

BOOL CMainCDlg::OnInitDialog()
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
	usr::util::alloc_cmd_window();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMainCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMainCDlg::OnPaint()
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
HCURSOR CMainCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//MFC�еĿ���̨����
void CMainCDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	usr::util::alloc_cmd_window();
	int i = 10;
	std::cout << "�������̨����ӡ10��:" << std::endl;
	while (i--)
	{
		printf("hello world\n");
		Sleep(500);
	}
	FreeConsole();
}


//����ļ�·��
void CMainCDlg::OnBnClickedButton2()
{
	//filter��ʽ:"��ʾ�ĸ��û�����\0��������\0"
	WCHAR szFileName[MAX_PATH];
	usr::util::GetOpenName(GetModuleHandle(nullptr),
		szFileName, L"ȫ���ļ�\0*.*\0ini�ļ�\0*.ini\0", L"��û�۾���");
	printf("%ws\n", szFileName);
}

//��ñ���·��
void CMainCDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	WCHAR szFileName[MAX_PATH];
	usr::util::GetSaveName(GetModuleHandle(NULL), szFileName, L"INI(*.INI)\0*.INI\0", L"�۾�");
	printf("%ws\n", szFileName);
}

//������������
//countһ���м�������
void foo(int count, ...)
{
	int index = 0;
	int arg;
	//����1��
	va_list	va;
	//����2��
	va_start(va, count);

	//����3
	for (int i = 0; i < count; i++)
	{
		//��ȡ����count����ĵ�һ������
		arg = va_arg(va, int);
		printf("%d\n", arg);
	}
	//����
	va_end(va);
}

void CMainCDlg::OnBnClickedTest()
{
	//foo(5, 1, 2, 3, 4, 5);
}

#include "DlgListCtrl.h"
#include "DlgTest.h"
void CMainCDlg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDlgListCtrl dlg;
	dlg.DoModal();

	//CDlgTest dlg1;
	//dlg1.DoModal();
}
