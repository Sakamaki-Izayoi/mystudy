
// PEDemoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PEDemo.h"
#include "PEDemoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPEDemoDlg �Ի���



CPEDemoDlg::CPEDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PEDEMO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPEDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPEDemoDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CPEDemoDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CPEDemoDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CPEDemoDlg::OnBnClickedButton3)
END_MESSAGE_MAP()

// CPEDemoDlg ��Ϣ�������
BOOL CPEDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	usr::util::alloc_cmd_window();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPEDemoDlg::OnPaint()
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
HCURSOR CPEDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//PE Dump
void CPEDemoDlg::OnBnClickedButton1()
{
	using namespace::LIEF::PE;
	WCHAR szFilePath[MAX_PATH] = {};
	usr::util::GetOpenName(GetModuleHandle(NULL), szFilePath,
		L"EXE(*EXE)\0*.EXE\0DLL(*.DLL)\0*.DLL\0SYS(*.SYS)\0*.SYS\0all file\0*.*\0", L"��ѡ��");

	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::string filename = converter.to_bytes(szFilePath);
	if (filename.empty()) return;

	std::unique_ptr<const Binary> binary{Parser::parse(filename.c_str())};

	std::cout << "== Dos Header ==" << std::endl;
	std::cout << binary->dos_header() << std::endl;

	std::cout << "== Header ==" << std::endl;
	std::cout << binary->header() << std::endl;

	std::cout << "== Optional Header ==" << std::endl;
	std::cout << binary->optional_header() << std::endl;

	if (binary->has_rich_header())
	{
		std::cout << "== Rich Header ==" << std::endl;
		std::cout << binary->rich_header() << std::endl;
	}

	std::cout << "== Data Directories ==" << std::endl;
	for (const auto &elem : binary->data_directories())
	{
		std::cout << elem << std::endl;
	}

	std::cout << "== Section ==" << std::endl;
	for (const auto &elem : binary->get_sections())
	{
		std::cout << elem << std::endl;
	}

	std::cout << "== Imports ==" << std::endl;
	for (const auto &elem : binary->imports())
	{
		//std::cout << elem << std::endl;
	}

	if (binary->relocations().size() > 0)
	{
		std::cout << "== Relocations ==" << std::endl;
		for (const auto &elem : binary->relocations())
		{
			//std::cout << elem << std::endl;
		}
	}

	if (binary->has_tls())
	{
		std::cout << "== TLS ==" << std::endl;
		std::cout << binary->tls() << std::endl;
	}

	if (binary->has_exports())
	{
		std::cout << "== Exports ==" << std::endl;
		std::cout << binary->get_export() << std::endl;
	}

	if (binary->symbols().size() > 0)
	{
		std::cout << "== Symbols ==" << std::endl;
		for (const auto &elem : binary->symbols())
		{
			std::cout << elem << std::endl;
		}
	}

	if (binary->has_debug())
	{
		std::cout << "== Debug ==" << std::endl;
		std::cout << binary->get_debug() << std::endl;
	}

	if (binary->has_resources())
	{
		std::cout << "== Resources ==" << std::endl;
		std::cout << binary->get_resources_manager() << std::endl;
	}

	if (binary->has_signature())
	{
		std::cout << "== Signature ==" << std::endl;
		std::cout << binary->signature() << std::endl;
	}
}
//�ֹ�PE
void CPEDemoDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	const BYTE code[] = {
		0x6a, 0x00, // push 0x00 uType
		0x68, 0x00, 0x20, 0x10, 0x00, // push VA(title)
		0x68, 0x06, 0x20, 0x10, 0x00, // push VA(message)
		0x6a, 0x00, // push 0 hWnd
		0xFF, 0x15, 0x54, 0x30, 0x10, 0x00, // call MessageBoxA
		0x6A, 0x00, // push 0 uExitCode
		0xFF, 0x15, 0x4C, 0x30, 0x10, 0x00  // call ExitProcess
	};



	using namespace LIEF::PE;
	auto bin32 = LIEF::PE::Binary(std::string("pe_builder"), PE_TYPE::PE32);

	//��������κ����ݶ�
	const char title[] = "haha\0";
	const char message[] = "Hello World\0";
	std::vector<uint8_t> t_data(sizeof(title) + sizeof(message));
	std::vector<uint8_t> t_code(sizeof(code));

	std::memcpy(&t_data[0], title, sizeof(title));
	std::memcpy(&t_data[0] + sizeof(title), message, sizeof(message));


	auto &sec1 = LIEF::PE::Section(".text");
	auto &sec2 = LIEF::PE::Section(".data");
	sec1.content(t_code);
	sec2.content(t_data);
	auto &textSec = bin32.add_section(sec1, LIEF::PE::SECTION_TYPES::TEXT);
	auto &dataSec = bin32.add_section(sec2, LIEF::PE::SECTION_TYPES::DATA);

	//���������
	auto &kernel32Dll = bin32.add_library("kernel32.dll");
	kernel32Dll.add_entry("ExitProcess");
	auto ExitAddr = bin32.predict_function_rva("kernel32.dll", "ExitProcess");

	auto &user32Dll = bin32.add_library("user32.dll");
	user32Dll.add_entry("MessageBoxA");
	auto MsgAddr = bin32.predict_function_rva("user32.dll", "MessageBoxA");

	//����ӳ���ַ
	bin32.optional_header().imagebase(0x3000000);
	auto imageBase = bin32.optional_header().imagebase();

	//shellcode ���Ե�ַ
	*((PDWORD)(&code[0] + 3)) = imageBase + dataSec.virtual_address();
	*((PDWORD)(&code[0] + 8)) = imageBase + dataSec.virtual_address() + sizeof(title);
	*((PDWORD)(&code[0] + 16)) = imageBase + MsgAddr;
	*((PDWORD)(&code[0] + 24)) = imageBase + ExitAddr;
	t_code.assign(std::begin(code), std::end(code));
	textSec.content(t_code);	//�޸�.text��

								//��������
	bin32.optional_header().addressof_entrypoint(textSec.virtual_address());
	bin32.optional_header().subsystem(IMAGE_SUBSYSTEM_WINDOWS_GUI);

	WCHAR szFileName[MAX_PATH];
	usr::util::GetSaveName(GetModuleHandle(nullptr), szFileName, L"�����ļ�\0*.*\0", L"����");
	std::wstring_convert<std::codecvt_utf8_utf16<WCHAR>> convert;
	auto FileName = convert.to_bytes(szFileName);

	//��ʼbuilder
	auto builder = LIEF::PE::Builder(&bin32);
	builder.build_imports();
	builder.build();
	builder.write(FileName);
}
//���Լ���IAT��ӵ�Ŀ���ļ���
void CPEDemoDlg::OnBnClickedButton3()
{
	//�ļ�ѡȡ
	WCHAR szFileName[MAX_PATH] = {};
	std::wstring_convert<std::codecvt_utf8_utf16<WCHAR>> convert;
	usr::util::GetOpenName(GetModuleHandle(nullptr), szFileName,
		L"EXE(*EXE)\0*.EXE\0DLL(*.DLL)\0*.DLL\0", L"Ŀ���ļ�");
	auto destFile = convert.to_bytes(szFileName);
	
	usr::util::GetOpenName(GetModuleHandle(nullptr), szFileName,
		L"DLL(*.DLL)\0*.DLL\0", L"�����ļ����������ӵ�Ŀ���ļ���");
	auto dllFile = convert.to_bytes(szFileName);
	
	//do add
	using namespace LIEF::PE;
	std::unique_ptr<Binary> binaryDest{Parser::parse(destFile)};
	std::unique_ptr<const Binary> binaryDll{ Parser::parse(dllFile) };
	auto dll_characteristics = binaryDest->optional_header().dll_characteristics();
	dll_characteristics &= ~LIEF::PE::DLL_CHARACTERISTICS::IMAGE_DLL_CHARACTERISTICS_DYNAMIC_BASE;	//��DYNAMIC_BASE��0
	dll_characteristics &= ~LIEF::PE::DLL_CHARACTERISTICS::IMAGE_DLL_CHARACTERISTICS_NX_COMPAT;
	binaryDest->optional_header().dll_characteristics(dll_characteristics);

	auto &lib = binaryDest->add_library(std::string(dllFile, dllFile.rfind("\\") + 1, dllFile.length() - dllFile.rfind("\\")));
	for (const auto &elem : binaryDll->get_exported_functions())
	{
		lib.add_entry(elem);
	}

	auto builder = Builder(binaryDest.get());
	builder.build_imports(true).patch_imports(true);

	try
	{
		builder.build();
	}
	catch (const LIEF::exception& e)
	{
		return;
	}
	builder.write(destFile + ".iat.exe");
}
