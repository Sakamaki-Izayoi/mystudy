#pragma once


// CDlgPage1 �Ի���

class CDlgPage1 : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgPage1)

public:
	CDlgPage1(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgPage1();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PAGE1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
