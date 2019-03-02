
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include "robo_init.h"
#include "pid.h"
#include <stdlib.h>
#include "motionProfile.h"
#include "leg.h"
#include "gait.h"

#define CALIBRATE_SPEED (-4.0) /* In omega */
#define HOME_POS_OMEGA (-4.0) 
#define MAX_POSSIBLE_ANGLE (140)

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
       
    // global variables
    int16_t ref_cnt[4]   = {0, 0, 0, 0};          // last count when interrupt occured
    int16_t curr_cnt[4]  = {0, 0, 0, 0};          // current count for angle calculation 
    uint16_t last_cnt[4] = {0, 0, 0, 0};
    
    float inst_angle[4]     = {0, 0, 0, 0};       // angle at the instant
    float update_omega[4]   = {0, 0, 0, 0};
 
    uint32_t dt_ms = 9L;
    float dt_secs  = 0.009;
    
    float all_set_points;
   
    //global flags
    uint8_t _PHASE = 0;
    uint16_t _CHECK_VARIABLE = 111;
    uint8_t _PHASE_CHANGE_FLAG = 0;
    uint8_t _RAISE_MOTOR_INDEX = 0;
    uint8_t _START_LOOP_FLAG = 0;
    uint8_t _NEXT_MOTOR_FLAG = 0;
    

/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/


/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

	
struct __FILE{
	
int handle;
};

FILE __stdout;
FILE __stdin;

int fputc(int ch, FILE *f)
{
	ITM_SendChar(ch);
	return(ch);
}


/*void calculate_setPoints()
{
    
     
    for(int i=0; i<4; i++)
    {
        int16_t counts_per_st = curr_cnt[i] - last_cnt[i];
        last_cnt[i]      = curr_cnt[i];
    
        float omega      = 0.71922 * counts_per_st / dt_ms;
        if((i == _RAISE_MOTOR_INDEX) && !_START_LOOP_FLAG)
        {
            raise_Leg(&leg_arr[_RAISE_MOTOR_INDEX]);
			
		    int temp_angle = i * (-60);		
            motionProfile_setAngle(&profile_arr[i], temp_angle);
            
            float set_point  = motionProfile_Generate(&profile_arr[i],inst_angle[i]);
            update_omega[i]  = pid_Compute(&pid[i], set_point, omega, dt_ms);
           
            if((profile_arr[i].status == COMPLETE) && (inst_angle[i] >= temp_angle))
            {   
                _START_LOOP_FLAG = 1; 
                update_omega[_RAISE_MOTOR_INDEX] = 0;
              
            }       
            
        }    
       
       if((i != _RAISE_MOTOR_INDEX) && _START_LOOP_FLAG )
       {
           motionProfile_setAngle(&profile_arr[i],60);
           float set_point  = motionProfile_Generate(&profile_arr[i],inst_angle[i]);               
           update_omega[i]  = pid_Compute(&pid[i], set_point, omega, dt_ms);
       }   
    }       
} */


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  	/* USER CODE BEGIN 1 */
	
	uint32_t update_tick = HAL_GetTick();

  	/* USER CODE END 1 */

  	/* MCU Configuration----------------------------------------------------------*/

  	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	
  	HAL_Init();

  	/* USER CODE BEGIN Init */

  	/* USER CODE END Init */

  	/* Configure the system clock */
  	SystemClock_Config();

  	/* USER CODE BEGIN SysInit */

  	/* USER CODE END SysInit */

  	/* Initialize all configured peripherals */
  	MX_GPIO_Init();
  	MX_TIM8_Init();
  	MX_USART3_UART_Init();
  	MX_TIM1_Init();
  	MX_TIM2_Init();
  	MX_TIM3_Init();
  	MX_TIM4_Init();
  	/* USER CODE BEGIN 2 */
	
	robot_init();
  	/* USER CODE END 2 */

  	/* Infinite loop */
  	/* USER 
  	CODE BEGIN WHILE */
	
  	set_HomePosition();

  	while(1) 
	{	    
  	     	if((HAL_GetTick()- update_tick) > dt_ms)
  	      	{
  	      		update_tick   = HAL_GetTick();
			start_Gallop();
  	      	}                

  	}   
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

    
   
    


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
        /* User can add his own implementation to report the HAL error return state */
        while (1)
        {
        }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
        /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

