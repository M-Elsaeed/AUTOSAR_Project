/******************************************************************************
 *
 * Module: Led
 *
 * File Name: Led.c
 *
 * Description: Source file for Led Module.
 *
 * Author: Mohamed Ehab
 ******************************************************************************/
#include "Port.h"
#include "Dio.h"
#include "Led.h"

/* LED Configurations Structure */
static Port_ConfigType  g_LED_Config;

/*********************************************************************************************/
/* Description: Called by the LED_Init function (only) used to fill the led configurations structure */
static void LED_configurations(void)
{
    g_LED_Config.port_num  = LED_PORT;        /* Set LED Port value */
    g_LED_Config.pin_num   = LED_PIN_NUM;     /* Set LED PIN Number value */
    g_LED_Config.direction = OUTPUT;          /* Set LED as OUTPUT pin */
    g_LED_Config.resistor  = OFF;             /* Disable internal resistor */
    g_LED_Config.initial_value  = LED_OFF;    /* Turn Off the LED */
}

/*********************************************************************************************/
 void LED_init(void)
{
    LED_configurations(); 
    Port_SetupGpioPin(&g_LED_Config);
}

/*********************************************************************************************/
void LED_setOn(void)
{
    Dio_WriteChannel(DioConf_LED1_CHANNEL_ID_INDEX,LED_ON);  /* LED ON */
}

/*********************************************************************************************/
void LED_setOff(void)
{
    Dio_WriteChannel(DioConf_LED1_CHANNEL_ID_INDEX,LED_OFF); /* LED OFF */
}

/*********************************************************************************************/
void LED_refreshOutput(void)
{
    Dio_LevelType state = Dio_ReadChannel(DioConf_LED1_CHANNEL_ID_INDEX);
    Dio_WriteChannel(DioConf_LED1_CHANNEL_ID_INDEX,state); /* re-write the same value */
}

/*********************************************************************************************/
void LED_toggle(void)
{
    Dio_LevelType state = Dio_FlipChannel(DioConf_LED1_CHANNEL_ID_INDEX);
}

/*********************************************************************************************/
