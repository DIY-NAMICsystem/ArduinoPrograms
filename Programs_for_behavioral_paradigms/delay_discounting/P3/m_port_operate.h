/*--------------------------------------------------------++
||                  Operate Middle Port                   ||
++--------------------------------------------------------*/

/* 
 *  Function: 
 *  Operate the left and right LEDs during valid response window 
 *  Dispense reward from middle port after correct response 
 *  Solenoid Reward will only be from the middle port!
 *  
*/ 

void activate_middle_led() { // turn on left and right LEDs during valid response window + turn off the LEDs after correct response 

     static unsigned long led_on_time = 0;
     static unsigned long led_off_time = 0;

     // static unsigned long valid_poke_timer = 0;
     // static unsigned long invalid_poke_timer = 0;

     // solenoid_active_M becomes false only after ITI time expires
     // Valid trial has started: Turn on Left and Right LED
     if (solenoid_active_M == false) {

       // (PORT LIGHT ON) Turn on both LEDs if it is a valid trial
         if ((valid_response_window) && (led_state_L == LOW) && (led_state_R == LOW)){

           led_state_L = HIGH;
           led_state_R = HIGH;
           digitalWrite(port_led_L, led_state_L);
           digitalWrite(port_led_R, led_state_R);

           led_on_time = millis();
           // Serial.print(F("Valid led On:"));


           // Both Stimulus Lights ON 
           Serial.print(F("71171:")); // Timestamp for Free Choice Valid Light On 
           Serial.println(led_on_time);
           Serial.print(F("91171:")); // Timestamp for Free Choice Valid Light On 
           Serial.println(led_on_time);

           // reset the poke counters when the response window starts to count the pokes during this window 
           left_port_counter = 0;
           mid_port_counter = 0;   
           right_port_counter = 0;

           }   // LEDs are on HIGH


         // (VALID POKE - LIGHT OFF) if correct nose poke during valid response window -> start reward window (type 1 = yes reward)
         // BOTH LIGHTS ON, poke in LEFT PORT
         if ((valid_response_window) && (led_state_L == HIGH) && (led_state_R == HIGH) && (poke_in_L) && (left_port_counter > 0)) {

           valid_response_window = false;  // response window ends and reward window starts

           led_state_L = LOW; // turn off the LEDs
           led_state_R = LOW;
           digitalWrite(port_led_L, led_state_L);
           digitalWrite(port_led_R, led_state_R);

           led_off_time = millis();
           // Serial.print(F("Valid led Off:"));

           Serial.print(F("71170:"));    // Timestamp for Free Choice Valid Light Off (only printing the left port code is better for analysis, so the code indicates which port was poked for reward) 
           Serial.println(led_off_time);

           // Serial.print("valid_poke_timer");
           // Serial.println(valid_poke_timer);


           // CHANGED HERE (JHL) (2/14/20) --> automatically subtracts one from relevant port to account for poke for reward

           // POKEs during the Response Window (free choice code since both L and R poke can lead to reward) 
           Serial.print("71589::");   // 715xx
           Serial.println(left_port_counter - 1);
           Serial.print("81589::");    // 815xx
           Serial.println(mid_port_counter);
           Serial.print("91589::");  // 915xx
           Serial.println(right_port_counter);

           reward_window = true;
           reward_type = 1;     // reward_type = 1 --> dispense reward
                                // reward_type = 2 --> no reward (start iti)
         }

         // (VALID POKE - LIGHT OFF) if correct nose poke during valid response window -> start reward window (type 1 = yes reward)
         // BOTH LIGHTS ON, poke in RIGHT PORT
         if ((valid_response_window) && (led_state_L == HIGH) && (led_state_R == HIGH) && (poke_in_R) && (right_port_counter > 0)) {

           valid_response_window = false;  // valid response window ends and reward window starts

           led_state_L = LOW; // turn off the LEDs
           led_state_R = LOW;
           digitalWrite(port_led_L, led_state_L);
           digitalWrite(port_led_R, led_state_R);

           led_off_time = millis();
           // Serial.print(F("Valid led Off:"));

           Serial.print(F("91170:"));  // Timestamp for free Choice Valid Light Off (only printing the right port code is better for analysis, so the code indicates which port was poked for reward)
           Serial.println(led_off_time);

           // Serial.print("valid_poke_timer");
           // Serial.println(valid_poke_timer);

           // CHANGED HERE (JHL) (2/14/20) --> automatically subtracts one from relevant port to account for poke for reward

            // POKEs during the RESPONSE Window (free choice code since both L and R poke can lead to reward) 
           Serial.print("71589::");   // 715xx
           Serial.println(left_port_counter);
           Serial.print("81589::");    // 815xx
           Serial.println(mid_port_counter);
           Serial.print("91589::");  // 915xx
           Serial.println(right_port_counter - 1);

           reward_window = true;
           reward_type = 1;     // reward_type = 1 --> dispense reward
                                // reward_type = 2 --> no reward (start iti)
         }

       // NO INVALID POKE NOR OMISSION TRIAL!!!

       }
}

