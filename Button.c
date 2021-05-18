/******************************************************************************
 *
 * Module: Button
 *
 * File Name: Button.c
 *
 * Description: Source file for Button Module.
 *
 * Author: Mohamed Ehab
 ******************************************************************************/
#include "Dio.h"
#include "Port.h"
#include "Button.h"

/* Button Configurations Structure */
static Port_ConfigType g_Button_Config;

/* Global variable to hold the button state */
static uint8 g_button_state = BUTTON_RELEASED;

/*******************************************************************************************************************/
/* Description: Called by the Button_Init function (only) used to fill the Button configurations structure */
static void BUTTON_configurations(void)
{
    g_Button_Config.port_num  = BUTTON_PORT;             /* Set Button PORT value */
    g_Button_Config.pin_num   = BUTTON_PIN_NUM;          /* Set Button PIN Number value */
    g_Button_Config.direction = INPUT;                   /* Set Button as INPUT pin */
    g_Button_Config.resistor  = PULL_UP;                 /* Enable Intrnal pull up at this pin */
    g_Button_Config.initial_value  = BUTTON_RELEASED;    /* Button is released */
}

/*******************************************************************************************************************/
void BUTTON_init(void)
{
    BUTTON_configurations();
    Port_SetupGpioPin(&g_Button_Config);
}

/*******************************************************************************************************************/
uint8 BUTTON_getState(void)
{
    return g_button_state;
}

/*******************************************************************************************************************/
void BUTTON_refreshState(void)
{
    uint8 state = Dio_ReadChannel(DioConf_SW1_CHANNEL_ID_INDEX);
    
    /* Count the number of Pressed times increment if the switch pressed for 20 ms */
    static uint8 g_Pressed_Count  = 0;

    /* Count the number of Released times increment if the switch released for 20 ms */
    static uint8 g_Released_Count = 0;
    
    if(state == BUTTON_PRESSED)
    {
        g_Pressed_Count++;
	g_Released_Count = 0;
    }
    else
    {
	g_Released_Count++;
	g_Pressed_Count = 0;
    }

    if(g_Pressed_Count == 3)
    {
	g_button_state = BUTTON_PRESSED;
	g_Pressed_Count       = 0;
	g_Released_Count      = 0;
    }
    else if(g_Released_Count == 3)
    {
	g_button_state = BUTTON_RELEASED;
	g_Released_Count      = 0;
	g_Pressed_Count       = 0;
    }
}
/*******************************************************************************************************************/
