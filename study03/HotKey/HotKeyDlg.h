
// HotKeyDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"


// CHotKeyDlg �Ի���
class CHotKeyDlg : public CDialogEx
{
// ����
public:
	CHotKeyDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HOTKEY_DIALOG };
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
	CHotKeyCtrl m_hotkey;
	afx_msg void OnBnClickedButtonSethotkey();
};
