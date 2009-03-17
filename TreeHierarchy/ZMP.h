//////////////////////////////////////////////////////////////////////////
// ZMP.h
//////////////////////////////////////////////////////////////////////////

#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "NodeMgr.h"

class CZMP
{
public:
	CZMP(LPDIRECT3DDEVICE9 pD3DDevice);
	~CZMP(void);

	void SetNodeMgr(vector<CNode*> nodes)	{ m_Nodes = nodes; }

	void Check();

private:
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	vector<CNode*> m_Nodes;
};
