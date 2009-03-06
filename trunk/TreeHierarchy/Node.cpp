//////////////////////////////////////////////////////////////////////////
// Node.cpp
//////////////////////////////////////////////////////////////////////////

#include "Node.h"

MESHCOMPONENT g_meshComponent[22] = 
{
	{L"NULL", BACKGROUND, NOTHING, {1.f,0.f,0.f,0.f, 0.f,0.f,-1.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,0.f,1.f}},

	{L"NULL", NOTHING, NOTHING, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,0.f,1.f}},
	{L"BODY.X", BODY, NOTHING, {1.f,0.f,0.f,0.f, 0.f,0.f,-1.f,0.f, 0.f,1.f,0.f,0.f, 0.f,50.f,0.f,1.f}},
	{L"HEAD.X", HEAD, BODY, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,15.f,1.f}},								

	{L"ARM_shoulder_L.X", ARM_SHOULDER_L, BODY, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, -20.f,0.f,10.f,1.f}},
	{L"ARM_middle_L.X", ARM_MIDDLE_L, ARM_SHOULDER_L, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, -3.f,0.f,-10.f,1.f}},
	{L"ARM_low_L.X", ARM_LOW_L, ARM_MIDDLE_L, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, -1.f,0.f,-10.f,1.f}},
	{L"ARM_shoulder_R.X", ARM_SHOULDER_R, BODY, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 20.f,0.f,10.f,1.f}},
	{L"ARM_middle_R.X", ARM_MIDDLE_R, ARM_SHOULDER_R, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 3.f,0.f,-10.f,1.f}},
	{L"ARM_low_R.X", ARM_LOW_R, ARM_MIDDLE_R, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,-14.f,1.f}},

	{L"LEG_up_L.X", LEG_UP_L, BODY, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, -9.f,3.f,-20.f,1.f}},
	{L"LEG_upMotor_L.X", LEG_UPMOTOR_L, LEG_UP_L, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,-3.f,-5.f,1.f}},
	{L"LEG_middle_L.X", LEG_MIDDLE_L, LEG_UPMOTOR_L, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 2.f,0.f,-7.f,1.f}},
	{L"LEG_low_L.X", LEG_LOW_L, LEG_MIDDLE_L, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,-21.f,1.f}},

	{L"FOOT_motor_L.X", FOOT_MOTOR_L, LEG_LOW_L, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, -2.f,0.f,-11.f,1.f}},
	{L"FOOT_L.X", FOOT_L, FOOT_MOTOR_L, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,7.f,-6.f,1.f}},

	{L"LEG_up_R.X", LEG_UP_R, BODY, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 9.f,2.f,-20.f,1.f}},
	{L"LEG_upMotor_R.X", LEG_UPMOTOR_R, LEG_UP_R, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,-3.f,-5.f,1.f}},
	{L"LEG_middle_R.X", LEG_MIDDLE_R, LEG_UPMOTOR_R, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, -1.f,0.f,-7.f,1.f}},
	{L"LEG_low_R.X", LEG_LOW_R, LEG_MIDDLE_R, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,-21.f,1.f}},

	{L"FOOT_motor_R.X", FOOT_MOTOR_R, LEG_LOW_R, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 2.f,0.f,-11.f,1.f}},
	{L"FOOT_R.X", FOOT_R, FOOT_MOTOR_R, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,7.f,-6.f,1.f}},
};

CNode::CNode(LPDIRECT3DDEVICE9 pD3DDevice, MESHCOMPONENT meshComponent)
{
	m_pD3DDevice = pD3DDevice;

	m_nObjectID = meshComponent.objectID;
	m_nParentID = meshComponent.parentID;

	// ±âº» Local ÁÂÇ¥°è·Î º¹»ç
	float data[16];
	memcpy(data, meshComponent.matTM, sizeof(data));
	D3DXMATRIXA16 matEmpty(data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7],data[8],
						   data[9],data[10],data[11],data[12],data[13],data[14],data[15]);
	memcpy(&m_matLocal, &matEmpty, sizeof(D3DXMATRIXA16));

	D3DXMatrixIdentity(&m_matAni);
	D3DXMatrixIdentity(&m_matTM);

	m_angle = 0.0f;
}

CNode::~CNode(void)
{
}

D3DXMATRIXA16* CNode::Animate(D3DXMATRIXA16* pParentTM)
{
	m_matTM = m_matLocal * m_matAni * *pParentTM;
	return &m_matTM;
}

void CNode::SetAngle(float angle)
{
//	m_angle += angle;
	m_angle = 0.f;

	switch(m_nObjectID)
	{
	case FOOT_L:
	case FOOT_R: // À§¾Æ·¡·Î¸¸ ±îµü±îµü
		if(m_angle < -0.5f)	m_angle = -0.5f;
		if(m_angle >  0.5f)	m_angle =  0.5f;
		D3DXMatrixRotationX(&m_matAni, m_angle);
		break;
	case FOOT_MOTOR_L: // ÁÂ¿ì·Î
	case FOOT_MOTOR_R:
//		if(m_angle < -10.f)	m_angle = -10.f;
//		if(m_angle >  10.f)	m_angle =  10.f;
//		D3DXMatrixRotationZ(&m_matAni, -10.f);
		break;
	case LEG_LOW_L: // ¾ÕµÚ·Î (¹«¸­)
	case LEG_LOW_R:
		if(m_angle <   0.f)	m_angle =   0.f;
		if(m_angle >   2.f)	m_angle =   2.f;
		D3DXMatrixRotationX(&m_matAni, m_angle);
		break;
	case LEG_MIDDLE_L: // ¾ÕµÚ·Î
	case LEG_MIDDLE_R:
		if(m_angle <  -1.f)	m_angle =  -1.f;
		if(m_angle >   0.f)	m_angle =   0.f;
		D3DXMatrixRotationX(&m_matAni, m_angle);
		break;
	case LEG_UPMOTOR_L: // ÁÂ¿ì·Î
		if(m_angle <-0.05f)	m_angle =-0.05f;
		if(m_angle >   1.f)	m_angle =   1.f;
		D3DXMatrixRotationY(&m_matAni, m_angle);
		break;
	case LEG_UPMOTOR_R:
		if(m_angle <  -1.f)	m_angle =  -1.f;
		if(m_angle > 0.05f)	m_angle = 0.05f;
		D3DXMatrixRotationY(&m_matAni, m_angle);
		break;
	case ARM_LOW_L: // ÁÂ¿ì·Î
	case ARM_LOW_R:
		m_angle = -0.3f;
		if(m_angle < -0.3f)	m_angle = -0.3f;
		if(m_angle >  0.3f)	m_angle =  0.3f;

		if(m_angle < 0)	D3DXMatrixRotationAxis(&m_matAni, &D3DXVECTOR3( 1.f,  1.f,  1.f), m_angle);
		else			D3DXMatrixRotationAxis(&m_matAni, &D3DXVECTOR3(-1.f, -1.f, -1.f), m_angle);

		break;
	case ARM_MIDDLE_L: // ÁÂ¿ì·Î
	case ARM_MIDDLE_R: 
		break;
	}
}


// {
// 	int nSign;
// 	if(m_angle <   0.f)	m_angle =   0.f, nSign =  1;
// 	if(m_angle >   2.f)	m_angle =   2.f, nSign = -1;
// 	D3DXMatrixRotationAxis(&m_matAni, &D3DXVECTOR3(1.f*nSign, 1.f*nSign, 1.f*nSign), m_angle);
// 	//			D3DXMatrixRotationY(&m_matAni, 0.3f);
// }