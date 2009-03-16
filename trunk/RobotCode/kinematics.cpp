#include "allHeader.h"

/************************************************************************/
/*                    kinematics function                               */
/************************************************************************/
void sv_motor()
{
	for(r=0;r<18;r++)
	{
		DX_move(r+1,1023,motor[r]);
	}
}

void initialize()
{
	buff_motor_value[0] = motor_value0; 
	buff_motor_value[1] = motor_value1;
	buff_motor_value[2] = motor_value2;
	buff_motor_value[3] = motor_value3;
	buff_motor_value[4] = motor_value4;
	buff_motor_value[5] = motor_value5;

	buff_motor_value[6] = motor_value6;
	buff_motor_value[7] = motor_value7;
	buff_motor_value[8] = motor_value8;
	buff_motor_value[9] = motor_value9;
	buff_motor_value[10] = motor_value10;
	buff_motor_value[11] = motor_value11;

	buff_motor_value[12] = motor_value12;
	buff_motor_value[13] = motor_value13;
	buff_motor_value[14] = motor_value14;

	buff_motor_value[15] = motor_value15;
	buff_motor_value[16] = motor_value16;
	buff_motor_value[17] = motor_value17;


	DX_move(1,100,buff_motor_value[0]);
	DX_move(2,100,buff_motor_value[1]);
	DX_move(3,100,buff_motor_value[2]);
	DX_move(4,100,buff_motor_value[3]);
	DX_move(5,100,buff_motor_value[4]);
	DX_move(6,100,buff_motor_value[5]);

	DX_move(7,100,buff_motor_value[6]);
	DX_move(8,100,buff_motor_value[7]);
	DX_move(9,100,buff_motor_value[8]);
	DX_move(10,100,buff_motor_value[9]);
	DX_move(11,100,buff_motor_value[10]);
	DX_move(12,100,buff_motor_value[11]);

	DX_move(19,100,buff_motor_value[12]);
	DX_move(20,100,buff_motor_value[13]);
	DX_move(21,100,buff_motor_value[14]);

	DX_move(22,100,buff_motor_value[15]);
	DX_move(23,100,buff_motor_value[16]);
	DX_move(24,100,buff_motor_value[17]);


}

void sit(Z)
{
	result = acos(((2*L)-Z)/(2*L));
	result = (result * 180) / 3.14 ; 

	sit_result = result * 3.41;	

	buff_motor_value1[0] = buff_motor_value[0]; 
	buff_motor_value1[1] = buff_motor_value[1] - sit_result;
	buff_motor_value1[2] = buff_motor_value[2] - (2 * sit_result);
	buff_motor_value1[3] = buff_motor_value[3] - sit_result;
	buff_motor_value1[4] = buff_motor_value[4];
	buff_motor_value1[5] = buff_motor_value[5];

	buff_motor_value1[6] = buff_motor_value[6];
	buff_motor_value1[7] = buff_motor_value[7] + sit_result;
	buff_motor_value1[8] = buff_motor_value[8] + (2*sit_result);
	buff_motor_value1[9] = buff_motor_value[9] + sit_result;
	buff_motor_value1[10] = buff_motor_value[10];
	buff_motor_value1[11] = buff_motor_value[11];

	buff_motor_value1[12] = buff_motor_value[12];
	buff_motor_value1[13] = buff_motor_value[13];
	buff_motor_value1[14] = buff_motor_value[14];

	buff_motor_value1[15] = buff_motor_value[15];
	buff_motor_value1[16] = buff_motor_value[16];
	buff_motor_value1[17] = buff_motor_value[17];

	for(i=0 ; i<=(TABLE-1) ; i++)												    //테이블 증가
	{
		for(j=0 ; j<18 ; j++)												//테이블내의 테이터 증가
		{
			motor_value[j][i] = ( i * buff_motor_value1[j] + ((TABLE-1) - i) * buff_motor_value[j] ) / (TABLE-1);       //내분점공식
		}
	}

	for(k=0 ; k<TABLE ; k++)
	{
		for(l=0;l<18;l++)
		{ 
			motor[l] = motor_value[l][k];
		}
		sv_motor();
		delay_ms(10);
	}	


	usart1_transmit(1);
	usart1_transmit(-((buff_motor_value1[1]-buff_motor_value[1])/3.41));
	usart1_transmit(2);
	usart1_transmit(((buff_motor_value1[2]-buff_motor_value[2])/3.41));
	usart1_transmit(3);
	usart1_transmit(-((buff_motor_value1[3]-buff_motor_value[3])/3.41));

	usart1_transmit(7);
	usart1_transmit(((buff_motor_value1[7]-buff_motor_value[7])/3.41));
	usart1_transmit(8);
	usart1_transmit(-((buff_motor_value1[8]-buff_motor_value[8])/3.41));
	usart1_transmit(9);
	usart1_transmit(((buff_motor_value1[9]-buff_motor_value[9])/3.41));
}

