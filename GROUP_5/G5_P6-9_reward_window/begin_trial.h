/*--------------------------------------------------------++
||                     Begin New Trial                    ||
++--------------------------------------------------------*/

void begin_new_trial() {

  static unsigned long trial_initiation_window_start_time = 0;
  static unsigned long trial_initiation_window_end_time = 0;

  static unsigned long iti_window_start_time = 0;
  static unsigned long iti_window_end_time = 0;

  static unsigned long previous_m_LED_millis=0;

  // Initiate New Trial is toggled on AFTER iti duration expires (from l/R port operate.h)

  // Initiate New Trial (Parent IF)
  if (initiate_new_trial){

    // Trial Initiation Window hasn't started yet - BLINK!!
    if ((initiate_delay == false) && (trial_initiation_window == false) && (valid_trial_window == false)){

       // initiate_delay boolean added as a condition so that this loop doesn't get evaluated
       //+.0

       // start Trial Initiation Window
       trial_initiation_window = true;

       // * * DON'T USE for loops for toggling components - always use STATES!! * *
       // for (byte i = 8; i <=10; i++) { digitalWrite(i, HIGH);}

       // Turn ON All three LEDs
       // led_state_L = HIGH;  digitalWrite(port_led_L, led_state_L);
       // led_state_M = HIGH;  digitalWrite(port_led_M, led_state_M);
       // led_state_R = HIGH;  digitalWrite(port_led_R, led_state_R);

       trial_initiation_window_start_time = millis();
       Serial.print(F("5521:"));
       Serial.println(trial_initiation_window_start_time);

       }

    // TRIAL WINDOW --> BLINKING WINDOW!
     // As long as trial window (state) is valid, BLINK the middle port!
     if (trial_initiation_window){

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
    // Also when delay window didn't start
    // (MOUSE CAN POKE REGARDLESS OF BLINK CYCLE - either ON or OFF cycle!) --> goverened by the STATE!

    // (Valid trial window toggles TRUE if poke in middle port (see IR.h))
    if ((initiate_delay == false) && (valid_trial_window)) {

       // Due to DELAY PERIOD, toggle below boolean elsewhere! (when delay period ends)
       // initiate_new_trial = false; // toggle boolean to false since we DON'T want to enter 'Parent IF' state next time

       // * * DON'T USE for loops for toggling components - always use STATES!! * *
       // for (byte i = 8; i <=10; i++) { digitalWrite(i, LOW);}

       // Turn OFF All three LEDs
       led_state_L = LOW;  digitalWrite(port_led_L, led_state_L);
       led_state_M = LOW;  digitalWrite(port_led_M, led_state_M);
       led_state_R = LOW;  digitalWrite(port_led_R, led_state_R);

       trial_initiation_window_end_time = millis();
       Serial.print(F("5520:"));
       Serial.println(trial_initiation_window_end_time);

       // Initiate Delay Window
       initiate_delay = true;

       }

    if (initiate_delay){

      // (DELAY PERIOD EXPIRES) (DELAY WINDOW ENDS)
       if ((millis() - trial_initiation_window_end_time) >= delay_duration) {

         initiate_delay = false;  // toggle boolean

         initiate_new_trial = false;  // toggle boolean to false HERE since we DON'T want to enter 'Parent IF' state next time
                                      // instead of within above

         // Serial.println("delay loop");

         // # of poke counts during delay window (between trial initiation and port activation)
         Serial.print(F("7559::"));   // 75xx  (left counter during delay window)
         Serial.println(left_port_counter);
         Serial.print(F("8559::"));    // 85xx (middle counter during delay window)
         Serial.println(mid_port_counter);
         Serial.print(F("9559::"));  // 95xx    (right counter during delay window)
         Serial.println(right_port_counter);

         // RESET poke_counter for activated trial period (activate_left/right_led() function in l/r_port_operate.h)
         left_port_counter = 0;
         mid_port_counter = 0;
         right_port_counter = 0;

         // SELECT PORT TO ACTIVATE (now that the delay is over)
         get_random_port = true;
         current_port = random_port();

         // FOR DEBUGGING PURPOSES: prints out the selected port (1 -> Left / 2 -> Right)
         // Serial.print("current: ");
         // Serial.println(current_port);

       }
    }
  }
}
