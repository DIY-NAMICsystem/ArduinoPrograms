/*--------------------------------------------------------++
||               Global Variables - Push Button           ||
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