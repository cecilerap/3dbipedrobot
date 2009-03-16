#include "allHeader.h"

int TABLE = 30;

int motor[18];
unsigned char RXD;
int rxd[4];

double L = 80;
double Z;
double Y_L;
double Y_R;
double H; 
double the_1;
double the_0;

double result;	
double result_the_a;
double result_the_b;
double result_the_c;
double result_the_a_L;
double result_the_b_L;
double result_the_c_L;

double the_2;
double the_3;
	
int the_2_result;
int the_3_result;	

int sit_result;
int L_shift_result;
int R_shift_result;
int the_1_result;
int the_a_result;
int the_b_result;
int the_c_result; 
int the_a_result_L;
int the_b_result_L;
int the_c_result_L; 

int buff_motor_value[18] ; 
int buff_motor_value1[18] ;  

int i;
int j;
int k;
int l;
int r;
int t = 0;
int m;
int u;
int motor_value[18][300];
int flag = 1;
int flag1 = 1;
int flag2 = 0;
int flag3 = 0;
int ad[8];
int ad_data[8];
int adc_result;

int shift = 0;

int gg;
int gl;
int zmpy=0, zmpx=0;
int lenx[8]={10,10,10,10,110,110,110,110};
int leny[8]={10,60,80,130,10,60,80,130};
int numerator=0, denominator=0, count_numerator=0,count_denominator=0;
int numerator_1=0, denominator_1 = 0, count_numerator_1=0,count_denominator_1=0;

/************************************************************************/
/*                    PORT_INIT function                                */
/************************************************************************/
void port_initialize(void)
{
    // First, enable the clock of the PIO
    AT91F_PMC_EnablePeriphClock ( AT91C_BASE_PMC, 1 << AT91C_ID_PIOA ) ;

    // then, we configure the PIO Lines corresponding to LED1 to LED4
    // to be outputs. No need to set these pins to be driven by the PIO because it is GPIO pins only.
    AT91F_PIO_CfgOutput( AT91C_BASE_PIOA, PA0 ) ;
    AT91F_PIO_CfgOutput( AT91C_BASE_PIOA, PA1 ) ;
    AT91F_PIO_CfgOutput( AT91C_BASE_PIOA, PA2 ) ;
    AT91F_PIO_CfgOutput( AT91C_BASE_PIOA, PA3 ) ;
    AT91F_PIO_CfgOutput( AT91C_BASE_PIOA, PA4 ) ;
    AT91F_PIO_CfgInput( AT91C_BASE_PIOA, PA5 ) ;
    AT91F_PIO_CfgOutput( AT91C_BASE_PIOA, PA6 ) ;
    AT91F_PIO_CfgOutput( AT91C_BASE_PIOA, PA7 ) ;
    AT91F_PIO_CfgOutput( AT91C_BASE_PIOA, PA8 ) ;
    AT91F_PIO_CfgOutput( AT91C_BASE_PIOA, PA9 ) ;
    AT91F_PIO_CfgOutput( AT91C_BASE_PIOA, PA10 ) ;
    AT91F_PIO_CfgOutput( AT91C_BASE_PIOA, PA11 ) ;
    AT91F_PIO_CfgOutput( AT91C_BASE_PIOA, PA12 ) ;
    AT91F_PIO_CfgOutput( AT91C_BASE_PIOA, PA13 ) ;
    AT91F_PIO_CfgOutput( AT91C_BASE_PIOA, PA14 ) ;
    AT91F_PIO_CfgOutput( AT91C_BASE_PIOA, PA15 ) ;
    AT91F_PIO_CfgInput( AT91C_BASE_PIOA, PA16 ) ;
    AT91F_PIO_CfgInput( AT91C_BASE_PIOA, PA17 ) ;
    AT91F_PIO_CfgInput( AT91C_BASE_PIOA, PA18 ) ;
    AT91F_PIO_CfgInput( AT91C_BASE_PIOA, PA19 ) ;
    AT91F_PIO_CfgInput( AT91C_BASE_PIOA, PA20 ) ;
    AT91F_PIO_CfgInput( AT91C_BASE_PIOA, PA21 ) ;
    AT91F_PIO_CfgOutput( AT91C_BASE_PIOA, PA22 ) ;
    AT91F_PIO_CfgOutput( AT91C_BASE_PIOA, PA23 ) ;
	AT91F_PIO_CfgOutput( AT91C_BASE_PIOA, PA24 ) ;
	AT91F_PIO_CfgOutput( AT91C_BASE_PIOA, PA25 ) ;
	AT91F_PIO_CfgOutput( AT91C_BASE_PIOA, PA26 ) ;
	AT91F_PIO_CfgOutput( AT91C_BASE_PIOA, PA27 ) ;
	AT91F_PIO_CfgOutput( AT91C_BASE_PIOA, PA28 ) ;
	AT91F_PIO_CfgOutput( AT91C_BASE_PIOA, PA29 ) ;
	AT91F_PIO_CfgOutput( AT91C_BASE_PIOA, PA30 ) ;
	AT91F_PIO_CfgOutput( AT91C_BASE_PIOA, PA30 ); 
	AT91F_PIO_CfgPullupDisable( AT91C_BASE_PIOA, PA17 ) ;
    AT91F_PIO_CfgPullupDisable( AT91C_BASE_PIOA, PA18 ) ;
    AT91F_PIO_CfgPullupDisable( AT91C_BASE_PIOA, PA19 ) ;
    AT91F_PIO_CfgPullupDisable( AT91C_BASE_PIOA, PA20 ) ;
}

