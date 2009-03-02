//////////////////////////////////////////////////////////////////////////
// DirectX3D.cpp
//////////////////////////////////////////////////////////////////////////

#include "AllHeader.h"

CDirectX3D g_DirectX3D;

CDirectX3D::CDirectX3D(void)
{
}

CDirectX3D::~CDirectX3D(void)
{
}

// User Function
HRESULT CDirectX3D::InitD3D(HWND hWnd)
{
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

//	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
//	m_pD3DDevice->SetRenderState(D3DRS_AMBIENT, 0xffffffff);

	return S_OK;
}

HRESULT CDirectX3D::InitGeometry()
{
	g_Body.InitMesh(m_pD3DDevice);
	g_Body.AddChild(m_pD3DDevice, new CNode(L"FOOT_L.X"));

	return S_OK;
}

void CDirectX3D::Cleanup()
{
	if(m_pD3DDevice != NULL)
		m_pD3DDevice->Release();

	if(m_pD3D != NULL)
		m_pD3D->Release();

	g_Body.CleanUp();
}

void CDirectX3D::Render()
{
	if(NULL == m_pD3DDevice)
		return;

	// 후면 버퍼를 초기화
	m_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,255), 1.0f, 0);

	SetupLights();
	SetupMatrices();

//	g_Body.SetupMatrices();

	if(SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		g_Body.Render(m_pD3DDevice);

		m_pD3DDevice->EndScene();
	}

	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void CDirectX3D::SetupMatrices()
{
	// World 행렬 설정
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	//	D3DXMatrixRotationX(&matWorld, timeGetTime()/1000.f);		// Y축을 기준으로 회전운동
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	// View 행렬 설정
	D3DXVECTOR3 vEyePt(0.0f, 0.0f, 100.0f);			// 눈의 위치
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);		// 눈이 바라보는 위치
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);			// 천정 방향을 나타내는 상방 벡터
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	m_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);

	// Projection 행렬 설정
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI/4, 1.0f, 1000.0f, 100.0f);
	m_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}

void CDirectX3D::SetupLights()
{
	// 재질 설정
	D3DMATERIAL9 mtrl;
	ZeroMemory(&mtrl, sizeof(D3DMATERIAL9));
	mtrl.Diffuse.r = mtrl.Ambient.r = 1.0f;
	mtrl.Diffuse.g = mtrl.Ambient.g = 1.0f;
	mtrl.Diffuse.b = mtrl.Ambient.b = 0.0f;
	mtrl.Diffuse.a = mtrl.Ambient.a = 1.0f;
	m_pD3DDevice->SetMaterial(&mtrl);

	// 광원 설정
	D3DXVECTOR3 vecDir;
	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;
	vecDir = D3DXVECTOR3(cosf(timeGetTime()/350.0f), 1.0f, sinf(timeGetTime()/350.0f));
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);
	light.Range = 1000.0f;
	m_pD3DDevice->SetLight(0, &light);
	m_pD3DDevice->LightEnable(0, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_AMBIENT, 0x00202020);
}