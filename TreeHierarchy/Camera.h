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
		: m_pD3DDevice(pD3DDevice), m_posTheta(270.f), m_posPhi(0.f), m_radius(300.f) {}
	~CCamera(void) {}

	void SetCamera();
	void SetMousePos(int x, int y);
	
	void Move(int x, int y);
	void Zoom(int nWheel);

	float GetTheta()  { return m_posTheta; }
	float GetPhi()    { return m_posPhi;   }
	float GetRadius() { return m_radius;   }

private:
	LPDIRECT3DDEVICE9 m_pD3DDevice;

	POINT m_curPt;	
	float m_posTheta;	// 좌우
	float m_posPhi;		// 상하
	float m_radius;		// 확대/축소
};