/*--------------------------------------------------------++
||    Global Variables - Time Related (Duration etc.)     ||
++--------------------------------------------------------*/


#define NUM_TIMES 5
//int wait_interval_L[NUM_TIMES] = {12000, 4000, 10000, 9000, 11000};
//int wait_interval_M[NUM_TIMES] = {8000, 8000, 9000, 9000, 11000};
//int wait_interval_R[NUM_TIMES] = {7000, 3000, 3000, 9000, 11000};

// Durations
//const int led_on_duration = 10000;
//const int void_window = 3000;  // time_window when no response will be valid even if poke occurs
const int solenoid_on_duration = 360;  // solenoid on interval: 72 ms  = 10ul (TEST_OPEN x5)


// VOID WINDOW VARIABLES
//unsigned long void_window_start_time = 0;

int poke_off_count_after_reward_L = 0;
int poke_off_count_after_reward_M = 0;
int poke_off_count_after_reward_R = 0;

int prev_poke_off_count_L = 0;
int prev_poke_off_count_M = 0;
int prev_poke_off_count_R = 0;
