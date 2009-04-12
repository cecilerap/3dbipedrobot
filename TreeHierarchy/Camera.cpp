//////////////////////////////////////////////////////////////////////////
// Camera.cpp
//////////////////////////////////////////////////////////////////////////

#include "Camera.h"

#define PI				((float)(3.141592654f))
#define DEG2RAD(deg)	((deg)*(PI/180.f))
#define RAD2DEG(rad)	((rad)*(180.f/PI))


void CCamera::SetCamera()
{
	float theta = DEG2RAD(m_posTheta);
	float phi = DEG2RAD(m_posPhi);
	
	D3DXVECTOR3 pos((float)(m_radius*cos(theta)*cos(phi)), (float)(m_radius*sin(phi)), (float)(m_radius*sin(theta)*cos(phi)));

	D3DXMATRIX matView;
	D3DXMatrixIdentity(&matView);
	D3DXMatrixLookAtLH(&matView, &pos, &D3DXVECTOR3(0.f,0.f,0.f), &D3DXVECTOR3(0.f,1.f,0.f));
	m_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);
}

void CCamera::SetMousePos(int x, int y)
{
	m_curPt.x = x, m_curPt.y = y;
}

void CCamera::Move(int x, int y)
{	
	float fDelta = 0.05f;

	int dx = x - m_curPt.x;
	int dy = m_curPt.y - y;

	m_posTheta += (dx*fDelta);
	m_posPhi   += (dy*fDelta);

	if(m_posPhi >= 90.f)		m_posPhi =  89.9999f;
	else if(m_posPhi <= -90.f)	m_posPhi = -89.9999f;

	if(m_posTheta > 360.f)		m_posTheta -= 360.f;
	else if(m_posTheta < 0.f)	m_posTheta += 360.f;

	SetCamera();
}

void CCamera::Zoom(int nWheel)
{
	if(nWheel < 0)		m_radius += ( 10.f);
	else				m_radius += (-10.f);

	if(m_radius <= 0.f)			m_radius = 0.f;
	else if(m_radius >= 500.f)	m_radius = 500.f;

	SetCamera();
}