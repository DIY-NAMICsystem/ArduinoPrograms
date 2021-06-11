/*--------------------------------------------------------++
||    Global Variables - Time Related (Duration etc.)     ||
++--------------------------------------------------------*/


//int wait_interval_L[NUM_TIMES] = {12000, 4000, 10000, 9000, 11000};
//int wait_interval_M[NUM_TIMES] = {8000, 8000, 9000, 9000, 11000};
//int wait_interval_R[NUM_TIMES] = {7000, 3000, 3000, 9000, 11000};

#define NUM_TIMES 12
unsigned long iti_interval[NUM_TIMES] = {30000, 32000, 34000, 37000, 40000, 45000, 47000, 50000, 51000, 55000, 57000, 60000};   // determines the length of the variable intertrial interval 

// TEST ITIs
//unsigned long iti_interval[NUM_TIMES] = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 11000, 12000};
//unsigned long iti_interval[NUM_TIMES] = {6000, 5000, 5000, 6000, 6000, 6000, 5000, 6000, 6000, 6000, 6000, 6000};

// Durations
//const int led_on_duration = 10000;
//const int void_window = 3000;  // time_window when no response will be valid even if poke occurs

const int solenoid_on_duration = 115;    // solenoid on interval: 115 ms  = 10ul
const int led_trial_duration = 10000;    // omission after 10 seconds --> change to adjust how long the animals have to respond! 
const int trial_delay_duration = 1;      // can be used to introduce a delay before trial window (not needed for the traditional DD paradigm) 
const int reward_delay_duration = 12000;  // 12 sec delay before large reward is dispensed (CHANGE HERE AS DELAY INCREASES)

const int reward_cue_duration = 3000;    // change here to display the reward cue for a different duration

// Blinking Duration
const unsigned int m_LED_onTime = 500;   // change HERE if needed! 
const unsigned int m_LED_offTime = 500;  // change HERE if needed! 

int interval = m_LED_onTime;
int i = 1;   //controls how many drops of reward will be dispensed (4 - i drops of reward will be given) 




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
