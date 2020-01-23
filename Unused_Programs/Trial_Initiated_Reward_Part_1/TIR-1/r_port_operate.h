/*--------------------------------------------------------++
||                    Operate Right Port                  ||
++--------------------------------------------------------*/


void activate_right_led() {

     static unsigned long led_on_time = 0;
     static unsigned long led_off_time = 0;

     // static unsigned long valid_poke_timer = 0;
     // static unsigned long invalid_poke_timer = 0;

      // solenoid_active_R becomes false only after ITI time expires
      // Valid trial has started: Turn on left LED

     if (solenoid_active_R == false) {

       // (PORT LIGHT ON) Turn on Left LED if it is a valid trial
         if ((valid_trial_window) && (led_state_R == LOW)){

           led_state_R = HIGH;
           digitalWrite(port_led_R, led_state_R);

           led_on_time = millis();
           // Serial.print(F("Valid led On:"));

           Serial.print(F("9171:")); // Timestamp for Valid Light On
           Serial.println(led_on_time);
           }   // led is on HIGH

         // (VALID POKE - LIGHT OFF) if correct nose poke during valid trial window -> start reward window (type 1 = yes reward)
         if ((valid_trial_window) && (led_state_R == HIGH) && (poke_in_R) && (valid_input_R)) {
           // // // Below conditions NOT needed
           //       --> only needed when I want to investigate timeframes between 'valid_trial_window' and 'reward_window'

           // mid_port_counter = 0; // reset port counter before reward_window starts
           // right_port_counter = 0;

           // EDIT: 9/15/19
           valid_input_R = false;
           valid_trial_window = false;  // valid trial window ends and response window starts

           led_state_R = LOW;
           digitalWrite(port_led_R, led_state_R);

           led_off_time = millis();
           // Serial.print(F("Valid led Off:"));

           Serial.print(F("9170:"));    // Timestamp for Valid Light Off
           Serial.println(led_off_time);

           // Serial.print("valid_poke_timer");
           // Serial.println(valid_poke_timer);

           reward_window = true;
           reward_type = 1;     // reward_type = 1 --> dispense reward
                                // reward_type = 2 --> no reward (start iti)
         }

         // If mouse pokes in Middle or Left Port during valid trial window,
         // then turn off the right LED and and start reward window (type 2 = no reward)
         // the mid port counter must be greater than 1
         // (since we don't want the first poke (trial initiation poke) to trigger the below if statement)

         // (INVALID_POKE - LIGHT OFF)
        if ((valid_trial_window) && (led_state_R == HIGH) && ((mid_port_counter > 0) || (left_port_counter > 0)) && ((poke_in_M) || (poke_in_L))) {

           // // // Below conditions NOT needed
           //       --> only needed when I want to investigate timeframes between 'valid_trial_window' and 'reward_window'

           // EDIT: Below conditions needed to count the TRUE number of poke counts during pre-trial phase
           // Without below conditions, would have to subtract 1 from (right_port_counter)   ((subtract 1 from left port counter in the case for right LED))

           // mid_port_counter = 0; // reset any port counters before reward_window starts
           // right_port_counter = 0; //  (could also be a measure of incorrect pokes during a certain TIMEFRAME)

           valid_input_R = false; 
           valid_trial_window = false;

           led_state_R = LOW;
           digitalWrite(port_led_R, led_state_R);

           led_off_time = millis();
           // Serial.print(F("Invalid led Off:"));

           Serial.print(F("9160:"));    // Timestamp for Invalid Light Off
           Serial.println(led_off_time);

           // Serial.print("invalid_poke_timer");
           // Serial.println(invalid_poke_timer);

           reward_window = true;
           reward_type = 2;

          }
       }

       // EDIT: 9/15/19 - toggle valid_input (one "real" poke (instead of just nose inside port)) to true for next valid poke
//       if (poke_in_R == false){
//            valid_input_R = true;
//
//          }

}

