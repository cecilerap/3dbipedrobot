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
	D3DXVECTOR3 m_vEyePt;			// ���� ��ġ
	D3DXVECTOR3 m_vLookatPt;		// ���� �ٶ󺸴� ��ġ
	D3DXVECTOR3 m_vUpVec;			// ��� ����

private:
	LPDIRECT3DDEVICE9 m_pD3DDevice;

	POINT m_curPt;
};