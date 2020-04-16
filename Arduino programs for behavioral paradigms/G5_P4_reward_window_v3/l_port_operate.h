/*--------------------------------------------------------++
||                    Operate Left Port                   ||
++--------------------------------------------------------*/

// Solenoid Reward will only be from the middle port!

void activate_left_led() {

     static unsigned long led_on_time = 0;
     static unsigned long led_off_time = 0;

     // static unsigned long valid_poke_timer = 0;
     // static unsigned long invalid_poke_timer = 0;

      // solenoid_active_L becomes false only after ITI time expires
      // Valid trial has started: Turn on left LED

     if (solenoid_active_M == false) {

       // (PORT LIGHT ON) Turn on Left LED if it is a valid trial
         if ((valid_trial_window) && (led_state_L == LOW)){

           led_state_L = HIGH;
           digitalWrite(port_led_L, led_state_L);

           led_on_time = millis();
           // Serial.print(F("Valid led On:"));

           Serial.print(F("7171:")); // Timestamp for Valid Light On
           Serial.println(led_on_time);

           // DIFFERENT FROM orig_P4
           // RESET PORT COUNTER to count # of incorrect pokes during trial window (when both response port lights come on)

           left_port_counter = 0;
           mid_port_counter = 0;   //  (could also be a measure of incorrect pokes during a certain TIMEFRAME)
           right_port_counter = 0;
           }   // led is on HIGH


         // (VALID POKE - LIGHT OFF) if correct nose poke during valid trial window -> start reward window (type 1 = yes reward)
         if ((valid_trial_window) && (led_state_L == HIGH) && (poke_in_L) && (left_port_counter > 0)) {
           // // // Below conditions NOT needed
           //       --> only needed when I want to investigate timeframes between 'valid_trial_window' and 'reward_window'

           // mid_port_counter = 0; // reset port counter before reward_window starts
           // right_port_counter = 0;

           // EDIT: 9/15/19 / EDIT: 9/16 --> NOT NEEDED!
           // valid_input_L = false;
           // valid_input_R = false;

           valid_trial_window = false;  // valid trial window ends and response window starts

           led_state_L = LOW;
           digitalWrite(port_led_L, led_state_L);

           led_off_time = millis();
           // Serial.print(F("Valid led Off:"));

           Serial.print(F("7170:"));    // Timestamp for Valid Light Off
           Serial.println(led_off_time);

           // Serial.print("valid_poke_timer");
           // Serial.println(valid_poke_timer);

           // CHANGED HERE (2/14/20) --> automatically subtracts one from relevant port to account for poke for reward
           
           // POKEs during the TRIAL Window (during when response ports light on)
           Serial.print("7589::");   // 75xx
           Serial.println(left_port_counter - 1);
           Serial.print("8589::");    // 85xx
           Serial.println(mid_port_counter);
           Serial.print("9589::");  // 95xx
           Serial.println(right_port_counter);


           reward_window = true;
           reward_type = 1;     // reward_type = 1 --> dispense reward
                                // reward_type = 2 --> no reward (start iti)
         }

         // If mouse pokes in Middle or Right Port during valid trial window,
         // then turn off the left LED and and start reward window (type 2 = no reward)
         // * * * * * * * * * *
         // the mid port counter must be greater than 1  // --> NOT NEEDED ANYMORE AFTER COUNTER RESETTING LOGIC
         // (since we don't want the first poke (trial initiation poke) to trigger the below if statement)
         // * * * * * * * * * *


       // NO INVALID POKE NOR OMISSION TRIAL!!!

       }
}

void activate_left_sol () {

    // SOLENOID ON time will be used to time REWARD_CUE (since they happen concurrently)
    static unsigned long solenoid_on_time = 0;
    static unsigned long solenoid_off_time = 0;

    static unsigned long iti_start_time = 0;
    static unsigned long reward_cue_off_time = 0;

    // solenoid only operates once led is turned off (have to keep solenoid component OFF normally)
    if (led_state_L == LOW) {

        // (SOL_ON) reward_type = 1;  --> dispense reward (need to go into this loop only once! (bc of timer))
        // REWARD_CUE_ON
        if ((reward_window) && (reward_type == 1)) {
            reward_window = false;
            reward_type = 0; // toggle back to default value

            solenoid_active_M = true;  // to prevent from going into the led loop
            sol_state_M = HIGH;
            digitalWrite(port_solenoid_M, sol_state_M);

            //* solenoid on time = reward cue start time! *//
            solenoid_on_time = millis();

            Serial.print(F("8271:"));     // MIDDLE SOLENOID Timestamp for Valid Solenoid On
            Serial.println(solenoid_on_time);

            // REWARD WINDOW COUNTS (diff from P4)
            // RESET LEFT PORT COUNTER! (for one previous valid count)
            // before REWARD light comes on --> later will be generalizable when delay window introduced
            left_port_counter = 0;
            mid_port_counter = 0;   //  (could also be a measure of incorrect pokes during a certain TIMEFRAME)
            right_port_counter = 0;

            // Reward Cue ON (Reward Cue Window ON)
            reward_cue_window = true;
            led_state_M = HIGH;
            digitalWrite(port_led_M, led_state_M);

          }

          // (SOL_OFF) reward_type = 1; --> After time expires, turn off solenoid
          if ((sol_state_M == HIGH) && (millis() - solenoid_on_time > solenoid_on_duration)) {

             solenoid_active_M = false;   // can now activate the leds
             sol_state_M = LOW;
             digitalWrite(port_solenoid_M, sol_state_M);

             solenoid_off_time = millis();
             // Serial.print(F("valid_solenoid_off:"));

             Serial.print(F("8270:"));   // Timestamp for Valid Solenoid Off
             Serial.println(solenoid_off_time);

           }

           // REWARD CUE OFF (solenoid_on_time = reward_cue_start_time)
           if ((reward_cue_window) && (led_state_M == HIGH) && (millis() - solenoid_on_time > reward_cue_duration) ) {
             reward_cue_window = false;
             led_state_M = LOW;
             digitalWrite(port_led_M, led_state_M);

             reward_cue_off_time = millis();
             // Serial.print(F("Invalid led Off:"));

             Serial.print(F("8170:"));    // Omission Trial END Timestamp (LEFT PORT OMISSION)
             Serial.println(reward_cue_off_time);

             // start ITI here
             start_iti_window = true;
             iti_start_time = millis();

             // POKEs during the REWARD Window
             Serial.print("7549::");   // 75xx
             Serial.println(left_port_counter);
             Serial.print("8549::");    // 85xx
             Serial.println(mid_port_counter);
             Serial.print("9549::");  // 95xx
             Serial.println(right_port_counter);

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


                // RESETTING counters before new trial starts (to count # of pokes made during trial window)
                left_port_counter = 0;  // reset any port counters before TRIAL WINDOW starts (so that any invalid pokes get resetted during iti window)
                mid_port_counter = 0;   //  (could also be a measure of incorrect pokes during a certain TIMEFRAME)
                right_port_counter = 0;

                // RESET current_port so that leds and solenoids don't get activated again
                current_port = 0;  // RESET NEEDED!!

                start_iti_window = false;
                initiate_new_trial = true;

              }
        }
    }
}
