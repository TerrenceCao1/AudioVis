#include "driver/uart.h"

void app_main() {
    while (1) {
        printf("Hello, World!\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
