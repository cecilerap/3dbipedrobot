//////////////////////////////////////////////////////////////////////////
// NodeMgr.cpp
//////////////////////////////////////////////////////////////////////////

#include "NodeMgr.h"

CNodeMgr::CNodeMgr(LPDIRECT3DDEVICE9 pD3DDevice)
{
	m_pD3DDevice = pD3DDevice;
	D3DXMatrixIdentity(&m_matTM);

	m_pZmp = new CZMP(pD3DDevice);

	for(int i = 0; i < sizeof(g_meshComponent)/sizeof(MESHCOMPONENT); ++i)
		m_nodes.push_back(new CMesh(m_pD3DDevice, g_meshComponent[i]));
}

CNodeMgr::~CNodeMgr(void)
{
	free(m_pZmp);

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

	for(DWORD i = 0; i < m_nodes.size(); ++i)
	{
		id = m_nodes[i]->GetParentID();
		pTM = m_nodes[id]->GetMatrixTM();

		if(i == FOOT_L)
			m_pZmp->SetVertics(CZMP::LEFT, m_nodes[i]->Animate(pTM));
		else if(i == FOOT_R)
			m_pZmp->SetVertics(CZMP::RIGHT, m_nodes[i]->Animate(pTM));
		else
			m_nodes[i]->Animate(pTM);
	}
}

void CNodeMgr::Draw()
{
	for(DWORD i = 0; i < m_nodes.size(); ++i)
	{
		m_nodes[i]->Draw();

		if(i == FOOT_L)
			m_pZmp->Draw(CZMP::LEFT);
		else if(i == FOOT_R)
			m_pZmp->Draw(CZMP::RIGHT);
		
		m_pD3DDevice->MultiplyTransform(D3DTS_WORLD, &m_matTM);
	}

//	m_pZmp->Draw();
//	m_pD3DDevice->MultiplyTransform(D3DTS_WORLD, &m_matTM);
}

void CNodeMgr::SetAngle(COMPONENT id, float angle)
{
 	if(m_pZmp->Check() > 0.f)
 		return;

	switch(id)
	{
	case BODY:
		m_nodes[id]->SetPosition(0.f, 0.f, angle);
		break;

	//////////////////////////////////////////////////////////////////////////
	// FOOT
	case FOOT_L: // À§¾Æ·¡·Î¸¸ ±îµü±îµü
		m_nodes[id]->SetAngle(D3DXMatrixRotationX, angle);
		break;
	case FOOT_R:
		m_nodes[id]->SetAngle(D3DXMatrixRotationX, angle);
		break;

	case FOOT_MOTOR_L: // ÁÂ¿ì·Î
		m_nodes[id]->SetAngle(D3DXMatrixRotationZ, angle);
//		m_nodes[FOOT_L]->SetAngle(D3DXMatrixRotationZ, angle);		// ¿Ö Çß´ÂÁö ±î¸Ô¾ùÀ½.. ¾ÈÇØµµ ¶È°°Àºµ¥... -_ -
		break;
	case FOOT_MOTOR_R:
		m_nodes[id]->SetAngle(D3DXMatrixRotationZ, angle);
//		m_nodes[FOOT_R]->SetAngle(D3DXMatrixRotationZ, angle);
		break;
	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	// LEG
	case LEG_LOW_L:		// ¾ÕµÚ·Î (¹«¸­)
		m_nodes[id]->SetAngle(D3DXMatrixRotationX, angle);
		break;
	case LEG_LOW_R:
		m_nodes[id]->SetAngle(D3DXMatrixRotationX, angle);
		break;

	case LEG_MIDDLE_L: // ¾ÕµÚ·Î
		m_nodes[id]->SetAngle(D3DXMatrixRotationX, angle);
		break;
	case LEG_MIDDLE_R:
		m_nodes[id]->SetAngle(D3DXMatrixRotationX, angle);
		break;

	case LEG_UPMOTOR_L: // ÁÂ¿ì·Î
		m_nodes[id]->SetAngle(D3DXMatrixRotationY, angle);
		break;
	case LEG_UPMOTOR_R:
		m_nodes[id]->SetAngle(D3DXMatrixRotationY, angle);
		break;
	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	// ARM
	case ARM_LOW_L: // ÁÂ¿ì·Î
		m_nodes[id]->SetAngle(D3DXMatrixRotationY, angle);
		break;
	case ARM_LOW_R:
		m_nodes[id]->SetAngle(D3DXMatrixRotationY, angle);
		break;

	case ARM_MIDDLE_L: // ÁÂ¿ì·Î
		m_nodes[id]->SetAngle(D3DXMatrixRotationY, angle);
		break;
	case ARM_MIDDLE_R: 
		m_nodes[id]->SetAngle(D3DXMatrixRotationY, angle);
		break;

	case ARM_SHOULDER_L: // ÁÂ¿ì·Î
		m_nodes[id]->SetAngle(D3DXMatrixRotationX, angle);
		break;
	case ARM_SHOULDER_R: 
		m_nodes[id]->SetAngle(D3DXMatrixRotationX, angle);
		break;
	//////////////////////////////////////////////////////////////////////////

	default:
		break;
	}
}