/*--------------------------------------------------------++
||                  Global Variables                      ||
++--------------------------------------------------------*/

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

// Reward Duration
const long sol_reward_DUR = 72;           // solenoid interval

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
