#ifndef _TIMER_H
#define _TIME_H

void start_timer0();
void stop_timer0();
void configure_timer0(); 

void start_timer1();
void stop_timer1();
void configure_timer1(); 

// Timer flags
#define TIMER0_FLAG (TCON&(1<<5))
#define TIMER1_FLAG (TCON&(1<<7))

#endif
