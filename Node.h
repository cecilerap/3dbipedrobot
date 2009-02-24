//////////////////////////////////////////////////////////////////////////
// Node.h
//////////////////////////////////////////////////////////////////////////

#pragma once

class CNode
{
public:
	CNode(void);
	~CNode(void);

	BOOL InitMesh() {}
	void Render() {}
	void AddChild() {}

protected:
	D3DXMATRIXA16 m_Matrix;

	LPD3DXMESH m_pMesh;	
	LPDIRECT3DTEXTURE9* m_pTextures;
	D3DMATERIAL9* m_pMaterials;
	DWORD m_dwNumMaterials;

	CNode* m_parent;
	CNode* m_child;
};

class CBody : public CNode
{
public:
	CBody() : CNode() {}
	~CBody() {}

	BOOL InitMesh(LPDIRECT3DDEVICE9 pD3DDevice);
	void Render(LPDIRECT3DDEVICE9 pD3DDevice);
	void AddChild();

	void SetupMatrices();
};