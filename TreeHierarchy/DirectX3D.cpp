//////////////////////////////////////////////////////////////////////////
// DirectX3D.cpp
//////////////////////////////////////////////////////////////////////////

#include "DirectX3D.h"

#pragma warning(disable:4996)

CDirectX3D::CDirectX3D(void)
{
}

CDirectX3D::~CDirectX3D(void)
{
}

// User Function
HRESULT CDirectX3D::InitD3D(HWND hWnd)
{
	m_hWnd = hWnd;

	// Device 생성하기 위한 D3D 객체 생성
	if(NULL == (m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	// Device 생성을 위한 구조체
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	if(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice)))
		return E_FAIL;

	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	return S_OK;
}

HRESULT CDirectX3D::InitGeometry()
{
	InitMatrix();
	InitLights();
	InitXYZVertex();

	return S_OK;
}

void CDirectX3D::InitMatrix()
{
	// World 행렬 설정
	D3DXMatrixIdentity(&m_matWorld);
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

 	// View 행렬 설정
	m_pCamera->SetCamera();

	// Projection 행렬 설정
	D3DXMatrixPerspectiveFovLH(&m_matProj, D3DX_PI/4, 1.0f, 1000.0f, 1.0f);
	m_pD3DDevice->SetTransform(D3DTS_PROJECTION, &m_matProj);
}

void CDirectX3D::InitLights()
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

struct CUSTOMVERTEXXYZ
{
	D3DXVECTOR3 position;
	D3DXCOLOR color;
};

void CDirectX3D::InitXYZVertex()
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

HRESULT CDirectX3D::InitObjects()
{
	m_pNodeMgr = new CNodeMgr(m_pD3DDevice);
	m_pCamera  = new CCamera(m_pD3DDevice);
	m_pSimul   = new CSimulate(m_pNodeMgr);

	return S_OK;
}

void CDirectX3D::DeleteObjects()
{
	if(m_pNodeMgr != NULL)
		delete m_pNodeMgr;

	if(m_pCamera != NULL)
		delete m_pCamera;
}

void CDirectX3D::Cleanup()
{
	if(m_pXYZVB != NULL)
		m_pXYZVB->Release();

	if(m_pD3DDevice != NULL)
		m_pD3DDevice->Release();

	if(m_pD3D != NULL)
		m_pD3D->Release();
}

void CDirectX3D::Animate()
{
	// 행렬 변환 작업 (이동이라든지 등등)
	m_pSimul->Simulate();
	m_pNodeMgr->Animate();
}

void CDirectX3D::Render()
{
	if(NULL == m_pD3DDevice)
		return;

	// 후면 버퍼를 초기화
	m_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(180,250,250), 1.0f, 0);

	Animate();

	HDC hDC;
	hDC = GetDC(m_hWnd);
	SetBkColor(hDC, RGB(180,250,250));
	TCHAR str[256] = {0,};

	if(SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		// 문자열 출력
		TextOut(hDC, 10, 10, L"Mouse Left Button Down + ↑↓←→ [카메라 이동]", 38);
		swprintf(str, L"Θ : %.2lf, Φ : %.2lf, Radius : %.2lf", m_pCamera->GetTheta(), m_pCamera->GetPhi(), m_pCamera->GetRadius());
		TextOut(hDC, 10, 30, str, wcslen(str));

		m_pD3DDevice->SetStreamSource(0, m_pXYZVB, 0, sizeof(CUSTOMVERTEXXYZ));
		m_pD3DDevice->SetFVF(D3DFVF_XYZ|D3DFVF_DIFFUSE);
		m_pD3DDevice->DrawPrimitive(D3DPT_LINELIST, 0, 3);

		m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

		// mesh 그려주는 작업
		m_pNodeMgr->Draw();

		m_pD3DDevice->EndScene();
	}

	ReleaseDC(m_hWnd, hDC);

	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
