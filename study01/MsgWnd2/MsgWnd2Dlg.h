
// MsgWnd2Dlg.h : ͷ�ļ�
//

#pragma once


// CMsgWnd2Dlg �Ի���
class CMsgWnd2Dlg : public CDialogEx
{
// ����
public:
	CMsgWnd2Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MSGWND2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	
protected:
	afx_msg LRESULT SendWnd2Fun(WPARAM wpD, LPARAM lpD);//������Ϣ���򣬲���2��������Ϣ����
};
