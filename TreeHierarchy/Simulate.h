//////////////////////////////////////////////////////////////////////////
// Simulate.h
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "DirectX3D.h"


class CSimulate
{
public:
	enum STATE { READY, WALKING };
public:
	CSimulate();
	~CSimulate(void);

	void SetNodeMgr(CNodeMgr* pNodeMgr)			{ m_pNodeMgr = pNodeMgr; }
	void SetDirectX3D(CDirectX3D* pDirectX3D)	{ m_pDirectX3D = pDirectX3D; }
	void SetState(STATE state)					{ m_state = state; }

	void Simulate();	

private:
	void Ready();
	void Walking();

	void sv_motor();
	void initialize();
	void sit(float Z);

private:
	CNodeMgr*   m_pNodeMgr;
	CDirectX3D* m_pDirectX3D;

	STATE m_state;

	float L;
	float buff_motor_value[18];
	float buff_motor_value1[18];
	float motor_value[18][300];
	float motor[18];

	int rxd[4];
	int flag, TABLE, shift, flag1, flag2, flag3;
};
