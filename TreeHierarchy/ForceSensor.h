//////////////////////////////////////////////////////////////////////////
// ForceSensor.h
//////////////////////////////////////////////////////////////////////////

#pragma once
#include <d3d9.h>
#include <d3dx9.h>

struct CUSTOMVERTEXFOOT
{
	D3DXVECTOR3 position;
	D3DXCOLOR color;
};

class CForceSensor
{
public:
	CForceSensor(LPDIRECT3DDEVICE9 pD3DDevice, D3DXVECTOR3 vec);
	~CForceSensor(void);

	void Draw();
	void SetVertex(D3DXMATRIXA16* pMatTM);

private:
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	D3DXVECTOR3 m_vec;

	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	CUSTOMVERTEXFOOT m_Vertics[5];
};
