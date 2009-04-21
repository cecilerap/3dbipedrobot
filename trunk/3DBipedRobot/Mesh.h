//////////////////////////////////////////////////////////////////////////
// Mesh.h
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "Node.h"

class CMesh : public CNode
{
public:
	CMesh(LPDIRECT3DDEVICE9 pD3DDevice, MESHCOMPONENT meshComponent);
	~CMesh(void);

	void LoadMesh(TCHAR* str);
	void Draw();

private:
	LPD3DXMESH m_pMesh;	
	LPDIRECT3DTEXTURE9* m_pTextures;
	D3DMATERIAL9* m_pMaterials;
	DWORD m_dwNumMaterials;
};
