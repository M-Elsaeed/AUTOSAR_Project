/******************************************************************************
*
* Module: Port
*
* File Name: Port.c
*
* Description: Source file for TM4C123GH6PM Microcontroller - Port Driver.
*
* Author: Mohamed Ehab
******************************************************************************/

#include "Port.h"
#include "Det.h"
#include "MemMap.h"
#include "SchM_Port.h"
#include "tm4c123gh6pm_registers.h"


// #define GPIO_PORTA_BASE_ADDRESS (*((volatile uint32 *)0x40004000))
#define GPIO_PORTA_BASE_ADDRESS 0x40004000U
#define GPIO_PORTE_BASE_ADDRESS 0x40004000U
#define GPIO_PORTF_BASE_ADDRESS 0x40004000U

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
#define MAX_MODE_NUMBER 15

volatile uint8 PORT_Status = 0;

void Port_Init(const Port_ConfigType* ConfigPtr)
{



#if PORT_DEV_ERROR_DETECT == STD_ON
    if (ConfigPtr == NULL_PTR) {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, Port_Init_SID, PORT_E_PARAM_CONFIG);
    }
    if (ConfigPtr->pinId > PortPin_F4_ID) {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, Port_Init_SID, PORT_E_PARAM_PIN);
    }
    if (!(ConfigPtr->isDirectionChangable)) {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, Port_Init_SID, PORT_E_DIRECTION_UNCHANGEABLE);
    }
#endif


    volatile uint32* baseRegAddr = NULL_PTR; /* point to the required Port Registers base address */
    volatile uint32 delay = 0;

    // If ports A to D. Ports E and F don't have 8 pins so they're treated differently.
    if (ConfigPtr->pinId <= PortPin_D7_ID) {
        baseRegAddr = (volatile uint32*)(GPIO_PORTA_BASE_ADDRESS + ((ConfigPtr->pinId / 8) * (0x1000)));
    }
    else if (ConfigPtr->pinId <= PortPin_E5_ID) {
        baseRegAddr = (volatile uint32*)GPIO_PORTE_BASE_ADDRESS;
    }
    else {
        baseRegAddr = (volatile uint32*)GPIO_PORTF_BASE_ADDRESS;
    }


    SYSCTL_REGCGC2_REG |= (1 << (ConfigPtr->pinId / 8));
    delay = SYSCTL_REGCGC2_REG;



    if ((((ConfigPtr->pinId / 8) == 3) && ((ConfigPtr->pinId % 8) == 7)) || (((ConfigPtr->pinId / 8) == 5) && ((ConfigPtr->pinId % 8) == 0))) /* PD7 or PF0 */
    {
        *(volatile uint32*)((volatile uint8*)baseRegAddr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;                     /* Unlock the GPIOCR register */
        SET_BIT(*(volatile uint32*)((volatile uint8*)baseRegAddr + PORT_COMMIT_REG_OFFSET), (ConfigPtr->pinId % 8));  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
    }
    else if (((ConfigPtr->pinId / 8) == 2) && ((ConfigPtr->pinId % 8) <= 3)) /* PC0 to PC3 */
    {
        /* Do Nothing ...  this is the JTAG pins */
        return;
    }
    else
    {
        /* Do Nothing ... No need to unlock the commit register for this pin */
    }

    CLEAR_BIT(*(volatile uint32*)((volatile uint8*)baseRegAddr + PORT_ANALOG_MODE_SEL_REG_OFFSET), (ConfigPtr->pinId % 8));      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
    CLEAR_BIT(*(volatile uint32*)((volatile uint8*)baseRegAddr + PORT_ALT_FUNC_REG_OFFSET), (ConfigPtr->pinId % 8));             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
    *(volatile uint32*)((volatile uint8*)baseRegAddr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << ((ConfigPtr->pinId % 8) * 4));     /* Clear the PMCx bits for this pin */

    if (ConfigPtr->pinDirection == PORT_PIN_OUT)
    {
        SET_BIT(*(volatile uint32*)((volatile uint8*)baseRegAddr + PORT_DIR_REG_OFFSET), (ConfigPtr->pinId % 8));                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */

        if (ConfigPtr->pinInitialLevel == STD_HIGH)
        {
            SET_BIT(*(volatile uint32*)((volatile uint8*)baseRegAddr + PORT_DATA_REG_OFFSET), (ConfigPtr->pinId % 8));          /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
        }
        else
        {
            CLEAR_BIT(*(volatile uint32*)((volatile uint8*)baseRegAddr + PORT_DATA_REG_OFFSET), (ConfigPtr->pinId % 8));        /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
        }
    }
    else if (ConfigPtr->pinDirection == PORT_PIN_IN)
    {
        CLEAR_BIT(*(volatile uint32*)((volatile uint8*)baseRegAddr + PORT_DIR_REG_OFFSET), (ConfigPtr->pinId % 8));             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */

        if (ConfigPtr->pinInternalResistor == PORT_RESISTOR_PULL_UP)
        {
            SET_BIT(*(volatile uint32*)((volatile uint8*)baseRegAddr + PORT_PULL_UP_REG_OFFSET), (ConfigPtr->pinId % 8));       /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
        }
        else if (ConfigPtr->pinInternalResistor == PORT_RESISTOR_PULL_DOWN)
        {
            SET_BIT(*(volatile uint32*)((volatile uint8*)baseRegAddr + PORT_PULL_DOWN_REG_OFFSET), (ConfigPtr->pinId % 8));     /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
        }
        else
        {
            CLEAR_BIT(*(volatile uint32*)((volatile uint8*)baseRegAddr + PORT_PULL_UP_REG_OFFSET), (ConfigPtr->pinId % 8));     /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
            CLEAR_BIT(*(volatile uint32*)((volatile uint8*)baseRegAddr + PORT_PULL_DOWN_REG_OFFSET), (ConfigPtr->pinId % 8));   /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
        }
    }
    else
    {
        /* Do Nothing */
    }

    SET_BIT(*(volatile uint32*)((volatile uint8*)baseRegAddr + PORT_DIGITAL_ENABLE_REG_OFFSET), (ConfigPtr->pinId % 8));        /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
    PORT_Status = 1;



}

