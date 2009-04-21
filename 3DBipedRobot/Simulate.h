// Simulate.h : 헤더 파일
//

#pragma once

// 전방선언
class C3DBipedRobotDlg;

class CSimulate
{
public:
	enum STATE { NOTHING, READY, WALK };

public:
	CSimulate(C3DBipedRobotDlg* pRobotDlg);
	~CSimulate(void);

	void SetState(STATE state)					{ m_state = state; }
	void Simulate();

	void Ready();
	void Walking();

private:
	void sv_motor();
	void initialize(float Z);
	void sit(float Z);
	void L_shift(float Y);
	void R_foot_up(float X_M, float Z_M);
	void move_center(float X_R, float Z_R);
	void R_shift(float Y);
	void L_foot_up(float X_M, float Z_M);
	void move_center_(float X_R, float Z_R);

private:
	C3DBipedRobotDlg* m_pRobotDlg;

	STATE m_state;
	float m_bodyPos;

	float L_shift_result, R_shift_result, sit_result;
	float buff_motor_value_Start[18];
	float buff_motor_value_End[18];
	float motor_value[18][300];
	float motor[18];

	int TABLE, time;
	float L, shift, step;
};
