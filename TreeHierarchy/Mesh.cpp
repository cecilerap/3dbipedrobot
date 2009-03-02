//////////////////////////////////////////////////////////////////////////
// Mesh.cpp
//////////////////////////////////////////////////////////////////////////

#include "Mesh.h"

CMesh::CMesh(LPDIRECT3DDEVICE9 pD3DDevice, MESHCOMPONENT meshComponent) 
: CNode(pD3DDevice, meshComponent), m_pMesh(NULL), m_pTextures(NULL), m_pMaterials(NULL), m_dwNumMaterials(0)
{
	LoadMesh(meshComponent.str);
}

CMesh::~CMesh(void)
{
}

void CMesh::LoadMesh(TCHAR* str)
{
	if(wcscmp(str ,L"NULL") == 0)
		return;

	LPD3DXBUFFER pD3DXMtrlBuffer;

	TCHAR strTemp[32] = {0,};
	wsprintfW(strTemp, L"X\\%s", str);
	if(FAILED(D3DXLoadMeshFromX(strTemp, D3DXMESH_IB_SYSTEMMEM, m_pD3DDevice, NULL,
								&pD3DXMtrlBuffer, NULL, &m_dwNumMaterials, &m_pMesh)))
	{
		MessageBox(NULL, strTemp, L"BipedTest.exe", MB_OK);
		return;
	}

	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)(pD3DXMtrlBuffer);
	m_pMaterials = new D3DMATERIAL9[m_dwNumMaterials];
	m_pTextures = new LPDIRECT3DTEXTURE9[m_dwNumMaterials];

	for(int i = 0; i < m_dwNumMaterials; ++i)
	{
		m_pMaterials[i] = d3dxMaterials[i].MatD3D;

		m_pMaterials[i].Ambient = m_pMaterials[i].Diffuse;

		m_pTextures[i] = NULL;
		if(d3dxMaterials[i].pTextureFilename != NULL && lstrlenA(d3dxMaterials[i].pTextureFilename) > 0)
		{
			if(FAILED(D3DXCreateTextureFromFileA(m_pD3DDevice, d3dxMaterials[i].pTextureFilename, &m_pTextures[i])))
			{
				return;
			}
		}
	}

	pD3DXMtrlBuffer->Release();
}

void CMesh::Draw()
{
	for(int i = 0; i < m_dwNumMaterials; ++i)
	{
		m_pD3DDevice->SetMaterial(&m_pMaterials[i]);
		m_pD3DDevice->SetTexture(0, m_pTextures[i]);

		m_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matTM);

		m_pMesh->DrawSubset(i);
	}
}