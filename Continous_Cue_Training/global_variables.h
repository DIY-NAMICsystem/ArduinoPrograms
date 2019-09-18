/*--------------------------------------------------------++
||                  Global Variables                      ||
++--------------------------------------------------------*/

#define NUM_TIMES 2
int wait_interval_L[NUM_TIMES] = {50, 50};
int wait_interval_M[NUM_TIMES] = {50, 50};
int wait_interval_R[NUM_TIMES] = {50, 50};
 
boolean start_ITI_L = false;
boolean start_ITI_M = false;
boolean start_ITI_R = false;

int run_Type_L = 0;
int run_Type_M = 0;
int run_Type_R = 0;

// * Push Button Variables *
byte button_pin = 2;
int prev_button_state = LOW;

int buttonVal = 0; // value read from button
int buttonLast = 0; // buffered value of the button's previous state

boolean hold_button = false; // whether to activate the "hold" function of button

// Button Time Components
unsigned long debounce_time = 10;  // 10 milliseconds
unsigned long button_press_time;  // when the button_ last changed state
const int holdTime = 2000; // ms hold period: how long to wait for press+hold event

long btnDnTime; // time the button was pressed down
long btnUpTime; // time the button was released

// * Solenoid Variables *
// Pin Numbers
byte port_solenoid_L = 4;
byte port_solenoid_M = 5;
byte port_solenoid_R = 6;

// Solenoid States
int sol_state_L = LOW;
int sol_state_M = LOW;
int sol_state_R = LOW; 

// // // // // // // // // // // // // // // // // // // // // // // 
//                        07/10/19 Update 
// Keep 'valid_input' booleans as global!! 
// Setting them up in local scope causes solenoid on if loop to evaluate continuously (idk why...) --> and print out solenoid code continuously
boolean valid_input_L = true; 
boolean valid_input_M = true;
boolean valid_input_R = true;
// // // // // // // // // // // // // // // // // // // // // // // 

// * LED Variables *
// Pin Numbers
byte port_led_L =  8;// the number of the LED pin
byte port_led_M =  9;// the number of the LED pin
byte port_led_R =  10;// the number of the LED pin

// LED States
int led_state_L = LOW;           // ledState used to set the LED
int led_state_M = LOW;
int led_state_R = LOW;

// * IR Variables *
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

// Durations
const unsigned long led_on_duration = 120000;       // (2 min): CHANGE type to unsigned long bc 120000 can't be held in 'int' memory
const int solenoid_on_duration = 72;  // solenoid on interval: 72 ms  = 10ul 

// Boolean States
boolean led_switched_off_L = false;
boolean led_switched_off_M = false;
boolean led_switched_off_R = false;

boolean solenoid_active_L = false;
boolean solenoid_active_M = false;
boolean solenoid_active_R = false;

boolean activate_random_gen = true;
int select_port = 0; 
