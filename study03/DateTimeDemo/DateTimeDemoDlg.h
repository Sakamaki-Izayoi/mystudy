
// DateTimeDemoDlg.h : ͷ�ļ�
//

#pragma once
#include "afxdtctl.h"
#include "afxwin.h"


// CDateTimeDemoDlg �Ի���
class CDateTimeDemoDlg : public CDialogEx
{
// ����
public:
	CDateTimeDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DATETIMEDEMO_DIALOG };
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
	CDateTimeCtrl m_date_begin;
	CDateTimeCtrl m_date_end;
	CEdit m_edit_output;
	afx_msg void OnDatetimechangeDateBegin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDatetimechangeDateEnd(NMHDR *pNMHDR, LRESULT *pResult);
};
