//////////////////////////////////////////////////////////////////////////
// Node.cpp
//////////////////////////////////////////////////////////////////////////

#include "Node.h"

MESHCOMPONENT g_meshComponent[22] = 
{
	{L"NULL", BACKGROUND, NOTHING, {1.f,0.f,0.f,0.f, 0.f,0.f,-1.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,0.f,1.f}},

	{L"NULL", NOTHING, NOTHING, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,0.f,1.f}},
	{L"BODY.X", BODY, NOTHING, {1.f,0.f,0.f,0.f, 0.f,0.f,-1.f,0.f, 0.f,1.f,0.f,0.f, 100.f,0.f,50.f,1.f}},
	{L"NULL", HEAD, BODY, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,0.f,1.f}},								

	{L"ARM_shoulder_L.X", ARM_SHOULDER_L, BODY, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,0.f,1.f}},
	{L"ARM_middle_L.X", ARM_MIDDLE_L, ARM_SHOULDER_L, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,0.f,1.f}},
	{L"ARM_low_L.X", ARM_LOW_L, ARM_MIDDLE_L, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,0.f,1.f}},
	{L"ARM_shoulder_R.X", ARM_SHOULDER_R, BODY, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,0.f,1.f}},
	{L"ARM_middle_R.X", ARM_MIDDLE_R, ARM_SHOULDER_R, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,0.f,1.f}},
	{L"ARM_low_R.X", ARM_LOW_R, ARM_MIDDLE_R, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,0.f,1.f}},

	{L"LEG_up_L.X", LEG_UP_L, BODY, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,0.f,1.f}},
	{L"LEG_upMotor_L.X", LEG_UPMOTOR_L, LEG_UP_L, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,0.f,1.f}},
	{L"LEG_middle_L.X", LEG_MIDDLE_L, LEG_UPMOTOR_L, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,0.f,1.f}},
	{L"LEG_low_L.X", LEG_LOW_L, LEG_MIDDLE_L, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,0.f,1.f}},

	{L"FOOT_motor_L.X", FOOT_MOTOR_L, LEG_LOW_L, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,0.f,1.f}},
	{L"FOOT_L.X", FOOT_L, FOOT_MOTOR_L, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,0.f,1.f}},

	{L"LEG_up_R.X", LEG_UP_R, BODY, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,0.f,1.f}},
	{L"LEG_upMotor_R.X", LEG_UPMOTOR_R, LEG_UP_R, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,0.f,1.f}},
	{L"LEG_middle_R.X", LEG_MIDDLE_R, LEG_UPMOTOR_R, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,0.f,1.f}},
	{L"LEG_low_R.X", LEG_LOW_R, LEG_MIDDLE_R, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,0.f,1.f}},

	{L"FOOT_motor_R.X", FOOT_MOTOR_R, LEG_LOW_R, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,0.f,1.f}},
	{L"FOOT_R.X", FOOT_R, FOOT_MOTOR_R, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,0.f,1.f}},
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
}

CNode::~CNode(void)
{
}
#pragma comment(lib, "winmm.lib")
D3DXMATRIXA16* CNode::Animate(D3DXMATRIXA16* pParentTM)
{
// 	if(m_nObjectID == LEG_UP_L)
// 	{
// //		D3DXMatrixRotationZ(&m_matAni, -150.f);
// 		D3DXMatrixIdentity(&m_matAni);
// //		m_matAni._11 = m_matAni._22 = m_matAni._33 = m_matAni._44 = 100.f;
// 	}
// 
	if(m_nObjectID == LEG_LOW_R)
	{
// 		m_matAni._11 = m_matAni._22 = m_matAni._33 = m_matAni._44 = 10.f;
// //		D3DXMatrixRotationY(&m_matAni, timeGetTime()/360.f);
// 		m_matAni._41 = m_matAni._42 = m_matAni._43 = 10.f;

		D3DXVECTOR3 vUp(0.f, 0.f, 200.f);
 		D3DXMatrixRotationAxis(&m_matAni, &vUp,  timeGetTime()/360.f);  

// 		D3DXVECTOR3 vUp(0.f, 1.f, 0.f);
// 		D3DXMATRIXA16 matRot;
// 		D3DXMatrixRotationAxis(&m_matAni, &vUp, timeGetTime()/360.f);  
// 		D3DXVECTOR3 vNewDst;
// 		D3DXVec3TransformCoord(&vNewDst, &m_vView, &matRot);	// view * rot로 새로운 dst vector를 구한다.
// 		vNewDst += m_vEye;										// 실제 dst position =  eye Position + dst vector

//		D3DXMatrixRotationZ(&m_matAni, timeGetTime()/360.f);
	}

	switch(m_nObjectID)
	{
	case FOOT_L:
	case FOOT_R: // 위아래로만 까딱까딱 (범위는 -140 ~ 140)
		break;
	case FOOT_MOTOR_L: // 좌우로
	case FOOT_MOTOR_R:
		break;
	case LEG_LOW_L: // 앞뒤로 (무릎)
	case LEG_LOW_R:
		break;
	case LEG_MIDDLE_L: // 좌우로
	case LEG_MIDDLE_R:
		break;
	case LEG_UP_L: // 앞뒤로
	case LEG_UP_R:
		break;
	case ARM_LOW_L: // 좌우로
	case ARM_LOW_R:
		break;
	case ARM_MIDDLE_L: // 좌우로
	case ARM_MIDDLE_R:
		break;
	}

	m_matTM = m_matLocal * m_matAni * *pParentTM;
	return &m_matTM;
}