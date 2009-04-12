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
	enum DIR{LEFT, RIGHT};
public:
	CZMP(LPDIRECT3DDEVICE9 pD3DDevice);
	~CZMP(void);

	void SetVertics(DIR dir, D3DXMATRIXA16* pMatTM);
	void Draw(DIR dir);

private:
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	
	D3DXVECTOR3 m_pos[2][4];

public:
	CForceSensor* m_pSensor[8];
};