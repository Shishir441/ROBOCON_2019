
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
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"


/* USER CODE BEGIN Includes */
#include "robo_init.h"
#include "robot.h"
#include "pid.h"
#include <stdlib.h>
#include "drive.h"

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/


/* USER CODE BEGIN PV */
extern double velocity[3];
extern float robotx, roboty, theta;
extern int32_t counts[4] ;
extern struct Str_pid pid_1;
extern struct Str_pid pid_2;
extern struct Str_pid pid_3;
extern struct Str_pid pid_4;
extern struct Str_pid_distance pid_dis_1;
extern struct Str_pid_distance pid_dis_2;
extern struct Str_pid_distance pid_dis_3;
extern uint16_t   update_tick;
float go[697][2] = {{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.245},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.245},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.245},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.245},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.245},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.245},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.245},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.245},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.245},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.245},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.245},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.245},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.245},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.245},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.245},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.2449},
			{-10 , 12.245},
			{-10 , 12.2449},
			{10 , 149.248},
			{10 , 60.752},
			{10 , 45.8809},
			{10 , 38.0579},
			{10 , 32.9788},
			{10 , 29.3127},
			{10 , 26.4902},
			{10 , 24.2192},
			{10 , 22.333},
			{10 , 20.7273},
			{10 , 19.3347},
			{10 , 18.1077},
			{10 , 17.0127},
			{10 , 16.0254},
			{10 , 15.1267},
			{10 , 14.302},
			{10 , 13.54},
			{10 , 12.832},
			{10 , 12.1702},
			{10 , 11.5486},
			{10 , 10.9624},
			{10 , 10.407},
			{10 , 9.87939},
			{10 , 9.37598},
			{10 , 8.89429},
			{10 , 8.43237},
			{10 , 7.98779},
			{10 , 7.55908},
			{10 , 7.14478},
			{10 , 6.74341},
			{10 , 6.35327},
			{10 , 5.97437},
			{10 , 5.60498},
			{10 , 5.24414},
			{10 , 4.89111},
			{10 , 4.54565},
			{10 , 4.20654},
			{10 , 3.87305},
			{10 , 3.54541},
			{10 , 3.22192},
			{10 , 2.90308},
			{10 , 2.58765},
			{10 , 2.27588},
			{10 , 1.9668},
			{10 , 1.66016},
			{10 , 1.35571},
			{10 , 1.05249},
			{10 , 0.750977},
			{10 , 0.450439},
			{10.4712 , 10},
			{10.4712 , 10},
			{10.4667 , 10},
			{10.4574 , 10},
			{10.4436 , 10},
			{10.4254 , 10},
			{10.4023 , 10},
			{10.3749 , 10},
			{10.3429 , 10},
			{10.3063 , 10},
			{10.2651 , 10},
			{10.2196 , 10},
			{10.1696 , 10},
			{10.115 , 10},
			{10.0559 , 10},
			{9.99268 , 10},
			{9.9248 , 10},
			{9.85266 , 10},
			{9.77625 , 10},
			{9.69556 , 10},
			{9.61053 , 10},
			{9.5213 , 10},
			{9.42792 , 10},
			{9.33044 , 10},
			{9.22882 , 10},
			{9.12317 , 10},
			{9.01349 , 10},
			{8.8999 , 10},
			{8.78241 , 10},
			{8.66101 , 10},
			{8.53583 , 10},
			{8.40692 , 10},
			{8.27435 , 10},
			{8.13806 , 10},
			{7.99835 , 10},
			{7.85498 , 10},
			{7.70825 , 10},
			{7.55811 , 10},
			{7.40466 , 10},
			{7.24799 , 10},
			{7.08807 , 10},
			{6.92511 , 10},
			{6.75909 , 10},
			{6.59015 , 10},
			{6.41821 , 10},
			{6.24353 , 10},
			{6.0661 , 10},
			{5.88605 , 10},
			{5.70331 , 10},
			{5.51819 , 10},
			{5.33057 , 10},
			{5.14062 , 10},
			{4.94849 , 10},
			{4.75409 , 10},
			{4.55762 , 10},
			{4.35919 , 10},
			{4.15887 , 10},
			{3.95667 , 10},
			{3.75275 , 10},
			{3.54718 , 10},
			{3.34009 , 10},
			{3.13147 , 10},
			{2.92157 , 10},
			{2.71027 , 10},
			{2.49786 , 10},
			{2.28436 , 10},
			{2.06982 , 10},
			{1.85443 , 10},
			{1.63812 , 10},
			{1.4212 , 10},
			{1.20355 , 10},
			{0.985535 , 10},
			{0.766907 , 10},
			{0.548035 , 10},
			{0.328918 , 10},
			{0.10968 , 10},
			{-0.10968 , 10},
			{-0.328918 , 10},
			{-0.548035 , 10},
			{-0.766907 , 10},
			{-0.985535 , 10},
			{-1.20355 , 10},
			{-1.4212 , 10},
			{-1.63812 , 10},
			{-1.85443 , 10},
			{-2.06982 , 10},
			{-2.28436 , 10},
			{-2.49786 , 10},
			{-2.71027 , 10},
			{-2.92157 , 10},
			{-3.13147 , 10},
			{-3.34009 , 10},
			{-3.54718 , 10},
			{-3.75275 , 10},
			{-3.95667 , 10},
			{-4.15887 , 10},
			{-4.35919 , 10},
			{-4.55762 , 10},
			{-4.75409 , 10},
			{-4.94849 , 10},
			{-5.14062 , 10},
			{-5.33057 , 10},
			{-5.51819 , 10},
			{-5.70331 , 10},
			{-5.88605 , 10},
			{-6.0661 , 10},
			{-6.24353 , 10},
			{-6.41821 , 10},
			{-6.59015 , 10},
			{-6.75909 , 10},
			{-6.92511 , 10},
			{-7.08807 , 10},
			{-7.24799 , 10},
			{-7.40466 , 10},
			{-7.55811 , 10},
			{-7.70825 , 10},
			{-7.85498 , 10},
			{-7.99835 , 10},
			{-8.13806 , 10},
			{-8.27435 , 10},
			{-8.40692 , 10},
			{-8.53583 , 10},
			{-8.66101 , 10},
			{-8.78241 , 10},
			{-8.8999 , 10},
			{-9.01349 , 10},
			{-9.12317 , 10},
			{-9.22882 , 10},
			{-9.33044 , 10},
			{-9.42792 , 10},
			{-9.5213 , 10},
			{-9.61053 , 10},
			{-9.69556 , 10},
			{-9.77625 , 10},
			{-9.85266 , 10},
			{-9.9248 , 10},
			{-9.99268 , 10},
			{-10.0559 , 10},
			{-10.115 , 10},
			{-10.1696 , 10},
			{-10.2196 , 10},
			{-10.2651 , 10},
			{-10.3063 , 10},
			{-10.3429 , 10},
			{-10.3749 , 10},
			{-10.4023 , 10},
			{-10.4254 , 10},
			{-10.4436 , 10},
			{-10.4574 , 10},
			{-10.4667 , 10},
			{-10.4712 , 10},
			{-10.4712 , 10},
			{-10.4667 , 10},
			{-10.4574 , 10},
			{-10.4436 , 10},
			{-10.4254 , 10},
			{-10.4023 , 10},
			{-10.3749 , 10},
			{-10.3429 , 10},
			{-10.3063 , 10},
			{-10.2651 , 10},
			{-10.2196 , 10},
			{-10.1696 , 10},
			{-10.115 , 10},
			{-10.0559 , 10},
			{-9.99268 , 10},
			{-9.9248 , 10},
			{-9.85266 , 10},
			{-9.77625 , 10},
			{-9.69556 , 10},
			{-9.61047 , 10},
			{-9.52136 , 10},
			{-9.42798 , 10},
			{-9.33044 , 10},
			{-9.22876 , 10},
			{-9.12317 , 10},
			{-9.01355 , 10},
			{-8.8999 , 10},
			{-8.78235 , 10},
			{-8.66101 , 10},
			{-8.53577 , 10},
			{-8.40698 , 10},
			{-8.27429 , 10},
			{-8.13818 , 10},
			{-7.99829 , 10},
			{-7.85498 , 10},
			{-7.70825 , 10},
			{-7.55811 , 10},
			{-7.40466 , 10},
			{-7.24792 , 10},
			{-7.08813 , 10},
			{-6.92517 , 10},
			{-6.75903 , 10},
			{-6.59009 , 10},
			{-6.41833 , 10},
			{-6.24353 , 10},
			{-6.06604 , 10},
			{-5.88599 , 10},
			{-5.70337 , 10},
			{-5.51819 , 10},
			{-5.33057 , 10},
			{-5.14062 , 10},
			{-4.94849 , 10},
			{-4.75403 , 10},
			{-4.55774 , 10},
			{-4.35913 , 10},
			{-4.15881 , 10},
			{-3.95667 , 10},
			{-3.75281 , 10},
			{-3.54724 , 10},
			{-3.33997 , 10},
			{-3.13159 , 10},
			{-2.92151 , 10},
			{-2.71033 , 10},
			{-2.4978 , 10},
			{-2.28442 , 10},
			{-2.06982 , 10},
			{-1.85437 , 10},
			{-1.63806 , 10},
			{-1.42126 , 10},
			{-1.20361 , 10},
			{-0.985474 , 10},
			{-0.766846 , 10},
			{-0.548096 , 10},
			{-0.328979 , 10},
			{-0.109619 , 10},
			{0.109619 , 10},
			{0.328979 , 10},
			{0.548096 , 10},
			{0.766846 , 10},
			{0.985474 , 10},
			{1.20361 , 10},
			{1.42126 , 10},
			{1.63806 , 10},
			{1.85437 , 10},
			{2.06982 , 10},
			{2.28442 , 10},
			{2.4978 , 10},
			{2.71033 , 10},
			{2.92151 , 10},
			{3.13159 , 10},
			{3.33997 , 10},
			{3.54724 , 10},
			{3.75281 , 10},
			{3.95667 , 10},
			{4.15881 , 10},
			{4.35913 , 10},
			{4.55774 , 10},
			{4.75403 , 10},
			{4.94849 , 10},
			{5.14062 , 10},
			{5.33057 , 10},
			{5.51819 , 10},
			{5.70337 , 10},
			{5.88599 , 10},
			{6.06604 , 10},
			{6.24353 , 10},
			{6.41833 , 10},
			{6.59009 , 10},
			{6.75903 , 10},
			{6.92517 , 10},
			{7.08813 , 10},
			{7.24792 , 10},
			{7.40466 , 10},
			{7.55811 , 10},
			{7.70825 , 10},
			{7.85498 , 10},
			{7.99829 , 10},
			{8.13818 , 10},
			{8.27429 , 10},
			{8.40698 , 10},
			{8.53577 , 10},
			{8.66101 , 10},
			{8.78235 , 10},
			{8.8999 , 10},
			{9.01355 , 10},
			{9.12317 , 10},
			{9.22876 , 10},
			{9.33044 , 10},
			{9.42798 , 10},
			{9.52136 , 10},
			{9.61047 , 10},
			{9.69556 , 10},
			{9.77625 , 10},
			{9.85266 , 10},
			{9.9248 , 10},
			{9.99268 , 10},
			{10.0559 , 10},
			{10.115 , 10},
			{10.1696 , 10},
			{10.2196 , 10},
			{10.2651 , 10},
			{10.3063 , 10},
			{10.3429 , 10},
			{10.3749 , 10},
			{10.4023 , 10},
			{10.4254 , 10},
			{10.4436 , 10},
			{10.4574 , 10},
			{10.4667 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10},
			{-0 , 10}};

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



