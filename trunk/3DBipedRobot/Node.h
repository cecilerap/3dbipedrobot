//////////////////////////////////////////////////////////////////////////
// Node.h
//////////////////////////////////////////////////////////////////////////

#pragma once

class CNode
{
public:
	CNode(TCHAR* str);
	~CNode();

	BOOL InitMesh(LPDIRECT3DDEVICE9 pD3DDevice);
	void Render(LPDIRECT3DDEVICE9 pD3DDevice);
	void SetupMatrices();

	void AddChild(LPDIRECT3DDEVICE9 pD3DDevice, CNode* node);
	void CleanUp();

private:
	TCHAR m_str[128];
	D3DXMATRIXA16 m_Matrix;
	D3DXMATRIXA16 m_MatView;

	LPD3DXMESH m_pMesh;	
	LPDIRECT3DTEXTURE9* m_pTextures;
	D3DMATERIAL9* m_pMaterials;
	DWORD m_dwNumMaterials;

	CNode* m_pParent;
	CNode* m_pChild;
};