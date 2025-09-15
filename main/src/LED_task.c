#include "LED_task.h"

void selectRow(int row)
{
    //check if the row is between 0 -> 31
    if (!(row >= 0 && row < HEIGHT))
    {
        printf("selected row is not in boundary.");
        while(1);
    }

    //set GPIOs based on the row...
        //for instance: row 5 = 0101, turn gpio's B and D on
    gpio_set_level(A_PIN, row >> 3 && 0b1);
    gpio_set_level(B_PIN, row >> 2 && 0b1);
    gpio_set_level(C_PIN, row >> 1 && 0b1);
    gpio_set_level(D_PIN, row && 0b1);
}
