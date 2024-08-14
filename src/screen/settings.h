#ifndef _SETTINGS_SCREEN_H
#define _SETTINGS_SCREEN_H

enum screen_type_t {SET_TIME, SET_DURATION};

void settings_screen_update(int* current_display_values, int* current_cursor_position, enum screen_type_t screen_type);
void settings_screen_loop(const char* title, int* current_display_values, enum screen_type_t screen_type);

#endif