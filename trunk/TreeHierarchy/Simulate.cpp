//////////////////////////////////////////////////////////////////////////
// Simulate.cpp
//////////////////////////////////////////////////////////////////////////

#include "Simulate.h"

CSimulate::CSimulate()
{
	m_state = READY;

	m_bodyPos = 0.f;

	L = 80.f;

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
	case WALK:
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
// 	int count = 0;
// 	while(count++ < 3)
// 	{
		L_shift(10.f);
		R_foot_up(30, 12);
 
		move_R(10.f);
		move_center(-30.f,0);

// 		R_shift(10.f);
// 		L_foot_center(0,12);
// 		
// 		L_foot_up(30/2,12);
// 
// 		move_L(10.f);
// 		move_center_(-30,0);
// 
// 		L_shift_(10.f);
// 		R_foot_center(0,12);
// 
// 		R_foot_up_(30/2,12);
// 
// 		move_R(10.f);
// 		move_center(-30,0);
// 	}

// 	if(rxd[0] == 0)
// 	{
// 		rxd[1] = 0;
// 		rxd[2] = 0;
// 		rxd[3] = 0;
// 		initialize();
// 		flag = 1;
// 	}
// 	//forward
// 	else if(rxd[0] == 1)
// 	{
// 		TABLE = 30 - rxd[2];
// 		shift = rxd[3];
// 
// 		if(rxd[0] == 1 && rxd[1] != 0 && flag3 == 1)
// 		{
// 			flag2 = 1;
// 			flag3 =0;
// 		}
// 		if(flag)
// 		{
//			sit(30.f);
// 			//				center();
// 			flag = 0;
// 			flag1 = 1;
// 		}
// 		else if(flag1)
// 		{
// 			L_shift(10.f);
// 			R_foot_up(30, 12);
// 			//				center();
// 
// 			move_R(10.f);
// 			move_center(-30.f,0);
// 			//				center();
// 			flag1 = 0;
// 			flag2 = 1;
// 		}
// 		else if(flag2)
// 		{
// 			R_shift(shift);
// 			L_foot_center(0,12);
// 			//				center();
// 			L_foot_up(rxd[1]/2,12);
// 
// 			move_L(shift);
// 			move_center_(-rxd[1],0);
// 			//				center();
// 
// 			L_shift_(shift);
// 			R_foot_center(0,12);
// 			//				center();
// 			R_foot_up_(rxd[1]/2,12);
// 
// 			move_R(shift);
// 			move_center(-rxd[1],0);
// 			//				center();
// 			if(flag2 == 1 && rxd[1] == 0)
// 			{
// 				flag2 = 0;
// 				flag1 = 0;	
// 				flag3 = 1;				
// 				sit_move();
// 			}
// 		}
// 	}

	m_state = READY;
}

void CSimulate::initialize()
{
	memset(buff_motor_value, 0, sizeof(buff_motor_value));
	memset(buff_motor_value1, 0, sizeof(buff_motor_value1));

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

	m_pNodeMgr->SetAngle(BODY,           m_bodyPos);
	m_bodyPos = 0.f;

	m_pDirectX3D->Render();
	Sleep(50);
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

	m_pNodeMgr->SetAngle(BODY,           m_bodyPos);
	m_bodyPos = 0.f;

	m_pDirectX3D->Render();
	Sleep(50);
}

