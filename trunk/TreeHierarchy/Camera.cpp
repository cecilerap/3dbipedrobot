//////////////////////////////////////////////////////////////////////////
// Camera.cpp
//////////////////////////////////////////////////////////////////////////

#include "Camera.h"

void CCamera::SetCamera()
{
	if(fabs(m_vEyePt.x) > 250)		m_vEyePt.x = 250*(m_vEyePt.x<0?-1:1);
	if(fabs(m_vEyePt.y) > 250)		m_vEyePt.y = 250*(m_vEyePt.y<0?-1:1);
	if(m_vEyePt.z >  -50)	m_vEyePt.z =  -50;
	if(m_vEyePt.z < -900)	m_vEyePt.z = -900;

	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &m_vEyePt, &m_vLookatPt, &m_vUpVec);
	m_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);
}

void CCamera::SetMousePos(int x, int y)
{
	m_curPt.x = x, m_curPt.y = y;
}

void CCamera::Move(int x, int y)
{	
	float fDelta = 0.05f;

	int dx = m_curPt.x - x;
	int dy = m_curPt.y - y;

	m_vEyePt.x += (dx*fDelta);
	m_vEyePt.y += (dy*fDelta);

	SetCamera();
}

void CCamera::Zoom(int nWheel)
{
	if(nWheel < 0)
		m_vEyePt.z += (-10);
	else
		m_vEyePt.z += ( 10);

	SetCamera();
}