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
	InitLights();
//	InitBackVertex();

	return S_OK;
}

void CDirectX3D::InitMatrix()
{
	// World 행렬 설정
	D3DXMatrixIdentity(&m_matWorld);
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	// View 행렬 설정
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &m_pCamera->m_vEyePt, &m_pCamera->m_vLookatPt, &m_pCamera->m_vUpVec);
	m_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);

	// Projection 행렬 설정
	D3DXMatrixPerspectiveFovLH(&m_matProj, D3DX_PI/4, 1.0f, 1000.0f, 1.0f);
	m_pD3DDevice->SetTransform(D3DTS_PROJECTION, &m_matProj);
}

void CDirectX3D::InitLights()
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
	vecDir = D3DXVECTOR3(0.0f, 100.0f, -300.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);
	light.Range = 1000.0f;

	m_pD3DDevice->SetLight(0, &light);
	m_pD3DDevice->LightEnable(0, TRUE);

	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_AMBIENT, 0x00202020);
}

struct CUSTOMVERTEX
{
	FLOAT x, y, z;      // The untransformed, 3D position for the vertex
	DWORD color;        // The vertex color
};

// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE)

void CDirectX3D::InitBackVertex()
{
	CUSTOMVERTEX g_Vertices[] =
	{
		{ -1.0f,-1.0f, 0.0f, 0xffff0000, },
		{  1.0f,-1.0f, 0.0f, 0xff0000ff, },
		{  0.0f, 5.0f, 0.0f, 0xffffffff, },
	};

	if( FAILED( m_pD3DDevice->CreateVertexBuffer( 3 * sizeof( CUSTOMVERTEX ),
		0, D3DFVF_CUSTOMVERTEX,
		D3DPOOL_DEFAULT, &m_pBackVB, NULL ) ) )
	{
		return;
	}

	// Fill the vertex buffer.
	VOID* pVertices;
	if( FAILED( m_pBackVB->Lock( 0, sizeof( g_Vertices ), ( void** )&pVertices, 0 ) ) )
		return;
	memcpy( pVertices, g_Vertices, sizeof( g_Vertices ) );
	m_pBackVB->Unlock();
}

HRESULT CDirectX3D::InitObjects()
{
	m_pNodeMgr = new CNodeMgr(m_pD3DDevice);
	m_pCamera  = new CCamera(m_pD3DDevice);

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
	if(m_pBackVB != NULL)
		m_pBackVB->Release();

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
	m_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(180,250,250), 1.0f, 0);

	Animate();

	if(SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
// 		// Render the vertex buffer contents
// 		m_pD3DDevice->SetStreamSource( 0, m_pBackVB, 0, sizeof( CUSTOMVERTEX ) );
// 		m_pD3DDevice->SetFVF( D3DFVF_CUSTOMVERTEX );
// 		m_pD3DDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 1 );

		// mesh 그려주는 작업
		m_pNodeMgr->Draw();

		m_pD3DDevice->EndScene();
	}

	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
