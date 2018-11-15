/*
 * main.c
 *
 * this is the main rtos mail queue application
 *
 * author:    Dr. Alex Shenfield
 * date:      06/09/2018
 * purpose:   55-604481 embedded computer networks : lab 103
 */

// include the basic headers for the hal drivers
#include "stm32f7xx_hal.h"
#include "cmsis_os.h"

// include necessary .h files 
#include "clock.h"
#include "pinmappings.h"
#include "stm32746g_discovery_lcd.h"
#include "adc.h"
#include "gpio.h"
#include "stdio.h"

// declare the extern methods that set the threads up for us 
extern int init_data_thread(void);
extern int init_display_thread(void);
extern int init_blinky_thread(void);



// LCD DEFINES

#define BOARDER     "****************************"


// Map the leds to GPIO pins PI_0,PI_1 and PI_2

gpio_pin_t ldr = {PA_0, GPIOA, GPIO_PIN_0};
//gpio_pin_t led1 = {PI_0, GPIOI, GPIO_PIN_0};


const char * welcome_message[2] =
{
	"*     Hello everyone!!     *",
	"*      Welcome to SHU      *"
};




// OVERRIDE HAL DELAY
// make HAL_Delay point to osDelay (otherwise any use of HAL_Delay breaks things)

void HAL_Delay(__IO uint32_t Delay)
{
	osDelay(Delay);
}


// this is the main method
int main()
{ 
  // initialise the real time kernel
  osKernelInitialize();
  
  // we need to initialise the hal library and set up the SystemCoreClock 
  // properly
  HAL_Init();
  init_sysclk_216MHz();
	



  
  // at this stage the microcontroller clock setting is already configured. 
  // this is done through SystemInit() function which is called from the 
  // startup file (startup_stm32f7xx.s) before to branch to application main.
  // to reconfigure the default setting of SystemInit() function, refer to
  // system_stm32f7xx.c file
  //
  // note also that we need to set the correct core clock in the RTX_Conf_CM.c
  // file (OS_CLOCK) which we can do using the configuration wizard
    
  // initialise our threads
  init_data_thread();
  init_display_thread();
  init_blinky_thread();
	
  // start everything running
  osKernelStart();
	
	
	//Initialise the LCD
	BSP_LCD_Init();
	BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, SDRAM_DEVICE_ADDR);
	BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);

	// set the background colour to blue and clear the lcd
	BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
	BSP_LCD_Clear(LCD_COLOR_BLUE);

	// set the font to use
	BSP_LCD_SetFont(&Font24);

	// print the welcome message ...
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_DisplayStringAtLine(0, (uint8_t *)BOARDER);
	BSP_LCD_DisplayStringAtLine(1, (uint8_t *)welcome_message[0]);
	BSP_LCD_DisplayStringAtLine(2, (uint8_t *)welcome_message[1]);
	BSP_LCD_DisplayStringAtLine(3, (uint8_t *)BOARDER);


	// delay a little ...
	osDelay(2000);



//Main loop
	while(1)
	{
		
		char str[20];
		uint16_t adc_val2 = read_adc(ldr); //declare adc_val as an unsigned integer 16 characters long, and declare it as the value read from the ldr
		
		sprintf(str, "ADC = %3.2d", (adc_val2)); // print the message to the lcd
		BSP_LCD_DisplayStringAtLine(7, (uint8_t *)str); //print the message to line 7 on the LCD
		//BSP_LCD_ClearStringLine(7);

		BSP_LCD_DrawRect(100, 240, 100, 15);
		BSP_LCD_FillRect(100, 240, adc_val2, 15);
		BSP_LCD_ClearStringLine(10);

		BSP_LCD_DrawRect(100, 240, 100, 15);
		BSP_LCD_FillRect(100, 240, adc_val2, 15);


		sprintf(str, "ADC = ");
		BSP_LCD_DisplayStringAtLine(10, (uint8_t *)str);
		osDelay(300);

		
		
//		if(adc_val2 < 33.33)	//if adc_val2 is less than 33.33

//		{
//			write_gpio(led1, HIGH);
//			sprintf(str, "LED1 ON");
//			BSP_LCD_DisplayStringAtLine(8, (uint8_t *)str); //turn on LED1 on and output the status of the LED to line 8 of the LCD
//		}

//		else
//		{
//			write_gpio(led1, LOW);
//		}

//		if(adc_val2 > 33.33 && adc_val2 < 66.67)
//		{
//			write_gpio(led2, HIGH);
//			sprintf(str, "LED2 ON");
//			BSP_LCD_DisplayStringAtLine(8, (uint8_t *)str); //turn on LED2 on and output the status of the LED to line 8 of the LCD
//		}

//		else
//		{
//			write_gpio(led2, LOW);
//		}

//		if(adc_val2 > 66.7)
//		{
//			write_gpio(led3, HIGH);
//			sprintf(str, "LED3 ON");
//			BSP_LCD_DisplayStringAtLine(8, (uint8_t *)str);	//turn on LED3 on and output the status of the LED to line 8 of the LCD
//		}

//		else
//		{
//			write_gpio(led3, LOW);
//		}


	}

}
		
		
		
		
		
		
	

