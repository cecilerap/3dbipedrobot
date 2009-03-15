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
	float m_angle = timeGetTime()/2000.f;

	switch(id)
	{
	//////////////////////////////////////////////////////////////////////////
	// FOOT
	case FOOT_L: // À§¾Æ·¡·Î¸¸ ±îµü±îµü
//		angle -= (137.75f + 0.2f);
// 		if(angle < -0.5f)	angle = -0.5f;
// 		if(angle >  0.5f)	angle =  0.5f;
		m_nodes[id]->SetAngle(D3DXMatrixRotationX, angle);
		break;
	case FOOT_R:
//		angle -= (179.8f + 0.2f);
// 		if(angle < -0.5f)	angle = -0.5f;
// 		if(angle >  0.5f)	angle =  0.5f;
		m_nodes[id]->SetAngle(D3DXMatrixRotationX, angle);
		break;

	case FOOT_MOTOR_L: // ÁÂ¿ì·Î
//		angle -= 155.15f;
// 		if(angle < -0.5f)	angle = -0.5f;
// 		if(angle >  0.5f)	angle =  0.5f;
		m_nodes[id]->SetAngle(D3DXMatrixRotationZ, angle);
		break;
	case FOOT_MOTOR_R:
//		angle -= 137.75f;
// 		if(angle < -0.5f)	angle = -0.5f;
// 		if(angle >  0.5f)	angle =  0.5f;
		m_nodes[id]->SetAngle(D3DXMatrixRotationZ, angle);
		break;
	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	// LEG
	case LEG_LOW_L: // ¾ÕµÚ·Î (¹«¸­)
//		angle -= (121.80f - 0.8f);
// 		if(angle <   0.f)	angle =   0.f;
// 		if(angle >   2.f)	angle =   2.f;
		m_nodes[id]->SetAngle(D3DXMatrixRotationX, angle);
		break;
	case LEG_LOW_R:
// 		angle -= (194.3f - 0.8f);
// 		if(angle <   0.f)	angle =   0.f;
// 		if(angle >   2.f)	angle =   2.f;
		m_nodes[id]->SetAngle(D3DXMatrixRotationX, angle);
		break;

	case LEG_MIDDLE_L: // ¾ÕµÚ·Î
// 		angle -= (134.85f + 0.6f);
// 		if(angle <  -1.f)	angle =  -1.f;
// 		if(angle >   0.f)	angle =   0.f;
		m_nodes[id]->SetAngle(D3DXMatrixRotationX, angle);
		break;
	case LEG_MIDDLE_R:
// 		angle -= (160.95f + 0.6f);
// 		if(angle <  -1.f)	angle =  -1.f;
// 		if(angle >   0.f)	angle =   0.f;
		m_nodes[id]->SetAngle(D3DXMatrixRotationX, angle);
		break;

	case LEG_UPMOTOR_L: // ÁÂ¿ì·Î
// 		angle -= 137.75f;
// 		if(angle <-0.05f)	angle =-0.05f;
// 		if(angle >   1.f)	angle =   1.f;
		m_nodes[id]->SetAngle(D3DXMatrixRotationY, angle);
		break;
	case LEG_UPMOTOR_R:
// 		angle -= 156.6f;
// 		if(angle <  -1.f)	angle =  -1.f;
// 		if(angle > 0.05f)	angle = 0.05f;
		m_nodes[id]->SetAngle(D3DXMatrixRotationY, angle);
		break;
	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	// ARM
	case ARM_LOW_L: // ÁÂ¿ì·Î
// 		angle -= 150.51f;
// 		if(angle < -0.3f)	angle = -0.3f;
// 		if(angle >  0.3f)	angle =  0.3f;
		m_nodes[id]->SetAngle(D3DXMatrixRotationY, angle);
		break;
	case ARM_LOW_R:
// 		angle -= 149.06f;
// 		if(angle < -0.3f)	angle = -0.3f;
// 		if(angle >  0.3f)	angle =  0.3f;
		m_nodes[id]->SetAngle(D3DXMatrixRotationY, angle);
		break;

	case ARM_MIDDLE_L: // ÁÂ¿ì·Î
// 		angle -= 149.06f;
// 		if(angle < -0.1f)	angle = -0.1f;
// 		if(angle >  0.3f)	angle =  0.3f;
		m_nodes[id]->SetAngle(D3DXMatrixRotationY, angle);
		break;
	case ARM_MIDDLE_R: 
// 		angle -= 150.51f;
// 		if(angle < -0.3f)	angle = -0.3f;
// 		if(angle >  0.1f)	angle =  0.1f;
		m_nodes[id]->SetAngle(D3DXMatrixRotationY, angle);
		break;

	case ARM_SHOULDER_L: // ÁÂ¿ì·Î
//		angle -= 138.62f;
// 		if(angle < -0.3f)	angle = -0.3f;
// 		if(angle >  0.3f)	angle =  0.3f;
		m_nodes[id]->SetAngle(D3DXMatrixRotationX, angle);
		break;
	case ARM_SHOULDER_R: 
//		angle -= 158.05f;
// 		if(angle < -0.3f)	angle = -0.3f;
// 		if(angle >  0.3f)	angle =  0.3f;
		m_nodes[id]->SetAngle(D3DXMatrixRotationX, angle);
		break;
	//////////////////////////////////////////////////////////////////////////

	default:
		break;
	}
}