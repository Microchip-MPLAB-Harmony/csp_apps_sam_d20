/*******************************************************************************
 CLOCK PLIB

  Company:
    Microchip Technology Inc.

  File Name:
    plib_clock.c

  Summary:
    CLOCK PLIB Implementation File.

  Description:
    None

*******************************************************************************/

/*******************************************************************************
* Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/

#include "plib_clock.h"
#include "device.h"
#include "interrupts.h"

static void SYSCTRL_Initialize(void)
{

    /* Configure 8MHz Oscillator */
    SYSCTRL_REGS->SYSCTRL_OSC8M = (SYSCTRL_REGS->SYSCTRL_OSC8M & (SYSCTRL_OSC8M_CALIB_Msk | SYSCTRL_OSC8M_FRANGE_Msk)) | SYSCTRL_OSC8M_ENABLE_Msk | SYSCTRL_OSC8M_PRESC(0x0U) | SYSCTRL_OSC8M_RUNSTDBY_Msk ;

    while((SYSCTRL_REGS->SYSCTRL_PCLKSR & SYSCTRL_PCLKSR_OSC8MRDY_Msk) != SYSCTRL_PCLKSR_OSC8MRDY_Msk)
    {
        /* Waiting for the OSC8M Ready state */
    }

    /****************** XOSC32K initialization  ******************************/

    /* Configure 32K External Oscillator */
    SYSCTRL_REGS->SYSCTRL_XOSC32K = SYSCTRL_XOSC32K_STARTUP(4U) | SYSCTRL_XOSC32K_ENABLE_Msk | SYSCTRL_XOSC32K_RUNSTDBY_Msk | SYSCTRL_XOSC32K_EN32K_Msk | SYSCTRL_XOSC32K_XTALEN_Msk;
    while(!((SYSCTRL_REGS->SYSCTRL_PCLKSR & SYSCTRL_PCLKSR_XOSC32KRDY_Msk) == SYSCTRL_PCLKSR_XOSC32KRDY_Msk))
    {
        /* Waiting for the XOSC32K Ready state */
    }

    SYSCTRL_REGS->SYSCTRL_OSC32K = 0x0U;
}



static void GCLK0_Initialize(void)
{

    GCLK_REGS->GCLK_GENCTRL = GCLK_GENCTRL_SRC(6U) | GCLK_GENCTRL_RUNSTDBY_Msk | GCLK_GENCTRL_GENEN_Msk | GCLK_GENCTRL_ID(0U);

    while((GCLK_REGS->GCLK_STATUS & GCLK_STATUS_SYNCBUSY_Msk) == GCLK_STATUS_SYNCBUSY_Msk)
    {
        /* wait for the Generator 0 synchronization */
    }
}


static void GCLK1_Initialize(void)
{
    GCLK_REGS->GCLK_GENCTRL = GCLK_GENCTRL_SRC(5U) | GCLK_GENCTRL_GENEN_Msk | GCLK_GENCTRL_ID(1U);

    GCLK_REGS->GCLK_GENDIV = GCLK_GENDIV_DIV(32U) | GCLK_GENDIV_ID(1U);
    while((GCLK_REGS->GCLK_STATUS & GCLK_STATUS_SYNCBUSY_Msk) == GCLK_STATUS_SYNCBUSY_Msk)
    {
        /* wait for the Generator 1 synchronization */
    }
}


static void GCLK2_Initialize(void)
{
    GCLK_REGS->GCLK_GENCTRL = GCLK_GENCTRL_SRC(5U) | GCLK_GENCTRL_GENEN_Msk | GCLK_GENCTRL_ID(2U);

    while((GCLK_REGS->GCLK_STATUS & GCLK_STATUS_SYNCBUSY_Msk) == GCLK_STATUS_SYNCBUSY_Msk)
    {
        /* wait for the Generator 2 synchronization */
    }
}




void CLOCK_Initialize (void)
{
    /* Function to Initialize the Oscillators */
    SYSCTRL_Initialize();

    GCLK0_Initialize();
    GCLK1_Initialize();
    GCLK2_Initialize();


    /* Selection of the Generator and write Lock for RTC */
    GCLK_REGS->GCLK_CLKCTRL = GCLK_CLKCTRL_ID(2U) | GCLK_CLKCTRL_GEN(0x1U)  | GCLK_CLKCTRL_CLKEN_Msk;
    /* Selection of the Generator and write Lock for EVSYS_0 */
    GCLK_REGS->GCLK_CLKCTRL = GCLK_CLKCTRL_ID(4U) | GCLK_CLKCTRL_GEN(0x0U)  | GCLK_CLKCTRL_CLKEN_Msk;
    /* Selection of the Generator and write Lock for SERCOM3_CORE */
    GCLK_REGS->GCLK_CLKCTRL = GCLK_CLKCTRL_ID(16U) | GCLK_CLKCTRL_GEN(0x0U)  | GCLK_CLKCTRL_CLKEN_Msk;
    /* Selection of the Generator and write Lock for AC_DIG */
    GCLK_REGS->GCLK_CLKCTRL = GCLK_CLKCTRL_ID(24U) | GCLK_CLKCTRL_GEN(0x1U)  | GCLK_CLKCTRL_CLKEN_Msk;
    /* Selection of the Generator and write Lock for AC_ANA */
    GCLK_REGS->GCLK_CLKCTRL = GCLK_CLKCTRL_ID(25U) | GCLK_CLKCTRL_GEN(0x1U)  | GCLK_CLKCTRL_CLKEN_Msk;

    /* Configure the AHB Bridge Clocks */
    PM_REGS->PM_AHBMASK = 0x1fU;


    /* Configure the APBB Bridge Clocks */
    PM_REGS->PM_APBBMASK = 0x1fU;


    /* Configure the APBC Bridge Clocks */
    PM_REGS->PM_APBCMASK = 0x20022U;



}
