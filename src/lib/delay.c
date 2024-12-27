#include "lib/delay.h"

#include "lib/global.h"
#include "lib/timer.h"

void delay_ms(unsigned int duration) {
    timer1_set_mode_16bit();

    unsigned int i = 0;
    for(i = 0; i < duration; i++) {
        timer1_start();

        while(!TIMER1_FLAG);

        timer1_stop();
    }
}
