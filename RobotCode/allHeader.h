#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <math.h>
#include "Board.h"

typedef unsigned char       BOOLEAN;
typedef	signed char			extern int8 ;		/* Signed 8-bit extern integer */
typedef	unsigned char		extern int8U ;		/* Unsigned 8-bit extern integer */
typedef	signed short extern int	extern int16 ;		/* Signed 16-bit extern integer */
typedef	unsigned short extern int	extern int16U ;	/* Unsigned 16-bit extern integer	*/
typedef	extern int			        extern int32 ;		/* Signed 32-bit extern integer */
typedef	unsigned extern int	    extern int32U ;	/* Unsigned 32-bit extern integer */
typedef	float				FLOAT32 ;	/* 32-bit IEEE single precision */
typedef	double				FLOAT64 ;	/* 64-bit IEEE double precision */
typedef	long double			FLOAT80 ;	/* 80-bit IEEE max precision */

#define FALSE 0                         //false = 0x00000000
#define TRUE -1							//true = 0xffffffff

#define  PA0 			(1<<0) //0000 0000
#define  PA1 			(1<<1)
#define  PA2 			(1<<2)
#define  PA3 			(1<<3)
#define  PA4 			(1<<4)
#define  PA5 			(1<<5)
#define  PA6            (1<<6)	
#define  PA7            (1<<7)	
#define  PA8            (1<<8)	
#define  PA9            (1<<9)	
#define  PA10           (1<<10)
#define  PA11           (1<<11)
#define  PA12           (1<<12)
#define  PA13           (1<<13)
#define  PA14           (1<<14)
#define  PA15           (1<<15)
#define  PA16           (1<<16)
#define  PA17           (1<<17)
#define  PA18           (1<<18)
#define  PA19           (1<<19)
#define  PA20           (1<<20)
#define  PA21           (1<<21)
#define  PA22           (1<<22)
#define  PA23           (1<<23)
#define  PA24           (1<<24)
#define  PA25           (1<<25)
#define  PA26           (1<<26)
#define  PA27           (1<<27)
#define  PA28           (1<<28)
#define  PA29           (1<<29)
#define  PA30           (1<<30)
#define  PA31           (1<<31)


								// 300/1024 = 0.29
#define motor_value0 535		// 0.29 * 535 = 155.15
#define motor_value1 475		// 0.29 * 475 = 137.75
#define motor_value2 420		// 0.29 * 420 = 121.80
#define motor_value3 465		// 0.29 * 465 = 134.85
#define motor_value4 475		// 0.29 * 475 = 137.75
#define motor_value5 483		// 0.29 * 483 = 140.07

#define motor_value6 475
#define motor_value7 620
#define motor_value8 670
#define motor_value9 555
#define motor_value10 540
#define motor_value11 480

#define motor_value12 478
#define motor_value13 514
#define motor_value14 519

#define motor_value15 545
#define motor_value16 519
#define motor_value17 514

#define motor_num 18



extern extern int TABLE;

extern extern int motor[18];
extern unsigned char RXD;
extern extern int rxd[4];

extern double L, Z, Y_L, Y_R, H, the_1, the_0;

extern double result, result_the_a, result_the_b, result_the_c, result_the_a_L, result_the_b_L, result_the_c_L, the_2, the_3;

extern extern int the_2_result, the_3_result;	

extern extern int sit_result;
extern int L_shift_result;
extern int R_shift_result;
extern int the_1_result;
extern int the_a_result;
extern int the_b_result;
extern int the_c_result; 
extern int the_a_result_L;
extern int the_b_result_L;
extern int the_c_result_L; 

extern int buff_motor_value[18]; 
extern int buff_motor_value1[18];  

extern int i;
extern int j;
extern int k;
extern int l;
extern int r;
extern int t;
extern int m;
extern int u;
extern int motor_value[18][300];
extern int flag;
extern int flag1;
extern int flag2;
extern int flag3;
extern int ad[8];
extern int ad_data[8];
extern int adc_result;

extern int shift;

extern int gg;
extern int gl;
extern int zmpy, zmpx;
extern int lenx[8];
extern int leny[8];
extern int numerator, denominator, count_numerator,count_denominator;
extern int numerator_1, denominator_1, count_numerator_1,count_denominator_1;