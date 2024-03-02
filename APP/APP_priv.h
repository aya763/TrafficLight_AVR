/*
 * APP_priv.h
 *
 *  Created on: Feb 11, 2024
 *      Author: aya
 */

#ifndef APP_APP_PRIV_H_
#define APP_APP_PRIV_H_



#define NORMAL_MODE_PORT          DIO_u8PORTA

#define PEDESTRAINS_MODE_PORT     DIO_u8PORTB

#define RED_LED            DIO_u8PIN2
#define YELLOW_LED         DIO_u8PIN1
#define GREEN_LED          DIO_u8PIN0

#define CAR_RED_ON()            DIO_enuSetPinValue(NORMAL_MODE_PORT,RED_LED,DIO_u8HIGH)
#define CAR_RED_OFF()           DIO_enuSetPinValue(NORMAL_MODE_PORT,RED_LED,DIO_u8LOW)

#define CAR_YELLOW_ON()         DIO_enuSetPinValue(NORMAL_MODE_PORT,YELLOW_LED,DIO_u8HIGH)
#define CAR_YELLOW_OFF()        DIO_enuSetPinValue(NORMAL_MODE_PORT,YELLOW_LED,DIO_u8LOW)
#define CAR_YELLOW_BLINK()         DIO_enuTogPinValue(NORMAL_MODE_PORT,YELLOW_LED)

#define CAR_GREEN_ON()          DIO_enuSetPinValue(NORMAL_MODE_PORT,GREEN_LED,DIO_u8HIGH)
#define CAR_GREEN_OFF()         DIO_enuSetPinValue(NORMAL_MODE_PORT,GREEN_LED,DIO_u8LOW)

#define PED_RED_ON()            DIO_enuSetPinValue(PEDESTRAINS_MODE_PORT,RED_LED,DIO_u8HIGH)
#define PED_RED_OFF()           DIO_enuSetPinValue(PEDESTRAINS_MODE_PORT,RED_LED,DIO_u8LOW)

#define PED_YELLOW_ON()         DIO_enuSetPinValue(PEDESTRAINS_MODE_PORT,YELLOW_LED,DIO_u8HIGH)
#define PED_YELLOW_OFF()        DIO_enuSetPinValue(PEDESTRAINS_MODE_PORT,YELLOW_LED,DIO_u8LOW)
#define PED_YELLOW_BLINK()         DIO_enuTogPinValue(PEDESTRAINS_MODE_PORT,YELLOW_LED)

#define PED_GREEN_ON()          DIO_enuSetPinValue(PEDESTRAINS_MODE_PORT,GREEN_LED,DIO_u8HIGH)
#define PED_GREEN_OFF()         DIO_enuSetPinValue(PEDESTRAINS_MODE_PORT,GREEN_LED,DIO_u8LOW)



static void Normal_Mode(void);

static void Pedestraints_Mode(void);

static void Pedestraints(void);

#endif /* APP_APP_PRIV_H_ */
