//////////////////////////////////////////////////////////////////////////
// Simulate.h
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "DirectX3D.h"

class CSimulate
{
public:
	enum STATE { READY, WALK };

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
	void L_shift(float Y);
	void R_foot_up(float X_M, float Z_M);
	void move_center(float X_R, float Z_R);
	void R_shift(float Y);
	void L_foot_up(float X_M, float Z_M);
	void move_center_(float X_R, float Z_R);

private:
	CNodeMgr*   m_pNodeMgr;
	CDirectX3D* m_pDirectX3D;

	STATE m_state;
	float m_bodyPos;

	float L_shift_result, R_shift_result, sit_result;
	float buff_motor_value[18];
	float buff_motor_value1[18];
	float motor_value[18][300];
	float motor[18];

	int TABLE, time;
	float L, shift, step;
};
