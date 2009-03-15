//////////////////////////////////////////////////////////////////////////
// Simulate.cpp
//////////////////////////////////////////////////////////////////////////

#include "Simulate.h"

CSimulate::CSimulate()
{
	m_state = READY;

	L = 80.f;

// 	float temp[18] = {535, 475, 420, 465, 475, 483,
// 					  475, 620, 670, 555, 540, 480,
// 					  478, 514, 519,
// 					  545, 519, 514};
// 	memcpy(buff_motor_value, temp, sizeof(temp));

	memset(buff_motor_value, 0, sizeof(buff_motor_value));
	memset(buff_motor_value1, 0, sizeof(buff_motor_value1));

	flag = 1, TABLE = 30, shift = 0, flag1 = 1, flag2 = 0, flag3 = 0;
}

CSimulate::~CSimulate(void)
{
}

void CSimulate::Simulate()
{
	switch(m_state)
	{
	case READY:
		Ready();
		break;
	case WALKING:
		Walking();
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
	initialize();
}

void CSimulate::Walking()
{
	initialize();

// 	while(1)

// 	{
// 		if(rxd[0] == 0)
// 		{
// 			rxd[1] = 0;
// 			rxd[2] = 0;
// 			rxd[3] = 0;
// 			initialize();
// 			flag = 1;
// 		}
// 
// 		//forward
// 		else if(rxd[0] == 1)
// 		{
// 			TABLE = 30 - rxd[2];
// 			shift = rxd[3];
// 
// 			if(rxd[0] == 1 && rxd[1] != 0 && flag3 == 1)
// 			{
// 				flag2 = 1;
// 				flag3 =0;
// 			}
// 			if(flag)
// 			{
 				sit(10.f);
// 				center();
// 				flag = 0;
// 				flag1 = 1;
// 			}
// 			else if(flag1)
// 			{
// 				L_shift(shift);
// 				R_foot_up(rxd[1]/2 , 12);
// 				center();
// 
// 				move_R(shift);
// 				move_center(-rxd[1],0);
// 				center();
// 				flag1 = 0;
// 				flag2 = 1;
// 			}
// 			else if(flag2)
// 			{
// 				R_shift(shift);
// 				L_foot_center(0,12);
// 				center();
// 				L_foot_up(rxd[1]/2,12);
// 
// 				move_L(shift);
// 				move_center_(-rxd[1],0);
// 				center();
// 
// 				L_shift_(shift);
// 				R_foot_center(0,12);
// 				center();
// 				R_foot_up_(rxd[1]/2,12);
// 
// 				move_R(shift);
// 				move_center(-rxd[1],0);
// 				center();
// 				if(flag2 == 1 && rxd[1] == 0)
// 				{
// 					flag2 = 0;
// 					flag1 = 0;	
// 					flag3 = 1;				
// 					sit_move();
// 				}
// 			}
// 
// 		}
// 
// 	}

	m_state = READY;
}

void CSimulate::sv_motor()
{
	m_pNodeMgr->SetAngle(FOOT_MOTOR_L,  motor[0]);
	m_pNodeMgr->SetAngle(FOOT_L,        motor[1]);
	m_pNodeMgr->SetAngle(LEG_LOW_L,     motor[2]);
	m_pNodeMgr->SetAngle(LEG_MIDDLE_L,  motor[3]);
	m_pNodeMgr->SetAngle(LEG_UPMOTOR_L, motor[4]);
	m_pNodeMgr->SetAngle(LEG_UP_L,      motor[5]);

	m_pNodeMgr->SetAngle(FOOT_MOTOR_R,  motor[6]);
	m_pNodeMgr->SetAngle(FOOT_R,        motor[7]);
	m_pNodeMgr->SetAngle(LEG_LOW_R,     motor[8]);
	m_pNodeMgr->SetAngle(LEG_MIDDLE_R,  motor[9]);
	m_pNodeMgr->SetAngle(LEG_UPMOTOR_R, motor[10]);
	m_pNodeMgr->SetAngle(LEG_UP_R,      motor[11]);

	m_pNodeMgr->SetAngle(ARM_SHOULDER_L, motor[12]);
	m_pNodeMgr->SetAngle(ARM_MIDDLE_L,   motor[13]);
	m_pNodeMgr->SetAngle(ARM_LOW_L,      motor[14]);

	m_pNodeMgr->SetAngle(ARM_SHOULDER_R, motor[15]);
	m_pNodeMgr->SetAngle(ARM_MIDDLE_R,   motor[16]);
	m_pNodeMgr->SetAngle(ARM_LOW_R,      motor[17]);

	m_pDirectX3D->Render();
	Sleep(50);
}

void CSimulate::initialize()
{
	m_pNodeMgr->SetAngle(FOOT_MOTOR_L,  buff_motor_value[0]);
	m_pNodeMgr->SetAngle(FOOT_L,        buff_motor_value[1]);
	m_pNodeMgr->SetAngle(LEG_LOW_L,     buff_motor_value[2]);
	m_pNodeMgr->SetAngle(LEG_MIDDLE_L,  buff_motor_value[3]);
	m_pNodeMgr->SetAngle(LEG_UPMOTOR_L, buff_motor_value[4]);
	m_pNodeMgr->SetAngle(LEG_UP_L,      buff_motor_value[5]);

	m_pNodeMgr->SetAngle(FOOT_MOTOR_R,  buff_motor_value[6]);
	m_pNodeMgr->SetAngle(FOOT_R,        buff_motor_value[7]);
	m_pNodeMgr->SetAngle(LEG_LOW_R,     buff_motor_value[8]);
	m_pNodeMgr->SetAngle(LEG_MIDDLE_R,  buff_motor_value[9]);
	m_pNodeMgr->SetAngle(LEG_UPMOTOR_R, buff_motor_value[10]);
	m_pNodeMgr->SetAngle(LEG_UP_R,      buff_motor_value[11]);

	m_pNodeMgr->SetAngle(ARM_SHOULDER_L, buff_motor_value[12]);
	m_pNodeMgr->SetAngle(ARM_MIDDLE_L,   buff_motor_value[13]);
	m_pNodeMgr->SetAngle(ARM_LOW_L,      buff_motor_value[14]);

	m_pNodeMgr->SetAngle(ARM_SHOULDER_R, buff_motor_value[15]);
	m_pNodeMgr->SetAngle(ARM_MIDDLE_R,   buff_motor_value[16]);
	m_pNodeMgr->SetAngle(ARM_LOW_R,      buff_motor_value[17]);

	m_pDirectX3D->Render();
	Sleep(5);
}

void CSimulate::sit(float Z)
{
	float result;
	result = acos((float)(((2*L)-Z)/(2*L)));
// 	result = (result * 180) / 3.14 ; 
// 	result *= 3.41;

	buff_motor_value1[0] = buff_motor_value[0]; 
	buff_motor_value1[1] = buff_motor_value[1] - result;
	buff_motor_value1[2] = buff_motor_value[2] + (2 * result);
	buff_motor_value1[3] = buff_motor_value[3] - result;
	buff_motor_value1[4] = buff_motor_value[4];
	buff_motor_value1[5] = buff_motor_value[5];

	buff_motor_value1[6] = buff_motor_value[6];
	buff_motor_value1[7] = buff_motor_value[7] - result;
	buff_motor_value1[8] = buff_motor_value[8] + (2*result);
	buff_motor_value1[9] = buff_motor_value[9] - result;
	buff_motor_value1[10] = buff_motor_value[10];
	buff_motor_value1[11] = buff_motor_value[11];

	buff_motor_value1[12] = buff_motor_value[12];
	buff_motor_value1[13] = buff_motor_value[13];
	buff_motor_value1[14] = buff_motor_value[14];

	buff_motor_value1[15] = buff_motor_value[15];
	buff_motor_value1[16] = buff_motor_value[16];
	buff_motor_value1[17] = buff_motor_value[17];

	for(int i = 0; i <= (TABLE-1); i++)						// 테이블 증가
	{
		for(int j = 0; j < 18; j++)							// 테이블내의 테이터 증가
		{
			// 내분점공식
			motor_value[j][i] = (i * buff_motor_value1[j] + ((TABLE-1) - i) * buff_motor_value[j]) / (TABLE-1);
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

// 	for(int i = 0; i < 18; ++i)
// 	{
// 		motor[i]  = buff_motor_value[i] = buff_motor_value1[i];
// 		sv_motor();
// 	}
}