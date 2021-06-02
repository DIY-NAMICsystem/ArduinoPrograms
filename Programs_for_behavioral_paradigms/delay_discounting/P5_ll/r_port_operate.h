/*--------------------------------------------------------++
||   Operate Right Port in FC trials (Small Reward Port)  ||
++--------------------------------------------------------*/

/* 
 *  Function: 
 *  Operate the right LED during trial window --> FORCED CHOICE TRIAL ON THE RIGHT PORT
 *  Dispense reward from middle port after correct response 
 *  Solenoid Reward will only be from the middle port!
 *  
*/


void activate_right_led() {   // turn on right LED during valid response window + turn off the LEDs after correct response 

     static unsigned long led_on_time = 0;
     static unsigned long led_off_time = 0;

     // static unsigned long valid_poke_timer = 0;
     // static unsigned long invalid_poke_timer = 0;

     // solenoid_active_M becomes false only after ITI time expires
     // Valid trial has started: Turn on right LED
     if (solenoid_active_M == false) {

       // (PORT LIGHT ON) Turn on Right LED if it is a valid trial
         if ((valid_response_window) && (led_state_R == LOW)){

           led_state_R = HIGH;
           digitalWrite(port_led_R, led_state_R);

           led_on_time = millis();
           // Serial.print(F("Valid led On:"));

           Serial.print(F("92171:"));   // Timestamp for FC Valid Light On
           Serial.println(led_on_time);

           // reset the poke counters when the response window starts to count the pokes during this window 
           left_port_counter = 0;
           mid_port_counter = 0;  
           right_port_counter = 0;

           }   // right LED is on HIGH

         // (VALID POKE - LIGHT OFF) if correct nose poke during valid trial window -> start reward window (type 1 = yes reward)
         // RIGHT LIGHT ON, poke in RIGHT PORT
         if ((valid_response_window) && (led_state_R == HIGH) && (poke_in_R) && (right_port_counter > 0)) {

           valid_response_window = false;  // valid response window ends and reward window starts

           led_state_R = LOW;  // turn off the LED
           digitalWrite(port_led_R, led_state_R);

           led_off_time = millis();
           // Serial.print(F("Valid led Off:"));

           Serial.print(F("92170:"));   // Timestamp for Forced Choice Valid Light Off
           Serial.println(led_off_time);

           // POKEs during the TRIAL Window (during when response ports light on) --> use FC event codes! (allows us to distinguish between trial types) 
           Serial.print("72589::");   // 725xx
           Serial.println(left_port_counter);
           Serial.print("82589::");    // 825xx
           Serial.println(mid_port_counter);
           Serial.print("92589::");  // 925xx
           Serial.println(right_port_counter-1);

           // Serial.print("valid_poke_timer");
           // Serial.println(valid_poke_timer);

           reward_window = true;
           reward_type = 1;     // reward_type = 1 --> dispense reward
                                // reward_type = 2 --> no reward (start iti)
         }

        // (INVALID_POKE - LIGHT OFF)
        // If mouse pokes in Middle or Left Port during valid trial window, then turn off the right LED and and start reward window (type 2 = no reward)
        if ((valid_response_window) && (led_state_R == HIGH) && ((mid_port_counter > 0) || (left_port_counter > 0)) && ((poke_in_M) || (poke_in_L))) {

           valid_response_window = false;  // end the response window 

           led_state_R = LOW;  // turn off the LED
           digitalWrite(port_led_R, led_state_R);

           led_off_time = millis();
           // Serial.print(F("Invalid led Off:"));

           Serial.print(F("92160:"));    // Timestamp for FC Invalid Light Off
           Serial.println(led_off_time);

           // POKEs during the TRIAL Window (during when response ports light on) --> use FC event codes! (allows us to distinguish between trial types) 
           Serial.print("72589::");   // 725xx
           Serial.println(left_port_counter);
           Serial.print("82589::");    // 825xx
           Serial.println(mid_port_counter);
           Serial.print("92589::");  // 925xx
           Serial.println(right_port_counter);

           // RESET PORT COUNTER to count # of pokes during the ITI window  
           left_port_counter = 0;
           mid_port_counter = 0;   
           right_port_counter = 0;

           // Serial.print("invalid_poke_timer");
           // Serial.println(invalid_poke_timer);

           // start reward_window (type=2 (no reward))
           reward_window = true;
           reward_type = 2; // no reward delivery 

          }

          // OMISSION TRIAL 
          // (NO RESPONSE - LIGHT OFF) 
          if ((valid_response_window) && (led_state_R == HIGH) && (millis() - led_on_time > led_trial_duration)) {

            valid_response_window = false;  // end the response window

            led_state_R = LOW;  // turn off LED
            digitalWrite(port_led_R, led_state_R);

            led_off_time = millis();
            // Serial.print(F("Invalid led Off:"));

            Serial.print(F("92540:"));    // FC Omission Trial END Timestamp (RIGHT PORT OMISSION since this was a FC trial on the right port) 
            Serial.println(led_off_time);

            // start reward_window (type=2 (no reward))
            reward_window = true;
            reward_type = 2;  // no reward delivery 

          }


       }
}

