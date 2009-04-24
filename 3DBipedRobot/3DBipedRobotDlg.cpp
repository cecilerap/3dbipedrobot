// 3DBipedRobotDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "3DBipedRobot.h"
#include "3DBipedRobotDlg.h"

#include <afxpriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// C3DBipedRobotDlg 대화 상자
C3DBipedRobotDlg::C3DBipedRobotDlg(CWnd* pParent /*=NULL*/)
	: CDialog(C3DBipedRobotDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C3DBipedRobotDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(C3DBipedRobotDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_KICKIDLE, OnKickIdle)
	//}}AFX_MSG_MAP
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_KEYDOWN()
	ON_WM_DESTROY()	
END_MESSAGE_MAP()


// C3DBipedRobotDlg 메시지 처리기

BOOL C3DBipedRobotDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	// 윈도우 크기 설정
	SetWindowPos(&CWnd::wndTop, 150, 150, 600, 600, SWP_NOZORDER);

	HWND hDevice, hFocus;

	// 윈도우 핸들 취득
	hDevice = GetSafeHwnd();
	hFocus  = GetTopLevelParent()->GetSafeHwnd();

	// 윈도우 클라이언트 영역 취득
	GetClientRect(&m_rtClient);
	
	// Direct3D 오브젝트 작성
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	// 디스플레이 모드 취득
	D3DDISPLAYMODE d3ddm;
	m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);

	// D3DPRESENT_PARAMETERS 구조체 설정
	::ZeroMemory(&m_d3dpp, sizeof(m_d3dpp));
	m_d3dpp.Windowed = TRUE;
	m_d3dpp.BackBufferCount = 1;
	m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_d3dpp.EnableAutoDepthStencil = TRUE;
	m_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	m_d3dpp.hDeviceWindow = hDevice;
	m_d3dpp.BackBufferWidth = m_rtClient.Width();
	m_d3dpp.BackBufferHeight = m_rtClient.Height();
	m_d3dpp.BackBufferFormat = d3ddm.Format;
	m_d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

	m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hFocus, D3DCREATE_SOFTWARE_VERTEXPROCESSING,
						 &m_d3dpp, &m_pD3DDevice);

	m_pD3DDevice->SetDialogBoxMode(TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// 3DBipedRobot Setting
	InitGeometry();

	// 3DBipedRobot Viewer Setting
	m_pViewerDlg = new CViewerDlg(this);
	m_pViewerDlg->Create(IDD_VIEWERDLG);
	m_pViewerDlg->ShowWindow(SW_SHOW);
	m_pViewerDlg->SetWindowPos(&CViewerDlg::wndTop, 700, 400, 0, 0, SWP_NOZORDER|SWP_NOSIZE);

	// Serial Comm Setting
	m_pComm.SetHwnd(m_hWnd);
	

	// 초기화 완료
	m_bReady = TRUE;

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void C3DBipedRobotDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR C3DBipedRobotDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT C3DBipedRobotDlg::OnKickIdle(WPARAM wParam, LPARAM lParam)
{
	UpdateDialogControls(this, FALSE);

	if(m_bReady)
	{
		if(m_pSimul->GetState() == CSimulate::READY)
			m_pViewerDlg->SetWindowText(L"3DBipedRobot_viewer");
		m_pSimul->Simulate();
		return TRUE;
	}

	return (LRESULT)1;
}

// User Function
void C3DBipedRobotDlg::Render()
{
	m_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(240,240,240), 1.f, 0);

//	// Test!!!!!!!!!!
//	m_pNodeMgr->SetWeight();

	// Simulation 에서 변화된 행렬을 Animation 적용
	// 무게중심 계산
	m_pNodeMgr->Animate();

//	// 무게중심 적용 (현재의 무게중심으로 다음번에 힘이 가해짐)
//	m_pNodeMgr->SetWeight();
	
	//////////////////////////////////////////////////////////////////////////
	// Viewer 출력
	m_pViewerDlg->SetDlgItemFloat(IDC_EDIT_THETA,  m_pCamera->GetTheta());
	m_pViewerDlg->SetDlgItemFloat(IDC_EDIT_PHI,    m_pCamera->GetPhi());
	m_pViewerDlg->SetDlgItemFloat(IDC_EDIT_RADIUS, m_pCamera->GetRadius());

	float retLeft  = m_pNodeMgr->m_pLeftZMP->Check();
	float retRight = m_pNodeMgr->m_pRightZMP->Check();
	for(int i = 0; i < 4; ++i)
	{
		m_pViewerDlg->SetDlgItemInt(IDC_EDIT_LEFT1+i, retLeft);
		m_pViewerDlg->SetDlgItemInt(IDC_EDIT_RIGHT1+i, retRight);
	}

// 	UINT tempZMP;
// 	UINT retLeft  = m_pNodeMgr->m_pLeftZMP->Check();
// 	UINT retRight = m_pNodeMgr->m_pRightZMP->Check();
// 	for(int i = 0; i < 4; ++i)
// 	{
// 		tempZMP = retLeft&0x000000FF;		// 1 이면 땅에 닿았다는 뜻
// 		m_pViewerDlg->SetDlgItemInt(IDC_EDIT_LEFT1+i, tempZMP);
// 		retLeft >>= 8;
// 
// 		tempZMP = retRight&0x000000FF;		// 1 이면 땅에 닿았다는 뜻
// 		m_pViewerDlg->SetDlgItemInt(IDC_EDIT_RIGHT1+i, tempZMP);
// 		retRight >>= 8;
// 	}

	D3DXVECTOR3 tempCtWeight = m_pNodeMgr->GetCenterWeight();
	m_pViewerDlg->SetDlgItemFloat(IDC_EDIT_CENTERX, tempCtWeight.x);
	m_pViewerDlg->SetDlgItemFloat(IDC_EDIT_CENTERY, tempCtWeight.y);
	m_pViewerDlg->SetDlgItemFloat(IDC_EDIT_CENTERZ, tempCtWeight.z);
	//////////////////////////////////////////////////////////////////////////

	if(SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		// Render 작업
		m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

		// mesh 그려주는 작업
		m_pNodeMgr->Draw();

		m_pD3DDevice->EndScene();
	}

	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void C3DBipedRobotDlg::InitGeometry()
{
	InitObject();
	InitMatrix();
	InitLights();
}

void C3DBipedRobotDlg::InitObject()
{
 	m_pNodeMgr = new CNodeMgr(m_pD3DDevice);
 	m_pCamera  = new CCamera(m_pD3DDevice);
	m_pSimul   = new CSimulate(this);
}

void C3DBipedRobotDlg::InitMatrix()
{
	// World 행렬 설정
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	m_pCamera->SetCamera();

	// Projection 행렬 설정
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI/4.f, 1.0f, 1.0f, 1000.0f);
	m_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}

