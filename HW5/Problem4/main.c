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

// Macros for event notification
#define TOGGLE_LED 0x01
#define LOG_STRING 0x02

uint32_t clkFreq;
int a = GPIO_PIN_0;
int b = GPIO_PIN_4;

static TaskHandle_t xTask1 = NULL, xTask2 = NULL, xTask3 = NULL;
QueueHandle_t xQueue;

#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif

void
ConfigureUART(void)
{
    //
    // Enable the GPIO Peripheral used by the UART.
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Enable UART0
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //
    // Configure GPIO Pins for UART mode.
    //
    ROM_GPIOPinConfigure(GPIO_PA0_U0RX);
    ROM_GPIOPinConfigure(GPIO_PA1_U0TX);
    ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, 115200, clkFreq);
}

void timerTask1 (TimerHandle_t xTimer1)
{

    if (xTaskNotify( xTask3, TOGGLE_LED, eSetBits) != pdPASS)
        UARTprintf("Notification not send task 1");

}

void timerTask2 (TimerHandle_t xTimer2)
{
   // while(1){
    if (xTaskNotify( xTask3, LOG_STRING, eSetBits) == pdPASS)
    {

        TickType_t ticks = xTaskGetTickCount();
        int t = ticks;
        xQueueSend(xQueue, &t, 1000);
    }
    else UARTprintf("Notification not send Task 2");
   // }

}

void task1(void *pvParameters)
{
    TimerHandle_t xTimer1 = NULL;
       xTimer1 = xTimerCreate(
               "Timer1", /* A text name to help debugging */
               pdMS_TO_TICKS(500), /* Timer period, i.e. 1 s */
               pdTRUE,  /* Timer type, auto-reload or one-shot*/
               (void *) pvTimerGetTimerID(xTimer1), /* Identifier of created timer */
               timerTask1   /* Callback function */
             );
       xTimerStart(xTimer1, 0);
    while(1){}
}

void task2(void *pvParameters)
{
    TimerHandle_t xTimer2 = NULL;
        xTimer2 = xTimerCreate(
                      "Timer2", /* A text name to help debugging */
                      pdMS_TO_TICKS(250), /* Timer period, i.e. 1 s */
                      pdTRUE,  /* Timer type, auto-reload or one-shot*/
                      (void *) pvTimerGetTimerID(xTimer2), /* Identifier of created timer */
                      timerTask2   /* Callback function */
                    );
        xTimerStart(xTimer2, 0);

    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_PIN_4);
    while(1){}
}

void task3(void *pvParameters)
{
    uint32_t NotifValue = 0;
        while(1){

        // Notify wait
        if(xTaskNotifyWait( 0, 0xFF, &NotifValue, portMAX_DELAY) == pdTRUE)
        {
            if (NotifValue & TOGGLE_LED)
            {
                //Toggle led
                UARTprintf("Toggle led\n");
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, b);
                b ^= GPIO_PIN_4;
            }
            if (NotifValue & LOG_STRING)
            {
                //Print String
                UARTprintf("log string\n");
                int ticks = 0;
                xQueueReceive(xQueue, &ticks, 1000);
                UARTprintf("%i\n", ticks);
            }
        }
        }

}

// Main function
int main(void)
{
    xQueue = xQueueCreate(1024, sizeof(int));

    // Set System Clock frequency 120Mhz
    clkFreq = SysCtlClockFreqSet(SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL |SYSCTL_CFG_VCO_480, 120000000);

    // Configure the device pins.
    PinoutSet(false, false);

    // Configure UART for printing
    ConfigureUART();
    UARTprintf("Vipraja Patil, Date: April 5, 2018\n");

    // Create Tasks
    xTaskCreate(task1, (const portCHAR *)"Task1", 1024, NULL, 1, &xTask1);
    xTaskCreate(task2, (const portCHAR *)"Task2", 1024, NULL, 1, &xTask2);
    xTaskCreate(task3, (const portCHAR *)"Task3", 1024, NULL, 1, &xTask3);

    vTaskStartScheduler();


    return 0;
}



