// ViewerDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "3DBipedRobot.h"
#include "ViewerDlg.h"

#pragma warning(disable:4996)


// CViewerDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CViewerDlg, CDialog)

CViewerDlg::CViewerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CViewerDlg::IDD, pParent)
	, m_fShift(0)
	, m_ctrlShift(0)
	, m_bGravity(false)
{

}

CViewerDlg::~CViewerDlg()
{
}

void CViewerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_NOSHIFT, m_ctrlShift);
	DDV_MinMaxInt(pDX, m_ctrlShift, 0, 2);
	DDX_Text(pDX, IDC_EDIT_SHIFT, m_fShift);
	DDV_MinMaxFloat(pDX, m_fShift, 0.0, 100.0);
}


BEGIN_MESSAGE_MAP(CViewerDlg, CDialog)
	ON_BN_CLICKED(IDC_RADIO_NOSHIFT,       &CViewerDlg::OnBnClickedRadioShift)
	ON_BN_CLICKED(IDC_RADIO_USERSHIFT,     &CViewerDlg::OnBnClickedRadioShift)
	ON_BN_CLICKED(IDC_RADIO_DYNAMICSSHIFT, &CViewerDlg::OnBnClickedRadioShift)
END_MESSAGE_MAP()


// CViewerDlg �޽��� ó�����Դϴ�.

BOOL CViewerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_ctrlShift = 0;			// No shift Set
	m_bGravity = FALSE;		// No Gravity Set

	SetDlgItemText(IDC_EDIT_SHIFT, L"0.00");
	OnBnClickedRadioShift();

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CViewerDlg::OnOK()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	/*CDialog::OnOK();*/
}

void CViewerDlg::OnCancel()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	/*CDialog::OnCancel();*/
}

void CViewerDlg::OnBnClickedRadioShift()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	if(m_ctrlShift == 0)
		m_fShift = 0.f, GetDlgItem(IDC_EDIT_SHIFT)->EnableWindow(FALSE);
	else if(m_ctrlShift == 2)		// Dynamics �Ἥ ���� ���� �־������!
		GetDlgItem(IDC_EDIT_SHIFT)->EnableWindow(FALSE);
	else
		m_fShift = 10.f, GetDlgItem(IDC_EDIT_SHIFT)->EnableWindow(TRUE);

	UpdateData(FALSE);
}

// User Function

void CViewerDlg::SetDlgItemFloat(int nID, float fValue)
{
	TCHAR str[32] = {0,};
	swprintf(str, L"%5.2f", fValue);
	this->SetDlgItemText(nID, str);
}
