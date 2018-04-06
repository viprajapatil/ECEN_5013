/* FreeRTOS 8.2 Tiva Demo
 *
 * main.c
 *
 * Andy Kobyljanec
 *
 * This is a simple demonstration project of FreeRTOS 8.2 on the Tiva Launchpad
 * EK-TM4C1294XL.  TivaWare driverlib sourcecode is included.
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "main.h"
#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"
#include "drivers/pinout.h"
#include "utils/uartstdio.h"


// TivaWare includes
#include "driverlib/timer.h"
#include "driverlib/sysctl.h"
#include "driverlib/debug.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "drivers/pinout.h"
#include "driverlib/pin_map.h"

// FreeRTOS includes
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

uint32_t clkFreq;
int a = GPIO_PIN_0;
int b = GPIO_PIN_4;

#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif

void task1 (TimerHandle_t xTimer1)
{
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, a);
        a ^= GPIO_PIN_0;
}

void task2 (TimerHandle_t xTimer2)
{
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, b);
        b ^= GPIO_PIN_4;
}

// Main function
int main(void)
{
    // Set System Clock frequency 120Mhz
    clkFreq = SysCtlClockFreqSet(SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL |SYSCTL_CFG_VCO_480, 120000000);

    // Configure the device pins.
    PinoutSet(false, false);

    TimerHandle_t xTimer1 = NULL;
    xTimer1 = xTimerCreate(
            "Timer1", /* A text name to help debugging */
            pdMS_TO_TICKS(500), /* Timer period, i.e. 1 s */
            pdTRUE,  /* Timer type, auto-reload or one-shot*/
            (void *) pvTimerGetTimerID(xTimer1), /* Identifier of created timer */
            task1   /* Callback function */
          );

    TimerHandle_t xTimer2 = NULL;
    xTimer2 = xTimerCreate(
                  "Timer2", /* A text name to help debugging */
                  pdMS_TO_TICKS(250), /* Timer period, i.e. 1 s */
                  pdTRUE,  /* Timer type, auto-reload or one-shot*/
                  (void *) pvTimerGetTimerID(xTimer2), /* Identifier of created timer */
                  task2   /* Callback function */
                );

    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_PIN_4);

    if(xTimerStart(xTimer1, 500) && xTimerStart(xTimer2, 500))
    {
        vTaskStartScheduler();
    }

    return 0;
}



