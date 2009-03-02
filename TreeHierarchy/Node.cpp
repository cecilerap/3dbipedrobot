//////////////////////////////////////////////////////////////////////////
// Node.cpp
//////////////////////////////////////////////////////////////////////////

#include "Node.h"

MESHCOMPONENT g_meshComponent[21] = 
{
	{L"NULL", NOTHING, NOTHING, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,0.f,1.f}},
	{L"NULL", BODY, NOTHING, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,0.f,1.f}},
	{L"NULL", HEAD, BODY, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,0.f,1.f}},								
	{L"NULL", ARM_SHOULDER_L, BODY, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,0.f,1.f}},
	{L"NULL", ARM_MIDDLE_L, ARM_SHOULDER_L, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,0.f,1.f}},
	{L"NULL", ARM_LOW_L, ARM_MIDDLE_L, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,0.f,1.f}},
	{L"NULL", ARM_SHOULDER_R, BODY, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,0.f,1.f}},
	{L"NULL", ARM_MIDDLE_R, ARM_SHOULDER_R, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,0.f,1.f}},
	{L"NULL", ARM_LOW_R, ARM_MIDDLE_R, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,0.f,1.f}},
	{L"NULL", LEG_UP_L, BODY, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,0.f,1.f}},
	{L"NULL", LEG_UPMOTOR_L, LEG_UP_L, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,0.f,1.f}},
	{L"NULL", LEG_MIDDLE_L, LEG_UPMOTOR_L, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,0.f,1.f}},
	{L"NULL", LEG_LOW_L, LEG_MIDDLE_L, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,0.f,1.f}},

	{L"NULL", FOOT_MOTOR_L, LEG_LOW_L, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,0.f,1.f}},
	{L"FOOT_L.X", FOOT_L, FOOT_MOTOR_L, {-1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,0.f,1.f}},

	{L"NULL", LEG_UP_R, BODY, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,0.f,1.f}},
	{L"NULL", LEG_UPMOTOR_R, LEG_UP_R, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,0.f,1.f}},
	{L"NULL", LEG_MIDDLE_R, LEG_UPMOTOR_R, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,0.f,1.f}},
	{L"NULL", LEG_LOW_R, LEG_MIDDLE_R, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,0.f,1.f}},

	{L"FOOT_Motor.X", FOOT_MOTOR_R, LEG_LOW_R, {1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,0.f,1.f}},
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
//  	D3DXMATRIXA16 matEmpty;
//  	D3DXMatrixIdentity(&matEmpty);
	memcpy(&m_matLocal, &matEmpty, sizeof(D3DXMATRIXA16));

	D3DXMatrixIdentity(&m_matAni);
	D3DXMatrixIdentity(&m_matTM);
}

CNode::~CNode(void)
{
}

D3DXMATRIXA16* CNode::Animate(D3DXMATRIXA16* pParentTM)
{
	m_matTM = m_matLocal * m_matAni * *pParentTM;
	return &m_matTM;
}