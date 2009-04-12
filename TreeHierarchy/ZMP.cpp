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
		m_pSensor[i]   = new CForceSensor(pD3DDevice, m_pos[LEFT][i]);
		m_pSensor[i+4] = new CForceSensor(pD3DDevice, m_pos[RIGHT][i]);
	}
}

CZMP::~CZMP(void)
{
	for(int i = 0; i < 8; ++i)
		free(m_pSensor[i]);
}

void CZMP::SetVertics(DIR dir, D3DXMATRIXA16* pMatTM)
{
	int i = (dir == LEFT ? 0 : 4);
	int end = (dir == LEFT ? 4 : 8);
	for( ; i < end; ++i)
		m_pSensor[i]->SetVertex(pMatTM);
}

void CZMP::Draw(DIR dir)
{
	int i = (dir == LEFT ? 0 : 4);
	int end = (dir == LEFT ? 4 : 8);
	for( ; i < end; ++i)
		m_pSensor[i]->Draw();
}