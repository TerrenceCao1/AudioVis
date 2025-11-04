#include "LED_task.h"
#include "driver/gpio.h"
#include "esp_rom_gpio.h"
#include "freertos/idf_additions.h"
#include "freertos/projdefs.h"
#include "hal/gpio_types.h"
#include "matrix_wrapper.h"
#include "portmacro.h"

// TODO: Color changing Button!
int colorIndex = 0;
static const uint16_t colors[] = {0xFFFF, 0xF000, 0x3EBF, 0xEC9D, 0x07E4, 0x20FE};
#define COLOR_COUNT (sizeof(colors) / sizeof(colors[0]))

void xDrawLEDLevels(void *pvParameter)
{
	matrix_init(WIDTH, HEIGHT);
	while(1)
	{
		if(xSemaphoreTake(LEDBufferMutex, portMAX_DELAY))
		{
			matrix_clear();
			matrix_draw_audio_levels(LED_Buffer, colors[colorIndex]);

			xSemaphoreGive(LEDBufferMutex);
		}
		vTaskDelay(pdMS_TO_TICKS(10));
	}
}

//Button Interrupt to change colors
QueueHandle_t interputQueue;

static uint32_t lastInterruptTime = 0;
static void IRAM_ATTR gpio_interrupt_handler(void *args)
{
	int pinNumber = (int)args;
	uint32_t currentTime = xTaskGetTickCountFromISR();

	if(currentTime - lastInterruptTime > pdMS_TO_TICKS(200))
	{
		xQueueSendFromISR(interputQueue, &pinNumber, NULL);
		lastInterruptTime = currentTime;
	}
}

void setInterruptGPIOs(void)
{
	esp_rom_gpio_pad_select_gpio(BUTTON_PIN);
	gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
	gpio_pulldown_en(BUTTON_PIN);
	gpio_pullup_dis(BUTTON_PIN);
	gpio_set_intr_type(BUTTON_PIN, GPIO_INTR_POSEDGE);

	gpio_install_isr_service(0);
	gpio_isr_handler_add(BUTTON_PIN, gpio_interrupt_handler, (void*)BUTTON_PIN);
}

void vColorChange(void* params)
{
	int pinNumber;
	while(1)
	{
		if(xQueueReceive(interputQueue, &pinNumber, portMAX_DELAY))
		{
			vTaskDelay(pdMS_TO_TICKS(50));
			if(gpio_get_level(BUTTON_PIN))
			{
				colorIndex = (colorIndex + 1) % COLOR_COUNT;			
			}
		}
	}
}
