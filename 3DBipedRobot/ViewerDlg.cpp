// ViewerDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "3DBipedRobot.h"
#include "ViewerDlg.h"


// CViewerDlg ��ȭ �����Դϴ�.

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


// CViewerDlg �޽��� ó�����Դϴ�.

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
