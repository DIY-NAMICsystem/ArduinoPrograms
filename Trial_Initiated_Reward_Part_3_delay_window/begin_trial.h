/*--------------------------------------------------------++
||                     Begin New Trial                    ||
++--------------------------------------------------------*/

void begin_new_trial() {

  static unsigned long trial_window_start_time = 0;
  static unsigned long trial_window_end_time = 0;

  static unsigned long iti_window_start_time = 0;
  static unsigned long iti_window_end_time = 0;

  // Initiate New Trial is toggled on AFTER iti duration expires (from l/R port operate.h)

  // Initiate New Trial (Parent IF)
  if (initiate_new_trial){

    // Trial Window hasn't started yet - If all lights are turned OFF, TURN ON all three lights
    if ((initiate_delay == false) && (trial_window == false) && (led_state_L == LOW) && (led_state_M == LOW) && (led_state_R == LOW)){

       // initiate_delay boolean added as a condition so that this loop doesn't get evaluated
       //

       // start Trial Window Period
       trial_window = true;

       // * * DON'T USE for loops for toggling components - always use STATES!! * *
       // for (byte i = 8; i <=10; i++) { digitalWrite(i, HIGH);}

       // Turn ON All three LEDs
       led_state_L = HIGH;  digitalWrite(port_led_L, led_state_L);
       led_state_M = HIGH;  digitalWrite(port_led_M, led_state_M);
       led_state_R = HIGH;  digitalWrite(port_led_R, led_state_R);

       trial_window_start_time = millis();
       Serial.print(F("5521:"));
       // Serial.print(F("5521:"));
       Serial.println(trial_window_start_time);

       }

    // Poke in Middle Port(IR.h) initiates Valid Trial:

    // Once Valid Trial initiated (by IR) --> LED turns off!
    if ((initiate_delay == false) && (valid_trial_window) && (led_state_L == HIGH) && (led_state_M == HIGH) && (led_state_R == HIGH)) {

       // Due to DELAY PERIOD, toggle below boolean elsewhere! (when delay period ends)
       // initiate_new_trial = false; // toggle boolean to false since we DON'T want to enter 'Parent IF' state next time

       // * * DON'T USE for loops for toggling components - always use STATES!! * *
       // for (byte i = 8; i <=10; i++) { digitalWrite(i, LOW);}

       // Turn OFF All three LEDs
       led_state_L = LOW;  digitalWrite(port_led_L, led_state_L);
       led_state_M = LOW;  digitalWrite(port_led_M, led_state_M);
       led_state_R = LOW;  digitalWrite(port_led_R, led_state_R);

       trial_window_end_time = millis();
       Serial.print(F("5520:"));
       // Serial.print(F("5520:"));
       Serial.println(trial_window_end_time);

       initiate_delay = true;

       }

    if (initiate_delay){

      // (DELAY PERIOD EXPIRES) (DELAY WINDOW ENDS)
       if ((millis() - trial_window_end_time) >= delay_duration) {

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
