/******************************************************************************
*
* Module: Port
*
* File Name: Port_Cfg.h
*
* Description: Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - Port Driver
*
* Author: Mohamed Ehab
******************************************************************************/

#ifndef PORT_CFG_H
#define PORT_CFG_H

/*
 * Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION              (1U)
#define PORT_CFG_SW_MINOR_VERSION              (0U)
#define PORT_CFG_SW_PATCH_VERSION              (0U)

 /*
  * AUTOSAR Version 4.0.3
  */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION     (3U)

// Port Driver Pre-processor switch to enable / disable the use of the functions and DEV errors detection
#define PORT_DEV_ERROR_DETECT (STD_ON)
#define PORT_VERSION_INFO_API (STD_ON)
#define PORT_SET_PIN_DIRECTION_API (STD_ON)
#define PORT_SET_PIN_MODE_API (STD_ON)

// Number of configured PINS
#define PORT_CONFIGURED_PORTPINS (2U)

// Configs for LED1
#define PORT_PIN_LED1_Index 0
#define PORT_PIN_LED1_DIRECTION (Port_PinDirectionType)PORT_PIN_OUT
#define PORT_PIN_LED1_DIRECTION_CHANGEABLE STD_ON
#define PORT_PIN_LED1_ID PortPin_F1_ID
#define PORT_PIN_LED1_INITIAL_MODE (Port_PinModeType) PORT_PIN_MODE_DIO
#define PORT_PIN_LED1_LEVEL_VALUE (Port_PinLevelType) PORT_PIN_LEVEL_LOW
#define PORT_PIN_LED1_MODE (Port_PinModeType) PORT_PIN_MODE_DIO
#define PORT_PIN_LED1_MODE_CHANGABLE STD_ON
#define PORT_PIN_LED1_INTERNAL_RESISTOR (Port_InternalResistorType)PORT_RESISTOR_OFF

// Configs for SW1
#define PORT_PIN_SW1_Index 1 
#define PORT_PIN_SW1_DIRECTION (Port_PinDirectionType)PORT_PIN_IN
#define PORT_PIN_SW1_DIRECTION_CHANGEABLE STD_ON
#define PORT_PIN_SW1_ID PortPin_F4_ID
#define PORT_PIN_SW1_INITIAL_MODE (Port_PinModeType) PORT_PIN_MODE_DIO
#define PORT_PIN_SW1_LEVEL_VALUE (Port_PinLevelType) PORT_PIN_LEVEL_LOW
#define PORT_PIN_SW1_MODE (Port_PinModeType) PORT_PIN_MODE_DIO
#define PORT_PIN_SW1_MODE_CHANGABLE STD_ON
#define PORT_PIN_SW1_INTERNAL_RESISTOR (Port_InternalResistorType)PORT_RESISTOR_PULL_UP

// Symbolic Names for Portpins
#define PortPin_A0_ID    (uint8)0
#define PortPin_A1_ID    (uint8)1
#define PortPin_A2_ID    (uint8)2
#define PortPin_A3_ID    (uint8)3
#define PortPin_A4_ID    (uint8)4
#define PortPin_A5_ID    (uint8)5
#define PortPin_A6_ID    (uint8)6
#define PortPin_A7_ID    (uint8)7
#define PortPin_B0_ID    (uint8)8
#define PortPin_B1_ID    (uint8)9
#define PortPin_B2_ID    (uint8)10
#define PortPin_B3_ID    (uint8)11
#define PortPin_B4_ID    (uint8)12
#define PortPin_B5_ID    (uint8)13
#define PortPin_B6_ID    (uint8)14
#define PortPin_B7_ID    (uint8)15
#define PortPin_C0_ID    (uint8)16
#define PortPin_C1_ID    (uint8)17
#define PortPin_C2_ID    (uint8)18
#define PortPin_C3_ID    (uint8)19
#define PortPin_C4_ID    (uint8)20
#define PortPin_C5_ID    (uint8)21
#define PortPin_C6_ID    (uint8)22
#define PortPin_C7_ID    (uint8)23
#define PortPin_D0_ID    (uint8)24
#define PortPin_D1_ID    (uint8)25
#define PortPin_D2_ID    (uint8)26
#define PortPin_D3_ID    (uint8)27
#define PortPin_D4_ID    (uint8)28
#define PortPin_D5_ID    (uint8)29
#define PortPin_D6_ID    (uint8)30
#define PortPin_D7_ID    (uint8)31
#define PortPin_E0_ID    (uint8)32
#define PortPin_E1_ID    (uint8)33
#define PortPin_E2_ID    (uint8)34
#define PortPin_E3_ID    (uint8)35
#define PortPin_E4_ID    (uint8)36
#define PortPin_E5_ID    (uint8)37
#define PortPin_F0_ID    (uint8)38
#define PortPin_F1_ID    (uint8)39
#define PortPin_F2_ID    (uint8)40
#define PortPin_F3_ID    (uint8)41
#define PortPin_F4_ID    (uint8)42

#endif /* PORT_CFG_H */