void activate_right_sol () {

    static unsigned long solenoid_on_time = 0;
    static unsigned long solenoid_off_time = 0;
    static unsigned long iti_start_time = 0;

    // solenoid only operates once led is turned off (have to keep solenoid component OFF normally)
    if (led_state_R == LOW) {

        // (SOL_ON) reward_type = 1;  --> dispense reward (need to go into this loop only once! (bc of timer))
        if ((reward_window) && (reward_type == 1)) {
            reward_window = false;
            reward_type = 0; // toggle back to default value

            solenoid_active_R = true;  // to prevent from going into the led loop
            sol_state_R = HIGH;
            digitalWrite(port_solenoid_R, sol_state_R);

            solenoid_on_time = millis();
            // Serial.print(F("valid_solenoid:"));

            Serial.print(F("9271:"));     // Timestamp for Valid Solenoid On
            Serial.println(solenoid_on_time);
          }

          // (SOL_OFF) reward_type = 1; --> After time expires, turn off solenoid
          if ((sol_state_R == HIGH) && (millis() - solenoid_on_time > solenoid_on_duration)) {

             solenoid_active_R = false;   // can now activate the leds
             sol_state_R = LOW;
             digitalWrite(port_solenoid_R, sol_state_R);

             solenoid_off_time = millis();
             // Serial.print(F("valid_solenoid_off:"));

             Serial.print(F("9270:"));   // Timestamp for Valid Solenoid Off
             Serial.println(solenoid_off_time);

             // RESET ITI_TIMER HERE IF DEPENDENT ON SOLENOID OFF
             start_iti_window = true;
             iti_start_time = millis();

             // RESET counter for poke counts during iti window
             left_port_counter = 0;  // reset any port counters before TRIAL WINDOW starts (so that any invalid pokes get resetted during iti window)
             mid_port_counter = 0;   //  (could also be a measure of incorrect pokes during a certain TIMEFRAME)
             right_port_counter = 0;
            }

           // (NO REWARD) If reward_type = 2; --> (don't dispense reward but start iti timer)
           if ((reward_window) && (reward_type == 2)) {
             reward_window = false;
             reward_type = 0;

             solenoid_active_R = false;

             start_iti_window = true;
             iti_start_time = millis();

             // NO NEED TO PRINT OUT invalid_solenoid (no reward) OR iti_start_time
             // Serial.print(F("invalid_solenoid: "));
             // Serial.print(F("7270:"));   // Timestamp for Inalid Solenoid Off
             // Serial.println(iti_start_time);

             // RESET counter for poke counts during iti window
             left_port_counter = 0;  // reset any port counters before TRIAL WINDOW starts (so that any invalid pokes get resetted during iti window)
             mid_port_counter = 0;   //  (could also be a measure of incorrect pokes during a certain TIMEFRAME)
             right_port_counter = 0;

           }


           if (start_iti_window) {

              // Initiate Next trial after ITI expires
              if ((millis() - iti_start_time) >= iti_interval[random_idx]) {

                // # of poke counts during iti window
                Serial.print("7519::");   // 75xx
                Serial.println(left_port_counter);
                Serial.print("8519::");    // 85xx
                Serial.println(mid_port_counter);
                Serial.print("9519::");  // 95xx
                Serial.println(right_port_counter);

                get_random_iti = true;
                random_idx = random_iti();

                // prints out the next iti (the next iti duration to be used after it loops around)
                // Serial.print("idx: ");
                // Serial.println(random_idx);
                // Serial.println(iti_interval[random_idx]);

                left_port_counter = 0;  // reset any port counters before TRIAL WINDOW starts (so that any invalid pokes get resetted during iti window)
                mid_port_counter = 0;   //  (could also be a measure of incorrect pokes during a certain TIMEFRAME)
                right_port_counter = 0;

                start_iti_window = false;
                initiate_new_trial = true;

              }
        }
    }
}
