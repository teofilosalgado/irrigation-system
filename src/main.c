#include "lib/global.h"
#include "lib/timer.h"
#include "lib/lcd.h"
#include "lib/delay.h"

#include "screen/settings.h"
#include "screen/home.h"

/*
 * View models
 */
// Set current time screen variables
__code const char set_current_time_screen_title[] = "Set current time";
int current_time[] = {0, 0, 0, 0, 0, 0};

// Set trigger time screen variables
__code const char set_trigger_time_screen_title[] = "Set trigger time";
int trigger_time[] = {0, 0, 0, 0, 0, 0};

// Set trigger time screen variables
__code const char set_duration_time_screen_title[] = "Set duration (s)";
int duration[] = {0, 0, 0, 0};

/*
 * Timing related globals
 */
// Duration value (s) as an integer
int active_time_duration = 0;

// Elapsed duration time (s)
int elapsed_active_time = 0;

// Current device status
enum status_t status = INACTIVE;

// Auxiliary counter for timer0, keeping frequency at 1Hz
int timer0_counter = 0;

// Updates LCD display whenever on-screen values change
int should_update_screen = 0;

void set_active_time_duration() {
    active_time_duration = (duration[0] * 1000) +  (duration[1] * 100) +  (duration[2] * 10) +  duration[3];
}

void update_current_time() {
    current_time[5]++;

    // Update seconds
    if(current_time[5] > 9) {
        current_time[5] = 0;
        current_time[4]++;
    }
    if(current_time[4] > 5) {
        current_time[4] = 0;
        current_time[3]++;
    }

    // Update minutes
    if(current_time[3] > 9) {
        current_time[3] = 0;
        current_time[2]++;
    }
    if(current_time[2] > 5) {
        current_time[2] = 0;
        current_time[1]++;
    }

    // Update hours
    if(current_time[0] < 2 && current_time[1] > 9) {
        current_time[1] = 0;
        current_time[0]++;
    }
    if(current_time[0] >= 2 && current_time[1] > 3) {
        current_time[1] = 0;
        current_time[0] = 0;
    }
}

void update_status() {
    if(status == INACTIVE
            && (current_time[0] == trigger_time[0])
            && (current_time[1] == trigger_time[1])
            && (current_time[2] == trigger_time[2])
            && (current_time[3] == trigger_time[3])
            && (current_time[4] == trigger_time[4])
            && (current_time[5] == trigger_time[5])) {
        status = ACTIVE;
    }

    if(status == ACTIVE) {
        elapsed_active_time++;

        if (elapsed_active_time >= active_time_duration) {
            status = INACTIVE;
            elapsed_active_time = 0;
        }
    }
}

void timer0_interrupt_handler() __interrupt(1) {
    stop_timer0();
    should_update_screen = 0;

    if(timer0_counter >= TIMER_COUNTER_MAX) {
        timer0_counter = 0;
        should_update_screen = 1;

        update_current_time();
        update_status();
    }
    timer0_counter++;

    start_timer0();
}

void main() {
    delay_ms(1000);
    lcd_init();
 
    // Initial setup
    settings_screen_loop(set_current_time_screen_title, current_time, SET_TIME);
    settings_screen_loop(set_trigger_time_screen_title, trigger_time, SET_TIME);
    settings_screen_loop(set_duration_time_screen_title, duration, SET_DURATION);

    // Configure timer0 interrupt
    set_active_time_duration();
    configure_timer0();
    start_timer0();

    home_screen_setup(trigger_time);
    while(1) {
        delay_ms(100);

        // Set trigger and duration values again
        if(!BUTTON_ENTER_BIT) {
            settings_screen_loop(set_trigger_time_screen_title, trigger_time, SET_TIME);
            settings_screen_loop(set_duration_time_screen_title, duration, SET_DURATION);
        }

        // Check if any on-scren value has been updated
        if(should_update_screen) {
            home_screen_update(current_time, &status);
        }
    }
}
