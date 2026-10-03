/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <inttypes.h>
#include <stdio.h>
#include "usart.h"
#include "ATH20.h"
#include "BMP280.h"
#include "bsp_i2c.h"
#include "oled.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
//typedef struct
//{
//    uint16_t id;
//    uint32_t value;
//    uint32_t timestamp;

//} SensorMsg;
typedef struct
{
    int32_t aht_temp_x10;
    int32_t humidity_x10;

    int32_t bmp_temp_x10;
    int32_t pressure_x10;
    int32_t altitude_x10;

    uint32_t timestamp;

} SensorMsg;


/* USER CODE BEGIN PTD */


/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

extern UART_HandleTypeDef huart1;

/* USER CODE END Variables */
/* Definitions for LED_Task1 */
osThreadId_t LED_Task1Handle;
const osThreadAttr_t LED_Task1_attributes = {
  .name = "LED_Task1",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for LED_Task2 */
osThreadId_t LED_Task2Handle;
const osThreadAttr_t LED_Task2_attributes = {
  .name = "LED_Task2",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for SensorTask */
osThreadId_t SensorTaskHandle;
const osThreadAttr_t SensorTask_attributes = {
  .name = "SensorTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for ProcessTask */
osThreadId_t ProcessTaskHandle;
const osThreadAttr_t ProcessTask_attributes = {
  .name = "ProcessTask",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for DisplayTask */
osThreadId_t DisplayTaskHandle;
const osThreadAttr_t DisplayTask_attributes = {
  .name = "DisplayTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for SensorQueue */
osMessageQueueId_t SensorQueueHandle;
const osMessageQueueAttr_t SensorQueue_attributes = {
  .name = "SensorQueue"
};
/* Definitions for DisplayQueue */
osMessageQueueId_t DisplayQueueHandle;
const osMessageQueueAttr_t DisplayQueue_attributes = {
  .name = "DisplayQueue"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartLED_Task1(void *argument);
void StartLED_Task2(void *argument);
void StartSensorTask(void *argument);
void StartProcessTask(void *argument);
void StartDisplayTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of SensorQueue */
  SensorQueueHandle = osMessageQueueNew (10, 24, &SensorQueue_attributes);

  /* creation of DisplayQueue */
  DisplayQueueHandle = osMessageQueueNew (10, 24, &DisplayQueue_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of LED_Task1 */
  LED_Task1Handle = osThreadNew(StartLED_Task1, NULL, &LED_Task1_attributes);

  /* creation of LED_Task2 */
  LED_Task2Handle = osThreadNew(StartLED_Task2, NULL, &LED_Task2_attributes);

  /* creation of SensorTask */
  SensorTaskHandle = osThreadNew(StartSensorTask, NULL, &SensorTask_attributes);

  /* creation of ProcessTask */
  ProcessTaskHandle = osThreadNew(StartProcessTask, NULL, &ProcessTask_attributes);

  /* creation of DisplayTask */
  DisplayTaskHandle = osThreadNew(StartDisplayTask, NULL, &DisplayTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartLED_Task1 */
/**
  * @brief  Function implementing the LED_Task1 thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartLED_Task1 */
void StartLED_Task1(void *argument)
{
  /* USER CODE BEGIN StartLED_Task1 */
  /* Infinite loop */
  for(;;)
  {
	  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_2);
      osDelay(500);
  }
  /* USER CODE END StartLED_Task1 */
}

/* USER CODE BEGIN Header_StartLED_Task2 */
/**
* @brief Function implementing the LED_Task2 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartLED_Task2 */
void StartLED_Task2(void *argument)
{
  /* USER CODE BEGIN StartLED_Task2 */
  /* Infinite loop */
  for(;;)
  {
	  osDelay(1000);
  }
  /* USER CODE END StartLED_Task2 */
}

/* USER CODE BEGIN Header_StartSensorTask */
/**
* @brief Function implementing the SensorTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartSensorTask */
void StartSensorTask(void *argument)
{
  /* USER CODE BEGIN StartSensorTask */
  /* Infinite loop */
	//uint32_t sensor_data = 0;
	SensorMsg sensor_msg = {0};
	
	uint32_t CT_data[2];

    int c1;
    int t1;

    float P;
    float T;
    float ALT;

	
  for(;;)
  {
	   /* AHT20 */
        if(ATH20_Read_Cal_Enable() == 0)
        {
            ATH20_Init();
            osDelay(30);
        }

        ATH20_Read_CTdata(CT_data);

        c1 = CT_data[0] * 1000 / 1024 / 1024;
        t1 = CT_data[1] * 200 * 10 / 1024 / 1024 - 500;

        /* BMP280 */
        BMP280GetData(&P, &T, &ALT);

        /* Pack sensor message */
        sensor_msg.aht_temp_x10 = t1;
        sensor_msg.humidity_x10 = c1;

        sensor_msg.bmp_temp_x10 = (int32_t)(T * 10.0f);
        sensor_msg.pressure_x10 = (int32_t)(P * 10.0f);
        sensor_msg.altitude_x10 = (int32_t)(ALT * 10.0f);
		
	  sensor_msg.timestamp = HAL_GetTick();
	  
	  osMessageQueuePut(
	  SensorQueueHandle,
	  &sensor_msg,
	  0,
	  100
	  );
	  osMessageQueuePut(
      DisplayQueueHandle,
      &sensor_msg,
      0,
      100
	  );
	//sensor_count++;  
    osDelay(1000);
  }
  /* USER CODE END StartSensorTask */
}

/* USER CODE BEGIN Header_StartProcessTask */
/**
* @brief Function implementing the ProcessTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartProcessTask */
void StartProcessTask(void *argument)
{
  /* USER CODE BEGIN StartProcessTask */
  /* Infinite loop */
	//uint32_t recv_data;
	SensorMsg recv_msg;
  for(;;)
  {
	  //uint32_t recv_data;
	  if(osMessageQueueGet(
		  SensorQueueHandle,
		  &recv_msg,
	      NULL,
	      osWaitForever
	  ) == osOK)
	  {
		  printf("AHT20 Temp: %d.%d C\r\n",
                   recv_msg.aht_temp_x10 / 10,
                   recv_msg.aht_temp_x10 % 10);

            printf("AHT20 Humi: %d.%d %%\r\n",
                   recv_msg.humidity_x10 / 10,
                   recv_msg.humidity_x10 % 10);

            printf("BMP280 Temp: %d.%d C\r\n",
                   recv_msg.bmp_temp_x10 / 10,
                   recv_msg.bmp_temp_x10 % 10);

            printf("BMP280 Press: %d.%d hPa\r\n",
                   recv_msg.pressure_x10 / 10,
                   recv_msg.pressure_x10 % 10);

            printf("BMP280 Alt: %d.%d m\r\n",
                   recv_msg.altitude_x10 / 10,
                   recv_msg.altitude_x10 % 10);

            printf("--------------------\r\n"); 
		  //process_count++;
		  //HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_2);
		  //printf("ID:%" PRIu16 "Value:%" PRIu32 "Time:%"PRIu32 "\r\n",
		  //recv_msg.id, 
		  //recv_msg.value, 
		  //recv_msg.timestamp);
		  //char test[] = "ProcessTask OK\r\n";
		  
		  //printf("ProcessTask OK\r\n");

		  //HAL_UART_Transmit(&huart1, (uint8_t *)test, sizeof(test) - 1, 100);
	  }
    //osDelay(1000);
  }
  /* USER CODE END StartProcessTask */
}

/* USER CODE BEGIN Header_StartDisplayTask */
/**
* @brief Function implementing the DisplayTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartDisplayTask */
void StartDisplayTask(void *argument)
{
  /* USER CODE BEGIN StartDisplayTask */
	SensorMsg display_msg;

    char line1[24];
    char line2[24];
    char line3[24];
    char line4[24];
  /* Infinite loop */
  for(;;)
  {
	  if(osMessageQueueGet(
            DisplayQueueHandle,
            &display_msg,
            NULL,
            osWaitForever
        ) == osOK)
        {
            sprintf(line1, "T:%d.%d C",
                    display_msg.aht_temp_x10 / 10,
                    display_msg.aht_temp_x10 % 10);

            sprintf(line2, "H:%d.%d %%",
                    display_msg.humidity_x10 / 10,
                    display_msg.humidity_x10 % 10);

            sprintf(line3, "P:%d.%d hPa",
                    display_msg.pressure_x10 / 10,
                    display_msg.pressure_x10 % 10);

            sprintf(line4, "Alt:%d.%d m",
                    display_msg.altitude_x10 / 10,
                    display_msg.altitude_x10 % 10);

            OLED_Clear();

            OLED_ShowString(0,  0, (uint8_t *)line1, 16, 1);
            OLED_ShowString(0, 16, (uint8_t *)line2, 16, 1);
            OLED_ShowString(0, 32, (uint8_t *)line3, 16, 1);
            OLED_ShowString(0, 48, (uint8_t *)line4, 16, 1);

            OLED_Refresh();
		}
    
  }
  /* USER CODE END StartDisplayTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

