#ifndef _TIMER_H
#define _TIME_H

void timer0_start();
void timer0_stop();
void timer0_enable_interrupt(); 
void timer0_set_mode_16bit(); 

void timer1_start();
void timer1_stop();
void timer1_enable_interrupt(); 
void timer1_set_mode_16bit(); 

// Timer flags
#define TIMER0_FLAG (TCON&(1<<5))
#define TIMER1_FLAG (TCON&(1<<7))

#endif