void L_shift(Y)
{
	result = asin(Y/(2*L));
	result = (result * 180) / 3.14 ; 

	L_shift_result = result * 3.41;

	buff_motor_value[0] = buff_motor_value1[0] - L_shift_result-1; //-10
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

	for(i=0 ; i<=(TABLE-1) ; i++)												    //테이블 증가
	{
		for(j=0 ; j<18 ; j++)												//테이블내의 테이터 증가
		{
			motor_value[j][i] = ( i * buff_motor_value[j] + ((TABLE-1) - i) * buff_motor_value1[j] ) / (TABLE-1);       //내분점공식
		}
	}

	for(k=0 ; k<TABLE ; k++)
	{
		for(l=0;l<18;l++)
		{ 
			motor[l] = motor_value[l][k];
		}
		sv_motor();
		delay_ms(5);
	}	
	usart1_transmit(0);
	usart1_transmit((buff_motor_value[0]-buff_motor_value1[0])/3.41);
	usart1_transmit(4);
	usart1_transmit((buff_motor_value[4]-buff_motor_value1[4])/3.41);
	usart1_transmit(6);
	usart1_transmit((buff_motor_value[6]-buff_motor_value1[6])/3.41);
	usart1_transmit(10);
	usart1_transmit((buff_motor_value[10]-buff_motor_value1[10])/3.41);
}

void R_foot_up(X_M,Z_M)
{
	H = sqrt((X_M*X_M)+((2*L)-Z_M-10)*((2*L)-Z_M-10));

	the_1 = acos(H/(2*L));
	the_1 = (the_1 * 180) / 3.14 ; 
	the_0 = atan(X_M/((2*L)-Z_M-10));
	the_0 = (the_0 * 180) / 3.14 ; 

	result_the_a = the_0 + the_1;
	result_the_b = 2 * the_1;
	result_the_c = the_1 - the_0;

	the_a_result = result_the_a * 3.41;  
	the_b_result = result_the_b * 3.41;  
	the_c_result = result_the_c * 3.41;  

	buff_motor_value1[0] = buff_motor_value[0]; 
	buff_motor_value1[1] = buff_motor_value[1];
	buff_motor_value1[2]  =buff_motor_value[2];
	buff_motor_value1[3] = buff_motor_value[3];
	buff_motor_value1[4] = buff_motor_value[4] + L_shift_result;
	buff_motor_value1[5] = buff_motor_value[5];

	buff_motor_value1[6] = buff_motor_value[6]; 
	buff_motor_value1[7] = motor_value7 + the_c_result;
	buff_motor_value1[8] = motor_value8 + the_b_result;
	buff_motor_value1[9] = motor_value9 + the_a_result;
	buff_motor_value1[10] = buff_motor_value[10];
	buff_motor_value1[11] = buff_motor_value[11];

	buff_motor_value1[12] = buff_motor_value[12];
	buff_motor_value1[13] = buff_motor_value[13];
	buff_motor_value1[14] = buff_motor_value[14];

	buff_motor_value1[15] = buff_motor_value[15];
	buff_motor_value1[16] = buff_motor_value[16];
	buff_motor_value1[17] = buff_motor_value[17];

	for(i=0 ; i<=(TABLE-1) ; i++)												    //테이블 증가
	{
		for(j=0 ; j<18 ; j++)												//테이블내의 테이터 증가
		{
			motor_value[j][i] = ( i * buff_motor_value1[j] + ((TABLE-1) - i) * buff_motor_value[j] ) / (TABLE-1);       //내분점공식
		}
	}

	for(k=0 ; k<TABLE ; k++)
	{
		for(l=0;l<18;l++)
		{ 
			motor[l] = motor_value[l][k];
		}
		sv_motor();
		delay_ms(1);
	}
	usart1_transmit(7);
	usart1_transmit(((buff_motor_value1[7]-buff_motor_value[7])/3.41));
	usart1_transmit(8);
	usart1_transmit(-((buff_motor_value1[8]-buff_motor_value[8])/3.41));
	usart1_transmit(9);
	usart1_transmit(((buff_motor_value1[9]-buff_motor_value[9])/3.41));
}

