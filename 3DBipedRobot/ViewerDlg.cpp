// ViewerDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "3DBipedRobot.h"
#include "ViewerDlg.h"
#include "3DBipedRobotDlg.h"

#pragma warning(disable:4996)


// CViewerDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CViewerDlg, CDialog)

CViewerDlg::CViewerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CViewerDlg::IDD, pParent)
	, m_fShift(0)
	, m_ctrlShift(0)
	, m_bGravity(false)
	, m_nVelocity(0)
	, m_fStride(0)
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
	DDX_Text(pDX, IDC_EDIT_SPEED, m_nVelocity);
	DDV_MinMaxInt(pDX, m_nVelocity, 10, 50);
	DDX_Text(pDX, IDC_EDIT_STRIDE, m_fStride);	
	DDV_MinMaxFloat(pDX, m_fStride, 25, 50);
	DDX_Control(pDX, IDC_COMBO_PORT, m_comboPort);
	DDX_Control(pDX, IDC_COMBO_BAUDRATE, m_comboBaudrate);
}


BEGIN_MESSAGE_MAP(CViewerDlg, CDialog)
	ON_BN_CLICKED(IDC_RADIO_NOSHIFT,       &CViewerDlg::OnBnClickedRadioShift)
	ON_BN_CLICKED(IDC_RADIO_USERSHIFT,     &CViewerDlg::OnBnClickedRadioShift)
	ON_BN_CLICKED(IDC_RADIO_DYNAMICSSHIFT, &CViewerDlg::OnBnClickedRadioShift)
	ON_BN_CLICKED(IDC_CHECK_CONNECT, &CViewerDlg::OnBnClickedCheckConnect)
	ON_BN_CLICKED(IDC_BUTTON_SENDDATA, &CViewerDlg::OnBnClickedButtonSenddata)
END_MESSAGE_MAP()


// CViewerDlg �޽��� ó�����Դϴ�.

BOOL CViewerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_ctrlShift = 0;		// No shift Set
	m_bGravity = FALSE;		// No Gravity Set
	m_nVelocity = 33;		// Velocity = 33
	m_fStride = 30.f;		// Stride   = 30.f
	SetDlgItemText(IDC_EDIT_SHIFT, L"0.00");

	m_comboPort.SetCurSel(1);
	m_comboBaudrate.SetCurSel(1);

	GetDlgItem(IDC_BUTTON_SENDDATA)->EnableWindow(FALSE);

	UpdateData(FALSE);

	OnBnClickedRadioShift();

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
		m_fShift = 43.f, GetDlgItem(IDC_EDIT_SHIFT)->EnableWindow(FALSE);
	else
		m_fShift = 10.f, GetDlgItem(IDC_EDIT_SHIFT)->EnableWindow(TRUE);

	UpdateData(FALSE);
}

void CViewerDlg::OnBnClickedCheckConnect()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	((C3DBipedRobotDlg*)GetParent())->OnBnClickedCheckConnect();
}

void CViewerDlg::OnBnClickedButtonSenddata()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	((C3DBipedRobotDlg*)GetParent())->SendData();
}

// User Function

void CViewerDlg::SetDlgItemFloat(int nID, float fValue)
{
	TCHAR str[32] = {0,};
	swprintf(str, L"%5.2f", fValue);
	this->SetDlgItemText(nID, str);
}
