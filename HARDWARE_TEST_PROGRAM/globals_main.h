/*--------------------------------------------------------++
||                 Global Variables - MAIN                ||
++--------------------------------------------------------*/

// 1. BOOLEAN VARIABLES ARE GLOBAL! 
// 2. TIMER VARIABLES ARE LOCAL!



// // // // // // // // // // // // // // // // // // // // // // // 
//                        07/10/19 Update 
// Keep 'valid_input' booleans as global!! 
// Setting them up in local scope causes solenoid on if loop to evaluate continuously (idk why...) 
// --> and print out solenoid code continuously

boolean valid_input_L = true; 
boolean valid_input_M = true;
boolean valid_input_R = true;

// // // // // // // // // // // // // // // // // // // // // // // 

boolean start_led_ITI_L = false;
boolean start_led_ITI_M = false;
boolean start_led_ITI_R = false;

boolean void_window_start_L = false;
boolean void_window_start_M = false;
boolean void_window_start_R = false;

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

boolean activate_random_gen = true;
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


boolean deliver_reward_L = false; 
boolean deliver_reward_M = false; 
boolean deliver_reward_R = false; 

boolean initiate_new_trial = false;
