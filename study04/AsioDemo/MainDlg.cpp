
// MainDlg.cpp : ʵ���ļ�
//

#include <boost/date_time/posix_time/posix_time.hpp>
#include "stdafx.h"
#include "MainApp.h"
#include "MainDlg.h"
#include "afxdialogex.h"
#include "CommonMFC/mfc_listview.h"
#include <boost/bind.hpp>
#include "AsioClient.h"
#include "AsioServer.h"




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
	ON_BN_CLICKED(IDC_BUTTON4, &CMainCDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CMainCDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CMainCDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CMainCDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CMainCDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CMainCDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CMainCDlg::OnBnClickedButton10)
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


//////////////////////////////////////////////////////////////////////////
void CMainCDlg::OnBnClickedButton1()
{
	// TODO: ͬ��
	asio::io_service io;
	asio::deadline_timer timer(io, boost::posix_time::seconds(2));
	timer.wait();
	printf("���\n");
}

//////////////////////////////////////////////////////////////////////////
void CMainCDlg::OnBnClickedButton2()
{
	// TODO: �첽�޲�
	asio::io_service io;
	asio::deadline_timer t(io, boost::posix_time::seconds(2));

	t.async_wait([=](const asio::error_code& err) {
		printf("�����ү\n");
	});

	printf("���Ȳ����裬Ȼ������˵�� ====��");
	io.run();
}

//////////////////////////////////////////////////////////////////////////
void AsioPrint(const asio::error_code&, asio::deadline_timer* t, int* count)
{
	if (*count < 5)
	{
		std::cout << *count << std::endl;
		++(*count);
		t->expires_at(t->expires_at() + boost::posix_time::seconds(1));
		t->async_wait(boost::bind(AsioPrint, asio::placeholders::error, t, count));
	}
}

void CMainCDlg::OnBnClickedButton3()
{
	// TODO: �첽���
	asio::io_service io;

	int count = 0;
	asio::deadline_timer t(io, boost::posix_time::seconds(1));
	t.async_wait(boost::bind(AsioPrint, asio::placeholders::error, &t, &count));
	//t.async_wait(AsioPrint); �����һ��Ҫbind

	io.run();
	std::cout << "Final count is " << count << std::endl;
}

//////////////////////////////////////////////////////////////////////////
class AsioPrintCls
{
public:
	AsioPrintCls(asio::io_service &io) : m_timer(io, boost::posix_time::seconds(1)), m_count(0)
	{
		m_timer.async_wait(boost::bind(&AsioPrintCls::print, this));
	}
	~AsioPrintCls() { std::cout << "Final count is " << m_count << std::endl; };

	void print()
	{
		if (m_count < 5)
		{
			std::cout << m_count << std::endl;
			++m_count;

			m_timer.expires_at(m_timer.expires_at() + boost::posix_time::seconds(1));
			m_timer.async_wait(boost::bind(&AsioPrintCls::print, this));
		}
	}
private:
	asio::deadline_timer m_timer;
	int m_count;
};



void CMainCDlg::OnBnClickedButton4()
{
	// TODO:�첽���ຯ��
	asio::io_service io;
	AsioPrintCls pnt(io);
	io.run();
}

//////////////////////////////////////////////////////////////////////////

class printer
{
public:
	printer(asio::io_service& io) : m_strand(io),
		m_timer1(io, boost::posix_time::seconds(1)),
		m_timer2(io, boost::posix_time::seconds(1)),
		m_count(0)
	{
		m_timer1.async_wait(m_strand.wrap(boost::bind(&printer::print1, this)));
		m_timer2.async_wait(m_strand.wrap(boost::bind(&printer::print2, this)));
	}
	~printer() { std::cout << "Final count is " << m_count << std::endl; };

