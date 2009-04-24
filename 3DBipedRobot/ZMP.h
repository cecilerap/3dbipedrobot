//////////////////////////////////////////////////////////////////////////
// ZMP.h
//////////////////////////////////////////////////////////////////////////

#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "ForceSensor.h"

class CZMP
{
public:
	enum DIR{LEFT = 0, RIGHT = 1};
public:
	CZMP(LPDIRECT3DDEVICE9 pD3DDevice, DIR dir);
	~CZMP(void);

	void SetVertics(D3DXMATRIXA16* pMatTM);
	void Draw();

	float Check();

private:
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	D3DXVECTOR3 m_pos[4];
	CForceSensor* m_pSensor[4];

	D3DXVECTOR3 m_vAver;
};
