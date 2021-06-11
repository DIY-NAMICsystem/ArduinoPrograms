/*--------------------------------------------------------++
||                     Begin New Trial                    ||
++--------------------------------------------------------*/


/* 
 *  Function: 
 *  Starts a new trial + middle port light blinking at the beginning of each trial (initiation window) 
 *  Can be used to add a delay between trial initiation and trial window (i.e. response cue presentation) 
 *  --> this function is not used in the original DIY-NAMIC delay discounting paradigm 
 *  
 */

 
void begin_new_trial() {  // controls initiation window functionality + runs at the beginning of each new trial 

  static unsigned long initiation_window_start_time = 0;
  static unsigned long initiation_window_end_time = 0;

  static unsigned long iti_window_start_time = 0;
  static unsigned long iti_window_end_time = 0;

  static unsigned long previous_m_LED_millis=0;

  // Initiate New Trial is toggled on AFTER iti duration expires (from L/M/R port operate.h) OR when the program first starts 

  // Initiate New Trial (Parent IF)
  if (initiate_new_trial){

    // Initiation Window hasn't started yet 
    if ((initiate_trial_delay == false) && (initiation_window == false) && (valid_response_window == false)){

       // initiate_trial_delay boolean added as a condition so that this loop doesn't get evaluated
       //+.0

       // start Initiation Window
       initiation_window = true;

       // * * DON'T USE for loops for toggling components - always use STATES!! * *
       // for (byte i = 8; i <=10; i++) { digitalWrite(i, HIGH);}

       // FOR DEBUGGING PURPOSES: Turn ON All three LEDs 
       // led_state_L = HIGH;  digitalWrite(port_led_L, led_state_L);
       // led_state_M = HIGH;  digitalWrite(port_led_M, led_state_M);
       // led_state_R = HIGH;  digitalWrite(port_led_R, led_state_R);

       initiation_window_start_time = millis();
       Serial.print(F("5521:"));  // initiation window start event code (does NOT necessarily mean the trial will be completed/initiated!) 
       Serial.println(initiation_window_start_time);

       }

     // INITIATION WINDOW --> BLINKING WINDOW!
     // As long as initiation window (state) is valid, BLINK the middle port!
     if (initiation_window){

         unsigned long current_m_LED_millis = millis();

         if ((unsigned long)(current_m_LED_millis - previous_m_LED_millis) >= interval) {
          
           // Change wait interval, based on current LED state
           if (led_state_M) { // if LED is ON, next interval would be OFF Timer

             interval = m_LED_offTime;
             }

           else {   // if LED is OFF, next interval would be ON Timer

             interval = m_LED_onTime;
             }

           // Toggle the LED state --> ***
           led_state_M = !(led_state_M);

           // Save the current time to compare "later"
           previous_m_LED_millis = current_m_LED_millis;

         digitalWrite(port_led_M, led_state_M);
         }

       // @ 1st loop, middle LED will blink ON! since initial state starts off as FALSE,
       // and the led_state_M is toggled to TRUE! (see line (***))

     }


    // Poke in Middle Port(IR.h) initiates Valid Trial:

    // If mouse pokes in MIDDLE port and initiates trial, --> LED turns off!! (all three should turn off!)
    // Also when trial_delay window didn't start --> (delay window is 0 ms in the original DIY-NAMIC delay discounting paradigm)  
    // (MOUSE CAN POKE REGARDLESS OF BLINK CYCLE - either ON or OFF cycle!) --> goverened by the STATE!

    // (Valid response window toggles TRUE if poke in middle port (see IR.h))
    
    if ((initiate_trial_delay == false) && (valid_response_window)) {

       // * * DON'T USE for loops for toggling components - always use STATES!! * *
       // for (byte i = 8; i <=10; i++) { digitalWrite(i, LOW);}

       // Turn OFF All three LEDs
       led_state_L = LOW;  digitalWrite(port_led_L, led_state_L);
       led_state_M = LOW;  digitalWrite(port_led_M, led_state_M);
       led_state_R = LOW;  digitalWrite(port_led_R, led_state_R);

       initiation_window_end_time = millis();
       Serial.print(F("5520:"));  // event code denoting that a trial has been initiated 
       Serial.println(initiation_window_end_time);

       // Initiate trial_delay Window (1 ms in the original DIY-NAMIC delay discounting paradigm) 
       initiate_trial_delay = true;

       }

    // this code allows the experimenter to introduce a delay between the initiation and response windows 
    // 1 ms in the original DIY-NAMIC delay discounting paradigm --> change trial_delay_duration in globals_time.h to adjust delay length
    if (initiate_trial_delay){

      // (TRIAL DELAY PERIOD EXPIRES) (TRIAL DELAY WINDOW ENDS) 
      // (trial_delay WINDOW will be 1 ms (practically 0ms) in the original DIY-NAMIC delay discounting paradigm)
       if ((millis() - initiation_window_end_time) >= trial_delay_duration) {

         initiate_trial_delay = false;  // toggle boolean

         initiate_new_trial = false;  // toggle boolean to false HERE since we DON'T want to enter 'Parent IF' state next time
                                      // instead of within above

         // # of poke counts during delay window (between trial initiation and port activation)--> uncomment if delay period > 1 ms
         // Serial.print(F("dw_counter_l::"));   // 75xx  (left counter during delay window)
         // Serial.println(left_port_counter);
         // Serial.print(F("dw_counter_m::"));    // 85xx (middle counter during delay window)
         // Serial.println(mid_port_counter);
         // Serial.print(F("dw_counter_r::"));  // 95xx    (right counter during delay window)
         // Serial.println(right_port_counter);

         // RESET poke_counter for use during response window
         left_port_counter = 0;
         mid_port_counter = 0;
         right_port_counter = 0;

         // SELECT A PORT TO ACTIVATE (now that the trial_delay is over)
         get_random_port = true;
         current_port = random_port();

       }
    }
  }
}