void C3DBipedRobotDlg::InitLights()
{
	// 재질 설정
	D3DMATERIAL9 mtrl;
	ZeroMemory(&mtrl, sizeof(D3DMATERIAL9));
	mtrl.Diffuse = mtrl.Ambient = D3DXCOLOR(0xffffffff);
	m_pD3DDevice->SetMaterial(&mtrl);

	// 광원 설정
	D3DXVECTOR3 vecDir;
	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse = D3DXCOLOR(0xffffffff);
	light.Ambient = D3DXCOLOR(0xff202020);
	vecDir = D3DXVECTOR3(0.0f, 1.0f, -300.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);
	light.Range = 1000.0f;

	m_pD3DDevice->SetLight(0, &light);
	m_pD3DDevice->LightEnable(0, TRUE);

	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_AMBIENT, 0x00202020);
}

void C3DBipedRobotDlg::DeleteObject()
{
	if(m_pNodeMgr != NULL)
		delete m_pNodeMgr;

	if(m_pCamera != NULL)
		delete m_pCamera;

	if(m_pSimul != NULL)
		delete m_pSimul;
}

void C3DBipedRobotDlg::Cleanup()
{
	if(m_pD3DDevice != NULL)
		m_pD3DDevice->Release();

	if(m_pD3D != NULL)
		m_pD3D->Release();
}

void C3DBipedRobotDlg::InitSerialComm()
{
	m_nSettingPort   = m_pViewerDlg->m_comboPort.GetCurSel()+1;
	m_nSettingParity = 0;
	m_nSettingBaud   = m_pViewerDlg->m_comboBaudrate.GetCurSel();
	m_nSettingData   = 1;
	m_nSettingStop   = 0;
	m_nSettingFlow   = 0;
}

TTYSTRUCT C3DBipedRobotDlg::Int2TTY()
{
	TTYSTRUCT tty;
	ZERO_MEMORY(tty);

	tty.byCommPort = (BYTE)m_nSettingPort;
	tty.byXonXoff  = FALSE;
	tty.byByteSize = (BYTE)_nDataValues[m_nSettingData];
	tty.byFlowCtrl = (BYTE)_nFlow[m_nSettingFlow];
	tty.byParity   = (BYTE)m_nSettingParity;
	tty.byStopBits = (BYTE)_nStopBits[m_nSettingStop];
	tty.dwBaudRate = (DWORD)_nBaudRates[m_nSettingBaud];

	return tty;
}