void R_foot_down(X_B,Z_B)
{
	H = sqrt((X_B*X_B)+((2*L)-Z_B-10)*((2*L)-Z_B-10));

	the_1 = acos(H/(2*L));
	the_1 = (the_1 * 180) / 3.14 ; 
	the_0 = atan(X_B/((2*L)-Z_B-10));
	the_0 = (the_0 * 180) / 3.14 ; 

	result_the_a = the_0 + the_1;
	result_the_b = 2 * the_1;
	result_the_c = the_1 - the_0;

	the_a_result = result_the_a * 3.41;  
	the_b_result = result_the_b * 3.41;  
	the_c_result = result_the_c * 3.41;  

	buff_motor_value[0] = buff_motor_value1[0]; 
	buff_motor_value[1] = buff_motor_value1[1];
	buff_motor_value[2]  =buff_motor_value1[2];
	buff_motor_value[3] = buff_motor_value1[3];
	buff_motor_value[4] = buff_motor_value1[4];
	buff_motor_value[5] = buff_motor_value1[5];

	buff_motor_value[6] = buff_motor_value1[6]; 
	buff_motor_value[7] = motor_value7 + the_c_result;
	buff_motor_value[8] = motor_value8 + the_b_result;
	buff_motor_value[9] = motor_value9 + the_a_result;
	buff_motor_value[10] = buff_motor_value1[10];
	buff_motor_value[11] = buff_motor_value1[11];

	buff_motor_value[12] = buff_motor_value1[12];
	buff_motor_value[13] = buff_motor_value1[13];
	buff_motor_value[14] = buff_motor_value1[14];

	buff_motor_value[15] = buff_motor_value1[15];
	buff_motor_value[16] = buff_motor_value1[16];
	buff_motor_value[17] = buff_motor_value1[17];

	for(i=0 ; i<=(TABLE-1) ; i++)												    //테이블 증가
	{
		for(j=0 ; j<18 ; j++)												//테이블내의 테이터 증가
		{
			motor_value[j][i] = ( i * buff_motor_value[j] + ((TABLE-1) - i) * buff_motor_value1[j] ) / (TABLE-1);       //내분점공식
		}
	}

	for(k=0 ; k<TABLE ; k++)
	{
		for(l=0;l<18;l++)
		{ 
			motor[l] = motor_value[l][k];
		}
		sv_motor();
		delay_ms(1);
	}
	usart1_transmit(7);
	usart1_transmit((buff_motor_value[7]-buff_motor_value1[7])/3.41);
	usart1_transmit(8);
	usart1_transmit(-((buff_motor_value[8]-buff_motor_value1[8])/3.41));
	usart1_transmit(9);
	usart1_transmit((buff_motor_value[9]-buff_motor_value1[9])/3.41);
}

void move_R(Y)
{
	result = asin(Y/(2*L));
	result = (result * 180) / 3.14 ; 

	R_shift_result = result * 3.41;

	/*buff_motor_value1[0] = buff_motor_value[0] + R_shift_result+1; //+10
	buff_motor_value1[1] = buff_motor_value[1];
	buff_motor_value1[2] = buff_motor_value[2];
	buff_motor_value1[3] = buff_motor_value[3];
	buff_motor_value1[4] = buff_motor_value[4];
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

	for(i=0 ; i<=(TABLE-1) ; i++)												    //테이블 증가
	{
	for(j=0 ; j<18 ; j++)												//테이블내의 테이터 증가
	{
	motor_value[j][i] = ( i * buff_motor_value1[j] + ((TABLE-1) - i) * buff_motor_value[j] ) / (TABLE-1);       //내분점공식
	}
	}

	for(k=0 ; k<TABLE ; k++)
	{
	for(l=0;l<18;l++)
	{ 
	motor[l] = motor_value[l][k];
	}
	sv_motor();
	delay_ms(5);
	}	
	usart1_transmit(0);
	usart1_transmit((buff_motor_value1[0]-buff_motor_value[0])/3.41);
	usart1_transmit(4);
	usart1_transmit(13);
	usart1_transmit(6);
	usart1_transmit((buff_motor_value1[6]-buff_motor_value[6])/3.41);
	usart1_transmit(10);
	usart1_transmit((buff_motor_value1[10]-buff_motor_value[10])/3.41);*/
}