	void print1()
	{
		if (m_count < 10)
		{
			std::cout << "Timer 1: " << m_count << std::endl;
			++m_count;

			m_timer1.expires_at(m_timer1.expires_at() + boost::posix_time::seconds(1));
			m_timer1.async_wait(m_strand.wrap(boost::bind(&printer::print1, this)));
		}
	}

	void print2()
	{
		if (m_count < 10)
		{
			std::cout << "Timer 2: " << m_count << std::endl;
			++m_count;

			m_timer2.expires_at(m_timer2.expires_at() + boost::posix_time::seconds(1));
			m_timer2.async_wait(m_strand.wrap(boost::bind(&printer::print2, this)));
		}
	}
private:
	asio::io_service::strand m_strand;
	asio::deadline_timer m_timer1;
	asio::deadline_timer m_timer2;
	int m_count;
};


void CMainCDlg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	asio::io_service io;
	printer p(io);
	asio::thread t1(boost::bind(&asio::io_service::run, &io));
	io.run();
	t1.join();
}

//////////////////////////////////////////////////////////////////////////
void CMainCDlg::OnBnClickedButton6()
{
	// Step 1. Assume that the client application has already
	// obtained the DNS name and protocol port number and
	// represented them as strings.
	std::string host = "www.youku.com";
	std::string port_num = "11180";
	asio::error_code ec;
	// Step 2.
	asio::io_service ios;
	// Step 3. Creating a query.
	asio::ip::tcp::resolver::query resolver_query(host,
		port_num, asio::ip::tcp::resolver::query::numeric_service);
	// Step 4. Creating a resolver.
	asio::ip::tcp::resolver resolver(ios);
	// Step 5.
	asio::ip::tcp::resolver::iterator it =
		resolver.resolve(resolver_query, ec);
	// Handling errors if any.
	if (ec.value() != 0) {
		// Failed to resolve the DNS name. Breaking execution.
		std::cout << "Failed to resolve a DNS name."
			<< "Error code = " << ec.value()
			<< ". Message = " << ec.message();
	}

	asio::ip::tcp::resolver::iterator it_end;
	for (; it != it_end; ++it) {
		asio::ip::tcp::endpoint ep = it->endpoint();
		auto ip = ep.address();
		std::string ipStr = ip.to_string();
		printf("%s\n", ipStr.c_str());
	}
}
//////////////////////////////////////////////////////////////////////////
DWORD WINAPI AsioTCPServer1(LPVOID lpParameter)
{
	unsigned short port_num = 3333;
	try {
		Server srv;
		srv.Start(port_num);
		std::this_thread::sleep_for(std::chrono::seconds(60));
		srv.Stop();
	}
	catch (asio::system_error&e) {
		std::cout << "Error occured! Error code = "
			<< e.code() << ". Message: "
			<< e.what();
	}
	return 0;
}

void CMainCDlg::OnBnClickedButton7()
{
	// TODO: TCP�����
	::CreateThread(NULL, 0, AsioTCPServer1, NULL, 0, NULL);
}

//////////////////////////////////////////////////////////////////////////
DWORD WINAPI AsioTcpClient1(LPVOID lpParameter)
{
	const std::string raw_ip_address = "127.0.0.1";
	const unsigned short port_num = 3333;

	try
	{
		SyncTCPClient client(raw_ip_address, port_num);
		client.connet();

		std::cout << "Sending request to the server..." << std::endl;

		std::string response = client.Foo(12);

		std::cout << "Response received: " << response << std::endl;
		client.close();
	}
	catch (asio::system_error& ec)
	{
		std::cout << "Error occured! Error code = " << ec.code() <<
			". Message: " << ec.what();
	}
	return 0;
}

void CMainCDlg::OnBnClickedButton8()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	::CreateThread(NULL, 0, AsioTcpClient1, NULL, 0, NULL);
}

//////////////////////////////////////////////////////////////////////////
void CMainCDlg::OnBnClickedButton9()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

}

//////////////////////////////////////////////////////////////////////////
void CMainCDlg::OnBnClickedButton10()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
