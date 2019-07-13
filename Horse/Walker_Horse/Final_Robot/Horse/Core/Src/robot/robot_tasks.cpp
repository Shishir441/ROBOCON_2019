#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "robot.h"
#include "robot_functions.h"

extern bool ROBOT_START_FLAG;
extern Robot_States robo_state;
extern float angles[7];
extern leg leg[2];
extern steering steering;
extern "C" void StartDefaultTask(void const *argument);
extern "C" void StartRobotTask(void const *argument);
extern "C" void StartLoggerTask(void const *argument);
extern "C" void StartCalculationTask(void const *argument);

float leg0_omega, leg1_omega, leg0_angle, leg1_angle;


/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const *argument)
{

	/* USER CODE BEGIN StartDefaultTask */
	/* Infinite loop */
	for (;;)
	{
		osDelay(1);
	}
	/* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartRobotTask */
/**
* @brief Function implementing the RobotTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartRobotTask */
void StartRobotTask(void const *argument)
{
	/* USER CODE BEGIN StartRobotTask */
	uint8_t sample_time = 10;
	uint32_t dt = HAL_GetTick();
	robo_state = HOME;
	leg[0].reset_angle(90 * PI / 180);
	leg[1].reset_angle(270 * PI / 180);
	/* Infinite loop */
	for (;;)
	{
		dt = HAL_GetTick();
		play();
		// if(HAL_GPIO_ReadPin(Proximity_Front_GPIO_Port, Proximity_Front_Pin) == GPIO_PIN_RESET){
		// 	printf("\n FRONT");
		// }
		// if(HAL_GPIO_ReadPin(Proximity_Back_GPIO_Port, Proximity_Back_Pin) == GPIO_PIN_RESET){
		// 	printf("\n BACK");
		// }
		// if(HAL_GPIO_ReadPin(Proximity_Up_GPIO_Port, Proximity_Up_Pin) == GPIO_PIN_RESET){
		// 	printf("\n UP");
		// }
		// leg[0].set_omega(0);
		// leg[1].set_omega(0);
		// steering.set_angle(0);
		// printf("\nleg0_angle = %d\tleg1_angle = %d\tsteering_angle = %d", (int)(leg[0].get_actual_angle() * 180 / PI),
		//        (int)(leg[1].get_actual_angle() * 180 / PI), (int)(steering.get_angle() * 180 / PI));
		
		// leg0_omega = leg[0].get_omega();
		// leg1_omega = leg[1].get_omega();
		// leg0_angle = leg[0].get_angle();
		// leg1_angle = leg[1].get_angle();
		dt = HAL_GetTick() - dt;
		osDelay(sample_time - dt);
	}
	/* USER CODE END StartRobotTask */
}

/* USER CODE BEGIN Header_StartLoggerTask */
/**
* @brief Function implementing the LoggerTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartLoggerTask */
void StartLoggerTask(void const *argument)
{
	/* USER CODE BEGIN StartLoggerTask */
	/* Infinite loop */
	uint8_t sample_time = 50;
	uint32_t dt = HAL_GetTick();
	for (;;)
	{
		dt = HAL_GetTick();

		dt = HAL_GetTick() - dt;
		osDelay(sample_time - dt);
	}
	/* USER CODE END StartLoggerTask */
}

/* USER CODE BEGIN Header_StartCalculationTask */
/**
* @brief Function implementing the CalculationTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartCalculationTask */
void StartCalculationTask(void const *argument)
{
	/* USER CODE BEGIN StartCalculationTask */
	/* Infinite loop */
	uint8_t sample_time = 10;
	uint32_t dt = HAL_GetTick();
	for (;;)
	{
		dt = HAL_GetTick();
		calculate_datas();
		dt = HAL_GetTick() - dt;
		osDelay(sample_time - dt);
	}
	/* USER CODE END StartCalculationTask */
}