void move_center(X_R,Z_R)
{
	H = sqrt((X_R*X_R)+((2*L)-Z_R-10)*((2*L)-Z_R-10));

	the_1 = acos(H/(2*L));
	the_1 = (the_1 * 180) / 3.14 ; 
	the_0 = atan(X_R/((2*L)-Z_R-10));
	the_0 = (the_0 * 180) / 3.14 ; 

	result_the_a = the_0 + the_1;
	result_the_b = 2 * the_1;
	result_the_c = the_1 - the_0;

	the_a_result = result_the_a * 3.41;  
	the_b_result = result_the_b * 3.41;  
	the_c_result = result_the_c * 3.41;  

	buff_motor_value[0] = buff_motor_value1[0] + R_shift_result+1; 
	buff_motor_value[1] = motor_value1 - the_c_result;
	buff_motor_value[2] = motor_value2 - the_b_result;
	buff_motor_value[3] = motor_value3 - the_a_result;
	buff_motor_value[4] = buff_motor_value1[4];
	buff_motor_value[5] = buff_motor_value1[5];

	buff_motor_value[6] = buff_motor_value1[6] + R_shift_result; 
	buff_motor_value[7] = motor_value7 + sit_result;
	buff_motor_value[8] = motor_value8 + (2*sit_result);
	buff_motor_value[9] = motor_value9 + sit_result;
	buff_motor_value[10] = buff_motor_value1[10] + R_shift_result;
	buff_motor_value[11] = buff_motor_value1[11];

	buff_motor_value[12] = buff_motor_value1[12];
	buff_motor_value[13] = buff_motor_value1[13];
	buff_motor_value[14] = buff_motor_value1[14];

	buff_motor_value[15] = buff_motor_value1[15];
	buff_motor_value[16] = buff_motor_value1[16];
	buff_motor_value[17] = buff_motor_value1[17];

	for(i=0 ; i<=(TABLE-1) ; i++)												    //테이블 증가
	{
		for(j=0 ; j<18 ; j++)												//테이블내의 테이터 증가
		{
			motor_value[j][i] = ( i * buff_motor_value[j] + ((TABLE-1) - i) * buff_motor_value1[j] ) / (TABLE-1);       //내분점공식
		}
	}

	for(k=0 ; k<TABLE ; k++)
	{
		for(l=0;l<18;l++)
		{ 
			motor[l] = motor_value[l][k];
		}
		sv_motor();
		delay_ms(7);
	}
	usart1_transmit(1);
	usart1_transmit(-((buff_motor_value[1]-buff_motor_value1[1])/3.41));
	usart1_transmit(2);
	usart1_transmit(((buff_motor_value[2]-buff_motor_value1[2])/3.41));
	usart1_transmit(3);
	usart1_transmit(-((buff_motor_value[3]-buff_motor_value1[3])/3.41));

	usart1_transmit(7);
	usart1_transmit((buff_motor_value[7]-buff_motor_value1[7])/3.41);
	usart1_transmit(8);
	usart1_transmit(-((buff_motor_value[8]-buff_motor_value1[8])/3.41));
	usart1_transmit(9);
	usart1_transmit((buff_motor_value[9]-buff_motor_value1[9])/3.41);
}

void R_shift(Y)
{
	result = asin(Y/(2*L));
	result = (result * 180) / 3.14 ; 

	R_shift_result = result * 3.41;

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

	for(i=0 ; i<=(TABLE-1) ; i++)												    //테이블 증가
	{
		for(j=0 ; j<18 ; j++)												//테이블내의 테이터 증가
		{
			motor_value[j][i] = ( i * buff_motor_value1[j] + ((TABLE-1) - i) * buff_motor_value[j] ) / (TABLE-1);       //내분점공식
		}
	}

	for(k=0 ; k<TABLE ; k++)
	{
		for(l=0;l<18;l++)
		{ 
			motor[l] = motor_value[l][k];
		}
		sv_motor();
		delay_ms(5);
	}	
	usart1_transmit(0);
	usart1_transmit((buff_motor_value1[0]-buff_motor_value[0])/3.41);
	usart1_transmit(4);
	usart1_transmit((buff_motor_value1[4]-buff_motor_value[4])/3.41);
	usart1_transmit(6);
	usart1_transmit((buff_motor_value1[6]-buff_motor_value[6])/3.41);
	usart1_transmit(10);
	usart1_transmit((buff_motor_value1[10]-buff_motor_value[10])/3.41);
}

