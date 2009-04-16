//////////////////////////////////////////////////////////////////////////
// ZMP.cpp
//////////////////////////////////////////////////////////////////////////

#include "ZMP.h"

CZMP::CZMP(LPDIRECT3DDEVICE9 pD3DDevice)
{
	m_pD3DDevice = pD3DDevice;

	m_pos[0][0].x =  0.768f, m_pos[0][0].y = 0.017f, m_pos[0][0].z = -23.719f;
	m_pos[0][1].x =  0.774f, m_pos[0][1].y = 0.017f, m_pos[0][1].z =   0.f;
	m_pos[0][2].x = 13.316f, m_pos[0][2].y = 0.017f, m_pos[0][2].z =   0.f;
	m_pos[0][3].x = 13.316f, m_pos[0][3].y = 0.017f, m_pos[0][3].z = -23.716f;

	m_pos[1][0].x = -16.280f, m_pos[1][0].y = -0.027f, m_pos[1][0].z = -23.546f;
	m_pos[1][1].x = -16.312f, m_pos[1][1].y = -0.027f, m_pos[1][1].z =   0.f;
	m_pos[1][2].x =  -4.010f, m_pos[1][2].y = -0.027f, m_pos[1][2].z =   0.f;
	m_pos[1][3].x =  -4.010f, m_pos[1][3].y = -0.027f, m_pos[1][3].z = -23.811f;

	for(int i = 0; i < 4; ++i)
	{
		m_pSensor[i]   = new CForceSensor(pD3DDevice, m_pos[0][i]);
		m_pSensor[i+4] = new CForceSensor(pD3DDevice, m_pos[1][i]);
	}
}

CZMP::~CZMP(void)
{
	for(int i = 0; i < 8; ++i)
		free(m_pSensor[i]);
}

void CZMP::SetVertics(DIR dir, D3DXMATRIXA16* pMatTM)
{
	for(int i = (int)dir; i < dir+4; ++i)
		m_pSensor[i]->SetVertex(pMatTM);
}

void CZMP::Draw(DIR dir)
{
	for(int i = (int)dir; i < dir+4; ++i)
		m_pSensor[i]->Draw();
}

float CZMP::Check()
{
	// 지금 현재 발은 어느 한부분이 더 올라가거나 하지 않으므로
	// 한군데라도 위에 올라가면 전체가 올라간 것으로 판단한다!
	return m_pSensor[0]->Check();

// 	int checkValue = 0;
// 	for(int i = 0; i < 8; ++i)
// 	{
// 		checkValue = m_pSensor[i]->Check();
// 		if(checkValue > 0)
// 			break;
// 	}
//
//	return checkValue;
}