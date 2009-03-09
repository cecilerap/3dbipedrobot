//////////////////////////////////////////////////////////////////////////
// Camera.h
//////////////////////////////////////////////////////////////////////////

#pragma once
#include <d3d9.h>
#include <d3dx9.h>

class CCamera
{
public:
	CCamera(LPDIRECT3DDEVICE9 pD3DDevice)
		: m_pD3DDevice(pD3DDevice), m_vEyePt(0.0f, 0.0f, -300.0f), m_vLookatPt(0.0f, 0.0f, 0.0f), m_vUpVec(0.0f, 1.0f, 0.0f) {}
	~CCamera(void) {}

	void SetCamera();
	void SetMousePos(int x, int y);
	
	void Move(int x, int y);
	void Zoom(int nWheel);

public:
	D3DXVECTOR3 m_vEyePt;			// 눈의 위치
	D3DXVECTOR3 m_vLookatPt;		// 눈이 바라보는 위치
	D3DXVECTOR3 m_vUpVec;			// 상방 벡터

private:
	LPDIRECT3DDEVICE9 m_pD3DDevice;

	POINT m_curPt;
};