// NodeMgr.cpp : 구현 파일
//

#include "stdafx.h"
#include "NodeMgr.h"

CNodeMgr::CNodeMgr(LPDIRECT3DDEVICE9 pD3DDevice)
{
	m_vOldCtWeight = m_vCtWeight = D3DXVECTOR3(0.f,0.f,0.f);

	m_pD3DDevice = pD3DDevice;
	D3DXMatrixIdentity(&m_matTM);

	m_pLeftZMP =  new CZMP(pD3DDevice, CZMP::LEFT);
	m_pRightZMP = new CZMP(pD3DDevice, CZMP::RIGHT);

	for(int i = 0; i < sizeof(g_meshComponent)/sizeof(MESHCOMPONENT); ++i)
		m_nodes.push_back(new CMesh(m_pD3DDevice, g_meshComponent[i]));
}

CNodeMgr::~CNodeMgr(void)
{
	free(m_pLeftZMP);
	free(m_pRightZMP);

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

	float fx, fy, fz;
	fx = fy = fz = 0.f;
	D3DXMATRIXA16* pMatTemp;
	for(DWORD i = 0; i < m_nodes.size(); ++i)
	{
		id = m_nodes[i]->GetParentID();
		pTM = m_nodes[id]->GetMatrixTM();

		pMatTemp = m_nodes[i]->Animate(pTM);

		if(i == FOOT_L)
			m_pLeftZMP->SetVertics(pMatTemp);
		else if(i == FOOT_R)
			m_pRightZMP->SetVertics(pMatTemp);

		// Calculate Center Of Weight
		fx += pMatTemp->m[3][0];
		fy += (pMatTemp->m[3][1]*m_nodes[i]->GetMass());
		fz += pMatTemp->m[3][2];
	}

	m_vOldCtWeight = m_vCtWeight;

	m_vCtWeight.x = fx/m_nodes.size();
	m_vCtWeight.y = fy/2820.f;
	m_vCtWeight.z = fz/m_nodes.size();	
}

void CNodeMgr::Draw()
{
	for(DWORD i = 0; i < m_nodes.size(); ++i)
	{
		m_nodes[i]->Draw();

// 		if(i == FOOT_L)
// 			m_pLeftZMP->Draw();
// 		else if(i == FOOT_R)
// 			m_pRightZMP->Draw();
		
		m_pD3DDevice->MultiplyTransform(D3DTS_WORLD, &m_matTM);
	}
}

void CNodeMgr::SetAngle(COMPONENT id, float angle)
{
	float y = 0.f;
 
	switch(id)
	{
	case BODY:
		m_nodes[id]->SetOffsetPos(0.f, 0.f, angle);
		break;

	//////////////////////////////////////////////////////////////////////////
	// FOOT
	case FOOT_L: // 위아래로만 까딱까딱
		m_nodes[id]->SetAngle(D3DXMatrixRotationX, angle);
// 		if((y=m_pZmp->Check()) > 0.f)
// 			m_nodes[BODY]->SetPosition(0.f, y/10, 0.f);
		break;
	case FOOT_R:
		m_nodes[id]->SetAngle(D3DXMatrixRotationX, angle);
		break;

	case FOOT_MOTOR_L: // 좌우로
		m_nodes[id]->SetAngle(D3DXMatrixRotationZ, angle);
//		m_nodes[FOOT_L]->SetAngle(D3DXMatrixRotationZ, angle);		// 왜 했는지 까먹엇음.. 안해도 똑같은데... -_ -
		break;
	case FOOT_MOTOR_R:
		m_nodes[id]->SetAngle(D3DXMatrixRotationZ, angle);
//		m_nodes[FOOT_R]->SetAngle(D3DXMatrixRotationZ, angle);
		break;
	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	// LEG
	case LEG_LOW_L:		// 앞뒤로 (무릎)
		m_nodes[id]->SetAngle(D3DXMatrixRotationX, angle);
		break;
	case LEG_LOW_R:
		m_nodes[id]->SetAngle(D3DXMatrixRotationX, angle);
		break;

	case LEG_MIDDLE_L: // 앞뒤로
		m_nodes[id]->SetAngle(D3DXMatrixRotationX, angle);
		break;
	case LEG_MIDDLE_R:
		m_nodes[id]->SetAngle(D3DXMatrixRotationX, angle);
		break;

	case LEG_UPMOTOR_L: // 좌우로
		m_nodes[id]->SetAngle(D3DXMatrixRotationY, angle);
		break;
	case LEG_UPMOTOR_R:
		m_nodes[id]->SetAngle(D3DXMatrixRotationY, angle);
		break;
	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	// ARM
	case ARM_LOW_L: // 좌우로
		m_nodes[id]->SetAngle(D3DXMatrixRotationY, angle);
		break;
	case ARM_LOW_R:
		m_nodes[id]->SetAngle(D3DXMatrixRotationY, angle);
		break;

	case ARM_MIDDLE_L: // 좌우로
		m_nodes[id]->SetAngle(D3DXMatrixRotationY, angle);
		break;
	case ARM_MIDDLE_R: 
		m_nodes[id]->SetAngle(D3DXMatrixRotationY, angle);
		break;

	case ARM_SHOULDER_L: // 좌우로
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

void CNodeMgr::SetWeight()
{
	D3DXMATRIXA16 matTemp;
	D3DXMatrixIdentity(&matTemp);
	matTemp.m[3][0] = m_vCtWeight.x - m_vOldCtWeight.x;
	matTemp.m[3][1] = m_vCtWeight.y - m_vOldCtWeight.y;
	matTemp.m[3][2] = m_vCtWeight.z - m_vOldCtWeight.z;

 	for(DWORD i = 0; i < m_nodes.size(); ++i)
 	{
 		m_nodes[i]->SetWeight(&matTemp);
 	}
}