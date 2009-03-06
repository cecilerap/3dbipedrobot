//////////////////////////////////////////////////////////////////////////
// DirectX3D.h
//////////////////////////////////////////////////////////////////////////

#pragma once
#include <d3d9.h>
#include <d3dx9.h>

#include "NodeMgr.h"

#define WINDOW_WIDTH		800
#define WINDOW_HEIGHT		800
enum MOUSE{DOWN, UP, MOVE};

struct CAMERA
{
	LPDIRECT3DDEVICE9 m_pD3DDevice;

	D3DXVECTOR3 m_vEyePt;			// ´«ÀÇ À§Ä¡
	D3DXVECTOR3 m_vLookatPt;		// ´«ÀÌ ¹Ù¶óº¸´Â À§Ä¡
	D3DXVECTOR3 m_vUpVec;			// »ó¹æ º¤ÅÍ

	struct CAMERA(LPDIRECT3DDEVICE9 pD3DDevice) 
		: m_pD3DDevice(pD3DDevice), m_vEyePt(0.0f, 0.0f, -300.0f), m_vLookatPt(0.0f, 0.0f, 0.0f), m_vUpVec(0.0f, 1.0f, 0.0f) {}

	void SetCamera()
	{
		D3DXMATRIXA16 matView;
		D3DXMatrixLookAtLH(&matView, &m_vEyePt, &m_vLookatPt, &m_vUpVec);
		m_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);
	}
};

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

	void SetMousePos(int x, int y);
	void CameraMove(int x, int y);
	void CameraZoom(int nWheel);

private:
	LPDIRECT3D9 m_pD3D;
	LPDIRECT3DDEVICE9 m_pD3DDevice;

	D3DXMATRIXA16 m_matWorld;
	D3DXMATRIXA16 m_matView;
	D3DXMATRIXA16 m_matProj;

	CNodeMgr* m_pNodeMgr;

	CAMERA* m_pCamera;

	POINT m_curPt;
};
