// ViewerDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "3DBipedRobot.h"
#include "ViewerDlg.h"
#include "3DBipedRobotDlg.h"

#pragma warning(disable:4996)


// CViewerDlg 대화 상자입니다.

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


// CViewerDlg 메시지 처리기입니다.

BOOL CViewerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
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
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CViewerDlg::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	/*CDialog::OnOK();*/
}

void CViewerDlg::OnCancel()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	/*CDialog::OnCancel();*/
}

void CViewerDlg::OnBnClickedRadioShift()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	if(m_ctrlShift == 0)
		m_fShift = 0.f, GetDlgItem(IDC_EDIT_SHIFT)->EnableWindow(FALSE);
	else if(m_ctrlShift == 2)		// Dynamics 써서 따로 값을 넣어줘야함!
		m_fShift = 43.f, GetDlgItem(IDC_EDIT_SHIFT)->EnableWindow(FALSE);
	else
		m_fShift = 10.f, GetDlgItem(IDC_EDIT_SHIFT)->EnableWindow(TRUE);

	UpdateData(FALSE);
}

void CViewerDlg::OnBnClickedCheckConnect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	((C3DBipedRobotDlg*)GetParent())->OnBnClickedCheckConnect();
}

void CViewerDlg::OnBnClickedButtonSenddata()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	((C3DBipedRobotDlg*)GetParent())->SendData();
}

// User Function

void CViewerDlg::SetDlgItemFloat(int nID, float fValue)
{
	TCHAR str[32] = {0,};
	swprintf(str, L"%5.2f", fValue);
	this->SetDlgItemText(nID, str);
}