/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
  {
        /* USER CODE BEGIN 1 */ 
        update_tick = HAL_GetTick();
        set_Gains_distance(&pid_dis_1, 13.55,0.025,300);	  // 13.55,0.025,300	25.55,0.004,1000
		set_Gains_distance(&pid_dis_2, 7.465,0.011,200);    // 7.465,0.011,200
		set_Gains_distance(&pid_dis_3, 2500,0.1,800);
				
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
        MX_ADC1_Init();
        MX_TIM8_Init();
        MX_USART1_UART_Init();
        MX_USART3_UART_Init();
     
        /* USER CODE BEGIN 2 */
				
	wheel_init();
	init_encoder();
	
	set_OutputLimit(&pid_1,120,-120);	
	set_OutputLimit(&pid_2,120,-120);
	set_OutputLimit(&pid_3,120,-120);
	set_OutputLimit(&pid_4,120,-120);
	
	HAL_TIM_Base_Start(&htim8);
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4);
	
        /* USER CODE END 2 */

        /* Infinite loop */
	int ok;
		
		ok = goto_distance(2000, 0, 0);
		
		ok = goto_distance(0,5000,0);
		//play();
		ok++;
	
	while (1)
	{
		printf("Hello\n");	
		velocity[0]=0;
		velocity[1]=0;
		velocity[2]=0;
		calculate_robot_velocity();
		calculate_robot_distance();
		//printf("\n%f ", robotx);
        
	/* USER CODE BEGIN WHILE */
	    	  
	}				
	/* USER CODE END WHILE */
            /* USER CODE BEGIN 3 */			
}
		
						
        /* USER CODE END 3 */
	 
			
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
        RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
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
        HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);

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

#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
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
