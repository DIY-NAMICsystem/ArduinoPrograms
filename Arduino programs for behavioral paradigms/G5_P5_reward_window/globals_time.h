/*--------------------------------------------------------++
||    Global Variables - Time Related (Duration etc.)     ||
++--------------------------------------------------------*/


//int wait_interval_L[NUM_TIMES] = {12000, 4000, 10000, 9000, 11000};
//int wait_interval_M[NUM_TIMES] = {8000, 8000, 9000, 9000, 11000};
//int wait_interval_R[NUM_TIMES] = {7000, 3000, 3000, 9000, 11000};

#define NUM_TIMES 12
unsigned long iti_interval[NUM_TIMES] = {30000, 32000, 34000, 37000, 40000, 45000, 47000, 50000, 51000, 55000, 57000, 60000};
// unsigned long iti_interval[NUM_TIMES] = {6000, 6000, 5000, 6000, 7000, 6000, 8000, 6000, 6000, 5000, 7000, 9000};

// TEST ITIs
// unsigned long iti_interval[NUM_TIMES] = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 11000, 12000};

// Durations
//const int led_on_duration = 10000;
//const int void_window = 3000;  // time_window when no response will be valid even if poke occurs

const int solenoid_on_duration = 72;  // solenoid on interval: 72 ms  = 10ul
const int led_trial_duration = 5000;
const int delay_duration = 1;     // CHANGE LATER

const int reward_cue_duration = 3000;     // CHANGE LATER

// Blinking Duration
const unsigned int m_LED_onTime = 500;  // change HERE!
const unsigned int m_LED_offTime = 500;  // change HERE!

int interval = m_LED_onTime;
// * * * * * NOT USED * * * * *

// VOID WINDOW VARIABLES
//unsigned long void_window_start_time = 0;
// int poke_off_count_after_reward_L = 0;
// int poke_off_count_after_reward_M = 0;
// int poke_off_count_after_reward_R = 0;
//
// int prev_poke_off_count_L = 0;
// int prev_poke_off_count_M = 0;
// int prev_poke_off_count_R = 0;
