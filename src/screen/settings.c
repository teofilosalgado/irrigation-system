#include "screen/settings.h"

#include "lib/global.h"
#include "lib/lcd.h"
#include "lib/delay.h"

void settings_screen_update(int* current_display_values, int* current_cursor_position, enum screen_type_t screen_type) {
    // Refresh display with current values
    if (screen_type == SET_TIME) {
        lcd_disable_cursor();
        lcd_move_cursor(1, 4);
        lcd_write_digit(current_display_values[0]);
        lcd_write_digit(current_display_values[1]);
        lcd_write_character(':');
        lcd_write_digit(current_display_values[2]);
        lcd_write_digit(current_display_values[3]);
        lcd_write_character(':');
        lcd_write_digit(0);
        lcd_write_digit(0);

        // Refresh cursor position
        lcd_move_cursor(1, 4 + (*current_cursor_position));
        lcd_enable_cursor();
    } else {
        lcd_disable_cursor();
        lcd_move_cursor(1, 6);
        lcd_write_digit(current_display_values[0]);
        lcd_write_digit(current_display_values[1]);
        lcd_write_digit(current_display_values[2]);
        lcd_write_digit(current_display_values[3]);

        // Refresh cursor position
        lcd_move_cursor(1, 6 + (*current_cursor_position));
        lcd_enable_cursor();
    }
}

void settings_screen_loop(const char* title, int* current_display_values, enum screen_type_t screen_type) {
    // Current display value being edited
    int current_display_value_index = 0;

    // Display cursor position on screen
    int current_cursor_position = 0;

    // Max display cursor position according to screen type
    int max_current_cursor_position = screen_type == SET_DURATION ? 2 : 3;

    lcd_move_cursor(0, 0);
    lcd_write_string(title);
    settings_screen_update(current_display_values, &current_cursor_position, screen_type);

    while(1) {
        if(!BUTTON_RIGHT_BIT && current_cursor_position <= max_current_cursor_position) {
            // Skip colon (:) if screen type is not duration
            if(current_cursor_position == 1 && screen_type == SET_TIME) {
                current_cursor_position += 2;
            } else {
                current_cursor_position++;
            }
            current_display_value_index++;
            settings_screen_update(current_display_values, &current_cursor_position, screen_type);
        }
        else if(!BUTTON_LEFT_BIT && current_cursor_position > 0) {
            // Skip colon (:) if screen type is not duration
            if(current_cursor_position == 3 && screen_type == SET_TIME) {
                current_cursor_position -= 2;
            } else {
                current_cursor_position--;
            }
            current_display_value_index--;
            settings_screen_update(current_display_values, &current_cursor_position, screen_type);
        }

        if(!BUTTON_SET_BIT) {
            current_display_values[current_display_value_index]++;

            if(current_display_values[3] > 9) {
                current_display_values[3] = 0;
            }
            if(screen_type == SET_TIME) {
                if(current_display_values[2] > 5) {
                    current_display_values[2] = 0;
                }            
                else if(current_display_values[0] >= 2 && current_display_values[1] > 3) {
                    current_display_values[1] = 0;
                }
                else if(current_display_values[0] < 2 && current_display_values[1] > 9) {
                    current_display_values[1] = 0;
                }
                else if(current_display_values[0] > 2) {
                    current_display_values[0] = 0;
                }
            } else {
                if(current_display_values[2] > 9) {
                    current_display_values[2] = 0;
                }
                else if(current_display_values[1] > 9) {
                    current_display_values[1] = 0;
                }
                else if(current_display_values[0] > 9) {
                    current_display_values[0] = 0;
                }
            }

            settings_screen_update(current_display_values, &current_cursor_position, screen_type);
        }

        // Exits currrent screen
        if(!BUTTON_ENTER_BIT) {
            lcd_clear();
            break;
        }
        delay_ms(100);
    }
}