void L_foot_center(X_M,Z_M)
{
	H = sqrt((X_M*X_M)+((2*L)-Z_M-10)*((2*L)-Z_M-10));

	the_1 = acos(H/(2*L));
	the_1 = (the_1 * 180) / 3.14 ; 
	the_0 = atan(X_M/((2*L)-Z_M-10));
	the_0 = (the_0 * 180) / 3.14 ; 

	result_the_a = the_0 + the_1;
	result_the_b = 2 * the_1;
	result_the_c = the_1 - the_0;

	the_a_result = result_the_a * 3.41;  
	the_b_result = result_the_b * 3.41;  
	the_c_result = result_the_c * 3.41;  

	buff_motor_value[0] = buff_motor_value1[0]; 
	buff_motor_value[1] = motor_value1 - the_c_result;
	buff_motor_value[2] = motor_value2 - the_b_result;
	buff_motor_value[3] = motor_value3 - the_a_result;
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

	for(i=0 ; i<=(TABLE-1) ; i++)												    //테이블 증가
	{
		for(j=0 ; j<18 ; j++)												//테이블내의 테이터 증가
		{
			motor_value[j][i] = ( i * buff_motor_value[j] + ((TABLE-1) - i) * buff_motor_value1[j] ) / (TABLE-1);       //내분점공식
		}
	}

	for(k=0 ; k<TABLE ; k++)
	{
		for(l=0;l<18;l++)
		{ 
			motor[l] = motor_value[l][k];
		}
		sv_motor();
		delay_ms(1);
	}
	usart1_transmit(1);
	usart1_transmit(-((buff_motor_value[1]-buff_motor_value1[1])/3.41));
	usart1_transmit(2);
	usart1_transmit(((buff_motor_value[2]-buff_motor_value1[2])/3.41));
	usart1_transmit(3);
	usart1_transmit(-((buff_motor_value[3]-buff_motor_value1[3])/3.41));
}

void L_foot_up(X_M,Z_M)
{
	H = sqrt((X_M*X_M)+((2*L)-Z_M-10)*((2*L)-Z_M-10));

	the_1 = acos(H/(2*L));
	the_1 = (the_1 * 180) / 3.14 ; 
	the_0 = atan(X_M/((2*L)-Z_M-10));
	the_0 = (the_0 * 180) / 3.14 ; 

	result_the_a = the_0 + the_1;
	result_the_b = 2 * the_1;
	result_the_c = the_1 - the_0;

	the_a_result = result_the_a * 3.41;  
	the_b_result = result_the_b * 3.41;  
	the_c_result = result_the_c * 3.41;  

	buff_motor_value1[0] = buff_motor_value[0]; 
	buff_motor_value1[1] = motor_value1 - the_c_result;
	buff_motor_value1[2] = motor_value2 - the_b_result;
	buff_motor_value1[3] = motor_value3 - the_a_result;
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

	/*for(i=0 ; i<=(TABLE-1) ; i++)												    //테이블 증가
	{
	for(j=0 ; j<18 ; j++)												//테이블내의 테이터 증가
	{
	motor_value[j][i] = ( i * buff_motor_value1[j] + ((TABLE-1) - i) * buff_motor_value[j] ) / (TABLE-1);       //내분점공식
	}
	}

	for(k=0 ; k<TABLE ; k++)
	{
	for(l=0;l<18;l++)
	{ 
	motor[l] = motor_value[l][k];
	}
	sv_motor();
	delay_ms(1);
	}*/
	usart1_transmit(1);
	usart1_transmit(-((buff_motor_value1[1]-buff_motor_value[1])/3.41));
	usart1_transmit(2);
	usart1_transmit(((buff_motor_value1[2]-buff_motor_value[2])/3.41));
	usart1_transmit(3);
	usart1_transmit(-((buff_motor_value1[3]-buff_motor_value[3])/3.41));
}

