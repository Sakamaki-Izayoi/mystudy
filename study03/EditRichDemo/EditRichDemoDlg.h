
// EditRichDemoDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"


// CEditRichDemoDlg �Ի���
class CEditRichDemoDlg : public CDialogEx
{
// ����
public:
	CEditRichDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EDITRICHDEMO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CRichEditCtrl m_edit;
	afx_msg void OnBnClickedButtonColor();
	afx_msg void OnBnClickedButtonFont();
};
