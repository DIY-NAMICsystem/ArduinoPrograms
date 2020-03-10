/*--------------------------------------------------------++
||    Global Variables - Time Related (Duration etc.)     ||
++--------------------------------------------------------*/


//int wait_interval_L[NUM_TIMES] = {12000, 4000, 10000, 9000, 11000};
//int wait_interval_M[NUM_TIMES] = {8000, 8000, 9000, 9000, 11000};
//int wait_interval_R[NUM_TIMES] = {7000, 3000, 3000, 9000, 11000};

#define NUM_TIMES 12
unsigned long iti_interval[NUM_TIMES] = {30000, 32000, 34000, 37000, 40000, 45000, 47000, 50000, 51000, 55000, 57000, 60000};

// TEST ITIs
// unsigned long iti_interval[NUM_TIMES] = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 11000, 12000};

// Durations
//const int led_on_duration = 10000;
//const int void_window = 3000;  // time_window when no response will be valid even if poke occurs

const int solenoid_on_duration = 72;  // solenoid on interval: 72 ms  = 10ul

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
