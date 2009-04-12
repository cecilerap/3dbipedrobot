//////////////////////////////////////////////////////////////////////////
// NodeMgr.h
//////////////////////////////////////////////////////////////////////////

#pragma once
#include <vector>
using namespace std;

#include "Node.h"
#include "Mesh.h"
#include "ZMP.h"

class CNodeMgr
{
public:
	CNodeMgr(LPDIRECT3DDEVICE9 pD3DDevice);
	~CNodeMgr(void);

	void Animate();
	void Draw();

	void SetAngle(COMPONENT id, float angle);

	CNode* GetNodes(COMPONENT id) { return m_nodes[id]; }

protected:
	vector<CNode*> m_nodes;

	LPDIRECT3DDEVICE9 m_pD3DDevice;
	D3DXMATRIXA16 m_matTM;

	D3DXMATRIXA16* m_pLFootTM;
	D3DXMATRIXA16* m_pRFootTM;

	CZMP* m_pZmp;
};
