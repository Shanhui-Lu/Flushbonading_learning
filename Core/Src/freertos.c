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
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef struct
{
    uint16_t id;
    uint32_t value;
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
/* Definitions for SensorQueue */
osMessageQueueId_t SensorQueueHandle;
const osMessageQueueAttr_t SensorQueue_attributes = {
  .name = "SensorQueue"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartLED_Task1(void *argument);
void StartLED_Task2(void *argument);
void StartSensorTask(void *argument);
void StartProcessTask(void *argument);

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
  SensorQueueHandle = osMessageQueueNew (10, 12, &SensorQueue_attributes);

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
	
  for(;;)
  {
	  sensor_msg.id = 1;
	  sensor_msg.value ++ ;
	  sensor_msg.timestamp = HAL_GetTick();
	  
	  osMessageQueuePut(
	  SensorQueueHandle,
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
		  //process_count++;
		  //HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_2);
		  //printf("ID:%" PRIu16 "Value:%" PRIu32 "Time:%"PRIu32 "\r\n",
		  //recv_msg.id, 
		  //recv_msg.value, 
		  //recv_msg.timestamp);
		  //char test[] = "ProcessTask OK\r\n";
		  
		  printf("ProcessTask OK\r\n");

		  //HAL_UART_Transmit(&huart1, (uint8_t *)test, sizeof(test) - 1, 100);
	  }
    //osDelay(1000);
  }
  /* USER CODE END StartProcessTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

