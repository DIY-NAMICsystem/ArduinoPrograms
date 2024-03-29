/*--------------------------------------------------------++
||                 Global Variables - MAIN                ||
++--------------------------------------------------------*/

// 1. BOOLEAN VARIABLES ARE GLOBAL!
// 2. TIMER VARIABLES ARE LOCAL!

// * * Booleans for Trial Initiated Reward Paradigm

// boolean to initiate new trial
boolean initiate_new_trial;

// booleans for windows (different states)
boolean initiation_window;
boolean valid_response_window;  // i.e. trial window in the paradigm diagram

boolean reward_window;
boolean reward_cue_window;

boolean start_iti_window;
boolean initiate_trial_delay;  // can be used to initiate a delay before the trial window 
boolean initiate_reward_delay; // used to introduce a delay before the reward is dispensed 
boolean initiate_iti_delay;    // used to ensure large and small reward trials are the same duration  

// tracks whether a small reward should be dispensed 
boolean give_small_reward = false;  

// counters / type ints
int reward_type = 0;


// Port Counters - Necessary in every paradigm without void window (Implemented in IR.h)
// Used to determine IF a particular poke is the FIRST poke or not
// Generally used in situations to trigger an event after SECOND relevant poke

int left_port_counter = 0;
int mid_port_counter = 0;
int right_port_counter = 0;

//count number of trials (to set the first 10 as FC) 
int count = 0; 


// Used to determine whether a forced choice (FC) or free choice trial will be execurted (2/20 trials are forced choice) 
int trial_type[20] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};  // 1 --> left FC, 2 --> right FC, otherwise --> free choice trial 
int trial_type_idx = 0; //used to move through this array 

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

// * * * * * Solenoid Variables * * * * *

// Pin Numbers
byte port_solenoid_L = 4;
byte port_solenoid_M = 5;
byte port_solenoid_R = 6;

// Solenoid States
int sol_state_L = LOW;
int sol_state_M = LOW;
int sol_state_R = LOW;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

// * * * * * LED Variables * * * * *

// Pin Numbers
byte port_led_L =  8;// the number of the LED pin
byte port_led_M =  9;// the number of the LED pin
byte port_led_R =  10;// the number of the LED pin

// LED States
int led_state_L = LOW;           // ledState used to set the LED
int led_state_M = LOW;
int led_state_R = LOW;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

// * * * * * IR Variables * * * * *

// Pin Numbers
byte port_ir_L = 11;
byte port_ir_M = 12;
byte port_ir_R = 13;

// IR States
boolean ir_previous_state_L;
boolean ir_previous_state_M;
boolean ir_previous_state_R;

// boolean to see if IR was broken:
boolean poke_in_L = false;
boolean poke_in_M = false;
boolean poke_in_R = false;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

boolean get_random_iti = true;
int random_idx = 0;
boolean get_random_port = true;
int current_port = 0;
int prev_port = 0;







// * * * * * NOT USED * * * * *

// Boolean States
//boolean led_switched_off_L = false;
//boolean led_switched_off_M = false;
//boolean led_switched_off_R = false;
//
boolean solenoid_active_L = false;
boolean solenoid_active_M = false;
boolean solenoid_active_R = false;

//int run_Type_L;
//int run_Type_M;
//int run_Type_R;
//
//boolean reset_ITI_L;
//boolean reset_ITI_M;
//boolean reset_ITI_R;

// * * * * * NOT USED * * * * *
//
//
//boolean deliver_reward_L = false;
//boolean deliver_reward_M = false;
//boolean deliver_reward_R = false;


// * * * * * NOT USED * * * * *


// // // // // // // // // // // // // // // // // // // // // // //
//                        07/10/19 Update
// Keep 'valid_input' booleans as global!!
// Setting them up in local scope causes solenoid on if loop to evaluate continuously (idk why...)
// --> and print out solenoid code continuously

// boolean valid_input_L = true;
// boolean valid_input_M = true;
// boolean valid_input_R = true;
//
// // // // // // // // // // // // // // // // // // // // // // // //
//
// boolean start_led_ITI_L = false;
// boolean start_led_ITI_M = false;
// boolean start_led_ITI_R = false;
//
// boolean void_window_start_L = false;
// boolean void_window_start_M = false;
// boolean void_window_start_R = false;
