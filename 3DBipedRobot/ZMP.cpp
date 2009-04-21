// ZMP.cpp : 구현 파일
//

#include "stdafx.h"
#include "ZMP.h"

D3DXVECTOR3 g_constPos[2][4] = 
{
	{
		D3DXVECTOR3(-4.768f,0.017f,-23.719f), D3DXVECTOR3(-4.774f,0.017f, 0.f),
		D3DXVECTOR3(13.316f,0.017f,  0.f),    D3DXVECTOR3(13.316f,0.017f,-23.716f)
	},
	{
		D3DXVECTOR3(-16.280f,-0.027f,-23.546f), D3DXVECTOR3(-16.312f,-0.027f,  0.f),
		D3DXVECTOR3( -4.010f,-0.027f,  0.f),    D3DXVECTOR3( -4.010f,-0.027f,-23.811f)
	}
};

CZMP::CZMP(LPDIRECT3DDEVICE9 pD3DDevice, DIR dir)
{
	m_pD3DDevice = pD3DDevice;

	for(int i = 0; i < 4; ++i)
		m_pSensor[i]   = new CForceSensor(pD3DDevice, g_constPos[dir][i]);
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

//	m_pSensor[0]->SetVertex(pMatTM);
}

void CZMP::Draw()
{
	for(int i = 0; i < 3; ++i)
	{
		if(m_pSensor[i]->Check() > 0)
			m_pSensor[i]->Draw();
	}

// 	if(m_pSensor[0]->Check() > 0)
// 		m_pSensor[0]->Draw();
}

UINT CZMP::Check()
{
	UINT ret = 0;
	float checkValue;
	for(int i = 0; i < 4; ++i)
	{
		checkValue = m_pSensor[i]->Check();
		ret <<= 8;
		if(checkValue > 0)		// 0보다 크면 땅에 닿음, 0보다 작으면 땅보다 위
			ret |= 0xFF;
	}

	return ret;
	
	
// 	// 지금 현재 발은 어느 한부분이 더 올라가거나 하지 않으므로
// 	// 한군데라도 위에 올라가면 전체가 올라간 것으로 판단한다!
// 	return m_pSensor[0]->Check();

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