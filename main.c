#include <stdio.h>
TIM_HandleTypeDef htim16;
UART_HandleTypeDef huart2;
/* Private function prototypes */
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM16_Init(void);
int main(void)
{
  char uart_buf[50];
  int uart_buf_len;
  uint16_t timer_val;
/* MCU Configuration*/
/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
  SystemClock_Config();
/* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_TIM16_Init();
  uart_buf_len = sprintf(uart_buf, "Timer Test\r\n");
  HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
// Start timer
  HAL_TIM_Base_Start(&htim16);
  while (1)
  {
    // Get current time (microseconds)
    timer_val = __HAL_TIM_GET_COUNTER(&htim16);
    // Wait for 50 ms
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
    HAL_Delay(50);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
   // Get time elapsed
    timer_val = __HAL_TIM_GET_COUNTER(&htim16) - timer_val;
   // Show elapsed time
    uart_buf_len = sprintf(uart_buf, "%u us\r\n", timer_val);
    HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
  // Wait again so we don't flood the Serial terminal
    HAL_Delay(1000);
}
}

  
