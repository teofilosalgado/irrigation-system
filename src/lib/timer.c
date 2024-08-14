#include "lib/timer.h"

#include "lib/global.h"

void start_timer0() {
    // Set TH0 and TL0
    TH0 = TH_VALUE;
    TL0 = TL_VALUE;

    // Set:
    //   - TR0 = 1 (Timer0 run flag)
    TCON |= (1 << 4);
}

void stop_timer0() {
    // Set:
    //   - TF0 = 0 (Timer0 interrupt flag)
    //   - TR0 = 0 (Timer0 run flag)
    TCON &= 0xEF;
}

void configure_timer0() {
    stop_timer0();
    
    // Set:
    //   - EA  = 1 (Enable all)
    //   - ET0 = 1 (Enable timer0 interrupt)
    IE |= (1 << 7) | (1 << 1);

    // Set:
    //   - T0M1 = 0  (Set timer0 to 16bit mode)
    //   - T0M0 = 1  (Set timer0 to 16bit mode)
    TMOD = (TMOD | (1 << 1)) & ~(1 << 0);
}

