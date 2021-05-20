/******************************************************************************
*
* Module: Port
*
* File Name: Port.h
*
* Description: Header file for TM4C123GH6PM Microcontroller - Port Driver.
*
* Author: Mohamed Ehab
******************************************************************************/

#ifndef PORT_H
#define PORT_H

#include "Common_Macros.h"
#include "Std_Types.h"
#include "Port_Cfg.h"


/* Id for the company in the AUTOSAR
 * for example Mohamed Ehab's ID = 1000 :) */
#define PORT_VENDOR_ID    (1000U)

 /* Port Module Id */
#define PORT_MODULE_ID    (124U)

/* Port Instance Id */
#define PORT_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

 /*
  * AUTOSAR Version 4.0.3
  */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)

  /*
   * Macros for Port Status
   */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)

   /* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and Port Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Std_Types.h does not match the expected version"
#endif

/* Port Pre-Compile Configuration Header file */
#include "Port_Cfg.h"

/* AUTOSAR Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Port_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
#error "The SW version of Port_Cfg.h does not match the expected version"
#endif

// Module Type Definitions


typedef uint8 Port_PinModeType;

typedef uint8 Port_PinType;

typedef enum { PORT_PIN_IN, PORT_PIN_OUT } Port_PinDirectionType;

typedef uint8 Port_PinLevelType;

typedef enum { PORT_RESISTOR_OFF, PORT_RESISTOR_PULL_UP, PORT_RESISTOR_PULL_DOWN } Port_InternalResistorType;

typedef struct {
  Port_PinDirectionType pinDirection;
  uint8 isDirectionChangable;
  Port_PinType pinId;
  Port_PinModeType pinInitialMode;
  Port_PinLevelType pinInitialLevel;
  Port_PinModeType pinMode;
  uint8 isPinModeChangable;
  Port_InternalResistorType pinInternalResistor;
} Port_ConfigType;

extern const Port_ConfigType Port_Configuration[];

// SID

#define Port_Init_SID 0x00
#define Port_SetPinDirection_SID 0x01
#define Port_RefreshPortDirection_SID 0x02
#define Port_GetVersionInfo_SID 0x03
#define Port_SetPinMode_SID 0x04

// Function Prototypes

void Port_Init(const Port_ConfigType * ConfigPtr);


#if PORT_SET_PIN_DIRECTION_API == STD_ON
void Port_SetPinDirection(
  Port_PinType Pin,
  Port_PinDirectionType Direction
);
#endif


void Port_RefreshPortDirection(
  void
);


#if  PORT_VERSION_INFO_API == STD_ON
void Port_GetVersionInfo(
  Std_VersionInfoType * versioninfo
);
#endif


#if PORT_SET_PIN_MODE_API == STD_ON
void Port_SetPinMode(
  Port_PinType Pin,
  Port_PinModeType Mode
);
#endif

// ERROR CODES

#define PORT_E_PARAM_PIN 0x0A
#define PORT_E_DIRECTION_UNCHANGEABLE 0x0B
#define PORT_E_PARAM_CONFIG 0x0C
#define PORT_E_PARAM_INVALID_MODE 0x0D
#define PORT_E_MODE_UNCHANGEABLE 0x0E
#define PORT_E_UNINIT 0x0F
#define PORT_E_PARAM_POINTER 0x10


// PIN MODES

#define MAX_MODE_NUMBER 15
#define  PORT_PIN_MODE_ADC  (0U)
#define  PORT_PIN_MODE_DIO  (10U)
#define  PORT_PIN_NOT_ACTIVE  (9U)
#define  PORT_PIN_MODE_UART  (1U)
#define  PORT_PIN_MODE_SSI  (2U)
#define  PORT_PIN_MODE_UART1  (2U)
#define  PORT_PIN_MODE_I2C  (3U)
#define  PORT_PIN_MODE_CAN0  (3U)
#define  PORT_PIN_MODE_PWM0  (4U)
#define  PORT_PIN_MODE_PWM1  (5U)
#define  PORT_PIN_MODE_QEI  (6U)
#define  PORT_PIN_MODE_GPT  (7U)
#define  PORT_PIN_MODE_CAN  (8U)
#define  PORT_PIN_MODE_USB  (8U)

// PIN LEVELS

#define PORT_PIN_LEVEL_HIGH STD_ACTIVE
#define PORT_PIN_LEVEL_LOW STD_IDLE

// GPIO Registers Base Adresses
#define GPIO_PORTA_BASE_ADDRESS 0x40004000U
#define GPIO_PORTE_BASE_ADDRESS 0x40004000U
#define GPIO_PORTF_BASE_ADDRESS 0x40004000U

// Registers Offsets

#define PORT_DATA_REG_OFFSET              0x3FC
#define PORT_DIR_REG_OFFSET               0x400
#define PORT_ALT_FUNC_REG_OFFSET          0x420
#define PORT_PULL_UP_REG_OFFSET           0x510
#define PORT_PULL_DOWN_REG_OFFSET         0x514
#define PORT_DIGITAL_ENABLE_REG_OFFSET    0x51C
#define PORT_LOCK_REG_OFFSET              0x520
#define PORT_COMMIT_REG_OFFSET            0x524
#define PORT_ANALOG_MODE_SEL_REG_OFFSET   0x528
#define PORT_CTL_REG_OFFSET               0x52C

extern const Port_ConfigType Port_Configuration[]; 


#endif /* PORT_H */
