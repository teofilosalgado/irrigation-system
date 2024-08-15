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
    TCON &= 0xCF;
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
    TMOD = (TMOD | (1 << 0)) & ~(1 << 1);
}

void start_timer1() {
    // Set TH1 and TL1
    TH0 = TH_VALUE;
    TL0 = TL_VALUE;

    // Set:
    //   - TR1 = 1 (Timer1 run flag)
    TCON |= (1 << 6);
}

void stop_timer1() {
    // Set:
    //   - TF1 = 0 (Timer1 interrupt flag)
    //   - TR1 = 0 (Timer1 run flag)
    TCON &= 0x3F;
}

void configure_timer1() {
    stop_timer1();

    // Set:
    //   - EA  = 1 (Enable all)
    //   - ET1 = 1 (Enable timer0 interrupt)
    IE |= (1 << 7) | (1 << 3);

    // Set:
    //   - T1M1 = 0  (Set timer0 to 16bit mode)
    //   - T1M0 = 1  (Set timer0 to 16bit mode)
    TMOD = (TMOD | (1 << 4)) & ~(1 << 5);
}
