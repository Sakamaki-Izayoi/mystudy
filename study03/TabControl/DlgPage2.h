#pragma once


// CDlgPage2 �Ի���

class CDlgPage2 : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgPage2)

public:
	CDlgPage2(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgPage2();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PAGE2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
