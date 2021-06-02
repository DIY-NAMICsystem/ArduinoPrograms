/*--------------------------------------------------------++
||                  Operate Middle Port                   ||
++--------------------------------------------------------*/

// Solenoid Reward will only be from the middle port!

void activate_middle_port() {

     static unsigned long led_on_time = 0;
     static unsigned long led_off_time = 0;

     static unsigned long solenoid_on_time = 0;
     static unsigned long solenoid_off_time = 0;

     static unsigned long iti_start_time = 0;
     // static unsigned long reward_retrieval_time = 0;

     // static unsigned long valid_poke_timer = 0;
     // static unsigned long invalid_poke_timer = 0;

      // solenoid_active_L becomes false only after ITI time expires
      // Valid trial has started: Turn on left LED

     if (reward_window) {

       // 1. REWARD CUE ON / SOLENOID ON
         if ((reward_cue_window == false) && (led_state_M == LOW) && (start_iti_window == false)){

           // Reward Cue ON
           led_state_M = HIGH;
           digitalWrite(port_led_M, led_state_M);

           // Activate Solenoid
           sol_state_M = HIGH;
           digitalWrite(port_solenoid_M, sol_state_M);

           led_on_time = millis();
           solenoid_on_time = millis();
           // Serial.print(F("Valid led On:"));

           // Reward Cue ON
           Serial.print(F("82171:")); // Timestamp for FC Valid Light On
           Serial.println(led_on_time);

           Serial.print(F("82271:"));     // MIDDLE SOLENOID ON Timestamp for FC Valid Solenoid On
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

          Serial.print(F("82270:"));   // MIDDLE SOLENOID Timestamp for Valid Solenoid Off
          Serial.println(solenoid_off_time);
        }

        // 3. REWARD CUE OFF
        if ((reward_cue_window) && (millis() - led_on_time > reward_cue_duration)) {

          reward_cue_window = false;

          led_state_M = LOW;
          digitalWrite(port_led_M, led_state_M);

          led_off_time = millis();
          // Serial.print(F("Invalid led Off:"));


          // LED_M_off
          Serial.print(F("82170:"));    // FC valid LED off 
          Serial.println(led_off_time);

          start_iti_window = true;
          iti_start_time = millis();

          
          // POKEs during the REWARD Window (pokes between when the reward has been dispensed ("click heard") and reward cue turns off)  
          Serial.print("72549::");   // 725xx
          Serial.println(left_port_counter);
          Serial.print("82549::");    // 825xx
          Serial.println(mid_port_counter);
          Serial.print("92549::");  // 925xx
          Serial.println(right_port_counter);

          // RESET counter for poke counts during iti window
          left_port_counter = 0;  // reset any port counters before TRIAL WINDOW starts (so that any invalid pokes get resetted during iti window)
          mid_port_counter = 0;   //  (could also be a measure of incorrect pokes during a certain TIMEFRAME)
          right_port_counter = 0;

        }

      // START ITI
       if (start_iti_window) {

          // Initiate Next trial after ITI expires
          if ((millis() - iti_start_time) >= iti_interval[random_idx]) {

            // # of poke counts during iti window
            Serial.print("72519::");   // 75xx
            Serial.println(left_port_counter);
            Serial.print("82519::");    // 85xx
            Serial.println(mid_port_counter);
            Serial.print("92519::");  // 95xx
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
