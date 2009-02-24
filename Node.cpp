//////////////////////////////////////////////////////////////////////////
// Node.cpp
//////////////////////////////////////////////////////////////////////////

#include "AllHeader.h"

CBody g_Body;

CNode::CNode(void) : m_pMesh(NULL), m_pTextures(NULL), m_pMaterials(NULL), m_dwNumMaterials(0)
{
}

CNode::~CNode(void)
{
}

BOOL CBody::InitMesh(LPDIRECT3DDEVICE9 pD3DDevice)
{
	LPD3DXBUFFER pD3DXMtrlBuffer;

	if(FAILED(D3DXLoadMeshFromX(L"BODY.X", D3DXMESH_IB_SYSTEMMEM, pD3DDevice, NULL,
		&pD3DXMtrlBuffer, NULL, &m_dwNumMaterials, &m_pMesh)))
	{
		MessageBox(NULL, L"Could not find Body.X", L"BipedTest.exe", MB_OK);
		return FALSE;
	}

	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)(pD3DXMtrlBuffer);
	m_pMaterials = new D3DMATERIAL9[m_dwNumMaterials];
	m_pTextures = new LPDIRECT3DTEXTURE9[m_dwNumMaterials];

	for(DWORD i = 0; i < m_dwNumMaterials; ++i)
	{
		m_pMaterials[i] = d3dxMaterials[i].MatD3D;

		m_pMaterials[i].Ambient = m_pMaterials[i].Diffuse;

		m_pTextures[i] = NULL;
		if(d3dxMaterials[i].pTextureFilename != NULL && lstrlenA(d3dxMaterials[i].pTextureFilename) > 0)
		{
			if(FAILED(D3DXCreateTextureFromFileA(pD3DDevice, d3dxMaterials[i].pTextureFilename, &m_pTextures[i])))
			{
				const CHAR* strPrefix = "..\\";
				CHAR strTexture[MAX_PATH];
				StringCchCopyA(strTexture, MAX_PATH, strPrefix);
				StringCchCatA(strTexture, MAX_PATH, d3dxMaterials[i].pTextureFilename);
				if(FAILED(D3DXCreateTextureFromFileA(pD3DDevice, strTexture, &m_pTextures[i])))
				{
					MessageBox(NULL, L"Could not find texture map", L"MeshTest.exe", MB_OK);
				}
			}
		}
	}

	pD3DXMtrlBuffer->Release();
	return TRUE;
}

void CBody::Render(LPDIRECT3DDEVICE9 pD3DDevice)
{
	for(DWORD i = 0; i < m_dwNumMaterials; ++i)
	{
		pD3DDevice->SetMaterial(&m_pMaterials[i]);
		pD3DDevice->SetTexture(0, m_pTextures[i]);

		pD3DDevice->SetTransform(D3DTS_WORLD, &m_Matrix);
//		m_pD3DDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );

		m_pMesh->DrawSubset(i);
	}
}

void CBody::AddChild()
{

}

void CBody::SetupMatrices()
{
	D3DXMatrixRotationX(&m_Matrix, timeGetTime()/500.f);
}
