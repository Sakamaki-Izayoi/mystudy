
// TreeCtrlDemoDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"


// CTreeCtrlDemoDlg �Ի���
class CTreeCtrlDemoDlg : public CDialogEx
{
// ����
public:
	CTreeCtrlDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TREECTRLDEMO_DIALOG };
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
	afx_msg void OnBnClickedButtonInsert();
	afx_msg void OnBnClickedButtonDel();
	afx_msg void OnBnClickedUpdate();
	CTreeCtrl m_tree;
	afx_msg void OnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult);
};
