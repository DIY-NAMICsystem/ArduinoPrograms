/*--------------------------------------------------------++
||                    Operate Left Port                   ||
++--------------------------------------------------------*/

// Solenoid Reward will only be from the middle port!

void activate_middle_port() {

     static unsigned long led_on_time = 0;
     static unsigned long led_off_time = 0;

     static unsigned long solenoid_on_time = 0;
     static unsigned long solenoid_off_time = 0;

     static unsigned long iti_start_time = 0;

     if (reward_window) {

       // 1. REWARD CUE ON / SOLENOID ON
         if ((reward_cue_window == false) && (led_state_L == LOW) && (led_state_R == LOW) && (start_iti_window == false)){

           // Reward Cue ON
           led_state_M = HIGH;
           digitalWrite(port_led_M, led_state_M);

           // Activate Solenoid
           sol_state_M = HIGH;
           digitalWrite(port_solenoid_M, sol_state_M);

           led_on_time = millis();
           solenoid_on_time = millis();
           // Serial.print(F("Valid led On:"));

           Serial.print(F("81171:"));  // Timestamp for Free Choice Valid Light On
           Serial.println(led_on_time);

           Serial.print(F("81271:"));     // MIDDLE SOLENOID ON Timestamp for Free Choice Valid Solenoid On
           Serial.println(solenoid_on_time);

           reward_cue_window = true;
           // solenoid_duration_window = true;

           }

        // 2. SOLENOID OFF
        if ((sol_state_M == HIGH) && (millis() - solenoid_on_time > solenoid_on_duration)) {

          sol_state_M = LOW;
          digitalWrite(port_solenoid_M, sol_state_M);

          solenoid_off_time = millis();
          // Serial.print(F("valid_solenoid_off:"));

          Serial.print(F("81270:"));   // MIDDLE SOLENOID Timestamp for Valid Solenoid Off
          Serial.println(solenoid_off_time);
        }

        // 3. REWARD CUE OFF
        if ((reward_cue_window) && (millis() - led_on_time > reward_cue_duration)) {

          reward_cue_window = false;

          led_state_M = LOW;
          digitalWrite(port_led_M, led_state_M);

          led_off_time = millis();
          // Serial.print(F("Invalid led Off:"));

          Serial.print(F("81170:"));    // free choice valid led off 
          Serial.println(led_off_time);

          start_iti_window = true;
          iti_start_time = millis();

          // # of poke counts during reward window (between when reward is given and reward cue turns off) 
          Serial.print("71549::");   // 715xx
          Serial.println(left_port_counter);
          Serial.print("81549::");    // 815xx
          Serial.println(mid_port_counter);
          Serial.print("91549::");  // 915xx
          Serial.println(right_port_counter);

          // RESET counter for poke counts during iti window
          left_port_counter = 0;  
          mid_port_counter = 0;   
          right_port_counter = 0;

        }

      // START ITI
       if (start_iti_window) {

          // Initiate Next trial after ITI expires
          if ((millis() - iti_start_time) >= iti_interval[random_idx]) {

            // # of poke counts during iti window
            Serial.print("71519::");   // 715xx
            Serial.println(left_port_counter);
            Serial.print("81519::");    // 815xx
            Serial.println(mid_port_counter);
            Serial.print("91519::");  // 915xx
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

            reward_window = false;


          }
        }


     }
}
