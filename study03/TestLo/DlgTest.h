#pragma once


// CDlgTest �Ի���

class CDlgTest : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTest)

public:
	CDlgTest(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgTest();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLGTEST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
