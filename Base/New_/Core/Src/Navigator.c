#include "Navigator.h"

#define NUM_LOCATION_RECEIVED	(6)
#define MAX_POSSIBLE_LOCATION	(50) 

//static uint8_t send_flag = 1;
static uint8_t gNavigator_Data;
static uint8_t gStart_Byte_Received = 0;
static uint8_t gNum_Data_Received = 0;
static int16_t gOmega;

static struct Queue8 gNavigator_Bytes;
static struct Queue16 gNavigator_datas[3];
//static uint16_t gu3_datas[4];


void Navigator_Init(void)
{
	HAL_UART_Receive_DMA(&huart3, &gNavigator_Data, 1);
	Queue8_Init(&gNavigator_Bytes);
	for (uint8_t i = 0; i < 3; ++i) {
		Queue16_Init(&gNavigator_datas[i]);
	}
}

void get_Navigator(float arr[3])
{
	for (uint8_t i= 0; i < 3; ++i) {
		arr[i] = Queue16_lookup(&gNavigator_datas[i]);
		arr[i] *= (MAX_POSSIBLE_LOCATION / 32768.0);
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	 if(huart->Instance == USART3)
	 {
		if(!gStart_Byte_Received)
		{
			if (gNavigator_Data == 0xA5) {
				gStart_Byte_Received = 1;
			}
		}
		else
		{
			Queue8_insert(&gNavigator_Bytes, gNavigator_Data);
			++gNum_Data_Received;
			if (gNum_Data_Received == NUM_LOCATION_RECEIVED) {
				gNum_Data_Received = 0;
				gStart_Byte_Received = 0;
				// Omega calculation using little-endian
				for (uint8_t i = 0; i < 3; ++i) {
					gOmega = (uint16_t)(Queue8_lookup(&gNavigator_Bytes) << 8);
					gOmega += (uint16_t)(Queue8_lookup(&gNavigator_Bytes));
					Queue16_insert(&gNavigator_datas[i], gOmega);
				}
			}
		}
	 }
}