void activate_right_sol () {  // controls Reward Window functionality (reward cue presentation + reward delivery) 

    static unsigned long solenoid_on_time = 0;
    static unsigned long solenoid_off_time = 0;

    static unsigned long iti_start_time = 0;
    static unsigned long reward_cue_off_time = 0;

    // solenoid only operates once LED is turned off (have to keep solenoid component OFF normally)
    if (led_state_R == LOW) {

        // (SOL_ON) reward_type = 1;  --> dispense reward (need to go into this loop only once! (bc of timer))
        // REWARD_CUE_ON
        if ((reward_window) && (reward_type == 1)) {
          
            reward_window = false;
            reward_type = 0; // toggle back to default value

            solenoid_active_M = true;  
            sol_state_M = HIGH;
            digitalWrite(port_solenoid_M, sol_state_M);

            solenoid_on_time = millis();
            // Serial.print(F("valid_solenoid:"));

            Serial.print(F("82271:"));    // MIDDLE SOLENOID ON Timestamp for FC Valid Solenoid On
            Serial.println(solenoid_on_time);

            // Reward Cue ON (Reward Cue Window ON)
            reward_cue_window = true;
            led_state_M = HIGH;
            digitalWrite(port_led_M, led_state_M);

            //* solenoid on time = reward cue start time! *//
            Serial.print(F("82171:"));    // Timestamp for FC Valid Light On
            Serial.println(solenoid_on_time);

            // reset poke counters to count the pokes that happen during the reward window 
            left_port_counter = 0;   
            mid_port_counter = 0;
            right_port_counter = 0;
          }

          // (SOL_OFF) reward_type = 1; --> After time expires, turn off solenoid
          if ((sol_state_M == HIGH) && (millis() - solenoid_on_time > solenoid_on_duration)) {

             solenoid_active_M = false;   
             sol_state_M = LOW;
             digitalWrite(port_solenoid_M, sol_state_M);

             solenoid_off_time = millis();
             // Serial.print(F("valid_solenoid_off:"));

             Serial.print(F("82270:"));  // MIDDLE SOLENOID Timestamp for FC Valid Solenoid Off
             Serial.println(solenoid_off_time);

           }

           // REWARD CUE OFF (solenoid_on_time = reward_cue_start_time) --> after reward cue duration expires, turn off the LED 
           if ((reward_cue_window) && (led_state_M == HIGH) && (millis() - solenoid_on_time > reward_cue_duration) ) {
             
             reward_cue_window = false;
             led_state_M = LOW;
             digitalWrite(port_led_M, led_state_M);

             reward_cue_off_time = millis();
             // Serial.print(F("Invalid led Off:"));

             Serial.print(F("82170:"));   // Event Code for Forced Choice Valid LED off
             Serial.println(reward_cue_off_time);

             // start ITI here
             start_iti_window = true;
             iti_start_time = millis();
             count = count + 1;     // count counts the number of VALID FC trials so the first 10 trials are FC

             // POKEs during the REWARD Window
             Serial.print("72549::");   // 725xx
             Serial.println(left_port_counter);
             Serial.print("82549::");    // 825xx
             Serial.println(mid_port_counter);
             Serial.print("92549::");  // 925xx
             Serial.println(right_port_counter);


             // reset any port counters before ITI WINDOW starts (to count the pokes during the ITI window) 
             left_port_counter = 0;  
             mid_port_counter = 0;   
             right_port_counter = 0;


           }

           // (NO REWARD) If reward_type = 2; --> (don't dispense reward but start ITI timer)
           if ((reward_window) && (reward_type == 2)) {
             
             reward_window = false;  
             reward_type = 0;  // reset reward_type

             solenoid_active_M = false;

             start_iti_window = true;  // start the ITI window 
             iti_start_time = millis();

             // NO NEED TO PRINT OUT invalid_solenoid (no reward) OR iti_start_time
             // Serial.print(F("invalid_solenoid: "));
             // Serial.print(F("7270:"));   // Timestamp for Inalid Solenoid Off
             // Serial.println(iti_start_time);

             // reset any port counters before ITI WINDOW starts (to count the pokes during the ITI window) 
             left_port_counter = 0;  
             mid_port_counter = 0;   
             right_port_counter = 0;

           }


           if (start_iti_window) {  // end the ITI window after predetermined length + get the counters and booleans ready for the new trial  

              // Initiate Next trial after ITI expires --> random ITI length chosen from values in globals_time.h  
              if ((millis() - iti_start_time) >= iti_interval[random_idx]) {

                // # of poke counts during the ITI window (forced choice ITI poke event codes) 
                Serial.print("72519::");   // 725xx
                Serial.println(left_port_counter);
                Serial.print("82519::");    // 825xx
                Serial.println(mid_port_counter);
                Serial.print("92519::");  // 925xx
                Serial.println(right_port_counter);

                // get the ITI length for the next trial 
                get_random_iti = true;
                random_idx = random_iti();

                // FOR DEBUGGING PURPOSES: prints out the next iti length 
                // Serial.print("idx: ");
                // Serial.println(random_idx);
                // Serial.println(iti_interval[random_idx]);

                // RESETTING counters before new trial starts (to count # of pokes made during the initiation window)
                left_port_counter = 0;  
                mid_port_counter = 0;   
                right_port_counter = 0;

                // RESET current_port so that leds and solenoids don't get activated again
                current_port = 0; // RESET NEEDED!!

                start_iti_window = false;
                initiate_new_trial = true;   // start the new trial 

              }
        }
    }
}
