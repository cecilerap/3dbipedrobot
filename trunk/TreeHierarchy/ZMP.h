//////////////////////////////////////////////////////////////////////////
// ZMP.h
//////////////////////////////////////////////////////////////////////////

#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "Node.h"

struct CUSTOMVERTEXFOOT
{
	D3DXVECTOR3 position;
	D3DXCOLOR color;
};

class CZMP
{
public:
	enum DIR{LEFT, RIGHT};
public:
	CZMP(LPDIRECT3DDEVICE9 pD3DDevice);
	~CZMP(void);

	void SetVertics(DIR dir, D3DXMATRIXA16* pMatTM);
	void Initialize();
	void Draw();

private:
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	
	D3DXVECTOR3 m_pos[2][4];
//	D3DXVECTOR3 m_endPos[2][4];

	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	CUSTOMVERTEXFOOT m_Vertics[2][5];
};