/************************************************************************/
/*                     Delay function                                   */
/************************************************************************/
void delay_us(unsigned int us)
{
  volatile unsigned int count, countmax = (MCK / 9600000) * us;
  
  for (count = 0; count < countmax; count++);	// one loop takes 5 cpu cycles
}

void delay_ms(unsigned int ms)
{
  volatile unsigned int count, countmax = (MCK / 10000) * ms;
  
  for (count = 0; count < countmax; count++);	// one loop takes 5 cpu cycles
}


/************************************************************************/
/*                     UART0 function DX-117                            */
/************************************************************************/
void init_USART0(void)
{
	AT91F_US0_CfgPMC();
	AT91F_PIO_CfgPeriph(AT91C_BASE_PIOA,AT91C_PA6_TXD0|AT91C_PA5_RXD0,0);
	*AT91C_US0_MR = 0x100008C0;
	*AT91C_US0_BRGR = 3;
	*AT91C_US0_CR = 0x00000140;
}

void init_USART(void)
{
	AT91F_US0_CfgPMC();
	AT91F_PIO_CfgPeriph(AT91C_BASE_PIOA,AT91C_PA6_TXD0|AT91C_PA5_RXD0,0);
	*AT91C_US0_MR = 0x100008C0;
	*AT91C_US0_BRGR = 52;
	*AT91C_US0_CR = 0x00000140;
}

void usart0_transmit(unsigned char data)
{
	while(!(*AT91C_US0_CSR & 0x0002));
	
	*AT91C_US0_THR = data;
}

void print_usart0(char *s)
{
  while(*s!='\0') {
    usart0_transmit(*s);
    s++;
  }
}

// 한 바이트를  16진수로 출력하는 함수 (USART0)
void print_hex_usart0(unsigned char num)
{
  unsigned char temp;
  
  usart0_transmit('0');
  usart0_transmit('x');
  
  temp=(unsigned char)num/16;
  if(temp<10) usart0_transmit(temp + '0');
  else usart0_transmit(temp-10 + (unsigned char)'a');
  temp=num%16;
  if(temp<10) usart0_transmit(temp + '0');
  else usart0_transmit(temp-10 + (unsigned char)'a');
}



// DX 모터의 ID를 결정하는 함수
void DX_set_ID(unsigned char ID) 
{
  unsigned char i,data[6];
  unsigned int check_sum=0;
  
  AT91F_PIO_SetOutput(AT91C_BASE_PIOA, PA7);
  usart0_transmit(0xff);
  usart0_transmit(0xff);
  
  data[0]=0xfe; // broadcasting ID
  data[1]=0x04; // length
  data[2]=0x03; // instruction
  data[3]=0x03;
  data[4]=ID;
  
  for(i=0;i<5;i++) {
    usart0_transmit(data[i]);
    check_sum+=data[i];
  }
  	
  // Check Sum 결정
  data[5]=~(unsigned char)(check_sum&0x00ff);
  usart0_transmit(data[5]);
  
  print_usart0("\n\n\rTX_data: ");
  for(i=0;i<6;i++) {
    print_hex_usart0(data[i]);
    print_usart0(" ");
  }

  delay_ms(1);
  AT91F_PIO_ClearOutput(AT91C_BASE_PIOA, PA7);
}

// DX 모터 테스트 함수
void DX_test(unsigned char ID) 
{
  unsigned char i,data[7];
  unsigned int check_sum=0;
  
  AT91F_PIO_SetOutput(AT91C_BASE_PIOA, PA7);
  usart0_transmit(0xff);
  usart0_transmit(0xff);
  
  data[0]=ID;   // ID
  data[1]=0x05; // length
  data[2]=0x03; // instruction
  data[3]=0x18;
  data[4]=0x01;
  data[5]=0x01;
  
  for(i=0;i<6;i++) {
    usart0_transmit(data[i]);
    check_sum+=data[i];
  }
  
  // Check Sum 결정
  data[6]=~(unsigned char)(check_sum&0x00ff);
  usart0_transmit(data[6]);

  print_usart0("\n\n\rTX_data: ");
  for(i=0;i<7;i++) {
    print_hex_usart0(data[i]);
    print_usart0(" ");
  }

  delay_ms(1);
  AT91F_PIO_ClearOutput(AT91C_BASE_PIOA, PA7);
}

