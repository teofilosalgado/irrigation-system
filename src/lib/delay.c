#include "lib/delay.h"

#include "lib/global.h"
#include "lib/timer.h"

void delay_ms(int duration) {
    configure_timer1();

    int i = 0;
    for(i = 0; i < duration; i++) {
        start_timer1();

        while(!TIMER1_FLAG);

        stop_timer0();
    }
}
