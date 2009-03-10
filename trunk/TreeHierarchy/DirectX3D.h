//////////////////////////////////////////////////////////////////////////
// DirectX3D.h
//////////////////////////////////////////////////////////////////////////

#pragma once
#include <d3d9.h>
#include <d3dx9.h>

#include "NodeMgr.h"
#include "Camera.h"
#include "Simulate.h"

#define WINDOW_WIDTH		800
#define WINDOW_HEIGHT		800


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
	void InitXYZVertex();
	void DeleteObjects();
	void Cleanup();

	void Animate();
	void Render();

public:
	CCamera* m_pCamera;

private:
	HWND m_hWnd;
	LPDIRECT3D9 m_pD3D;
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	LPDIRECT3DVERTEXBUFFER9 m_pXYZVB;

	D3DXMATRIXA16 m_matWorld;
	D3DXMATRIXA16 m_matView;
	D3DXMATRIXA16 m_matProj;

	CNodeMgr* m_pNodeMgr;
	CSimulate* m_pSimul;
};
