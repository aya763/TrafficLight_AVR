
/*****************************************************************************/
/********Traffic Light using TIMER0 Overflow Interrupt & External INT0********/
/**    Required Time=5 sec /system freq=8MHZ / Prescaler=1024               **/
/**                   Num of Overflow=154 PreLoad=208                       **/
/**                    External INT0 at Rising Edge                         **/
/*****************************************************************************/
/*****************************************************************************/

#include "../LIB/errorState.h"
#include "../LIB/types.h"

#include "../MCAL/DIO/DIO_int.h"

#include "../MCAL/EINT/INT_config.h"
#include "../MCAL/EINT/INT_int.h"

#include "../MCAL/GIE/GIE_int.h"

#include "../MCAL/TIMER/TIMER0/TIMER0_int.h"

#include "../HAL/SWITCH/Switch_config.h"
#include "../HAL/SWITCH/Switch_int.h"

#include "APP_config.h"
#include "APP_priv.h"



extern EINT_t EINT_tstrEINTcofig[3];


static volatile u8 Car_Led_State;
static  volatile u16 APP_TIMER0_u16Counter=0;

ES_t APP_enuInit(void)
{
	ES_t Local_enuErrorState=ES_NOK;

	TIMER0_enuInit();
	TIMER0_enuSetPreload(208);
	GIE_enuDisable();

	EINT_enuInit(EINT_tstrEINTcofig);
	EINT_enuSelectSenceLevel(0,RISING_EDGE);
	EINT_enuCallBack(&Pedestraints,NULL,0);
	EINT_enuEnableINT(0);

	DIO_enuSetPinDirection(NORMAL_MODE_PORT,RED_LED,DIO_u8OUTPUT);
	DIO_enuSetPinDirection(NORMAL_MODE_PORT,YELLOW_LED,DIO_u8OUTPUT);
	DIO_enuSetPinDirection(NORMAL_MODE_PORT,GREEN_LED,DIO_u8OUTPUT);

	DIO_enuSetPinDirection(PEDESTRAINS_MODE_PORT,RED_LED,DIO_u8OUTPUT);
	DIO_enuSetPinDirection(PEDESTRAINS_MODE_PORT,YELLOW_LED,DIO_u8OUTPUT);
	DIO_enuSetPinDirection(PEDESTRAINS_MODE_PORT,GREEN_LED,DIO_u8OUTPUT);

	DIO_enuSetPinValue(NORMAL_MODE_PORT,RED_LED,DIO_u8LOW);
	DIO_enuSetPinValue(NORMAL_MODE_PORT,YELLOW_LED,DIO_u8LOW);
	DIO_enuSetPinValue(NORMAL_MODE_PORT,GREEN_LED,DIO_u8LOW);

	DIO_enuSetPinValue(PEDESTRAINS_MODE_PORT,RED_LED,DIO_u8LOW);
	DIO_enuSetPinValue(PEDESTRAINS_MODE_PORT,YELLOW_LED,DIO_u8LOW);
	DIO_enuSetPinValue(PEDESTRAINS_MODE_PORT,GREEN_LED,DIO_u8LOW);

	DIO_enuSetPinDirection(DIO_u8PORTD,DIO_u8PIN2,DIO_u8INPUT);//INT0 PIN

	TIMER0_enuEnableOVFINTERRUPT();
	GIE_enuEnable();

	return Local_enuErrorState;
}

ES_t APP_enuStart(void)
{
	ES_t Local_enuErrorState=ES_NOK;

	TIMER0_enuCallBackOVF(Normal_Mode,NULL);
	Local_enuErrorState=ES_OK;

	return Local_enuErrorState;
}


static void Pedestraints(void)
{
	APP_TIMER0_u16Counter=0;
	TIMER0_enuCallBackOVF(Pedestraints_Mode,NULL);

}


