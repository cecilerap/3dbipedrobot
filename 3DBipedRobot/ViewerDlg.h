#pragma once


// CViewerDlg ��ȭ �����Դϴ�.

class CViewerDlg : public CDialog
{
	DECLARE_DYNAMIC(CViewerDlg)

public:
	CViewerDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CViewerDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_VIEWERDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
	virtual void OnCancel();
	virtual void OnOK();
};