// DX 모터 속도와 위치 제어 함수
void DX_move(unsigned char ID,unsigned int spd,unsigned int pos) 
{
  unsigned char i,data[9];
  unsigned int check_sum=0;
  
  AT91F_PIO_SetOutput(AT91C_BASE_PIOA, PA7);
  usart0_transmit(0xff);
  usart0_transmit(0xff);
  
  data[0]=ID;   // ID
  data[1]=0x07; // length
  data[2]=0x03; // instruction
  data[3]=0x1e;
  data[4]=(unsigned char)(pos&0x00ff);      // position (L)
  data[5]=(unsigned char)((pos>>8)&0x00ff); // position (H)
  data[6]=(unsigned char)(spd&0x00ff);      // speed (L)
  data[7]=(unsigned char)((spd>>8)&0x00ff); // speed (H)
  
  for(i=0;i<8;i++) {
    usart0_transmit(data[i]);
    check_sum+=data[i];
  }
  
  // Check Sum 결정
  data[8]=~(unsigned char)(check_sum&0x00ff);
  usart0_transmit(data[8]);
  delay_ms(1);
  AT91F_PIO_ClearOutput(AT91C_BASE_PIOA, PA7);
}

/************************************************************************/
/*                USART1 function - BlueTooth                           */
/************************************************************************/
void usart1_transmit(short int data1)
{
	/*while(!(*AT91C_US1_CSR & 0x0002));
	
	*AT91C_US1_THR = data1;*/
	
	while (!AT91F_US_TxReady(AT91C_BASE_US1)); 
	  
    AT91F_US_PutChar(AT91C_BASE_US1, data1);     
}

void usart1_transmit_1(unsigned int data1)
{
	while(!(*AT91C_US1_CSR & 0x0002));
	
	*AT91C_US1_THR = data1;
}

void UART_1_ISR(void)
{
	unsigned int status;
	
	AT91PS_USART USART_pt = AT91C_BASE_US1;
	
	status = USART_pt->US_CSR;
	RXD=AT91F_US_GetChar(AT91C_BASE_US1);
	
	if(t<3)
	{
		rxd[t] = RXD;
		t++;
	}
	else
	{
		rxd[t] = RXD;
		t = 0;
	}
}

void init_USART1()
{
	AT91F_US1_CfgPMC();
	AT91F_PIO_CfgPeriph(AT91C_BASE_PIOA,AT91C_PA22_TXD1|AT91C_PA21_RXD1,0);
	*AT91C_US1_MR = 0x100008C0;
	*AT91C_US1_BRGR = 312;
	*AT91C_US1_CR = 0x00000150;
	
	AT91F_US_EnableIt(AT91C_BASE_US1,AT91C_US_RXRDY);
	AT91F_AIC_ConfigureIt(AT91C_BASE_AIC,AT91C_ID_US1,7,1,UART_1_ISR);
	AT91F_AIC_EnableIt(AT91C_BASE_AIC,AT91C_ID_US1);
}




/************************************************************************/
/*                    main function                                     */
/************************************************************************/
int main(void)
{
	port_initialize();
	
	init_USART1();
	ADC_Init();
	init_USART0();	
		
	for(r=0;r<5;r++){		
		initialize();
		delay_ms(500);
	}
	
	while(1)
	{
		
		if(rxd[0] == 0)
		{
			rxd[1] = 0;
			rxd[2] = 0;
			rxd[3] = 0;
			initialize();
			flag = 1;
		}
		
		//forward
		else if(rxd[0] == 1)
		{
			TABLE = 30 - rxd[2];
			shift = rxd[3];
			
			if(rxd[0] == 1 && rxd[1] != 0 && flag3 == 1)
			{
				flag2 = 1;
				flag3 =0;
			}
			if(flag)
			{
				sit(0);
				center();
				flag = 0;
				flag1 = 1;
			}
			else if(flag1)
			{
				L_shift(shift);
				R_foot_up(rxd[1]/2 , 12);
				center();
				
				move_R(shift);
				move_center(-rxd[1],0);
				center();
				flag1 = 0;
				flag2 = 1;
			}
			else if(flag2)
			{
				R_shift(shift);
				L_foot_center(0,12);
				center();
				L_foot_up(rxd[1]/2,12);
				
				move_L(shift);
				move_center_(-rxd[1],0);
				center();
						
				L_shift_(shift);
				R_foot_center(0,12);
				center();
				R_foot_up_(rxd[1]/2,12);
				
				move_R(shift);
				move_center(-rxd[1],0);
				center();
				if(flag2 == 1 && rxd[1] == 0)
				{
					flag2 = 0;
					flag1 = 0;	
					flag3 = 1;				
					sit_move();
				}
			}

		}
		
	}			
}