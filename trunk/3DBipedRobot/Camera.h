//////////////////////////////////////////////////////////////////////////
// Camera.h
//////////////////////////////////////////////////////////////////////////

#pragma once
#include <d3d9.h>
#include <d3dx9.h>

class CCamera
{
public:
	CCamera(LPDIRECT3DDEVICE9 pD3DDevice);
	~CCamera(void);

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

	D3DXMATRIX m_matView;

	D3DXVECTOR3 m_vEye;
	D3DXVECTOR3 m_vLookat;
	D3DXVECTOR3 m_vUp;

	D3DXVECTOR3 m_vView;		// 카메라의 단위 방향 벡터
	D3DXVECTOR3 m_vCross;		// 카메라의 측면 벡터
};