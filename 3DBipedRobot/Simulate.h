// Simulate.h : 헤더 파일
//

#pragma once
#include <afxmt.h>

// 전방선언
class C3DBipedRobotDlg;

class CSimulate
{
public:
	enum STATE { NOTHING, READY, START, WALK, FALLDOWN };

public:
	CSimulate(C3DBipedRobotDlg* pRobotDlg);
	~CSimulate(void);

	void SetOption(float _shift, int velocity, float stride)
	{ shift = _shift, TABLE = velocity, m_fStride = stride; }

	STATE GetState() { return m_state; }
	void SetState(STATE state)	{ m_state = state; }	
	
	void Simulate();
	void Ready();
	void Start();
	void Walking();

	void FallDown();
	void ZMP(float arr1[4], float arr2[4]);

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
	CCriticalSection  cs;

	STATE m_state;
	float m_fBodyPos, m_fStartPos, m_fStride;
	
	float L_shift_result, R_shift_result, sit_result;
	float buff_motor_value_Start[18];
	float buff_motor_value_End[18];
	float motor_value[18][300];
	float motor[18];

	int TABLE, time;
	float L, shift, step;
};
