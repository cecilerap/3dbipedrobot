//////////////////////////////////////////////////////////////////////////
// DirectX3D.cpp
//////////////////////////////////////////////////////////////////////////

#include "DirectX3D.h"

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

	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	return S_OK;
}

HRESULT CDirectX3D::InitGeometry()
{
	InitMatrix();

	return S_OK;
}

void CDirectX3D::InitMatrix()
{
	// World 행렬 설정
	D3DXMatrixIdentity(&m_matWorld);
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	// View 행렬 설정
	D3DXVECTOR3 vEyePt(0.0f, 0.0f, 100.0f);			// 눈의 위치
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);		// 눈이 바라보는 위치
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);			// 천정 방향을 나타내는 상방 벡터
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	m_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);

	// Projection 행렬 설정
	D3DXMatrixPerspectiveFovLH(&m_matProj, D3DX_PI/4, 1.0f, 100.0f, 1.0f);
	m_pD3DDevice->SetTransform(D3DTS_PROJECTION, &m_matProj);
}

HRESULT CDirectX3D::InitObjects()
{
	m_pNodeMgr = new CNodeMgr(m_pD3DDevice);
	return S_OK;
}

void CDirectX3D::DeleteObjects()
{

}

void CDirectX3D::Cleanup()
{
	if(m_pD3DDevice != NULL)
		m_pD3DDevice->Release();

	if(m_pD3D != NULL)
		m_pD3D->Release();
}

void CDirectX3D::Animate()
{
	// 행렬 변환 작업 (이동이라든지 등등)
	m_pNodeMgr->Animate();
}

void CDirectX3D::Render()
{
	if(NULL == m_pD3DDevice)
		return;

	// 후면 버퍼를 초기화
	m_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,255), 1.0f, 0);

	Animate();

	if(SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		// mesh 그려주는 작업
		m_pNodeMgr->Draw();

		m_pD3DDevice->EndScene();
	}

	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}