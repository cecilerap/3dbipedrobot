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
#pragma comment(lib, "winmm.lib")
void CNodeMgr::Animate()
{
	int id;
	D3DXMATRIXA16* pTM;

	for(DWORD i = 0; i < m_nodes.size(); ++i)
	{
		id = m_nodes[i]->GetParentID();
		pTM = m_nodes[id]->GetMatrixTM();

		
		//////////////////////////////////////////////////////////////////////////
//		m_nodes[i]->SetAngle(timeGetTime()/2000.f);
		//////////////////////////////////////////////////////////////////////////
		
		m_nodes[i]->Animate(pTM);
	}
}

void CNodeMgr::Draw()
{
	for(DWORD i = 0; i < m_nodes.size(); ++i)
	{
		m_pD3DDevice->MultiplyTransform(D3DTS_WORLD, &m_matTM);
		m_nodes[i]->Draw();
	}
}

void CNodeMgr::SetAngle(COMPONENT id, float angle)
{
	angle *= 0.29f;		// 300/1024*angle 모터가 움직일 각도(?)

	switch(id)
	{
	case FOOT_L:
	case FOOT_R: // 위아래로만 까딱까딱
		if(angle < -0.5f)	angle = -0.5f;
		if(angle >  0.5f)	angle =  0.5f;
		m_nodes[id]->SetAngle(D3DXMatrixRotationX, angle);
		break;
	case FOOT_MOTOR_L: // 좌우로
	case FOOT_MOTOR_R:
		if(angle < -0.5f)	angle = -0.5f;
		if(angle >  0.5f)	angle =  0.5f;
		m_nodes[id]->SetAngle(D3DXMatrixRotationZ, angle);
		break;
	case LEG_LOW_L: // 앞뒤로 (무릎)
	case LEG_LOW_R:
		if(angle <   0.f)	angle =   0.f;
		if(angle >   2.f)	angle =   2.f;
		m_nodes[id]->SetAngle(D3DXMatrixRotationX, angle);
		break;
	case LEG_MIDDLE_L: // 앞뒤로
	case LEG_MIDDLE_R:
		if(angle <  -1.f)	angle =  -1.f;
		if(angle >   0.f)	angle =   0.f;
		m_nodes[id]->SetAngle(D3DXMatrixRotationX, angle);
		break;
	case LEG_UPMOTOR_L: // 좌우로
		if(angle <-0.05f)	angle =-0.05f;
		if(angle >   1.f)	angle =   1.f;
		m_nodes[id]->SetAngle(D3DXMatrixRotationY, angle);
		break;
	case LEG_UPMOTOR_R:
		if(angle <  -1.f)	angle =  -1.f;
		if(angle > 0.05f)	angle = 0.05f;
		m_nodes[id]->SetAngle(D3DXMatrixRotationY, angle);
		break;
	case ARM_LOW_L: // 좌우로
	case ARM_LOW_R:
		if(angle < -0.3f)	angle = -0.3f;
		if(angle >  0.3f)	angle =  0.3f;
		m_nodes[id]->SetAngle(D3DXMatrixRotationY, angle);
		break;
	case ARM_MIDDLE_L: // 좌우로
		if(angle < -0.1f)	angle = -0.1f;
		if(angle >  0.3f)	angle =  0.3f;
		m_nodes[id]->SetAngle(D3DXMatrixRotationY, angle);
		break;
	case ARM_MIDDLE_R: 
		if(angle < -0.3f)	angle = -0.3f;
		if(angle >  0.1f)	angle =  0.1f;
		m_nodes[id]->SetAngle(D3DXMatrixRotationY, angle);
		break;
	case ARM_SHOULDER_L: // 좌우로
	case ARM_SHOULDER_R: 
// 		if(angle < -0.3f)	angle = -0.3f;
// 		if(angle >  0.3f)	angle =  0.3f;
		m_nodes[id]->SetAngle(D3DXMatrixRotationX, angle);
		break;
	}
}