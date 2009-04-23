#pragma once
#include "afxwin.h"


// CViewerDlg 대화 상자입니다.

class CViewerDlg : public CDialog
{
	DECLARE_DYNAMIC(CViewerDlg)

public:
	CViewerDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CViewerDlg();

	void SetDlgItemFloat(int nID, float fValue);

// 대화 상자 데이터입니다.
	enum { IDD = IDD_VIEWERDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