void CSimulate::sit(float Z)
{
	sit_result = acos((float)(((2*L)-Z)/(2*L)));

	buff_motor_value1[0] = buff_motor_value[0]; 
	buff_motor_value1[1] = buff_motor_value[1] - sit_result;
	buff_motor_value1[2] = buff_motor_value[2] + (2 * sit_result);
	buff_motor_value1[3] = buff_motor_value[3] - sit_result;
	buff_motor_value1[4] = buff_motor_value[4];
	buff_motor_value1[5] = buff_motor_value[5];

	buff_motor_value1[6] = buff_motor_value[6];
	buff_motor_value1[7] = buff_motor_value[7] - sit_result;
	buff_motor_value1[8] = buff_motor_value[8] + (2*sit_result);
	buff_motor_value1[9] = buff_motor_value[9] - sit_result;
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

void CSimulate::L_shift(float Y)
{
	L_shift_result = asin((float)(Y/(2*L)));

	buff_motor_value[0] = buff_motor_value1[0] - L_shift_result; //-10
	buff_motor_value[1] = buff_motor_value1[1];
	buff_motor_value[2] = buff_motor_value1[2];
	buff_motor_value[3] = buff_motor_value1[3];
	buff_motor_value[4] = buff_motor_value1[4] - L_shift_result;
	buff_motor_value[5] = buff_motor_value1[5];

	buff_motor_value[6] = buff_motor_value1[6] - L_shift_result;
	buff_motor_value[7] = buff_motor_value1[7];
	buff_motor_value[8] = buff_motor_value1[8];
	buff_motor_value[9] = buff_motor_value1[9];
	buff_motor_value[10] = buff_motor_value1[10] - L_shift_result;
	buff_motor_value[11] = buff_motor_value1[11];

	buff_motor_value[12] = buff_motor_value1[12];
	buff_motor_value[13] = buff_motor_value1[13];
	buff_motor_value[14] = buff_motor_value1[14];

	buff_motor_value[15] = buff_motor_value1[15];
	buff_motor_value[16] = buff_motor_value1[16];
	buff_motor_value[17] = buff_motor_value1[17];

	for(int i = 0; i <= (TABLE-1); i++)												    //테이블 증가
	{
		for(int j = 0; j < 18; j++)												//테이블내의 테이터 증가
		{
			motor_value[j][i] = (i * buff_motor_value[j] + ((TABLE-1) - i) * buff_motor_value1[j] ) / (TABLE-1);       //내분점공식
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

void CSimulate::L_shift_(float Y)
{
	L_shift_result = asin(Y/(2*L));

	buff_motor_value1[0] = buff_motor_value[0] - L_shift_result; //-10
	buff_motor_value1[1] = buff_motor_value[1];
	buff_motor_value1[2] = buff_motor_value[2];
	buff_motor_value1[3] = buff_motor_value[3];
	buff_motor_value1[4] = buff_motor_value[4] - L_shift_result;
	buff_motor_value1[5] = buff_motor_value[5];

	buff_motor_value1[6] = buff_motor_value[6] - L_shift_result;
	buff_motor_value1[7] = buff_motor_value[7];
	buff_motor_value1[8] = buff_motor_value[8];
	buff_motor_value1[9] = buff_motor_value[9];
	buff_motor_value1[10] = buff_motor_value[10] - L_shift_result;
	buff_motor_value1[11] = buff_motor_value[11];

	buff_motor_value1[12] = buff_motor_value[12];
	buff_motor_value1[13] = buff_motor_value[13];
	buff_motor_value1[14] = buff_motor_value[14];

	buff_motor_value1[15] = buff_motor_value[15];
	buff_motor_value1[16] = buff_motor_value[16];
	buff_motor_value1[17] = buff_motor_value[17];

	for(int i = 0; i <= (TABLE-1); i++)												    //테이블 증가
	{
		for(int j = 0; j < 18; j++)												//테이블내의 테이터 증가
		{
			motor_value[j][i] = (i * buff_motor_value[j] + ((TABLE-1) - i) * buff_motor_value1[j]) / (TABLE-1);       //내분점공식
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

void CSimulate::R_shift(float Y)
{
	R_shift_result = asin(Y/(2*L));

	buff_motor_value1[0] = buff_motor_value[0] + R_shift_result; 
	buff_motor_value1[1] = buff_motor_value[1];
	buff_motor_value1[2] = buff_motor_value[2];
	buff_motor_value1[3] = buff_motor_value[3];
	buff_motor_value1[4] = buff_motor_value[4] + R_shift_result;
	buff_motor_value1[5] = buff_motor_value[5];

	buff_motor_value1[6] = buff_motor_value[6] + R_shift_result;
	buff_motor_value1[7] = buff_motor_value[7];
	buff_motor_value1[8] = buff_motor_value[8];
	buff_motor_value1[9] = buff_motor_value[9];
	buff_motor_value1[10] = buff_motor_value[10] + R_shift_result;
	buff_motor_value1[11] = buff_motor_value[11];

	buff_motor_value1[12] = buff_motor_value[12];
	buff_motor_value1[13] = buff_motor_value[13];
	buff_motor_value1[14] = buff_motor_value[14];

	buff_motor_value1[15] = buff_motor_value[15];
	buff_motor_value1[16] = buff_motor_value[16];
	buff_motor_value1[17] = buff_motor_value[17];

	for(int i = 0; i <= (TABLE-1); i++)												    //테이블 증가
	{
		for(int j = 0; j < 18; j++)												//테이블내의 테이터 증가
		{
			motor_value[j][i] = (i * buff_motor_value1[j] + ((TABLE-1) - i) * buff_motor_value[j]) / (TABLE-1);       //내분점공식
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
	float H = sqrt((X_M*X_M)+((2*L)-Z_M-10)*((2*L)-Z_M-10));

	float the_1 = acos(H/(2*L));
	float the_0 = atan(X_M/((2*L)-Z_M-10));

	float result_the_a = the_0 + the_1;
	float result_the_b = 2 * the_1;
	float result_the_c = the_1 - the_0;

	buff_motor_value1[0] = buff_motor_value[0]; 
	buff_motor_value1[1] = buff_motor_value[1];
	buff_motor_value1[2]  =buff_motor_value[2];
	buff_motor_value1[3] = buff_motor_value[3];
	buff_motor_value1[4] = buff_motor_value[4];
	buff_motor_value1[5] = buff_motor_value[5];

	buff_motor_value1[6] = buff_motor_value[6]; 
	buff_motor_value1[7] = -result_the_c;
	buff_motor_value1[8] = result_the_b;
	buff_motor_value1[9] = -result_the_a;
	buff_motor_value1[10] = buff_motor_value[10];
	buff_motor_value1[11] = buff_motor_value[11];

	buff_motor_value1[12] = buff_motor_value[12];
	buff_motor_value1[13] = buff_motor_value[13];
	buff_motor_value1[14] = buff_motor_value[14];

	buff_motor_value1[15] = buff_motor_value[15];
	buff_motor_value1[16] = buff_motor_value[16];
	buff_motor_value1[17] = buff_motor_value[17];

	for(int i = 0; i <= (TABLE-1); i++)												    //테이블 증가
	{
		for(int j = 0; j < 18; j++)												//테이블내의 테이터 증가
		{
			motor_value[j][i] = (i * buff_motor_value1[j] + ((TABLE-1) - i) * buff_motor_value[j]) / (TABLE-1);       //내분점공식
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

void CSimulate::move_L(float Y)
{
	R_shift_result = asin(Y/(2*L));

	// 	buff_motor_value1[0] = buff_motor_value[0] - R_shift_result; 
	// 	buff_motor_value1[1] = buff_motor_value[1];
	// 	buff_motor_value1[2] = buff_motor_value[2];
	// 	buff_motor_value1[3] = buff_motor_value[3];
	// 	buff_motor_value1[4] = buff_motor_value[4] - R_shift_result;
	// 	buff_motor_value1[5] = buff_motor_value[5];
	// 
	// 	buff_motor_value1[6] = buff_motor_value[6] - R_shift_result;
	// 	buff_motor_value1[7] = buff_motor_value[7];
	// 	buff_motor_value1[8] = buff_motor_value[8];
	// 	buff_motor_value1[9] = buff_motor_value[9];
	// 	buff_motor_value1[10] = buff_motor_value[10];
	// 	buff_motor_value1[11] = buff_motor_value[11];
	// 
	// 	buff_motor_value1[12] = buff_motor_value[12];
	// 	buff_motor_value1[13] = buff_motor_value[13];
	// 	buff_motor_value1[14] = buff_motor_value[14];
	// 
	// 	buff_motor_value1[15] = buff_motor_value[15];
	// 	buff_motor_value1[16] = buff_motor_value[16];
	// 	buff_motor_value1[17] = buff_motor_value[17];
	// 
	// 	for(int i = 0; i <= (TABLE-1); i++)												    //테이블 증가
	// 	{
	// 		for(int j = 0; j < 18; j++)												//테이블내의 테이터 증가
	// 		{
	// 			motor_value[j][i] = (i * buff_motor_value1[j] + ((TABLE-1) - i) * buff_motor_value[j]) / (TABLE-1);       //내분점공식
	// 		}
	// 	}
	// 
	// 	for(int k = 0; k < TABLE; k++)
	// 	{
	// 		for(int l = 0; L < 18; l++)
	// 		{ 
	// 			motor[l] = motor_value[l][k];
	// 		}
	// 		sv_motor();
	// 	}
}

void CSimulate::move_R(float Y)
{
	R_shift_result = asin(Y/(2*L));

// 	buff_motor_value1[0] = buff_motor_value[0] + R_shift_result+1; //+10
// 	buff_motor_value1[1] = buff_motor_value[1];
// 	buff_motor_value1[2] = buff_motor_value[2];
// 	buff_motor_value1[3] = buff_motor_value[3];
// 	buff_motor_value1[4] = buff_motor_value[4];
// 	buff_motor_value1[5] = buff_motor_value[5];
// 
// 	buff_motor_value1[6] = buff_motor_value[6] + R_shift_result;
// 	buff_motor_value1[7] = buff_motor_value[7];
// 	buff_motor_value1[8] = buff_motor_value[8];
// 	buff_motor_value1[9] = buff_motor_value[9];
// 	buff_motor_value1[10] = buff_motor_value[10] + R_shift_result;
// 	buff_motor_value1[11] = buff_motor_value[11];
// 
// 	buff_motor_value1[12] = buff_motor_value[12];
// 	buff_motor_value1[13] = buff_motor_value[13];
// 	buff_motor_value1[14] = buff_motor_value[14];
// 
// 	buff_motor_value1[15] = buff_motor_value[15];
// 	buff_motor_value1[16] = buff_motor_value[16];
// 	buff_motor_value1[17] = buff_motor_value[17];
// 
// 	for(int i = 0; i <= (TABLE-1); i++)												    //테이블 증가
// 	{
// 		for(int j = 0; j < 18; j++)												//테이블내의 테이터 증가
// 		{
// 			motor_value[j][i] = ( i * buff_motor_value1[j] + ((TABLE-1) - i) * buff_motor_value[j] ) / (TABLE-1);       //내분점공식
// 		}
// 	}
// 
// 	for(int k = 0; k < TABLE; k++)
// 	{
// 		for(int l = 0; l < 18; l++)
// 		{ 
// 			motor[l] = motor_value[l][k];
// 		}
// 		sv_motor();
// 	}	
}

void CSimulate::move_center(float X_R, float Z_R)
{
	float H = sqrt((X_R*X_R)+((2*L)-Z_R-10)*((2*L)-Z_R-10));

	float the_1 = acos(H/(2*L));
	float the_0 = atan(X_R/((2*L)-Z_R-10));

	float result_the_a = the_0 + the_1;
	float result_the_b = 2 * the_1;
	float result_the_c = the_1 - the_0;

	buff_motor_value[0] = buff_motor_value1[0] + R_shift_result+1; 
	buff_motor_value[1] = result_the_c;
	buff_motor_value[2] = result_the_b;
	buff_motor_value[3] = result_the_a;
	buff_motor_value[4] = buff_motor_value1[4];
	buff_motor_value[5] = buff_motor_value1[5];

	buff_motor_value[6] = buff_motor_value1[6] + R_shift_result; 
	buff_motor_value[7] = sit_result;
	buff_motor_value[8] = (2*sit_result);
	buff_motor_value[9] = sit_result;
	buff_motor_value[10] = buff_motor_value1[10] + R_shift_result;
	buff_motor_value[11] = buff_motor_value1[11];

	buff_motor_value[12] = buff_motor_value1[12];
	buff_motor_value[13] = buff_motor_value1[13];
	buff_motor_value[14] = buff_motor_value1[14];

	buff_motor_value[15] = buff_motor_value1[15];
	buff_motor_value[16] = buff_motor_value1[16];
	buff_motor_value[17] = buff_motor_value1[17];

	for(int i = 0; i <= (TABLE-1); i++)												    //테이블 증가
	{
		for(int j = 0; j < 18; j++)												//테이블내의 테이터 증가
		{
			motor_value[j][i] = (i * buff_motor_value[j] + ((TABLE-1) - i) * buff_motor_value1[j]) / (TABLE-1);       //내분점공식
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

void CSimulate::move_center_(float X_R, float Z_R)
{
	float H = sqrt((X_R*X_R)+((2*L)-Z_R-10)*((2*L)-Z_R-10));

	float the_1 = acos(H/(2*L));
	float the_0 = atan(X_R/((2*L)-Z_R-10));

	float result_the_a = the_0 + the_1;
	float result_the_b = 2 * the_1;
	float result_the_c = the_1 - the_0;

	buff_motor_value[0] = buff_motor_value1[0] - R_shift_result; 
	buff_motor_value[1] = sit_result;
	buff_motor_value[2] = (2*sit_result);
	buff_motor_value[3] = sit_result;
	buff_motor_value[4] = buff_motor_value1[4] - R_shift_result;
	buff_motor_value[5] = buff_motor_value1[5];

	buff_motor_value[6] = buff_motor_value1[6] - R_shift_result; 
	buff_motor_value[7] = result_the_c;
	buff_motor_value[8] = result_the_b;
	buff_motor_value[9] = result_the_a;
	buff_motor_value[10] = buff_motor_value1[10];
	buff_motor_value[11] = buff_motor_value1[11];

	buff_motor_value[12] = buff_motor_value1[12];
	buff_motor_value[13] = buff_motor_value1[13];
	buff_motor_value[14] = buff_motor_value1[14];

	buff_motor_value[15] = buff_motor_value1[15];
	buff_motor_value[16] = buff_motor_value1[16];
	buff_motor_value[17] = buff_motor_value1[17];

	for(int i = 0; i <= (TABLE-1); i++)												    //테이블 증가
	{
		for(int j = 0; j < 18; j++)												//테이블내의 테이터 증가
		{
			motor_value[j][i] = (i * buff_motor_value[j] + ((TABLE-1) - i) * buff_motor_value1[j]) / (TABLE-1);       //내분점공식
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

void CSimulate::L_foot_center(float X_M, float Z_M)
{
	float H = sqrt((X_M*X_M)+((2*L)-Z_M-10)*((2*L)-Z_M-10));

	float the_1 = acos(H/(2*L));
	float the_0 = atan(X_M/((2*L)-Z_M-10));
	
	float result_the_a = the_0 + the_1;
	float result_the_b = 2 * the_1;
	float result_the_c = the_1 - the_0;

	buff_motor_value[0] = buff_motor_value1[0]; 
	buff_motor_value[1] = result_the_c;
	buff_motor_value[2] = result_the_b;
	buff_motor_value[3] = result_the_a;
	buff_motor_value[4] = buff_motor_value1[4];
	buff_motor_value[5] = buff_motor_value1[5];

	buff_motor_value[6] = buff_motor_value1[6]; 
	buff_motor_value[7] = buff_motor_value1[7];
	buff_motor_value[8] = buff_motor_value1[8];
	buff_motor_value[9] = buff_motor_value1[9];
	buff_motor_value[10] = buff_motor_value1[10] - R_shift_result;
	buff_motor_value[11] = buff_motor_value1[11];

	buff_motor_value[12] = buff_motor_value1[12];
	buff_motor_value[13] = buff_motor_value1[13];
	buff_motor_value[14] = buff_motor_value1[14];

	buff_motor_value[15] = buff_motor_value1[15];
	buff_motor_value[16] = buff_motor_value1[16];
	buff_motor_value[17] = buff_motor_value1[17];

	for(int i = 0; i <= (TABLE-1); i++)												    //테이블 증가
	{
		for(int j = 0; j < 18; j++)												//테이블내의 테이터 증가
		{
			motor_value[j][i] = (i * buff_motor_value[j] + ((TABLE-1) - i) * buff_motor_value1[j]) / (TABLE-1);       //내분점공식
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
	float H = sqrt((X_M*X_M)+((2*L)-Z_M-10)*((2*L)-Z_M-10));

	float the_1 = acos(H/(2*L));
	float the_0 = atan(X_M/((2*L)-Z_M-10));
	
	float result_the_a = the_0 + the_1;
	float result_the_b = 2 * the_1;
	float result_the_c = the_1 - the_0;

	buff_motor_value1[0] = buff_motor_value[0]; 
	buff_motor_value1[1] = result_the_c;
	buff_motor_value1[2] = result_the_b;
	buff_motor_value1[3] = result_the_a;
	buff_motor_value1[4] = buff_motor_value[4];
	buff_motor_value1[5] = buff_motor_value[5];

	buff_motor_value1[6] = buff_motor_value[6]; 
	buff_motor_value1[7] = buff_motor_value[7];
	buff_motor_value1[8] = buff_motor_value[8];
	buff_motor_value1[9] = buff_motor_value[9];
	buff_motor_value1[10] = buff_motor_value[10];
	buff_motor_value1[11] = buff_motor_value[11];

	buff_motor_value1[12] = buff_motor_value[12];
	buff_motor_value1[13] = buff_motor_value[13];
	buff_motor_value1[14] = buff_motor_value[14];

	buff_motor_value1[15] = buff_motor_value[15];
	buff_motor_value1[16] = buff_motor_value[16];
	buff_motor_value1[17] = buff_motor_value[17];

// 	for(int i = 0; i <= (TABLE-1); i++)												    //테이블 증가
// 	{
// 		for(int j = 0; j < 18; j++)												//테이블내의 테이터 증가
// 		{
// 			motor_value[j][i] = (i * buff_motor_value1[j] + ((TABLE-1) - i) * buff_motor_value[j]) / (TABLE-1);       //내분점공식
// 		}
// 	}
// 
// 	for(int k = 0; k < TABLE; k++)
// 	{
// 		for(int l = 0; l < 18; l++)
// 		{ 
// 			motor[l] = motor_value[l][k];
// 		}
// 		sv_motor();
// 	}
}

void CSimulate::L_foot_down(float X_B, float Z_B)
{
	float H = sqrt((X_B*X_B)+((2*L)-Z_B-10)*((2*L)-Z_B-10));

	float the_1 = acos(H/(2*L));
	float the_0 = atan(X_B/((2*L)-Z_B-10));
	
	float result_the_a = the_0 + the_1;
	float result_the_b = 2 * the_1;
	float result_the_c = the_1 - the_0;

	buff_motor_value[0] = buff_motor_value1[0]; 
	buff_motor_value[1] = result_the_c;
	buff_motor_value[2] = result_the_b;
	buff_motor_value[3] = result_the_a;
	buff_motor_value[4] = buff_motor_value1[4];
	buff_motor_value[5] = buff_motor_value1[5];

	buff_motor_value[6] = buff_motor_value1[6]; 
	buff_motor_value[7] = buff_motor_value1[7];
	buff_motor_value[8] = buff_motor_value1[8];
	buff_motor_value[9] = buff_motor_value1[9];
	buff_motor_value[10] = buff_motor_value1[10];
	buff_motor_value[11] = buff_motor_value1[11];

	buff_motor_value[12] = buff_motor_value1[12];
	buff_motor_value[13] = buff_motor_value1[13];
	buff_motor_value[14] = buff_motor_value1[14];

	buff_motor_value[15] = buff_motor_value1[15];
	buff_motor_value[16] = buff_motor_value1[16];
	buff_motor_value[17] = buff_motor_value1[17];

	for(int i = 0; i <= (TABLE-1); i++)												    //테이블 증가
	{
		for(int j = 0; j < 18; j++)												//테이블내의 테이터 증가
		{
			motor_value[j][i] = (i * buff_motor_value[j] + ((TABLE-1) - i) * buff_motor_value1[j]) / (TABLE-1);       //내분점공식
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

void CSimulate::R_foot_center(float X_M, float Z_M)
{
	float H = sqrt((X_M*X_M)+((2*L)-Z_M-10)*((2*L)-Z_M-10));

	float the_1 = acos(H/(2*L));
	float the_0 = atan(X_M/((2*L)-Z_M-10));

	float result_the_a = the_0 + the_1;
	float result_the_b = 2 * the_1;
	float result_the_c = the_1 - the_0;

	buff_motor_value[0] = buff_motor_value1[0]; 
	buff_motor_value[1] = buff_motor_value1[1];
	buff_motor_value[2]  =buff_motor_value1[2];
	buff_motor_value[3] = buff_motor_value1[3];
	buff_motor_value[4] = buff_motor_value1[4] + L_shift_result;
	buff_motor_value[5] = buff_motor_value1[5];

	buff_motor_value[6] = buff_motor_value1[6]; 
	buff_motor_value[7] = result_the_c;
	buff_motor_value[8] = result_the_b;
	buff_motor_value[9] = result_the_a;
	buff_motor_value[10] = buff_motor_value1[10];
	buff_motor_value[11] = buff_motor_value1[11];

	buff_motor_value[12] = buff_motor_value1[12];
	buff_motor_value[13] = buff_motor_value1[13];
	buff_motor_value[14] = buff_motor_value1[14];

	buff_motor_value[15] = buff_motor_value1[15];
	buff_motor_value[16] = buff_motor_value1[16];
	buff_motor_value[17] = buff_motor_value1[17];

	for(int i = 0; i <= (TABLE-1); i++)												    //테이블 증가
	{
		for(int j = 0; j < 18; j++)												//테이블내의 테이터 증가
		{
			motor_value[j][i] = (i * buff_motor_value[j] + ((TABLE-1) - i) * buff_motor_value1[j]) / (TABLE-1);       //내분점공식
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

void CSimulate::R_foot_up_(float X_M, float Z_M)
{
	float H = sqrt((X_M*X_M)+((2*L)-Z_M-10)*((2*L)-Z_M-10));

	float the_1 = acos(H/(2*L));
	float the_0 = atan(X_M/((2*L)-Z_M-10));

	float result_the_a = the_0 + the_1;
	float result_the_b = 2 * the_1;
	float result_the_c = the_1 - the_0;

	buff_motor_value1[0] = buff_motor_value[0]; 
	buff_motor_value1[1] = buff_motor_value[1];
	buff_motor_value1[2]  =buff_motor_value[2];
	buff_motor_value1[3] = buff_motor_value[3];
	buff_motor_value1[4] = buff_motor_value[4];
	buff_motor_value1[5] = buff_motor_value[5];

	buff_motor_value1[6] = buff_motor_value[6]; 
	buff_motor_value1[7] = result_the_c;
	buff_motor_value1[8] = result_the_b;
	buff_motor_value1[9] = result_the_a;
	buff_motor_value1[10] = buff_motor_value[10];
	buff_motor_value1[11] = buff_motor_value[11];

	buff_motor_value1[12] = buff_motor_value[12];
	buff_motor_value1[13] = buff_motor_value[13];
	buff_motor_value1[14] = buff_motor_value[14];

	buff_motor_value1[15] = buff_motor_value[15];
	buff_motor_value1[16] = buff_motor_value[16];
	buff_motor_value1[17] = buff_motor_value[17];

// 	for(int i = 0; i <= (TABLE-1); i++)												    //테이블 증가
// 	{
// 		for(int j = 0; j < 18; j++)												//테이블내의 테이터 증가
// 		{
// 			motor_value[j][i] = (i * buff_motor_value[j] + ((TABLE-1) - i) * buff_motor_value1[j]) / (TABLE-1);       //내분점공식
// 		}
// 	}
// 
// 	for(int k = 0; k < TABLE; k++)
// 	{
// 		for(int l = 0; l < 18; l++)
// 		{ 
// 			motor[l] = motor_value[l][k];
// 		}
// 		sv_motor();
// 	}
}

void CSimulate::sit_move()
{
// 	DX_move(1,512,535);
// 	DX_move(2,512,475);
// 	DX_move(3,512,420);
// 	DX_move(4,512,465);
// 	DX_move(5,512,475);
// 	DX_move(6,512,483);
// 
// 	DX_move(7,512,475);
// 	DX_move(8,512,610);
// 	DX_move(9,512,670);
// 	DX_move(10,512,560);
// 	DX_move(11,512,540);
// 	DX_move(12,512,480);
// 
// 	DX_move(13,512,478);
// 	DX_move(14,512,514);
// 	DX_move(15,512,519);
// 
// 	DX_move(16,512,545);
// 	DX_move(17,512,519);
// 	DX_move(18,512,514);
// 
// 	m_pNodeMgr->SetAngle(FOOT_MOTOR_L,  motor[0]);
// 	m_pNodeMgr->SetAngle(FOOT_L,        motor[1]);
// 	m_pNodeMgr->SetAngle(LEG_LOW_L,     motor[2]);
// 	m_pNodeMgr->SetAngle(LEG_MIDDLE_L,  motor[3]);
// 	m_pNodeMgr->SetAngle(LEG_UPMOTOR_L, motor[4]);
// 	m_pNodeMgr->SetAngle(LEG_UP_L,      motor[5]);
// 
// 	m_pNodeMgr->SetAngle(FOOT_MOTOR_R,  motor[6]);
// 	m_pNodeMgr->SetAngle(FOOT_R,        motor[7]);
// 	m_pNodeMgr->SetAngle(LEG_LOW_R,     motor[8]);
// 	m_pNodeMgr->SetAngle(LEG_MIDDLE_R,  motor[9]);
// 	m_pNodeMgr->SetAngle(LEG_UPMOTOR_R, motor[10]);
// 	m_pNodeMgr->SetAngle(LEG_UP_R,      motor[11]);
// 
// 	m_pNodeMgr->SetAngle(ARM_SHOULDER_L, motor[12]);
// 	m_pNodeMgr->SetAngle(ARM_MIDDLE_L,   motor[13]);
// 	m_pNodeMgr->SetAngle(ARM_LOW_L,      motor[14]);
// 
// 	m_pNodeMgr->SetAngle(ARM_SHOULDER_R, motor[15]);
// 	m_pNodeMgr->SetAngle(ARM_MIDDLE_R,   motor[16]);
// 	m_pNodeMgr->SetAngle(ARM_LOW_R,      motor[17]);
}
