// Simulate.cpp : 구현 파일
//

#include "stdafx.h"
#include "Simulate.h"
#include <math.h>

#include "resource.h"
#include "3DBipedRobotDlg.h"

CSimulate::CSimulate(C3DBipedRobotDlg* pRobotDlg)
{
	m_pRobotDlg = pRobotDlg;

	m_state = READY;
	m_bodyPos = 0.f;

	memset(buff_motor_value_Start, 0, sizeof(buff_motor_value_Start));
	memset(buff_motor_value_End, 0, sizeof(buff_motor_value_End));

	TABLE = 30, time = 10, L = 80.f, shift = 10.f, step = 30.f;
}

CSimulate::~CSimulate(void)
{
}

DWORD WINAPI CallBackWalking(PVOID pVoid)
{
	CSimulate* pSimul = (CSimulate*)pVoid;
	pSimul->Walking();
	return 0;
}

void CSimulate::Simulate()
{
	switch(m_state)
	{
	case READY:
		Ready();
		break;
	case WALK:
		m_state = NOTHING;
		CreateThread(NULL, NULL, CallBackWalking, this, 0, 0);/*Walking();*/
		break;
	default:
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
// private 함수
//////////////////////////////////////////////////////////////////////////

void CSimulate::Ready()
{
	initialize(5.f);
}

void CSimulate::Walking()
{
	//forward
	L_shift(50);		// shift 를 일정값 이상으로 하면 넘어져야함!

	R_foot_up(0,15);

	move_center(step*-1,0);


	R_shift(shift);

	L_foot_up(0,15);

	move_center_(step*-1,0);

//////////////////////////////////////////////////////////////////////////

	L_shift(shift);

	R_foot_up(0,15);

	move_center(step*-1,0);


	R_shift(shift);

	L_foot_up(0,15);

	move_center_(step*-1,0);

	m_state = READY;
}

void CSimulate::initialize(float Z)
{
	memset(buff_motor_value_Start, 0, sizeof(buff_motor_value_Start));
	memset(buff_motor_value_End, 0, sizeof(buff_motor_value_End));

	sit_result = acos((float)(((2*L)-Z)/(2*L)));

	buff_motor_value_End[0]  = buff_motor_value_Start[0]; 
	buff_motor_value_End[1]  = buff_motor_value_Start[1] - sit_result;
	buff_motor_value_End[2]  = buff_motor_value_Start[2] + (2 * sit_result);
	buff_motor_value_End[3]  = buff_motor_value_Start[3] - sit_result;
	buff_motor_value_End[4]  = buff_motor_value_Start[4];
	buff_motor_value_End[5]  = buff_motor_value_Start[5];

	buff_motor_value_End[6]  = buff_motor_value_Start[6];
	buff_motor_value_End[7]  = buff_motor_value_Start[7] - sit_result;
	buff_motor_value_End[8]  = buff_motor_value_Start[8] + (2*sit_result);
	buff_motor_value_End[9]  = buff_motor_value_Start[9] - sit_result;
	buff_motor_value_End[10] = buff_motor_value_Start[10];
	buff_motor_value_End[11] = buff_motor_value_Start[11];

	buff_motor_value_End[12] = buff_motor_value_Start[12];
	buff_motor_value_End[13] = buff_motor_value_Start[13];
	buff_motor_value_End[14] = buff_motor_value_Start[14];

	buff_motor_value_End[15] = buff_motor_value_Start[15];
	buff_motor_value_End[16] = buff_motor_value_Start[16];
	buff_motor_value_End[17] = buff_motor_value_Start[17];

	for(int i = 0; i < TABLE; i++)						// 테이블 증가
	{
		for(int j = 0; j < 18; j++)							// 테이블내의 테이터 증가
		{
			// 내분점공식
			motor[j] = motor_value[j][i] = (i * buff_motor_value_End[j] + ((TABLE-1) - i) * buff_motor_value_Start[j]) / (TABLE-1);
		}
	}

	sv_motor();			// 아래 Sit이랑 다른 점! 아래 Sit 에서 여기부분은 일부러 연결동작 하게 할라고 한거이므로
						// 여기서는 그게 필요 없음!
}

void CSimulate::sv_motor()
{
	m_pRobotDlg->m_pNodeMgr->SetAngle(FOOT_MOTOR_L,	motor[0]);
	m_pRobotDlg->m_pNodeMgr->SetAngle(FOOT_L,		motor[1]);
	m_pRobotDlg->m_pNodeMgr->SetAngle(LEG_LOW_L,     motor[2]);
	m_pRobotDlg->m_pNodeMgr->SetAngle(LEG_MIDDLE_L,  motor[3]);
	m_pRobotDlg->m_pNodeMgr->SetAngle(LEG_UPMOTOR_L, motor[4]);
	m_pRobotDlg->m_pNodeMgr->SetAngle(LEG_UP_L,      motor[5]);

	m_pRobotDlg->m_pNodeMgr->SetAngle(FOOT_MOTOR_R,	motor[6]);
	m_pRobotDlg->m_pNodeMgr->SetAngle(FOOT_R,		motor[7]);
	m_pRobotDlg->m_pNodeMgr->SetAngle(LEG_LOW_R,     motor[8]);
	m_pRobotDlg->m_pNodeMgr->SetAngle(LEG_MIDDLE_R,  motor[9]);
	m_pRobotDlg->m_pNodeMgr->SetAngle(LEG_UPMOTOR_R, motor[10]);
	m_pRobotDlg->m_pNodeMgr->SetAngle(LEG_UP_R,      motor[11]);

	m_pRobotDlg->m_pNodeMgr->SetAngle(ARM_SHOULDER_L, motor[12]);
	m_pRobotDlg->m_pNodeMgr->SetAngle(ARM_MIDDLE_L,   motor[13]);
	m_pRobotDlg->m_pNodeMgr->SetAngle(ARM_LOW_L,      motor[14]);

	m_pRobotDlg->m_pNodeMgr->SetAngle(ARM_SHOULDER_R, motor[15]);
	m_pRobotDlg->m_pNodeMgr->SetAngle(ARM_MIDDLE_R,   motor[16]);
	m_pRobotDlg->m_pNodeMgr->SetAngle(ARM_LOW_R,      motor[17]);

	m_pRobotDlg->m_pNodeMgr->SetAngle(BODY,           m_bodyPos);
	m_bodyPos = 0.f;

	m_pRobotDlg->Render();
	Sleep(time);
}

void CSimulate::sit(float Z)
{
	sit_result = acos((float)(((2*L)-Z)/(2*L)));

	// 앞에서 한 결과값은 End 에 들어있으므로 다음 작업을 하기 위해선 Start로 옮기고 함!
	memcpy(buff_motor_value_Start, buff_motor_value_End, sizeof(buff_motor_value_End));

	buff_motor_value_End[0]  = buff_motor_value_Start[0]; 
	buff_motor_value_End[1]  = buff_motor_value_Start[1] - sit_result;
	buff_motor_value_End[2]  = buff_motor_value_Start[2] + (2 * sit_result);
	buff_motor_value_End[3]  = buff_motor_value_Start[3] - sit_result;
	buff_motor_value_End[4]  = buff_motor_value_Start[4];
	buff_motor_value_End[5]  = buff_motor_value_Start[5];

	buff_motor_value_End[6]  = buff_motor_value_Start[6];
	buff_motor_value_End[7]  = buff_motor_value_Start[7] - sit_result;
	buff_motor_value_End[8]  = buff_motor_value_Start[8] + (2*sit_result);
	buff_motor_value_End[9]  = buff_motor_value_Start[9] - sit_result;
	buff_motor_value_End[10] = buff_motor_value_Start[10];
	buff_motor_value_End[11] = buff_motor_value_Start[11];

	buff_motor_value_End[12] = buff_motor_value_Start[12];
	buff_motor_value_End[13] = buff_motor_value_Start[13];
	buff_motor_value_End[14] = buff_motor_value_Start[14];

	buff_motor_value_End[15] = buff_motor_value_Start[15];
	buff_motor_value_End[16] = buff_motor_value_Start[16];
	buff_motor_value_End[17] = buff_motor_value_Start[17];

	for(int i = 0; i <= (TABLE-1); i++)						// 테이블 증가
	{
		for(int j = 0; j < 18; j++)							// 테이블내의 테이터 증가
		{
			// 내분점공식
			motor_value[j][i] = (i * buff_motor_value_End[j] + ((TABLE-1) - i) * buff_motor_value_Start[j]) / (TABLE-1);
		}
	}

	for(int k = 0; k < TABLE; k++)
	{
		for(int l = 0; l < 18; l++)
		{ 
			motor[l] = motor_value[l][k];
		}
		sv_motor();
	}	
}

void CSimulate::L_shift(float Y)
{
	L_shift_result = asin((float)(Y/(2*L)));

	// 앞에서 한 결과값은 End 에 들어있으므로 다음 작업을 하기 위해선 Start로 옮기고 함!
	memcpy(buff_motor_value_Start, buff_motor_value_End, sizeof(buff_motor_value_End));

	buff_motor_value_End[0]  = buff_motor_value_Start[0] - L_shift_result; //-10
	buff_motor_value_End[1]  = buff_motor_value_Start[1];
	buff_motor_value_End[2]  = buff_motor_value_Start[2];
	buff_motor_value_End[3]  = buff_motor_value_Start[3];
	buff_motor_value_End[4]  = buff_motor_value_Start[4] - L_shift_result;
	buff_motor_value_End[5]  = buff_motor_value_Start[5];

	buff_motor_value_End[6]  = buff_motor_value_Start[6] - L_shift_result;
	buff_motor_value_End[7]  = buff_motor_value_Start[7];
	buff_motor_value_End[8]  = buff_motor_value_Start[8];
	buff_motor_value_End[9]  = buff_motor_value_Start[9];
	buff_motor_value_End[10] = buff_motor_value_Start[10] - L_shift_result;
	buff_motor_value_End[11] = buff_motor_value_Start[11];

	buff_motor_value_End[12] = buff_motor_value_Start[12];
	buff_motor_value_End[13] = buff_motor_value_Start[13];
	buff_motor_value_End[14] = buff_motor_value_Start[14];

	buff_motor_value_End[15] = buff_motor_value_Start[15];
	buff_motor_value_End[16] = buff_motor_value_Start[16];
	buff_motor_value_End[17] = buff_motor_value_Start[17];

	for(int i = 0; i <= (TABLE-1); i++)												    //테이블 증가
	{
		for(int j = 0; j < 18; j++)												//테이블내의 테이터 증가
		{
			motor_value[j][i] = (i * buff_motor_value_End[j] + ((TABLE-1) - i) * buff_motor_value_Start[j] ) / (TABLE-1);       //내분점공식
		}
	}

	for(int k = 0; k < TABLE; k++)
	{
		for(int l = 0; l < 18; l++)
		{ 
			motor[l] = motor_value[l][k];
		}
		sv_motor();
	}	
}

void CSimulate::R_foot_up(float X_M, float Z_M)
{
	float H = sqrt((X_M*X_M)+((2*L)-Z_M-3)*((2*L)-Z_M-3));

	float the_1 = acos(H/(2*L));
	float the_0 = atan(X_M/((2*L)-Z_M-3));

	float result_the_a = the_0 + the_1;
	float result_the_b = 2 * the_1;
	float result_the_c = the_1 - the_0;

	// 앞에서 한 결과값은 End 에 들어있으므로 다음 작업을 하기 위해선 Start로 옮기고 함!
	memcpy(buff_motor_value_Start, buff_motor_value_End, sizeof(buff_motor_value_End));

	buff_motor_value_End[0]  = buff_motor_value_Start[0]; 
	buff_motor_value_End[1]  = buff_motor_value_Start[1];
	buff_motor_value_End[2]  = buff_motor_value_Start[2];
	buff_motor_value_End[3]  = buff_motor_value_Start[3];
	buff_motor_value_End[4]  = buff_motor_value_Start[4];
	buff_motor_value_End[5]  = buff_motor_value_Start[5];

	buff_motor_value_End[6]  = buff_motor_value_Start[6]; 
	buff_motor_value_End[7]  = -result_the_c;
	buff_motor_value_End[8]  = result_the_b;
	buff_motor_value_End[9]  = -result_the_a;
	buff_motor_value_End[10] = buff_motor_value_Start[10];
	buff_motor_value_End[11] = buff_motor_value_Start[11];

	buff_motor_value_End[12] = buff_motor_value_Start[12];
	buff_motor_value_End[13] = buff_motor_value_Start[13];
	buff_motor_value_End[14] = buff_motor_value_Start[14];

	buff_motor_value_End[15] = buff_motor_value_Start[15];
	buff_motor_value_End[16] = buff_motor_value_Start[16];
	buff_motor_value_End[17] = buff_motor_value_Start[17];

	for(int i = 0; i <= (TABLE-1); i++)												    //테이블 증가
	{
		for(int j = 0; j < 18; j++)												//테이블내의 테이터 증가
		{
			motor_value[j][i] = (i * buff_motor_value_End[j] + ((TABLE-1) - i) * buff_motor_value_Start[j]) / (TABLE-1);       //내분점공식
		}
	}

	for(int k = 0; k < TABLE ; k++)
	{
		for(int l = 0; l < 18; l++)
		{ 
			motor[l] = motor_value[l][k];
		}
		sv_motor();
	}
}

void CSimulate::move_center(float X_R, float Z_R)
{
	float H = sqrt((X_R*X_R)+((2*L)-Z_R-3)*((2*L)-Z_R-3));

	float the_1 = acos(H/(2*L));
	float the_0 = atan(X_R/((2*L)-Z_R-3));

	float result_the_a = the_0 + the_1;
	float result_the_b = 2 * the_1;
	float result_the_c = the_1 - the_0;

	// 앞에서 한 결과값은 End 에 들어있으므로 다음 작업을 하기 위해선 Start로 옮기고 함!
	memcpy(buff_motor_value_Start, buff_motor_value_End, sizeof(buff_motor_value_End));

	buff_motor_value_End[0]  = buff_motor_value_Start[0] + L_shift_result; 
	buff_motor_value_End[1]  = -result_the_c;
	buff_motor_value_End[2]  = result_the_b;
	buff_motor_value_End[3]  = -result_the_a;
	buff_motor_value_End[4]  = buff_motor_value_Start[4]+ L_shift_result;
	buff_motor_value_End[5]  = buff_motor_value_Start[5];

	buff_motor_value_End[6]  = buff_motor_value_Start[6] + L_shift_result; 
	buff_motor_value_End[7]  = -sit_result;
	buff_motor_value_End[8]  = (2*sit_result);
	buff_motor_value_End[9]  = -sit_result;
	buff_motor_value_End[10] = buff_motor_value_Start[10] + L_shift_result;
	buff_motor_value_End[11] = buff_motor_value_Start[11];

	buff_motor_value_End[12] = buff_motor_value_Start[12];
	buff_motor_value_End[13] = buff_motor_value_Start[13];
	buff_motor_value_End[14] = buff_motor_value_Start[14];

	buff_motor_value_End[15] = buff_motor_value_Start[15];
	buff_motor_value_End[16] = buff_motor_value_Start[16];
	buff_motor_value_End[17] = buff_motor_value_Start[17];

	for(int i = 0; i <= (TABLE-1); i++)												    //테이블 증가
	{
		for(int j = 0; j < 18; j++)												//테이블내의 테이터 증가
		{
			motor_value[j][i] = (i * buff_motor_value_End[j] + ((TABLE-1) - i) * buff_motor_value_Start[j]) / (TABLE-1);       //내분점공식
		}
	}

	for(int k = 0; k < TABLE; k++)
	{
		for(int l = 0; l < 18; l++)
		{ 
			motor[l] = motor_value[l][k];
		}

		m_bodyPos = (10.f/TABLE);
		sv_motor();
	}
}

void CSimulate::R_shift(float Y)
{
	R_shift_result = asin(Y/(2*L));

	// 앞에서 한 결과값은 End 에 들어있으므로 다음 작업을 하기 위해선 Start로 옮기고 함!
	memcpy(buff_motor_value_Start, buff_motor_value_End, sizeof(buff_motor_value_End));

	buff_motor_value_End[0]  = buff_motor_value_Start[0] + R_shift_result; 
	buff_motor_value_End[1]  = buff_motor_value_Start[1];
	buff_motor_value_End[2]  = buff_motor_value_Start[2];
	buff_motor_value_End[3]  = buff_motor_value_Start[3];
	buff_motor_value_End[4]  = buff_motor_value_Start[4] + R_shift_result;
	buff_motor_value_End[5]  = buff_motor_value_Start[5];

	buff_motor_value_End[6]  = buff_motor_value_Start[6] + R_shift_result;
	buff_motor_value_End[7]  = buff_motor_value_Start[7];
	buff_motor_value_End[8]  = buff_motor_value_Start[8];
	buff_motor_value_End[9]  = buff_motor_value_Start[9];
	buff_motor_value_End[10] = buff_motor_value_Start[10] + R_shift_result;
	buff_motor_value_End[11] = buff_motor_value_Start[11];

	buff_motor_value_End[12] = buff_motor_value_Start[12];
	buff_motor_value_End[13] = buff_motor_value_Start[13];
	buff_motor_value_End[14] = buff_motor_value_Start[14];

	buff_motor_value_End[15] = buff_motor_value_Start[15];
	buff_motor_value_End[16] = buff_motor_value_Start[16];
	buff_motor_value_End[17] = buff_motor_value_Start[17];

	for(int i = 0; i <= (TABLE-1); i++)												    //테이블 증가
	{
		for(int j = 0; j < 18; j++)												//테이블내의 테이터 증가
		{
			motor_value[j][i] = (i * buff_motor_value_End[j] + ((TABLE-1) - i) * buff_motor_value_Start[j]) / (TABLE-1);       //내분점공식
		}
	}

	for(int k = 0; k < TABLE; k++)
	{
		for(int l = 0; l < 18; l++)
		{ 
			motor[l] = motor_value[l][k];
		}
		sv_motor();
	}	
}

void CSimulate::L_foot_up(float X_M, float Z_M)
{
	float H = sqrt((X_M*X_M)+((2*L)-Z_M-3)*((2*L)-Z_M-3));

	float the_1 = acos(H/(2*L));
	float the_0 = atan(X_M/((2*L)-Z_M-3));
	
	float result_the_a = the_0 + the_1;
	float result_the_b = 2 * the_1;
	float result_the_c = the_1 - the_0;

	// 앞에서 한 결과값은 End 에 들어있으므로 다음 작업을 하기 위해선 Start로 옮기고 함!
	memcpy(buff_motor_value_Start, buff_motor_value_End, sizeof(buff_motor_value_End));

	buff_motor_value_End[0]  = buff_motor_value_Start[0]; 
	buff_motor_value_End[1]  = -result_the_c;
	buff_motor_value_End[2]  = result_the_b;
	buff_motor_value_End[3]  = -result_the_a;
	buff_motor_value_End[4]  = buff_motor_value_Start[4];
	buff_motor_value_End[5]  = buff_motor_value_Start[5];

	buff_motor_value_End[6]  = buff_motor_value_Start[6]; 
	buff_motor_value_End[7]  = buff_motor_value_Start[7];
	buff_motor_value_End[8]  = buff_motor_value_Start[8];
	buff_motor_value_End[9]  = buff_motor_value_Start[9];
	buff_motor_value_End[10] = buff_motor_value_Start[10];
	buff_motor_value_End[11] = buff_motor_value_Start[11];

	buff_motor_value_End[12] = buff_motor_value_Start[12];
	buff_motor_value_End[13] = buff_motor_value_Start[13];
	buff_motor_value_End[14] = buff_motor_value_Start[14];

	buff_motor_value_End[15] = buff_motor_value_Start[15];
	buff_motor_value_End[16] = buff_motor_value_Start[16];
	buff_motor_value_End[17] = buff_motor_value_Start[17];

	for(int i = 0; i <= (TABLE-1); i++)												    //테이블 증가
	{
		for(int j = 0; j < 18; j++)												//테이블내의 테이터 증가
		{
			motor_value[j][i] = (i * buff_motor_value_End[j] + ((TABLE-1) - i) * buff_motor_value_Start[j]) / (TABLE-1);       //내분점공식
		}
	}

	for(int k = 0; k < TABLE; k++)
	{
		for(int l = 0; l < 18; l++)
		{ 
			motor[l] = motor_value[l][k];
		}
		sv_motor();
	}
}

void CSimulate::move_center_(float X_R, float Z_R)
{
	float H = sqrt((X_R*X_R)+((2*L)-Z_R-3)*((2*L)-Z_R-3));

	float the_1 = acos(H/(2*L));
	float the_0 = atan(X_R/((2*L)-Z_R-3));

	float result_the_a = the_0 + the_1;
	float result_the_b = 2 * the_1;
	float result_the_c = the_1 - the_0;

	// 앞에서 한 결과값은 End 에 들어있으므로 다음 작업을 하기 위해선 Start로 옮기고 함!
	memcpy(buff_motor_value_Start, buff_motor_value_End, sizeof(buff_motor_value_End));

	buff_motor_value_End[0]  = buff_motor_value_Start[0] - R_shift_result; 
	buff_motor_value_End[1]  = -sit_result;
	buff_motor_value_End[2]  = (2*sit_result);
	buff_motor_value_End[3]  = -sit_result;
	buff_motor_value_End[4]  = buff_motor_value_Start[4] - R_shift_result;
	buff_motor_value_End[5]  = buff_motor_value_Start[5];

	buff_motor_value_End[6]  = buff_motor_value_Start[6] - R_shift_result; 
	buff_motor_value_End[7]  = -result_the_c;
	buff_motor_value_End[8]  = result_the_b;
	buff_motor_value_End[9]  = -result_the_a;
	buff_motor_value_End[10] = buff_motor_value_Start[10]- R_shift_result;
	buff_motor_value_End[11] = buff_motor_value_Start[11];

	buff_motor_value_End[12] = buff_motor_value_Start[12];
	buff_motor_value_End[13] = buff_motor_value_Start[13];
	buff_motor_value_End[14] = buff_motor_value_Start[14];

	buff_motor_value_End[15] = buff_motor_value_Start[15];
	buff_motor_value_End[16] = buff_motor_value_Start[16];
	buff_motor_value_End[17] = buff_motor_value_Start[17];

	for(int i = 0; i <= (TABLE-1); i++)												    //테이블 증가
	{
		for(int j = 0; j < 18; j++)												//테이블내의 테이터 증가
		{
			motor_value[j][i] = (i * buff_motor_value_End[j] + ((TABLE-1) - i) * buff_motor_value_Start[j]) / (TABLE-1);       //내분점공식
		}
	}

	for(int k = 0; k < TABLE; k++)
	{
		for(int l = 0; l < 18; l++)
		{ 
			motor[l] = motor_value[l][k];
		}
		m_bodyPos = (10.f/TABLE);
		sv_motor();
	}
}