void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction)
{
    sint8 index = -1;

    for (uint8 i = 0; i < PORT_CONFIGURED_PORTPINS; i++)
    {
        if (Port_Configuration[i].pinId == Pin)
        {
            index = i;
            break;
        }
    }

    volatile uint32* baseRegAddr = NULL_PTR; /* point to the required Port Registers base address */
    volatile uint32 delay = 0;
    const Port_ConfigType* ConfigPtr = &Port_Configuration[index];

    // If ports A to D. Ports E and F don't have 8 pins so they're treated differently.
    if (ConfigPtr->pinId <= PortPin_D7_ID) {
        baseRegAddr = (volatile uint32*)(GPIO_PORTA_BASE_ADDRESS + ((ConfigPtr->pinId / 8) * (0x1000)));
    }
    else if (ConfigPtr->pinId <= PortPin_E5_ID) {
        baseRegAddr = (volatile uint32*)GPIO_PORTE_BASE_ADDRESS;
    }
    else {
        baseRegAddr = (volatile uint32*)GPIO_PORTF_BASE_ADDRESS;
    }

#if (PORT_DEV_ERROR_DETECT == STD_ON)
    if (PORT_NOT_INITIALIZED == PORT_Status)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
            Port_SetPinDirection_SID, PORT_E_UNINIT);
        // error = TRUE;
    }
    else
    {
        /* No Action Required */
    }
    /* check if the input pin is valid */
    if (index == -1)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, Port_SetPinDirection_SID,
            PORT_E_PARAM_PIN);
    }
    else
    {
    }

    if (Port_Configuration[index].isDirectionChangable == STD_OFF)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, Port_SetPinDirection_SID,
            PORT_E_DIRECTION_UNCHANGEABLE);
    }
    else
    {
    }

#endif

    if (Direction == PORT_PIN_OUT)
    {
        SET_BIT(*(volatile uint32*)((volatile uint8*)baseRegAddr + PORT_DIR_REG_OFFSET), (ConfigPtr->pinId % 8)); /* Set the corresponding bit in the GPIODIR register to configure it as output pin */

        if (Port_Configuration[index].pinInitialLevel == STD_HIGH)
        {
            SET_BIT(*(volatile uint32*)((volatile uint8*)baseRegAddr + PORT_DATA_REG_OFFSET), (ConfigPtr->pinId % 8)); /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
        }
        else
        {
            CLEAR_BIT(*(volatile uint32*)((volatile uint8*)baseRegAddr + PORT_DATA_REG_OFFSET), (ConfigPtr->pinId % 8)); /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
        }
    }
    else if (Direction == PORT_PIN_IN)
    {
        CLEAR_BIT(*(volatile uint32*)((volatile uint8*)baseRegAddr + PORT_DIR_REG_OFFSET), (ConfigPtr->pinId % 8)); /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */

        if (Port_Configuration[index].pinInternalResistor == PORT_RESISTOR_PULL_UP)
        {
            SET_BIT(*(volatile uint32*)((volatile uint8*)baseRegAddr + PORT_PULL_UP_REG_OFFSET), (ConfigPtr->pinId % 8)); /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
        }
        else if (Port_Configuration[index].pinInternalResistor == PORT_RESISTOR_PULL_DOWN)
        {
            SET_BIT(*(volatile uint32*)((volatile uint8*)baseRegAddr + PORT_PULL_DOWN_REG_OFFSET), (ConfigPtr->pinId % 8)); /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
        }
        else
        {
            CLEAR_BIT(*(volatile uint32*)((volatile uint8*)baseRegAddr + PORT_PULL_UP_REG_OFFSET), (ConfigPtr->pinId % 8));   /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
            CLEAR_BIT(*(volatile uint32*)((volatile uint8*)baseRegAddr + PORT_PULL_DOWN_REG_OFFSET), (ConfigPtr->pinId % 8)); /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
        }
    }
}

