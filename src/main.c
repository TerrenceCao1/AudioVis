#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"

void app_main() {
  while (1) {
    printf("Hello, World!\n");  // ESP-IDF uses printf() instead of Serial
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
