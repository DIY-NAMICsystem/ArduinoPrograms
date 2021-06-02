/*--------------------------------------------------------++
||     Push_Button (Click for A, Press and Hold for B     ||
++--------------------------------------------------------*/

// Single click toggles solenoids
// Press and Hold toggles LEDs

// From Jeff's Arduino Blog (Click for A, Press and Hold for B) 
// Reference: http://jmsarduino.blogspot.com/2009/05/click-for-press-and-hold-for-b.html

void activate_button() {

  // Read the state of the button
  buttonVal = digitalRead(button_pin);

  // Test for button pressed and store the down time (when button is pressed) 
  if (buttonVal == LOW && buttonLast == HIGH && (millis() - btnUpTime) > long(debounce_time)) {
    btnDnTime = millis();
    }

  // Test for button release and store the up time (when button is released) 
  // Single Click! 
  if (buttonVal == HIGH && buttonLast == LOW && (millis() - btnDnTime) > long(debounce_time)) {
    // boolean needed for press and hold 
    if (hold_button == false) {
      
      // toggles on/off all the solenoids 
      for (byte i = 4; i <=6; i++) { digitalWrite(i, !digitalRead(i));}
      
    }
    
    else {
      hold_button = false;
      btnUpTime = millis();
    }
  }

  // Test for button held down for longer than the hold time
  // Press and Hold 
  if (buttonVal == LOW && (millis() - btnDnTime) > long(holdTime)) {
      
      // toggles on/off all the LEDs
      for (byte i = 8; i <=10; i++) { digitalWrite(i, !digitalRead(i));}
      hold_button = true;
      btnDnTime = millis();
    }

    buttonLast = buttonVal;

 } // end of activate_button function



// Once button pressed and held, will toggle LED on and off continously, 
// since btnDnTime is going to get updated only once when 
// "(millis() - btnDnTime) > long(holdTime)" evaluates to True. 

// --> btnDnTime won't be updated every cycle because it will not go inside the if clause
// unless the time component evaluates to True, which happens every "holdTime" cycle. 



/* Additional Functions Below
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 
1. button_push() function turns on solenoid as long as the button is pressed down!! 
2. and turns off solenoid when button released
3. (it is NOT toggle)
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
void button_push() {
// see if button_is open or closed
  byte button_State = digitalRead (button_Pin);
  // has it changed since last time?
  if (button_State != old_button_State) {
    // debounce
    if (millis () - button_PressTime >= debounceTime) {
       button_PressTime = millis ();  // time when we close the button
       old_button_State =  button_State;  // remember for next time
       if (button_State == LOW) {
          Serial.println ("button_closed.");
          digitalWrite(port_solenoid_L, HIGH);
          digitalWrite(port_solenoid_M, HIGH);
          digitalWrite(port_solenoid_R, HIGH);
          }  // end if button_State is LOW
       else {
          Serial.println ("button_opened.");
          digitalWrite(port_solenoid_L, LOW);
          digitalWrite(port_solenoid_M, LOW);
          digitalWrite(port_solenoid_R, LOW);
          }  // end if button_State is HIGH
       }  // end if debounce time up
    }  // end of state change
} // end of button_push() 
*/ 