
// CheckBoxDemoDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CCheckBoxDemoDlg �Ի���
class CCheckBoxDemoDlg : public CDialogEx
{
// ����
public:
	CCheckBoxDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHECKBOXDEMO_DIALOG };
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
	CButton m_chkRed;
	CButton m_chkBlue;
	CButton m_chkGreen;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedCheckRed();
	afx_msg void OnBnClickedCheckGreen();
	afx_msg void OnBnClickedCheckBlue();
	afx_msg void OnBnClickedRadioRect();
	afx_msg void OnBnClickedRadioCircle();
};