void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode)
{
    sint8 index = -1;

    for (uint8 i = 0; i < PORT_CONFIGURED_PORTPINS; i++)
    {
        if (Port_Configuration[i].pinId == Pin)
        {
            index = i;
            break;
        }
    }

    volatile uint32* baseRegAddr = NULL_PTR; /* point to the required Port Registers base address */
    volatile uint32 delay = 0;
    const Port_ConfigType* ConfigPtr = &Port_Configuration[index];

    // If ports A to D. Ports E and F don't have 8 pins so they're treated differently.
    if (ConfigPtr->pinId <= PortPin_D7_ID) {
        baseRegAddr = (volatile uint32*)(GPIO_PORTA_BASE_ADDRESS + ((ConfigPtr->pinId / 8) * (0x1000)));
    }
    else if (ConfigPtr->pinId <= PortPin_E5_ID) {
        baseRegAddr = (volatile uint32*)GPIO_PORTE_BASE_ADDRESS;
    }
    else {
        baseRegAddr = (volatile uint32*)GPIO_PORTF_BASE_ADDRESS;
    }

#if (PORT_DEV_ERROR_DETECT == STD_ON)
    if (PORT_NOT_INITIALIZED == PORT_Status)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
            Port_SetPinMode_SID, PORT_E_UNINIT);
        // error = TRUE;
    }
    else
    {
        /* No Action Required */
    }
    /* check if the input configuration pointer is not a NULL_PTR */
    if (index == -1)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, Port_SetPinMode_SID,
            PORT_E_PARAM_PIN);
    }
    else
    {
    }

    if (Port_Configuration[index].isPinModeChangable == STD_OFF)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, Port_SetPinMode_SID,
            PORT_E_MODE_UNCHANGEABLE);
    }
    else
    {
    }

    if (Mode > MAX_MODE_NUMBER)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, Port_SetPinMode_SID,
            PORT_E_PARAM_INVALID_MODE);
    }
    else
    {
    }

#endif

    SET_BIT(*(volatile uint32*)((volatile uint8*)baseRegAddr + PORT_ALT_FUNC_REG_OFFSET), (ConfigPtr->pinId % 8));            /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
    *(volatile uint32*)((volatile uint8*)baseRegAddr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << ((ConfigPtr->pinId % 8) * 4)); /* Clear the PMCx bits for this pin */
    *(volatile uint32*)((volatile uint8*)baseRegAddr + PORT_CTL_REG_OFFSET) |= (Mode << ((ConfigPtr->pinId % 8) * 4));        /* set the PMCx bits for this pin with the desired mode */
}

void Port_GetVersionInfo(Std_VersionInfoType* versioninfo)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    if (PORT_NOT_INITIALIZED == PORT_Status)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
            Port_GetVersionInfo_SID, PORT_E_UNINIT);
        // error = TRUE;
    }
    else
    {
        /* No Action Required */
    }
    /* check if the input configuration pointer is not a NULL_PTR */
    if (NULL_PTR == versioninfo)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, Port_GetVersionInfo_SID,
            PORT_E_PARAM_POINTER);
    }

#endif
    versioninfo->vendorID = PORT_VENDOR_ID;
    versioninfo->moduleID = PORT_MODULE_ID;
    versioninfo->sw_major_version = PORT_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = PORT_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = PORT_SW_PATCH_VERSION;
}

void Port_RefreshPortDirection(void)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    if (PORT_NOT_INITIALIZED == PORT_Status)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
            Port_RefreshPortDirection_SID, PORT_E_UNINIT);
        // error = TRUE;
    }
    else
    {
        /* No Action Required */
    }

#endif
    for (uint8 i = 0; i < PORT_CONFIGURED_PORTPINS; i++)
    {
        Port_SetPinDirection(Port_Configuration[i].pinId, Port_Configuration[i].pinDirection);
    }
}
