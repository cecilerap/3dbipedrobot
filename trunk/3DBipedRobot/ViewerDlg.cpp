// ViewerDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "3DBipedRobot.h"
#include "ViewerDlg.h"


// CViewerDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CViewerDlg, CDialog)

CViewerDlg::CViewerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CViewerDlg::IDD, pParent)
{

}

CViewerDlg::~CViewerDlg()
{
}

void CViewerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CViewerDlg, CDialog)
END_MESSAGE_MAP()


// CViewerDlg 메시지 처리기입니다.

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