void L_foot_down(X_B,Z_B)
{
	H = sqrt((X_B*X_B)+((2*L)-Z_B-10)*((2*L)-Z_B-10));

	the_1 = acos(H/(2*L));
	the_1 = (the_1 * 180) / 3.14 ; 
	the_0 = atan(X_B/((2*L)-Z_B-10));
	the_0 = (the_0 * 180) / 3.14 ; 

	result_the_a = the_0 + the_1;
	result_the_b = 2 * the_1;
	result_the_c = the_1 - the_0;

	the_a_result = result_the_a * 3.41;  
	the_b_result = result_the_b * 3.41;  
	the_c_result = result_the_c * 3.41;  

	buff_motor_value[0] = buff_motor_value1[0]; 
	buff_motor_value[1] = motor_value1 - the_c_result;
	buff_motor_value[2] = motor_value2 - the_b_result;
	buff_motor_value[3] = motor_value3 - the_a_result;
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

	for(i=0 ; i<=(TABLE-1) ; i++)												    //테이블 증가
	{
		for(j=0 ; j<18 ; j++)												//테이블내의 테이터 증가
		{
			motor_value[j][i] = ( i * buff_motor_value[j] + ((TABLE-1) - i) * buff_motor_value1[j] ) / (TABLE-1);       //내분점공식
		}
	}

	for(k=0 ; k<TABLE ; k++)
	{
		for(l=0;l<18;l++)
		{ 
			motor[l] = motor_value[l][k];
		}
		sv_motor();
		delay_ms(1);
	}
	usart1_transmit(1);
	usart1_transmit(-((buff_motor_value[1]-buff_motor_value1[1])/3.41));
	usart1_transmit(2);
	usart1_transmit(((buff_motor_value[2]-buff_motor_value1[2])/3.41));
	usart1_transmit(3);
	usart1_transmit(-((buff_motor_value[3]-buff_motor_value1[3])/3.41));
}

void move_L(Y)
{
	result = asin(Y/(2*L));
	result = (result * 180) / 3.14 ; 

	R_shift_result = result * 3.41;

	/*buff_motor_value1[0] = buff_motor_value[0] - R_shift_result; 
	buff_motor_value1[1] = buff_motor_value[1];
	buff_motor_value1[2] = buff_motor_value[2];
	buff_motor_value1[3] = buff_motor_value[3];
	buff_motor_value1[4] = buff_motor_value[4] - R_shift_result;
	buff_motor_value1[5] = buff_motor_value[5];

	buff_motor_value1[6] = buff_motor_value[6] - R_shift_result;
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

	for(i=0 ; i<=(TABLE-1) ; i++)												    //테이블 증가
	{
	for(j=0 ; j<18 ; j++)												//테이블내의 테이터 증가
	{
	motor_value[j][i] = ( i * buff_motor_value1[j] + ((TABLE-1) - i) * buff_motor_value[j] ) / (TABLE-1);       //내분점공식
	}
	}

	for(k=0 ; k<TABLE ; k++)
	{
	for(l=0;l<18;l++)
	{ 
	motor[l] = motor_value[l][k];
	}
	sv_motor();
	delay_ms(5);
	}
	usart1_transmit(0);
	usart1_transmit((buff_motor_value1[0]-buff_motor_value[0])/3.41);
	usart1_transmit(4);
	usart1_transmit((buff_motor_value1[4]-buff_motor_value[4])/3.41);
	usart1_transmit(6);
	usart1_transmit((buff_motor_value1[6]-buff_motor_value[6])/3.41);
	usart1_transmit(10);
	usart1_transmit(-13);*/
}

