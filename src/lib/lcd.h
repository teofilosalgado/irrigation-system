#ifndef _LCD_H
#define _LCD_H

void lcd_write(unsigned char content);
void lcd_write_character(unsigned char character);
void lcd_write_command(unsigned char command);
void lcd_write_string(const char *string);
void lcd_write_digit(int value);
void lcd_disable_cursor();
void lcd_enable_cursor();
void lcd_move_cursor(unsigned char row, unsigned char column);
void lcd_clear();
void lcd_init();

#endif
