//////////////////////////////////////////////////////////////////////////
// DirectX3D.h
//////////////////////////////////////////////////////////////////////////

#pragma once
#include <d3d9.h>
#include <d3dx9.h>

#include "NodeMgr.h"

class CDirectX3D
{
public:
	CDirectX3D(void);
	~CDirectX3D(void);

	HRESULT InitD3D(HWND hWnd);
	HRESULT InitGeometry();
	HRESULT InitObjects();
	void InitMatrix();
	void InitLights();
	void DeleteObjects();
	void Cleanup();

	void Animate();
	void Render();

private:
	LPDIRECT3D9 m_pD3D;
	LPDIRECT3DDEVICE9 m_pD3DDevice;

	D3DXMATRIXA16 m_matWorld;
	D3DXMATRIXA16 m_matView;
	D3DXMATRIXA16 m_matProj;

	CNodeMgr* m_pNodeMgr;
};
