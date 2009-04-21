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
	float m_posTheta;	// �¿�
	float m_posPhi;		// ����
	float m_radius;		// Ȯ��/���

	D3DXMATRIX m_matView;

	D3DXVECTOR3 m_vEye;
	D3DXVECTOR3 m_vLookat;
	D3DXVECTOR3 m_vUp;

	D3DXVECTOR3 m_vView;		// ī�޶��� ���� ���� ����
	D3DXVECTOR3 m_vCross;		// ī�޶��� ���� ����
};