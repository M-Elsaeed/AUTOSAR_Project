/******************************************************************************
*
* Module: Port
*
* File Name: Port_PBcfg.c
*
* Description: Post Build Configuration Source file for TM4C123GH6PM Microcontroller - Port Driver
*
* Author: Mohamed Ehab
******************************************************************************/

#include "Port.h"

/*
 * Module Version 1.0.0
 */
#define PORT_PBCFG_SW_MAJOR_VERSION              (1U)
#define PORT_PBCFG_SW_MINOR_VERSION              (0U)
#define PORT_PBCFG_SW_PATCH_VERSION              (0U)

 /*
  * AUTOSAR Version 4.0.3
  */
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION     (3U)

  /* AUTOSAR Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of PBcfg.c does not match the expected version"
#endif

/* Software Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
#error "The SW version of PBcfg.c does not match the expected version"
#endif

/* PB structure used with Port_Init API */
const Port_ConfigType Port_Configuration[] = {

{PORT_PIN_LED1_DIRECTION,
PORT_PIN_LED1_DIRECTION_CHANGEABLE,
PORT_PIN_LED1_ID,
PORT_PIN_LED1_INITIAL_MODE,
PORT_PIN_LED1_LEVEL_VALUE,
PORT_PIN_LED1_MODE,
PORT_PIN_LED1_MODE_CHANGABLE,
PORT_PIN_LED1_INTERNAL_RESISTOR},

{PORT_PIN_SW1_DIRECTION,
PORT_PIN_SW1_DIRECTION_CHANGEABLE,
PORT_PIN_SW1_ID,
PORT_PIN_SW1_INITIAL_MODE,
PORT_PIN_SW1_LEVEL_VALUE,
PORT_PIN_SW1_MODE,
PORT_PIN_SW1_MODE_CHANGABLE,
PORT_PIN_SW1_INTERNAL_RESISTOR}
};