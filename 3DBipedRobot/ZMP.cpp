// ZMP.cpp : 구현 파일
//

#include "stdafx.h"
#include "ZMP.h"

D3DXVECTOR3 g_constPos[2][4] = 
{
	{
		D3DXVECTOR3( 1.f,0.f,-32.5f), D3DXVECTOR3( 1.f,0.f, -6.f),
		D3DXVECTOR3(15.f,0.f, -6.f),  D3DXVECTOR3(15.f,0.f,-33.f)
	},
	{
		D3DXVECTOR3(-18.f,0.f,-33.f), D3DXVECTOR3(-18.f,0.f, -6.f),
		D3DXVECTOR3( -4.f,0.f, -6.f), D3DXVECTOR3( -4.f,0.f,-33.f)
	}
};

CZMP::CZMP(LPDIRECT3DDEVICE9 pD3DDevice, DIR dir)
{
	m_pD3DDevice = pD3DDevice;

	for(int i = 0; i < 4; ++i)
		m_pSensor[i] = new CForceSensor(pD3DDevice, g_constPos[dir][i]);
}

CZMP::~CZMP(void)
{
	for(int i = 0; i < 4; ++i)
		free(m_pSensor[i]);
}

void CZMP::SetVertics(D3DXMATRIXA16* pMatTM)
{
	float fx = 0.f, fy = 0.f;
	for(int i = 0; i < 4; ++i)
	{
		m_pSensor[i]->SetVertex(pMatTM);
		fx += m_pSensor[i]->m_vEndPoint.x;
		fy += m_pSensor[i]->m_vEndPoint.y;
	}

	fx /= 4.f;
	fy /= 4.f;

	m_vAver = D3DXVECTOR3(fx, fy, 0.f);
}

void CZMP::Draw()
{
	for(int i = 0; i < 4; ++i)
	{
			m_pSensor[i]->Draw();
	}
}

// UINT CZMP::Check()
// {
// 	UINT ret = 0;
// 	float checkValue;
// 	for(int i = 0; i < 4; ++i)
// 	{
// 		checkValue = m_pSensor[i]->Check();
// 		ret <<= 8;
// 		if(checkValue > 0)		// 0보다 크면 땅에 닿음, 0보다 작으면 땅보다 위
// 			ret |= 0xFF;
// 	}
// 
// 	return ret;
// }

float CZMP::Check()
{
	UINT ret = 0;
	float checkValue = m_pSensor[0]->Check();
	return checkValue;
}