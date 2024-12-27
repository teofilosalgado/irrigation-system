#include "lib/global.h"
#include "lib/timer.h"
#include "lib/lcd.h"
#include "lib/delay.h"
#include "lib/util.h"

#include "screen/settings.h"
#include "screen/home.h"

/*
 * View models
 */
// Set current time screen variables
__code const char set_current_time_screen_title[] = "Set current time";
unsigned int current_time[] = {0, 0, 0, 0, 0, 0};

// Set trigger time screen variables
__code const char set_trigger_time_screen_title[] = "Set trigger time";
unsigned int trigger_time[] = {0, 0, 0, 0, 0, 0};

// Set trigger time screen variables
__code const char set_duration_time_screen_title[] = "Set duration (s)";
unsigned int duration[] = {0, 0, 0, 0};

/*
 * Timing related globals
 */
// Duration value (s) as an integer
unsigned int active_time_duration = 0;

// Elapsed duration time (s)
unsigned int elapsed_active_time = 0;

// Prevents triggering twice in the same day
unsigned int was_already_triggered_today = 0;

// Current device status
enum status_t status = INACTIVE;

// Auxiliary counter for timer0, keeping frequency at 1Hz
unsigned int timer0_counter = 0;

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

        // Reset variable after every 24h
        was_already_triggered_today = 0;
    }
}

void update_status() {
    // If duration is 0, never activate
    if(sum_array(duration, 5) == 0) {
        return;
    }

    if(status == INACTIVE 
        && is_array_equal(current_time, trigger_time, 4)
        && !was_already_triggered_today) {
        status = ACTIVE;
        OUTPUT_PIN = 1;
        was_already_triggered_today = 1;
    }
    if(status == ACTIVE) {
        elapsed_active_time++;

        if (elapsed_active_time >= active_time_duration) {
            status = INACTIVE;
            OUTPUT_PIN = 0;
            elapsed_active_time = 0;
        }
    }
}

void timer0_interrupt_handler() __interrupt(1) {
    if(timer0_counter >= TIMER_COUNTER_MAX) {
        timer0_counter = 0;

        update_current_time();
        update_status();

        home_screen_update(current_time, &status);
        
        // Toggle the heartbeat led
        HEARTBEAT_PIN ^= 0x01;
    }
    timer0_counter++;
}

void main() {
    // Prevent undesired output state
    OUTPUT_PIN = 0;

    // Initialize LCD display
    delay_ms(1000);
    lcd_init();
 
    // Initial setup
    settings_screen_loop(set_current_time_screen_title, current_time, SET_TIME);
    settings_screen_loop(set_trigger_time_screen_title, trigger_time, SET_TIME);
    settings_screen_loop(set_duration_time_screen_title, duration, SET_DURATION);

    // Calculate total active time
    set_active_time_duration();

    // Configure timer0 interrupt
    timer0_set_mode_16bit();
    timer0_enable_interrupt();
    timer0_start();

    // Main screen loop
    home_screen_setup(trigger_time);
    while(1) {
        // Set trigger and duration values again
        if(!BUTTON_ENTER_BIT) {            
            settings_screen_loop(set_trigger_time_screen_title, trigger_time, SET_TIME);
            settings_screen_loop(set_duration_time_screen_title, duration, SET_DURATION);
        }

        delay_ms(250);
    }
}
