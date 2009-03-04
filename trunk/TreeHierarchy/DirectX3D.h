//////////////////////////////////////////////////////////////////////////
// DirectX3D.h
//////////////////////////////////////////////////////////////////////////

#pragma once
#include <d3d9.h>
#include <d3dx9.h>

#include "NodeMgr.h"
#include "Camera.h"

#define WINDOW_WIDTH		800
#define WINDOW_HEIGHT		800
enum MOUSE{DOWN, UP, MOVE};

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

	void SetMousePos(int x, int y) { m_curPt.x = x, m_curPt.y = y; }
	void FrameMove(MOUSE mouse, int x, int y);
	void FrameRotate(int x, int y);
	void FrameZoom(MOUSE mouse);

private:
	LPDIRECT3D9 m_pD3D;
	LPDIRECT3DDEVICE9 m_pD3DDevice;

	D3DXMATRIXA16 m_matWorld;
	D3DXMATRIXA16 m_matView;
	D3DXMATRIXA16 m_matProj;

	CNodeMgr* m_pNodeMgr;
	CCamera* m_pCamera;

	POINT m_curPt;
	BOOL m_bMove;
};
