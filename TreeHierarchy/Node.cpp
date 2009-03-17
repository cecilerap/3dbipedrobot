//////////////////////////////////////////////////////////////////////////
// Node.cpp
//////////////////////////////////////////////////////////////////////////

#include "Node.h"

MESHCOMPONENT g_meshComponent[22] = 
{
	{L"NULL",	NOTHING, NOTHING, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,0.f,1.f}},

	{L"BODY.X",	BODY,	 NOTHING, {1.f,0.f,0.f,0.f, 0.f,0.f,-1.f,0.f, 0.f,1.f,0.f,0.f, 0.f,72.f, 0.f,1.f}},
	{L"HEAD.X", HEAD,	 BODY,	  {1.f,0.f,0.f,0.f, 0.f,1.f, 0.f,0.f, 0.f,0.f,1.f,0.f, 0.f, 0.f,18.f,1.f}},

	{L"ARM_shoulder_L.X", ARM_SHOULDER_L, BODY,           {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, -19.f,0.f,10.f,1.f}},
	{L"ARM_middle_L.X",   ARM_MIDDLE_L,   ARM_SHOULDER_L, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,0.f,1.f}},
	{L"ARM_low_L.X",      ARM_LOW_L,      ARM_MIDDLE_L,   {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,-20.f,1.f}},

	{L"ARM_shoulder_R.X", ARM_SHOULDER_R, BODY,           {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 19.f,0.f,10.f,1.f}},
	{L"ARM_middle_R.X",   ARM_MIDDLE_R,   ARM_SHOULDER_R, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,0.f,1.f}},
	{L"ARM_low_R.X",      ARM_LOW_R,      ARM_MIDDLE_R,   {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,-20.f,1.f}},

	{L"LEG_up_L.X",      LEG_UP_L,      BODY,          {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, -9.f,0.f,-20.f,1.f}},
	{L"LEG_upMotor_L.X", LEG_UPMOTOR_L, BODY,          {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, -9.f,0.f,-20.f,1.f}},
	{L"LEG_middle_L.X",  LEG_MIDDLE_L,  LEG_UPMOTOR_L, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,0.f,1.f}},
	{L"LEG_low_L.X",     LEG_LOW_L,     LEG_MIDDLE_L,  {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,-21.f,1.f}},

	{L"FOOT_motor_L.X", FOOT_MOTOR_L, LEG_LOW_L,    {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,-22.f,1.f}},
	{L"FOOT_L.X",       FOOT_L,       FOOT_MOTOR_L, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,10.f,-8.f,1.f}},

	{L"LEG_up_R.X",      LEG_UP_R,      BODY,          {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 9.f,0.f,-20.f,1.f}},
	{L"LEG_upMotor_R.X", LEG_UPMOTOR_R, BODY,          {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 9.f,0.f,-20.f,1.f}},
	{L"LEG_middle_R.X",  LEG_MIDDLE_R,  LEG_UPMOTOR_R, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,0.f,1.f}},
	{L"LEG_low_R.X",     LEG_LOW_R,     LEG_MIDDLE_R,  {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,-21.f,1.f}},

	{L"FOOT_motor_R.X", FOOT_MOTOR_R, LEG_LOW_R,    {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,-22.f,1.f}},
	{L"FOOT_R.X",       FOOT_R,       FOOT_MOTOR_R, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,10.f,-8.f,1.f}},
	
	{L"PLANE.X", ORIGIN, NOTHING, {2.f,0.f,0.f,0.f, 0.f,0.f,-2.f,0.f, 0.f,2.f,0.f,0.f, 0.f,0.f,0.f,1.f}}
};

CNode::CNode(LPDIRECT3DDEVICE9 pD3DDevice, MESHCOMPONENT meshComponent)
{
	m_pD3DDevice = pD3DDevice;

	m_nObjectID = meshComponent.objectID;
	m_nParentID = meshComponent.parentID;

	// 기본 Local 좌표계로 복사
	float data[16];
	memcpy(data, meshComponent.matTM, sizeof(data));
	D3DXMATRIXA16 matEmpty(data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7],data[8],
						   data[9],data[10],data[11],data[12],data[13],data[14],data[15]);
	memcpy(&m_matLocal, &matEmpty, sizeof(D3DXMATRIXA16));

	D3DXMatrixIdentity(&m_matAni);
	D3DXMatrixIdentity(&m_matTM);

	m_angle = 0.f;
}

CNode::~CNode(void)
{
}

D3DXMATRIXA16* CNode::Animate(D3DXMATRIXA16* pParentTM)
{
	m_matTM = m_matAni * m_matLocal * *pParentTM;
	return &m_matTM;
}

void CNode::SetAngle(D3DXMATRIX* (__stdcall *pfunc)(D3DXMATRIX*, FLOAT), float angle)
{
	pfunc(&m_matAni, angle);
}

void CNode::SetPosition(float angle)
{
	float x, y, z;
	x = m_matLocal.m[3][0];
	y = m_matLocal.m[3][1];
	z = m_matLocal.m[3][2];
	D3DXMatrixTranslation(&m_matLocal, x+0.f, y+0.f, z+angle);
	
	if(m_nObjectID == BODY)
	{
		m_matLocal.m[1][1] = 0;
		m_matLocal.m[1][2] = -1;
		m_matLocal.m[2][1] = 1;
		m_matLocal.m[2][2] = 0;
	}
	
}