void C3DBipedRobotDlg::OnBnClickedCheckConnect()
{
	m_pViewerDlg->UpdateData(TRUE);
	
	BOOL bCheck = ((CButton*)(m_pViewerDlg->GetDlgItem(IDC_CHECK_CONNECT)))->GetCheck();
	if(bCheck)
	{
		InitSerialComm();
		if(m_pComm.OpenCommPort(&Int2TTY()) != TRUE)
		{
			AfxMessageBox(L"이미 사용중이거나 Comport가 연결되지 않았습니다.");

			((CButton*)(m_pViewerDlg->GetDlgItem(IDC_CHECK_CONNECT)))->SetCheck(!bCheck);
			return;
		}

		m_pViewerDlg->GetDlgItem(IDC_CHECK_CONNECT)->SetWindowText(L"D I S C O N N E T");
		m_pViewerDlg->GetDlgItem(IDC_COMBO_PORT)->EnableWindow(FALSE);
		m_pViewerDlg->GetDlgItem(IDC_COMBO_BAUDRATE)->EnableWindow(FALSE);
		m_pViewerDlg->GetDlgItem(IDC_BUTTON_SENDDATA)->EnableWindow(TRUE);
	}
	else
	{
		m_pComm.CloseConnection();

		m_pViewerDlg->GetDlgItem(IDC_CHECK_CONNECT)->SetWindowText(L"C O N N E T");
		m_pViewerDlg->GetDlgItem(IDC_COMBO_PORT)->EnableWindow(TRUE);
		m_pViewerDlg->GetDlgItem(IDC_COMBO_BAUDRATE)->EnableWindow(TRUE);
		m_pViewerDlg->GetDlgItem(IDC_BUTTON_SENDDATA)->EnableWindow(FALSE);
	}
}

void C3DBipedRobotDlg::SendData()
{
	m_pViewerDlg->UpdateData(TRUE);

	unsigned char TX_Motion[4];
	TX_Motion[0] = 1;			// 무조건 1
	TX_Motion[1] = m_pViewerDlg->GetDlgItemInt(IDC_EDIT_STRIDE);
	TX_Motion[2] = m_pViewerDlg->GetDlgItemInt(IDC_EDIT_SPEED)-33;			// 수정할것!!!!
	TX_Motion[3] = m_pViewerDlg->GetDlgItemInt(IDC_EDIT_SHIFT);

	m_pComm.WriteCommBlock((LPSTR)TX_Motion, 4);
}

// Message Function

void C3DBipedRobotDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	SetCapture();
	m_pCamera->SetMousePos(point.x, point.y);

	CDialog::OnLButtonDown(nFlags, point);
}

void C3DBipedRobotDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	ReleaseCapture();

	CDialog::OnLButtonUp(nFlags, point);
}

void C3DBipedRobotDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	RECT rt;
	GetClientRect(&rt);

	if(!PtInRect(&rt, point))
		return;

	if(MK_LBUTTON & nFlags)
		m_pCamera->Move(point.x, point.y);

	CDialog::OnMouseMove(nFlags, point);
}

BOOL C3DBipedRobotDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_pCamera->Zoom(zDelta);

	return CDialog::OnMouseWheel(nFlags, zDelta, pt);
}

void C3DBipedRobotDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_pViewerDlg->UpdateData(TRUE);

	switch(nChar)
	{
			   // 여기서 반드시 순서 중요!!!!!
			   // 항상 State를 보고 있다가 State 변화되면 그 때 쓰레드 생성해서 하는데
			   // Shift를 State보다 나중에 지정해주면 이미 Walking 쓰레드가 실행되있는 상태에서
			   // Shift를 바꾸니 문제가 생김!!!!
			   // 쓰레드 동기화를 해줘야 했지만 아직 못함!!!
	case 'W' :  
	case 'w' : 
		m_pSimul->SetOption(m_pViewerDlg->m_fShift, m_pViewerDlg->m_nVelocity, m_pViewerDlg->m_fStride-20.f);
		m_pSimul->SetState(CSimulate::WALK);
		m_pViewerDlg->SetWindowText(L"Viewer.... Walking");
		break;

	case 'S' :
	case 's' : 
		m_pSimul->SetState(CSimulate::START);
		m_pViewerDlg->SetWindowText(L"Viewer.... Start");
		break;

	case 'F' :  
	case 'f' : 
		m_pSimul->SetOption(m_pViewerDlg->m_fShift, m_pViewerDlg->m_nVelocity, m_pViewerDlg->m_fStride-20.f);
		m_pSimul->SetState(CSimulate::FALLDOWN);
		m_pViewerDlg->SetWindowText(L"Viewer.... Falldown");
		break;

	default:
		break;
	}

	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

void C3DBipedRobotDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if(m_pViewerDlg)
		delete m_pViewerDlg;
	m_pViewerDlg = NULL;
}

void C3DBipedRobotDlg::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	/*CDialog::OnOK();*/
}
