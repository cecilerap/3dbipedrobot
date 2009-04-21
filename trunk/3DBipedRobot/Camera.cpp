// Camera.cpp : 구현 파일
//

#include "stdafx.h"
#include "Camera.h"

#define PI				((float)(3.141592654f))
#define DEG2RAD(deg)	((deg)*(PI/180.f))
#define RAD2DEG(rad)	((rad)*(180.f/PI))

CCamera::CCamera(LPDIRECT3DDEVICE9 pD3DDevice)
: m_pD3DDevice(pD3DDevice), m_posTheta(90.f), m_posPhi(0.f), m_radius(300.f)
{
//	m_vEye = D3DXVECTOR3(0.f, -50.f, -300.f);
	m_vLookat = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_vUp = D3DXVECTOR3(0.f, 1.f, 0.f);
}

CCamera::~CCamera()
{
}

void CCamera::SetCamera()
{
	float theta = DEG2RAD(m_posTheta);
	float phi = DEG2RAD(m_posPhi);
	
	D3DXVECTOR3 pos((float)(m_radius*cos(theta)*cos(phi)), (float)(m_radius*sin(phi)), (float)(m_radius*sin(theta)*cos(phi)));

	D3DXMatrixIdentity(&m_matView);
	D3DXMatrixLookAtLH(&m_matView, &pos, &m_vLookat, &m_vUp);
	// 카메라 수정하면서 추가된 코드
// 	D3DXVec3Normalize(&m_vView, &(m_vLookat-m_vEye));
// 	D3DXVec3Cross(&m_vCross, &m_vUp, &m_vView);
//	D3DXMatrixLookAtLH(&m_matView, &m_vEye, &m_vLookat, &m_vUp);
	m_pD3DDevice->SetTransform(D3DTS_VIEW, &m_matView);
}

void CCamera::SetMousePos(int x, int y)
{
	m_curPt.x = x, m_curPt.y = y;
}

void CCamera::Move(int x, int y)
{	
	float fDelta = 0.05f;

	int dx = m_curPt.x - x;
	int dy = y - m_curPt.y;

	m_posTheta += (dx*fDelta);
	m_posPhi   += (dy*fDelta);

	if(m_posPhi >= 90.f)		m_posPhi =  89.9999f;
	else if(m_posPhi <= -90.f)	m_posPhi = -89.9999f;

	if(m_posTheta > 360.f)		m_posTheta -= 360.f;
	else if(m_posTheta < 0.f)	m_posTheta += 360.f;

// 	// 카메라 수정하면서 추가된 코드
//	fDelta = 0.00005f;
// 	m_posTheta = (dx*fDelta);
// 	m_posPhi   = (dy*fDelta);
// 
// 	// x축 rotation
// 	D3DXMATRIXA16 matRot;
// 	D3DXVECTOR3 vNewUp;
// 	D3DXMatrixRotationAxis(&matRot, &m_vCross, m_posPhi);
// 	D3DXVec3TransformCoord(&m_vLookat, &m_vView, &matRot);
// 	D3DXVec3Cross(&vNewUp, &m_vLookat, &m_vCross);
// 	D3DXVec3Normalize(&vNewUp, &vNewUp);
// 	m_vLookat += m_vEye;
// 
// 	SetCamera();
// 
// 	// y축 rotation
// 	D3DXMatrixRotationAxis(&matRot, &m_vUp, m_posTheta);
// 	D3DXVec3TransformCoord(&m_vLookat, &m_vView, &matRot);
// 	m_vLookat += m_vEye;

	SetCamera();
}

void CCamera::Zoom(int nWheel)
{
	if(nWheel < 0)		m_radius += ( 10.f);
	else				m_radius += (-10.f);

	if(m_radius <= 0.f)			m_radius = 0.f;
	else if(m_radius >= 500.f)	m_radius = 500.f;

//	// 카메라 수정하면서 추가된 코드
// 	// 얼마 이상이면 안 커지고, 얼마 이상이면 안 작아지는거 마저 구현!
// 	D3DXVECTOR3 vMove;
// 	D3DXVec3Normalize(&vMove, &m_vView);
// 	vMove *= (nWheel/50.f);
// 	m_vEye += vMove;
// 	m_vLookat += vMove;

	SetCamera();
}