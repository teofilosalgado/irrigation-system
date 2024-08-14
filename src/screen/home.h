#ifndef _HOME_SCREEN_H
#define _HOME_SCREEN_H

enum status_t {INACTIVE, ACTIVE};

void home_screen_update(int* current_time, enum status_t* status);
void home_screen_setup(int* trigger_time);

#endif
