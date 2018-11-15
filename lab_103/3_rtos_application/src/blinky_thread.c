/* 
 * blinky_thread.c
 *
 * simple thread to handle blinking some leds on the discovery board - updated
 * for the stm32f7xx hal libraries
 *
 * author:    Dr. Alex Shenfield
 * date:      01/09/2018
 * purpose:   55-604481 embedded computer networks : lab 103
 */

// include the basic headers for the hal drivers
#include "stm32f7xx_hal.h"
#include "cmsis_os.h"

// include the shu bsp libraries for the stm32f7 discovery board
#include "clock.h"
#include "gpio.h"
#include "pinmappings.h"

// HARDWARE DEFINES

// specify some leds
gpio_pin_t led1 = {PI_1, GPIOI, GPIO_PIN_1};
gpio_pin_t led2 = {PB_14, GPIOB, GPIO_PIN_14};
gpio_pin_t led3 = {PB_15, GPIOB, GPIO_PIN_15};
gpio_pin_t ldr = {PA_0, GPIOA, GPIO_PIN_0};

// RTOS DEFINES

// declare the thread function prototypes
void led_1_thread(void const *argument);
void led_2_thread(void const *argument);
void led_3_thread(void const *argument);
void ldr_thread(void const *argument);

// declare the thread ids
osThreadId tid_led_1_thread;
osThreadId tid_led_2_thread;
osThreadId tid_led_3_thread;
osThreadId tid_ldr_thread;

// define thread priorities
osThreadDef(led_1_thread, osPriorityNormal, 1, 0);
osThreadDef(led_2_thread, osPriorityNormal, 1, 0);
osThreadDef(led_3_thread, osPriorityNormal, 1, 0);
osThreadDef(ldr_thread, osPriorityNormal, 1, 0);

// OTHER FUNCTIONS

// function prototype for our dumb delay function
void dumb_delay(uint32_t delay);

// THREAD INITIALISATION

// create the threads
int init_blinky_thread(void)
{
  // initialize peripherals here
  init_gpio(led1, OUTPUT);
  init_gpio(led2, OUTPUT);
  init_gpio(led3, OUTPUT);
	init_gpio(ldr, INPUT);
  
  // create the thread and get its taks id
  tid_led_1_thread = osThreadCreate(osThread(led_1_thread), NULL);
  tid_led_2_thread = osThreadCreate(osThread(led_2_thread), NULL);
  tid_led_3_thread = osThreadCreate(osThread(led_3_thread), NULL);
	tid_ldr_thread = osThreadCreate(osThread(ldr_thread), NULL);
  
  // check if everything worked ...
  if(!(tid_led_1_thread && tid_led_2_thread && tid_led_3_thread))
  {
    return(-1);
  }
  return(0);
}

// ACTUAL THREADS
//Create two threads, one for leds and ldr, and one for displaying data on the LCD screen 
// blink led 1
void led_1_thread(void const *argument)
{
  while(1)
  {
    // toggle the first led on the gpio pin
    toggle_gpio(led1);
    osDelay(500);
  }
}

// blink led 2
void led_2_thread(void const *argument)
{
  while(1)
  {
    // toggle the second led on the gpio pin
    toggle_gpio(led2);
    osDelay(200);
  }
}

// blink led 3
void led_3_thread(void const *argument)
{
  while(1)
  {
    // toggle the second led on the gpio pin
    toggle_gpio(led3);
    osDelay(1000);
  }
}

// OTHER FUNCTIONS

// dumb delay function
void dumb_delay(uint32_t delay)
{
  // just spin through processor cycles to introduce a delay 
  long delaytime;
  for(delaytime = 0; delaytime < (delay * 10000); delaytime++)
  {
    __nop();
  }
}


