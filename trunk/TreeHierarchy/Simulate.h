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
	void L_shift(float Y);
	void R_foot_up(float X_M, float Z_M);
	void move_R(float Y);
	void move_center(float X_R, float Z_R);
	void R_shift(float Y);
	void L_foot_center(float X_M, float Z_M);
	void L_foot_up(float X_M, float Z_M);
	void L_foot_down(float X_B, float Z_B);
	void move_L(float Y);
	void move_center_(float X_R, float Z_R);
	void L_shift_(float Y);
	void R_foot_center(float X_M, float Z_M);
	void R_foot_up_(float X_M, float Z_M);
	void sit_move();

private:
	CNodeMgr*   m_pNodeMgr;
	CDirectX3D* m_pDirectX3D;

	STATE m_state;

	float L, L_shift_result, R_shift_result, sit_result;
	float buff_motor_value[18];
	float buff_motor_value1[18];
	float motor_value[18][300];
	float motor[18];

	int rxd[4];
	int flag, TABLE, shift, flag1, flag2, flag3;
};
