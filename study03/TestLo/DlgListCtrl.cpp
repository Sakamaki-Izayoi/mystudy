// DlgListCtrl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "resource.h"
#include "DlgListCtrl.h"
#include "afxdialogex.h"
#include "CommonLib/usr_ini_file.h"


// CDlgListCtrl �Ի���

IMPLEMENT_DYNAMIC(CDlgListCtrl, CDialogEx)

CDlgListCtrl::CDlgListCtrl(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LISTDEMO, pParent)
{

	EnableAutomation();

}

CDlgListCtrl::~CDlgListCtrl()
{
}

void CDlgListCtrl::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CDialogEx::OnFinalRelease();
}

void CDlgListCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTDEMO, m_list);
}


BEGIN_MESSAGE_MAP(CDlgListCtrl, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgListCtrl::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDlgListCtrl::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDlgListCtrl::OnBnClickedButton3)
	ON_NOTIFY(NM_RCLICK, IDC_LISTDEMO, &CDlgListCtrl::OnRclickListdemo)
	ON_COMMAND(ID__SDF, &CDlgListCtrl::MenuAdd)
	ON_COMMAND(ID__SDF32772, &CDlgListCtrl::MenuDel)
	ON_BN_CLICKED(IDC_BUTTON5, &CDlgListCtrl::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON4, &CDlgListCtrl::OnBnClickedButton4)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgListCtrl, CDialogEx)
END_DISPATCH_MAP()

// ע��: ������� IID_IDlgListCtrl ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {8872B7B7-9466-43BB-8D62-E902A25B11AA}
static const IID IID_IDlgListCtrl =
{ 0x8872B7B7, 0x9466, 0x43BB, { 0x8D, 0x62, 0xE9, 0x2, 0xA2, 0x5B, 0x11, 0xAA } };

BEGIN_INTERFACE_MAP(CDlgListCtrl, CDialogEx)
	INTERFACE_PART(CDlgListCtrl, IID_IDlgListCtrl, Dispatch)
END_INTERFACE_MAP()





BOOL CDlgListCtrl::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_listview = mfc::listview(&m_list);

	return TRUE; 
}


void CDlgListCtrl::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��Ҫ��ѡ����Ҫ��initȥ��
	mfc::_listview_list SelList;
	m_listview.getSelected(SelList);
}


void CDlgListCtrl::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_listview.delSelected();
}


void CDlgListCtrl::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int i = rand();
	CString str;
	str.Format(L"%d", i);
	m_listview.insert(str , str, str, str);
}


void CDlgListCtrl::OnRclickListdemo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMenu menu;
	POINT pt;
	menu.LoadMenu(IDR_MENU1);
	GetCursorPos(&pt);
	menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON
		| TPM_RIGHTBUTTON, pt.x, pt.y, this, NULL);
	*pResult = 0;
}


void CDlgListCtrl::MenuAdd()
{
	// TODO: �ڴ���������������
	MessageBox(L"Menu Add");
}


void CDlgListCtrl::MenuDel()
{
	// TODO: �ڴ���������������
	MessageBox(L"Menu Del");
}

//����ini
void CDlgListCtrl::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//����1.��ñ���·��
	WCHAR filePath[MAX_PATH] = {};
	if (!usr::util::GetSaveName(GetModuleHandle(NULL), filePath, L"INI(*.INI)\0*.ini\0", L"����"))
	{
		return;
	}
	
	//����2������б�ؼ��е��к�ÿ������
	
	mfc::_listview_list _save;
	std::vector<_tstring> sublist;
	m_listview.save(_save);
	m_listview.get_column(sublist);

	//����3�����б��е����ݿ�����file��
	auto file = usr::ini_file(filePath);
	file.set(_save);
	file.set_sub_list(sublist);

	//wcscat_s(filePath, L".ini");
	//������file_sava
	file.save_ini();
	AfxMessageBox(filePath);
}

//����ini
void CDlgListCtrl::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//����1������ļ�¬��
	WCHAR filePath[MAX_PATH] = {};
	if (!usr::util::GetOpenName(GetModuleHandle(NULL), filePath, L"INI(*.ini)\0*.ini\0", L"ѡ��"))
		return;

	//����2,�������Ϣ
	m_listview.clear();
	auto file = usr::ini_file(filePath);
	std::vector<_tstring> subs;
	file.get_sub_list(subs);

	//����3������list_view����
	for (auto sub : subs)
	{
		m_listview.add_column(sub);
	}

	//��������
	m_listview.load(file.get());

}
