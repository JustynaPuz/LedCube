/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "main.h"
#include "LedCubeModes.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define MAX_COMMAND_QUEUE 10
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
uint8_t rxData;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM3_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

char *demo_string = "Hello \r\n"; //demo string
uint8_t recv_char;
uint8_t recv_str[40];
uint8_t command[40];
int i=0;
char *on = "on";
char *off = "off";
char *all_leds_on = "all_leds_on";
char *all_leds_off = "all_leds_off";
uint8_t ft = 76;
volatile bool interruptOccurred = false;


#define COMMAND_FLICKER_ON "command_flicker_on"
#define COMMAND_LAYER_UP_DOWN "command_layer_up_down"
#define COMMAND_COLUMNS_SIDEWAYS "command_columns_sideways"
#define COMMAND_STOMP_UP_DOWN "command_stomp_up_down"
#define COMMAND_FLICKER_OFF "command_flicker_off"
#define COMMAND_AROUND_EDGE "command_around_edge"
#define COMMAND_RECTANGLE "command_rectangle"
#define COMMAND_PROPELLER "command_propeller"
#define COMMAND_SPIRAL "command_spiral"
#define COMMAND_ALL_LEDS "command_all_leds"
#define COMMAND_ALL_ON "all_leds_on"
#define COMMAND_ALL_OFF "all_leds_off"

typedef struct {
    char command[40];
    bool active;
} CommandQueueItem;

CommandQueueItem commandQueue[MAX_COMMAND_QUEUE];
int commandQueueSize = 0;

void processBluetoothCommands(char* recv_str) {
    char commandOn[40];
    char commandOff[40];

    strcpy(commandOn, recv_str);
    strcpy(commandOff, recv_str);
    strcat(commandOn, "_on");
    strcat(commandOff, "_off");

    // Check if the received command is to turn on
    if (strstr(recv_str, "_on")) {
        // Remove "_on" from the command
        recv_str[strlen(recv_str) - 3] = '\0';

        // Check if the command is already in the queue
        for (int j = 0; j < commandQueueSize; ++j) {
            if (!strcmp(commandQueue[j].command, recv_str)) {
                // Command already in queue, no need to add it again
                return;
            }
        }

        // Add the command to the queue
        if (commandQueueSize < MAX_COMMAND_QUEUE) {
            strcpy(commandQueue[commandQueueSize].command, recv_str);
            commandQueue[commandQueueSize].active = true;
            commandQueueSize++;
        }
    } else if (strstr(recv_str, "_off")) {
        // Remove "_off" from the command
        recv_str[strlen(recv_str) - 4] = '\0';

        // Deactivate the command in the queue
        for (int j = 0; j < commandQueueSize; ++j) {
            if (!strcmp(commandQueue[j].command, recv_str)) {
                // Remove the command from the queue
                for (int k = j; k < commandQueueSize - 1; ++k) {
                    commandQueue[k] = commandQueue[k + 1];
                }
                commandQueueSize--;
                return;
            }
        }
    }
}




void executeCommandQueue() {
    for (int j = 0; j < commandQueueSize; ++j) {
        if (commandQueue[j].active) {
            if (!strcmp(commandQueue[j].command, COMMAND_FLICKER_ON)) {
                flickerOn();
            } else if (!strcmp(commandQueue[j].command, COMMAND_LAYER_UP_DOWN)) {
                turnOnAndOffAllByLayerUpAndDownNotTimed();
            } else if (!strcmp(commandQueue[j].command, COMMAND_COLUMNS_SIDEWAYS)) {
                turnOnAndOffAllByColumnSideways();
            } else if (!strcmp(commandQueue[j].command, COMMAND_STOMP_UP_DOWN)) {
                layerstompUpAndDown();
            } else if (!strcmp(commandQueue[j].command, COMMAND_FLICKER_OFF)) {
                flickerOff();
            } else if (!strcmp(commandQueue[j].command, COMMAND_AROUND_EDGE)) {
                aroundEdgeDown();
            } else if (!strcmp(commandQueue[j].command, COMMAND_RECTANGLE)) {
                diagonalRectangle();
            } else if (!strcmp(commandQueue[j].command, COMMAND_PROPELLER)) {
                propeller();
            } else if (!strcmp(commandQueue[j].command, COMMAND_SPIRAL)) {
                spiralInAndOut();
            } else if (!strcmp(commandQueue[j].command, COMMAND_ALL_LEDS)) {
                goThroughAllLedsOneAtATime();
            }
        }
    }
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

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
  MX_TIM3_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_UART_Receive_IT(&huart1, &recv_char, 1);

//    HAL_UART_Receive_IT(&huart1, &recv_char, 1); //UART1 Interrupt call
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if(!strcmp(recv_str, on)){
	  		   HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, SET);
	  		}
	  if(!strcmp(recv_str, off)){
	  		    HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, RESET);
	  	    }
	  if(!strcmp(recv_str, all_leds_on)){
	  	  		    enableAllPins();
	  	  	    }
	  if(!strcmp(recv_str, all_leds_off)){
	 	  	  		    disableAllPins();
	 	  	  	    }




	  		if(interruptOccurred) {
	  			interruptOccurred = false;
	  			processBluetoothCommands(command);
	  		}
	 executeCommandQueue();

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 84;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 720;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 1999;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, PIN11_Pin|PIN12_Pin|PIN31_Pin|PIN13_Pin
                          |PIN32_Pin|LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LAYER1_Pin|LAYER2_Pin|LAYER3_Pin|PIN42_Pin
                          |PIN41_Pin|PIN34_Pin|PIN24_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LAYER4_Pin|PIN23_Pin|PIN14_Pin|PIN22_Pin
                          |PIN21_Pin|PIN33_Pin|PIN44_Pin|PIN43_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PIN11_Pin PIN12_Pin PIN31_Pin PIN13_Pin
                           PIN32_Pin LED_Pin */
  GPIO_InitStruct.Pin = PIN11_Pin|PIN12_Pin|PIN31_Pin|PIN13_Pin
                          |PIN32_Pin|LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : LAYER1_Pin LAYER2_Pin LAYER3_Pin PIN42_Pin
                           PIN41_Pin PIN34_Pin PIN24_Pin */
  GPIO_InitStruct.Pin = LAYER1_Pin|LAYER2_Pin|LAYER3_Pin|PIN42_Pin
                          |PIN41_Pin|PIN34_Pin|PIN24_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LAYER4_Pin PIN23_Pin PIN14_Pin PIN22_Pin
                           PIN21_Pin PIN33_Pin PIN44_Pin PIN43_Pin */
  GPIO_InitStruct.Pin = LAYER4_Pin|PIN23_Pin|PIN14_Pin|PIN22_Pin
                          |PIN21_Pin|PIN33_Pin|PIN44_Pin|PIN43_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
    if(huart->Instance == USART1 ){
        if(recv_char == '\r'){
        memset(command, 0, sizeof(command));
        memcpy(command, recv_str, sizeof(recv_str));
		memset(recv_str, 0, sizeof(recv_str));
		i=0;
		interruptOccurred = true;
		}else{
		    if(recv_char != '\n'){
		    	recv_str[i++] = recv_char;
		}
	 }
	 HAL_UART_Receive_IT(&huart1, &recv_char, 1); //UART1 Interrupt call

    }
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
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
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
