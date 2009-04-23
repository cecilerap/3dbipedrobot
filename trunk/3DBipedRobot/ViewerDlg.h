#pragma once
#include "afxwin.h"


// CViewerDlg ��ȭ �����Դϴ�.

class CViewerDlg : public CDialog
{
	DECLARE_DYNAMIC(CViewerDlg)

public:
	CViewerDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CViewerDlg();

	void SetDlgItemFloat(int nID, float fValue);

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_VIEWERDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
	virtual void OnCancel();
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadioShift();
	float m_fShift;
	int m_ctrlShift;
	bool m_bGravity;	
	int m_nVelocity;
	float m_fStride;
	CComboBox m_comboPort;
	CComboBox m_comboBaudrate;
	afx_msg void OnBnClickedCheckConnect();
};
