#include "screen/home.h"

#include "lib/lcd.h"

__code const char home_screen_title[] = "Status";

__code const char inactive_status[] = "Inactive";
__code const char active_status[] = " Active ";

void home_screen_update(int* current_time, enum status_t* status) {
    lcd_move_cursor(0, 0);
    lcd_write_character('C');
    lcd_move_cursor(0, 2);
    lcd_write_digit(current_time[0]);
    lcd_write_digit(current_time[1]);
    lcd_write_character(':');
    lcd_write_digit(current_time[2]);
    lcd_write_digit(current_time[3]);

    if((*status) == INACTIVE) {
        lcd_move_cursor(1, 8);
        lcd_write_string(inactive_status);
    } else {
        lcd_move_cursor(1, 8);
        lcd_write_string(active_status);
    }
}

void home_screen_setup(int* trigger_time) {
    lcd_disable_cursor();

    lcd_move_cursor(0, 9);
    lcd_write_string(home_screen_title);

    lcd_move_cursor(1, 0);
    lcd_write_character('T');
    lcd_move_cursor(1, 2);
    lcd_write_digit(trigger_time[0]);
    lcd_write_digit(trigger_time[1]);
    lcd_write_character(':');
    lcd_write_digit(trigger_time[2]);
    lcd_write_digit(trigger_time[3]);
}
