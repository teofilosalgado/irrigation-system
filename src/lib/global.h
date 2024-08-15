#ifndef _GLOBAL_H
#define _GLOBAL_H

#include <8051.h>

// LCD pins
#define LCD_RS_BIT P3_0
#define LCD_EN_BIT P3_1
#define LCD_PORT P3

// Button pins
#define BUTTON_LEFT_BIT P0_3
#define BUTTON_RIGHT_BIT P0_0

#define BUTTON_ENTER_BIT P0_1
#define BUTTON_SET_BIT P0_2

// Timer constants, giving a 1KHz update frequency (1ms period)
#define TH_VALUE 0xFC 
#define TL_VALUE 0x66

// Timer flags
#define TIMER0_FLAG (TCON&(1<<5))
#define TIMER1_FLAG (TCON&(1<<7))

#endif
