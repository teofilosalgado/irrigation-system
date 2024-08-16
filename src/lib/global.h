#ifndef _GLOBAL_H
#define _GLOBAL_H

#include <8051.h>

/*
 * IO
 */
// LCD pins
#define LCD_RS_BIT P2_0
#define LCD_EN_BIT P2_1
#define LCD_PORT P2

// Button pins
#define BUTTON_LEFT_BIT P0_0
#define BUTTON_RIGHT_BIT P0_3

#define BUTTON_ENTER_BIT P0_1
#define BUTTON_SET_BIT P0_2

/*
 * Timers
 */
// Timer counter register values, giving a 1KHz update frequency (1ms period)
#define TH_VALUE 0xFC 
#define TL_VALUE 0x66

// Maximum value for timer auxiliary counter, resulting in a 1Hz update frequency (1s period)
#define TIMER_COUNTER_MAX 1000

// Timer flags
#define TIMER0_FLAG (TCON&(1<<5))
#define TIMER1_FLAG (TCON&(1<<7))

#endif
