#include "lib/lcd.h"

#include "lib/global.h"
#include "lib/delay.h"

void lcd_write(unsigned char content) {
    // Send upper nibble
    LCD_PORT = (LCD_PORT & 0x0F) | (content & 0xF0);
    LCD_EN_BIT = 1;
    delay_ms(1);
    LCD_EN_BIT = 0;
    delay_ms(2);

    // Send lower nibble
    LCD_PORT = (LCD_PORT & 0x0F) | (content << 4);
    LCD_EN_BIT = 1;
    delay_ms(1);
    LCD_EN_BIT = 0;
    delay_ms(5);
}

void lcd_write_command(unsigned char command) {
    // Set command register
    LCD_RS_BIT = 0;
    lcd_write(command);
}

void lcd_write_character(unsigned char character) {
    // Set data register
    LCD_RS_BIT = 1;
    lcd_write(character);
}

void lcd_write_string(const char *string) {
    // Send each character until the NULL terminator
    int i = 0;
    for(i = 0; string[i] != 0; i++)  
    {
        lcd_write_character(string[i]);
    }
}

void lcd_write_digit(int value) {
    lcd_write_character(value%10 + 48);
}

void lcd_move_cursor(unsigned char row, unsigned char column) {
    if (row == 0) {
        lcd_write_command((column & 0x0F) | 0x80);
    }
    else if (row == 1) {
        lcd_write_command((column & 0x0F) | 0xC0);
    }
}

void lcd_disable_cursor() {
    lcd_write_command(0x0C);
}

void lcd_enable_cursor() {
    lcd_write_command(0x0F);
}

void lcd_clear() {
    lcd_write_command(0x01);
}

void lcd_init() {
    // HD44780 initialization time (>15ms)
    delay_ms(30);

    // 4bit mode
    lcd_write_command(0x02);

    // Initialization of 16X2 LCD in 4bit mode
    lcd_write_command(0x28);

    // Display ON, cursor OFF
    lcd_disable_cursor();

    // Auto increment cursor
    lcd_write_command(0x06);

    // Clear display
    lcd_clear();

    // Cursor at home position
    lcd_write_command(0x80);
}
