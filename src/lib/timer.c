#include "lib/timer.h"

#include "lib/global.h"

void timer0_start() {
    // Set TH0 and TL0
    TH0 = TH_VALUE;
    TL0 = TL_VALUE;

    // Set:
    //   - TR0 = 1 (Timer0 run flag)
    TR0 = 1;
}

void timer0_stop() {
    // Set:
    //   - TF0 = 0 (Timer0 interrupt flag)
    //   - TR0 = 0 (Timer0 run flag)
    TF0 = 0;
    TR0 = 0;
}

void timer0_enable_interrupt() {
    // Set:
    //   - EA  = 1 (Enable all)
    //   - ET0 = 1 (Enable timer0 interrupt)
    EA = 1;
    ET0 = 1;
}

void timer0_set_mode_16bit() {
    timer0_stop();
    // Set:
    //   - T0M1 = 0  (Set timer0 to 16bit mode)
    //   - T0M0 = 1  (Set timer0 to 16bit mode)
    TMOD = (TMOD | (1 << 0)) & ~(1 << 1);
}

void timer1_start() {
    // Set TH1 and TL1
    TH1 = TH_VALUE;
    TL1 = TL_VALUE;

    // Set:
    //   - TR1 = 1 (Timer1 run flag)
    TR1 = 1;
}

void timer1_stop() {
    // Set:
    //   - TF1 = 0 (Timer1 interrupt flag)
    //   - TR1 = 0 (Timer1 run flag)
    TF1 = 0;
    TR1 = 0;
}

void timer1_enable_interrupt() {
    // Set:
    //   - EA  = 1 (Enable all)
    //   - ET1 = 1 (Enable timer1 interrupt)
    EA = 1;
    ET1 = 1;
}

void timer1_set_mode_16bit() {
    timer1_stop();

    // Set:
    //   - T1M1 = 0  (Set timer1 to 16bit mode)
    //   - T1M0 = 1  (Set timer1 to 16bit mode)
    TMOD = (TMOD | (1 << 4)) & ~(1 << 5);
}