void activate_middle_sol () {  // controls Reward Window functionality (reward cue presentation + reward delivery) 

    // SOLENOID ON time will be used to time REWARD_CUE (since they happen concurrently)
    static unsigned long solenoid_on_time = 0;
    static unsigned long solenoid_off_time = 0;

    static unsigned long iti_start_time = 0;
    static unsigned long reward_cue_off_time = 0;

    // solenoid only operates once LED is turned off (to keep solenoid component OFF normally)
    if (led_state_L == LOW) {

        // (SOL_ON) reward_type = 1;  --> dispense reward (need to go into this loop only once!)
        // REWARD_CUE_ON
        if ((reward_window) && (reward_type == 1)) {
            reward_window = false;  // to go into this loop only once! (because of timer)
            reward_type = 0;  // toggle back to default value

            solenoid_active_M = true;  // to prevent from going into the LED loop
            sol_state_M = HIGH;
            digitalWrite(port_solenoid_M, sol_state_M);

            // solenoid on time = reward cue start time!
            solenoid_on_time = millis();

            Serial.print(F("81271:"));     // MIDDLE SOLENOID Timestamp for Free Choice Valid Solenoid On
            Serial.println(solenoid_on_time);

            // Reward Cue ON (Reward Cue Window ON)
            reward_cue_window = true;
            led_state_M = HIGH;
            digitalWrite(port_led_M, led_state_M);

            Serial.print(F("81171:"));  // free choice LED ON event code 
            Serial.println(solenoid_on_time);

            // reset poke counters to count the pokes that happen during the reward window 
            left_port_counter = 0;
            mid_port_counter = 0;
            right_port_counter = 0;


          }

          // (SOL_OFF) reward_type = 1; --> After time expires (i.e. the predetermined amount of reward has been delievered), turn off solenoid
          if ((sol_state_M == HIGH) && (millis() - solenoid_on_time > solenoid_on_duration)) {

             solenoid_active_M = false;   // can now activate the LEDs
             sol_state_M = LOW;
             digitalWrite(port_solenoid_M, sol_state_M);

             solenoid_off_time = millis();
             // Serial.print(F("valid_solenoid_off:"));

             Serial.print(F("81270:"));   // Timestamp for Free Choice Valid Solenoid Off
             Serial.println(solenoid_off_time);

           }

           // REWARD CUE OFF (solenoid_on_time = reward_cue_start_time) --> after reward cue duration expires, turn off the LED 
           if ((reward_cue_window) && (led_state_M == HIGH) && (millis() - solenoid_on_time > reward_cue_duration) ) {
             
             reward_cue_window = false;  
             led_state_M = LOW;
             digitalWrite(port_led_M, led_state_M);

             reward_cue_off_time = millis();
             // Serial.print(F("Invalid led Off:"));

             Serial.print(F("81170:"));    // Event Code for Free Choice Valid LED off
             Serial.println(reward_cue_off_time);

             // start ITI here
             start_iti_window = true;
             iti_start_time = millis();

             // POKEs during the REWARD Window
             Serial.print("71549::");   // 75xx
             Serial.println(left_port_counter);
             Serial.print("81549::");    // 85xx
             Serial.println(mid_port_counter);
             Serial.print("91549::");  // 95xx
             Serial.println(right_port_counter);

             // reset any port counters before ITI WINDOW starts (to count the pokes during the ITI window) 
             left_port_counter = 0;  
             mid_port_counter = 0;  
             right_port_counter = 0;


           }

           if (start_iti_window) {  // end the ITI window after predetermined length + get the counters and booleans ready for the new trial  

              // Initiate Next trial after ITI expires --> random ITI chosen from values in globals_time.h 
              if ((millis() - iti_start_time) >= iti_interval[random_idx]) {

                // # of poke counts during the ITI window (free choice ITI poke event codes) 
                Serial.print("71519::");   // 75xx
                Serial.println(left_port_counter);
                Serial.print("81519::");    // 85xx
                Serial.println(mid_port_counter);
                Serial.print("91519::");  // 95xx
                Serial.println(right_port_counter);

                get_random_iti = true;
                random_idx = random_iti(); // get a random ITI length for the next trial

                //FOR DEBUGGING PURPOSES: prints out the next iti length 
                // Serial.print("idx: ");
                // Serial.println(random_idx);
                // Serial.println(iti_interval[random_idx]);


                // RESETTING counters before new trial starts (to count # of pokes made during the initiation window)
                left_port_counter = 0;  
                mid_port_counter = 0;   
                right_port_counter = 0;

                // RESET current_port so that leds and solenoids don't get activated again
                current_port = 0;  // RESET NEEDED!!

                start_iti_window = false;
                initiate_new_trial = true;  // start the new trial 

              }
        }
    }
}
