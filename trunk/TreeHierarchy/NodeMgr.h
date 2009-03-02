//////////////////////////////////////////////////////////////////////////
// NodeMgr.h
//////////////////////////////////////////////////////////////////////////

#pragma once
#include <vector>
using namespace std;

#include "Node.h"
#include "Mesh.h"

class CNodeMgr
{
public:
	CNodeMgr(LPDIRECT3DDEVICE9 pD3DDevice);
	~CNodeMgr(void);

	void Animate();
	void Draw();

protected:
	vector<CNode*> m_nodes;

	LPDIRECT3DDEVICE9 m_pD3DDevice;
	D3DXMATRIXA16 m_matTM;
};