static void Normal_Mode(void)
{


	APP_TIMER0_u16Counter++;

	if(APP_TIMER0_u16Counter<154)
	{
		CAR_GREEN_ON();
		Car_Led_State=GREEN_LED;

	}
	else if(APP_TIMER0_u16Counter>=154 && APP_TIMER0_u16Counter%10==0 && APP_TIMER0_u16Counter<290)//
	{
		if(APP_TIMER0_u16Counter==154)
		{
			TIMER0_enuSetPreload(208);
		}
		CAR_GREEN_OFF();
		CAR_YELLOW_BLINK();
		Car_Led_State=YELLOW_LED;
	}
	else if(APP_TIMER0_u16Counter>=290 && APP_TIMER0_u16Counter<462 )
	{
		if(APP_TIMER0_u16Counter==290)
		{
			TIMER0_enuSetPreload(208);
		}
		CAR_YELLOW_OFF();
		CAR_RED_ON();
		Car_Led_State=RED_LED;
	}
	else if(APP_TIMER0_u16Counter>=462 && APP_TIMER0_u16Counter%10==0 && APP_TIMER0_u16Counter<616)//
	{
		if(APP_TIMER0_u16Counter==462)
		{
			TIMER0_enuSetPreload(208);
		}
		CAR_RED_OFF();
		CAR_YELLOW_BLINK();
		Car_Led_State=YELLOW_LED;
	}
	else if(APP_TIMER0_u16Counter== 616)
	{
		TIMER0_enuSetPreload(208);
		CAR_YELLOW_OFF();
		CAR_GREEN_ON();
		Car_Led_State=GREEN_LED;
		APP_TIMER0_u16Counter=0;
	}

}

static void Pedestraints_Mode(void)
{
	APP_TIMER0_u16Counter++;


	if(APP_TIMER0_u16Counter==1)
	{
		PED_GREEN_OFF();
		PED_RED_OFF();
		PED_YELLOW_OFF();
	}
	if(Car_Led_State==RED_LED )
	{
		if(APP_TIMER0_u16Counter<154)
		{
			PED_GREEN_ON();
			CAR_RED_ON();
		}
		else if(APP_TIMER0_u16Counter%10==0 && APP_TIMER0_u16Counter>=154 && APP_TIMER0_u16Counter<290)
		{
			if(APP_TIMER0_u16Counter==154)
			{
				TIMER0_enuSetPreload(208);
			}
			CAR_RED_OFF();
			PED_GREEN_ON();
			CAR_YELLOW_BLINK();
			PED_YELLOW_BLINK();
		}
		else if(APP_TIMER0_u16Counter==290)
		{
			PED_YELLOW_OFF();
			PED_GREEN_OFF();
			PED_RED_ON();
			CAR_YELLOW_OFF();
			CAR_GREEN_ON();

			TIMER0_enuSetPreload(208);
			APP_TIMER0_u16Counter=0;
			TIMER0_enuCallBackOVF(Normal_Mode,NULL);
		}
	}
	else if((Car_Led_State==GREEN_LED || Car_Led_State==YELLOW_LED) )
	{
		if (APP_TIMER0_u16Counter%10==0 && APP_TIMER0_u16Counter<154)
		{
			PED_RED_ON();
			CAR_YELLOW_BLINK();
			PED_YELLOW_BLINK();
		}
		else if(APP_TIMER0_u16Counter>=154 && APP_TIMER0_u16Counter<290)
		{
			if (APP_TIMER0_u16Counter==154)
			{
				TIMER0_enuSetPreload(208);
			}
			CAR_GREEN_OFF();
			CAR_YELLOW_OFF();
			PED_YELLOW_OFF();
			CAR_RED_ON();
			PED_RED_OFF();
			PED_GREEN_ON();
		}
		else if(APP_TIMER0_u16Counter%10==0 && APP_TIMER0_u16Counter>290 && APP_TIMER0_u16Counter<462)
		{
			if (APP_TIMER0_u16Counter==290)
			{
				TIMER0_enuSetPreload(208);
			}
			CAR_RED_OFF();
			PED_GREEN_ON();
			CAR_YELLOW_BLINK();
			PED_YELLOW_BLINK();
		}
		else if(APP_TIMER0_u16Counter==462)
		{
			PED_YELLOW_OFF();
			PED_GREEN_OFF();
			PED_RED_ON();
			CAR_YELLOW_OFF();
			CAR_GREEN_ON();

			TIMER0_enuSetPreload(208);
			APP_TIMER0_u16Counter=0;
			TIMER0_enuCallBackOVF(Normal_Mode,NULL);
		}

	}

}

















