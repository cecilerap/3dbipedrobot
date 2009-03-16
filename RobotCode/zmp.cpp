#include "allHeader.h"

/************************************************************************/
/*                   ZMP <Flexiforce Sensor>                            */
/************************************************************************/
void ADC_Init(void)
{
	AT91F_ADC_CfgPMC();
	AT91F_ADC_SoftReset (AT91C_BASE_ADC);
	*AT91C_ADC_MR = 0x02020400;
}

void ADC_Start(unsigned char ch)
{
	AT91F_ADC_EnableChannel (AT91C_BASE_ADC, (1<<ch)); 
	AT91F_ADC_StartConversion (AT91C_BASE_ADC);
	while (!((AT91F_ADC_GetStatus (AT91C_BASE_ADC)) & (1<<ch)));
	AT91F_ADC_DisableChannel (AT91C_BASE_ADC, (1<<ch)); 
}

void ADC_Get(int * data )
{
	/* Read the ADC result output */
	*data = AT91F_ADC_GetLastConvertedData (AT91C_BASE_ADC);
}

void unsigned_dec(int dec)  // 십진수 출력(네자리)
{
	unsigned int result[5];
	result[0] = 0;
	result[1] = 0;
	result[2] = 0;
	result[3] = 0;
	result[4] = 0;

	{
		char i = 0;

		do
		{
			result[i] = (dec % 10) + 48;
			dec = dec / 10;
			i++;

		}while(dec != 0); 

		while(i > 0)
		{
			i--;
			usart1_transmit(result[i]);   
		}
	}
}  

/************************************************************************/
/*                    ZMP	                                            */
/************************************************************************/
void zmp()
{

	for(m = 0; m < 8; m++)
	{
		ADC_Start(m);
		ADC_Get( &ad[m] );

		ad_data[m] = ad[m];
	}
	for(gg=0;gg<8;gg++)
	{
		numerator=ad_data[gg]*lenx[gg];
		count_numerator = count_numerator+numerator;
	}
	for(gg=0;gg<8;gg++)
	{
		denominator=ad_data[gg];
		count_denominator = count_denominator+denominator;
	}
	zmpx = count_numerator/count_denominator;

	for(gg=0;gg<8;gg++)
	{
		numerator_1=ad_data[gg]*leny[gg];
		count_numerator_1 = count_numerator_1+numerator_1;
	}
	for(gg=0;gg<8;gg++)
	{
		denominator_1=ad_data[gg];
		count_denominator_1 = count_denominator_1+denominator_1;
	}
	zmpy = count_numerator_1/count_denominator_1;

	unsigned_dec(zmpx);
	unsigned_dec(zmpy);
	usart1_transmit(0x0d);
	usart1_transmit(0x0a);
}


int X_l, Y_l,X_r, Y_r, center_x, center_y;

void center()
{
	for(m = 0; m < 8; m++)
	{
		ADC_Start(m);
		ADC_Get( &ad[m] );

		ad_data[m] = ad[m];
	}

	X_l = abs(abs(ad_data[0]-ad_data[1]) - abs(ad_data[2]-ad_data[3]));
	Y_l = abs(abs(ad_data[0]-ad_data[2]) - abs(ad_data[1]-ad_data[3]));

	X_r = abs(abs(ad_data[4]-ad_data[5]) - abs(ad_data[6]-ad_data[7]));
	Y_r = abs(abs(ad_data[4]-ad_data[6]) - abs(ad_data[5]-ad_data[7]));

	if(X_l>X_r)
	{
		center_x = ((float)(X_l-X_r))/2;
		center_y = ((float)(Y_l-Y_r))/2;
	}
	if(X_l<X_r)
	{
		center_x = ((float)(X_r-X_l))/2;
		center_y = ((float)(Y_r-Y_l))/2;
	}

	usart1_transmit(100); 
	usart1_transmit(center_x);

}

void sit_move()
{
	DX_move(1,512,535);
	DX_move(2,512,475);
	DX_move(3,512,420);
	DX_move(4,512,465);
	DX_move(5,512,475);
	DX_move(6,512,483);

	DX_move(7,512,475);
	DX_move(8,512,610);
	DX_move(9,512,670);
	DX_move(10,512,560);
	DX_move(11,512,540);
	DX_move(12,512,480);

	DX_move(13,512,478);
	DX_move(14,512,514);
	DX_move(15,512,519);

	DX_move(16,512,545);
	DX_move(17,512,519);
	DX_move(18,512,514);
}