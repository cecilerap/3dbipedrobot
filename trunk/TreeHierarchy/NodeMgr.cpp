//////////////////////////////////////////////////////////////////////////
// NodeMgr.cpp
//////////////////////////////////////////////////////////////////////////

#include "NodeMgr.h"

CNodeMgr::CNodeMgr(LPDIRECT3DDEVICE9 pD3DDevice)
{
	m_pD3DDevice = pD3DDevice;
	D3DXMatrixIdentity(&m_matTM);

	for(int i = 0; i < sizeof(g_meshComponent)/sizeof(MESHCOMPONENT); ++i)
		m_nodes.push_back(new CMesh(m_pD3DDevice, g_meshComponent[i]));
}

CNodeMgr::~CNodeMgr(void)
{
	for(int i = 0; i < sizeof(g_meshComponent)/sizeof(MESHCOMPONENT); ++i)
	{
		if(m_nodes[i] != NULL)
			free(m_nodes[i]);
	}
}

void CNodeMgr::Animate()
{
	int id;
	D3DXMATRIXA16* pTM;

	for(int i = 0; i < m_nodes.size(); ++i)
	{
		id = m_nodes[i]->GetParentID();
		pTM = m_nodes[id]->GetMatrixTM();
		m_nodes[i]->Animate(pTM);
	}
}

void CNodeMgr::Draw()
{
	for(int i = 0; i < m_nodes.size(); ++i)
	{
		m_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matTM);
		m_nodes[i]->Draw();
	}
}