void move_center_(X_R,Z_R)
{
	H = sqrt((X_R*X_R)+((2*L)-Z_R-10)*((2*L)-Z_R-10));

	the_1 = acos(H/(2*L));
	the_1 = (the_1 * 180) / 3.14 ; 
	the_0 = atan(X_R/((2*L)-Z_R-10));
	the_0 = (the_0 * 180) / 3.14 ; 

	result_the_a = the_0 + the_1;
	result_the_b = 2 * the_1;
	result_the_c = the_1 - the_0;

	the_a_result = result_the_a * 3.41;  
	the_b_result = result_the_b * 3.41;  
	the_c_result = result_the_c * 3.41;  

	buff_motor_value[0] = buff_motor_value1[0] - R_shift_result; 
	buff_motor_value[1] = motor_value1 - sit_result;
	buff_motor_value[2] = motor_value2 - (2*sit_result);
	buff_motor_value[3] = motor_value3 - sit_result;
	buff_motor_value[4] = buff_motor_value1[4] - R_shift_result;
	buff_motor_value[5] = buff_motor_value1[5];

	buff_motor_value[6] = buff_motor_value1[6] - R_shift_result; 
	buff_motor_value[7] = motor_value7 + the_c_result;
	buff_motor_value[8] = motor_value8 + the_b_result;
	buff_motor_value[9] = motor_value9 + the_a_result;
	buff_motor_value[10] = buff_motor_value1[10];
	buff_motor_value[11] = buff_motor_value1[11];

	buff_motor_value[12] = buff_motor_value1[12];
	buff_motor_value[13] = buff_motor_value1[13];
	buff_motor_value[14] = buff_motor_value1[14];

	buff_motor_value[15] = buff_motor_value1[15];
	buff_motor_value[16] = buff_motor_value1[16];
	buff_motor_value[17] = buff_motor_value1[17];

	for(i=0 ; i<=(TABLE-1) ; i++)												    //테이블 증가
	{
		for(j=0 ; j<18 ; j++)												//테이블내의 테이터 증가
		{
			motor_value[j][i] = ( i * buff_motor_value[j] + ((TABLE-1) - i) * buff_motor_value1[j] ) / (TABLE-1);       //내분점공식
		}
	}

	for(k=0 ; k<TABLE ; k++)
	{
		for(l=0;l<18;l++)
		{ 
			motor[l] = motor_value[l][k];
		}
		sv_motor();
		delay_ms(7);
	}
	usart1_transmit(1);
	usart1_transmit(-((buff_motor_value[1]-buff_motor_value1[1])/3.41));
	usart1_transmit(2);
	usart1_transmit(((buff_motor_value[2]-buff_motor_value1[2])/3.41));
	usart1_transmit(3);
	usart1_transmit(-((buff_motor_value[3]-buff_motor_value1[3])/3.41));

	usart1_transmit(7);
	usart1_transmit((buff_motor_value[7]-buff_motor_value1[7])/3.41);
	usart1_transmit(8);
	usart1_transmit(-((buff_motor_value[8]-buff_motor_value1[8])/3.41));
	usart1_transmit(9);
	usart1_transmit((buff_motor_value[9]-buff_motor_value1[9])/3.41);
}

void L_shift_(Y)
{
	result = asin(Y/(2*L));
	result = (result * 180) / 3.14 ; 

	L_shift_result = result * 3.41;

	buff_motor_value1[0] = buff_motor_value[0] - L_shift_result-1; //-10
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

	for(i=0 ; i<=(TABLE-1) ; i++)												    //테이블 증가
	{
		for(j=0 ; j<18 ; j++)												//테이블내의 테이터 증가
		{
			motor_value[j][i] = ( i * buff_motor_value1[j] + ((TABLE-1) - i) * buff_motor_value[j] ) / (TABLE-1);       //내분점공식
		}
	}

	for(k=0 ; k<TABLE ; k++)
	{
		for(l=0;l<18;l++)
		{ 
			motor[l] = motor_value[l][k];
		}
		sv_motor();
		delay_ms(5);
	}	
	usart1_transmit(0);
	usart1_transmit((buff_motor_value1[0]-buff_motor_value[0])/3.41);
	usart1_transmit(4);
	usart1_transmit((buff_motor_value1[4]-buff_motor_value[4])/3.41);
	usart1_transmit(6);
	usart1_transmit((buff_motor_value1[6]-buff_motor_value[6])/3.41);
	usart1_transmit(10);
	usart1_transmit((buff_motor_value1[10]-buff_motor_value[10])/3.41);
}

