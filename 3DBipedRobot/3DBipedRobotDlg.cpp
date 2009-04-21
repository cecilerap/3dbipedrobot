// 3DBipedRobotDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "3DBipedRobot.h"
#include "3DBipedRobotDlg.h"

#include <afxpriv.h>

#include "Simulate.h"

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

	m_pViewerDlg = new CViewerDlg(this);
	m_pViewerDlg->Create(IDD_VIEWERDLG);
	m_pViewerDlg->ShowWindow(SW_SHOW);
	m_pViewerDlg->SetWindowPos(&CViewerDlg::wndTop, 700, 500, 0, 0, SWP_NOZORDER|SWP_NOSIZE);

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
		m_pSimul->Simulate();
//		Render();
		return TRUE;
	}

	return (LRESULT)1;
}

// User Function
void C3DBipedRobotDlg::Render()
{
	m_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(240,240,240), 1.f, 0);

	m_pNodeMgr->Animate();
	
	//////////////////////////////////////////////////////////////////////////
	// Viewer 출력
	m_pViewerDlg->SetDlgItemInt(IDC_EDIT_THETA, m_pCamera->GetTheta());
	m_pViewerDlg->SetDlgItemInt(IDC_EDIT_PHI, m_pCamera->GetPhi());
	m_pViewerDlg->SetDlgItemInt(IDC_EDIT_RADIUS, m_pCamera->GetRadius());

	UINT temp;
	UINT retLeft  = m_pNodeMgr->m_pLeftZMP->Check();
	UINT retRight = m_pNodeMgr->m_pRightZMP->Check();
	for(int i = 0; i < 4; ++i)
	{
		temp = retLeft&0x000000FF;		// 1 이면 땅에 닿았다는 뜻
		m_pViewerDlg->SetDlgItemInt(IDC_EDIT_LEFT1+i, temp);
		retLeft >>= 8;

		temp = retRight&0x000000FF;		// 1 이면 땅에 닿았다는 뜻
		m_pViewerDlg->SetDlgItemInt(IDC_EDIT_RIGHT1+i, temp);
		retRight >>= 8;
	}
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
	InitXYZVertex();
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

void C3DBipedRobotDlg::InitXYZVertex()
{
	// x,y,z vertex
	CUSTOMVERTEXXYZ xyzVertics[] = { {D3DXVECTOR3(  0.f, 0.f, 0.f), D3DXCOLOR(0xffff0000)},
									 {D3DXVECTOR3(300.f, 0.f, 0.f), D3DXCOLOR(0xffff0000)},
									 {D3DXVECTOR3(0.f,   0.f, 0.f), D3DXCOLOR(0xff00ff00)},
									 {D3DXVECTOR3(0.f, 300.f, 0.f), D3DXCOLOR(0xff00ff00)},
									 {D3DXVECTOR3(0.f, 0.f,   0.f), D3DXCOLOR(0xff0000ff)},
									 {D3DXVECTOR3(0.f, 0.f, 300.f), D3DXCOLOR(0xff0000ff)} };

	if(FAILED(m_pD3DDevice->CreateVertexBuffer(sizeof(xyzVertics), 0, D3DFVF_XYZ|D3DFVF_DIFFUSE, D3DPOOL_DEFAULT, &m_pXYZVB, NULL)))
		return;

	VOID* pVertices;
	if(FAILED(m_pXYZVB->Lock(0, sizeof(xyzVertics), (void**)&pVertices, 0)))
		return;
	memcpy(pVertices, xyzVertics, sizeof(xyzVertics));
	m_pXYZVB->Unlock();
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
	if(m_pXYZVB != NULL)
		m_pXYZVB->Release();

	if(m_pD3DDevice != NULL)
		m_pD3DDevice->Release();

	if(m_pD3D != NULL)
		m_pD3D->Release();
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
	switch(nChar)
	{
	case 'W' :
	case 'w' : m_pSimul->SetState(CSimulate::WALK);
		break;

	case 'S':
	case 's':
//		if(g_Sock.m_sock != INVALID_SOCKET)	
//			g_Sock.Send("hello", 5);
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
}

void C3DBipedRobotDlg::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	/*CDialog::OnOK();*/
}