void R_foot_center(X_M,Z_M)
{
	H = sqrt((X_M*X_M)+((2*L)-Z_M-10)*((2*L)-Z_M-10));

	the_1 = acos(H/(2*L));
	the_1 = (the_1 * 180) / 3.14 ; 
	the_0 = atan(X_M/((2*L)-Z_M-10));
	the_0 = (the_0 * 180) / 3.14 ; 

	result_the_a = the_0 + the_1;
	result_the_b = 2 * the_1;
	result_the_c = the_1 - the_0;

	the_a_result = result_the_a * 3.41;  
	the_b_result = result_the_b * 3.41;  
	the_c_result = result_the_c * 3.41;  

	buff_motor_value[0] = buff_motor_value1[0]; 
	buff_motor_value[1] = buff_motor_value1[1];
	buff_motor_value[2]  =buff_motor_value1[2];
	buff_motor_value[3] = buff_motor_value1[3];
	buff_motor_value[4] = buff_motor_value1[4] + L_shift_result;
	buff_motor_value[5] = buff_motor_value1[5];

	buff_motor_value[6] = buff_motor_value1[6]; 
	buff_motor_value[7] = motor_value7 + the_c_result;
	buff_motor_value[8] = motor_value8 + the_b_result;
	buff_motor_value[9] = motor_value9 + the_a_result;
	buff_motor_value[10] = buff_motor_value1[10];
	buff_motor_value[11] = buff_motor_value1[11];

	buff_motor_value[12] = buff_motor_value1[12];
	buff_motor_value[13] = buff_motor_value1[13];
	buff_motor_value[14] = buff_motor_value1[14];

	buff_motor_value[15] = buff_motor_value1[15];
	buff_motor_value[16] = buff_motor_value1[16];
	buff_motor_value[17] = buff_motor_value1[17];

	for(i=0 ; i<=(TABLE-1) ; i++)												    //테이블 증가
	{
		for(j=0 ; j<18 ; j++)												//테이블내의 테이터 증가
		{
			motor_value[j][i] = ( i * buff_motor_value[j] + ((TABLE-1) - i) * buff_motor_value1[j] ) / (TABLE-1);       //내분점공식
		}
	}

	for(k=0 ; k<TABLE ; k++)
	{
		for(l=0;l<18;l++)
		{ 
			motor[l] = motor_value[l][k];
		}
		sv_motor();
		delay_ms(2);
	}
	usart1_transmit(7);
	usart1_transmit((buff_motor_value[7]-buff_motor_value1[7])/3.41);
	usart1_transmit(8);
	usart1_transmit(-((buff_motor_value[8]-buff_motor_value1[8])/3.41));
	usart1_transmit(9);
	usart1_transmit((buff_motor_value[9]-buff_motor_value1[9])/3.41);

}

void R_foot_up_(X_M,Z_M)
{
	H = sqrt((X_M*X_M)+((2*L)-Z_M-10)*((2*L)-Z_M-10));

	the_1 = acos(H/(2*L));
	the_1 = (the_1 * 180) / 3.14 ; 
	the_0 = atan(X_M/((2*L)-Z_M-10));
	the_0 = (the_0 * 180) / 3.14 ; 

	result_the_a = the_0 + the_1;
	result_the_b = 2 * the_1;
	result_the_c = the_1 - the_0;

	the_a_result = result_the_a * 3.41;  
	the_b_result = result_the_b * 3.41;  
	the_c_result = result_the_c * 3.41;  

	buff_motor_value1[0] = buff_motor_value[0]; 
	buff_motor_value1[1] = buff_motor_value[1];
	buff_motor_value1[2]  =buff_motor_value[2];
	buff_motor_value1[3] = buff_motor_value[3];
	buff_motor_value1[4] = buff_motor_value[4];
	buff_motor_value1[5] = buff_motor_value[5];

	buff_motor_value1[6] = buff_motor_value[6]; 
	buff_motor_value1[7] = motor_value7 + the_c_result;
	buff_motor_value1[8] = motor_value8 + the_b_result;
	buff_motor_value1[9] = motor_value9 + the_a_result;
	buff_motor_value1[10] = buff_motor_value[10];
	buff_motor_value1[11] = buff_motor_value[11];

	buff_motor_value1[12] = buff_motor_value[12];
	buff_motor_value1[13] = buff_motor_value[13];
	buff_motor_value1[14] = buff_motor_value[14];

	buff_motor_value1[15] = buff_motor_value[15];
	buff_motor_value1[16] = buff_motor_value[16];
	buff_motor_value1[17] = buff_motor_value[17];

	/*for(i=0 ; i<=(TABLE-1) ; i++)												    //테이블 증가
	{
	for(j=0 ; j<18 ; j++)												//테이블내의 테이터 증가
	{
	motor_value[j][i] = ( i * buff_motor_value1[j] + ((TABLE-1) - i) * buff_motor_value[j] ) / (TABLE-1);       //내분점공식
	}
	}

	for(k=0 ; k<TABLE ; k++)
	{
	for(l=0;l<18;l++)
	{ 
	motor[l] = motor_value[l][k];
	}
	sv_motor();
	delay_ms(1);
	}*/
	usart1_transmit(7);
	usart1_transmit((buff_motor_value1[7]-buff_motor_value[7])/3.41);
	usart1_transmit(8);
	usart1_transmit(-((buff_motor_value1[8]-buff_motor_value[8])/3.41));
	usart1_transmit(9);
	usart1_transmit((buff_motor_value1[9]-buff_motor_value[9])/3.41);
}
