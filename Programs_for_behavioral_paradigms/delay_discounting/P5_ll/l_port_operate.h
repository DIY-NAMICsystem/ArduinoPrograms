/*--------------------------------------------------------++
||   Operate Left Port in FC trials (Large Reward Port)   ||
++--------------------------------------------------------*/


/* 
 *  Function: 
 *  Operate the left LED during trial window --> FORCED CHOICE TRIAL ON THE LEFT PORT
 *  Dispense reward from middle port after correct response 
 *  Solenoid Reward will only be from the middle port!
 *  
*/

void activate_left_led() {   // turn on left LED during trial window + turn off the LEDs after correct response 

     static unsigned long led_on_time = 0;
     static unsigned long led_off_time = 0;

     // static unsigned long valid_poke_timer = 0;
     // static unsigned long invalid_poke_timer = 0;

      // solenoid_active_M becomes false only after ITI time expires
      // Valid trial has started: Turn on left LED
     if (solenoid_active_M == false) {

       // (PORT LIGHT ON) Turn on Left LED if it is a valid trial
         if ((valid_response_window) && (led_state_L == LOW)){

           led_state_L = HIGH;  
           digitalWrite(port_led_L, led_state_L);

           led_on_time = millis();
           // Serial.print(F("Valid led On:"));

           // Left Response Cue On 
           Serial.print(F("72171:")); // Timestamp for FC Valid Light On
           Serial.println(led_on_time);

           // reset the poke counters when the response window starts to count the pokes during this window 
           left_port_counter = 0;
           mid_port_counter = 0;   
           right_port_counter = 0;
           
           }   // left LED is on HIGH


         // (VALID POKE - LIGHT OFF) if correct nose poke during valid response window -> start reward window (type 1 = yes reward)
         // LEFT LIGHT ON, poke in LEFT PORT
         if ((valid_response_window) && (led_state_L == HIGH) && (poke_in_L) && (left_port_counter > 0)) {

           valid_response_window = false;  // valid response window ends and reward window starts

           led_state_L = LOW;     // turn off the LED 
           digitalWrite(port_led_L, led_state_L);

           led_off_time = millis();
           // Serial.print(F("Valid led Off:"));

           Serial.print(F("72170:"));   // Timestamp for Forced Choice Valid Light Off
           Serial.println(led_off_time);

           // Serial.print("valid_poke_timer");
           // Serial.println(valid_poke_timer);

           // CHANGED HERE (JHL) (2/14/20) --> automatically subtracts one from relevant port to account for poke for reward
           
           // POKEs during the TRIAL Window (during when response ports light on) --> use FC event codes! (allows us to distinguish between trial types) 
            Serial.print("72589::");   // 725xx 
            Serial.println(left_port_counter - 1);
            Serial.print("82589::");    // 825xx 
            Serial.println(mid_port_counter);
            Serial.print("92589::");  // 925xx 
            Serial.println(right_port_counter);

           // RESET PORT COUNTER to count # of pokes during the reward window 
           left_port_counter = 0;
           mid_port_counter = 0;   
           right_port_counter = 0;

           reward_window = true;
           reward_type = 1;     // reward_type = 1 --> dispense reward
                                // reward_type = 2 --> no reward (start iti)
         }

      
         // (INVALID_POKE - LIGHT OFF) --> poke in the unlit right or middle ports
        if ((valid_response_window) && (led_state_L == HIGH) && ((mid_port_counter > 0) || (right_port_counter > 0)) && ((poke_in_M) || (poke_in_R))) {
          
           valid_response_window = false;  // end the response window 

           led_state_L = LOW;    // turn off the LED 
           digitalWrite(port_led_L, led_state_L);

           led_off_time = millis();
           // Serial.print(F("Invalid led Off:"));

           Serial.print(F("72160:"));    // Timestamp for FC Invalid Light Off
           Serial.println(led_off_time);

           // Serial.print("invalid_poke_timer");
           // Serial.println(invalid_poke_timer);
          
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

           // start reward_window (type=2 (no reward))
           reward_window = true;
           reward_type = 2;  // no reward delivery 

          }

        // OMISSION TRIAL
        // (NO RESPONSE - LIGHT OFF) 
        if ((valid_response_window) && (led_state_L == HIGH) && (millis() - led_on_time > led_trial_duration)) {

          valid_response_window = false;  // end the response window

          led_state_L = LOW;   // turn off the LED
          digitalWrite(port_led_L, led_state_L);

          led_off_time = millis();
          // Serial.print(F("Invalid led Off:"));

          Serial.print(F("72540:"));    // FC Omission Trial END Timestamp (LEFT PORT OMISSION since this was a left port FC trial) 
          Serial.println(led_off_time);

          // start reward_window (type=2 (no reward))
          reward_window = true;
          reward_type = 2;  // no reward delivery 

        }

       }
}

void activate_left_sol () {  // controls Reward Window functionality (reward cue presentation + reward delivery) 

    // SOLENOID ON time will be used to time REWARD_CUE (since they happen concurrently)
    static unsigned long solenoid_on_time = 0;
    static unsigned long solenoid_off_time = 0;

    static unsigned long iti_start_time = 0;
    static unsigned long reward_cue_off_time = 0;

    // solenoid only operates once LED is turned off (have to keep solenoid component OFF normally)
    if (led_state_L == LOW) {

        // (SOL_ON) reward_type = 1;  --> dispense reward (need to go into this loop only once! (bc of timer))
        // REWARD_CUE_ON
        if ((reward_window) && (reward_type == 1)) {
          
            reward_window = false;
            reward_type = 0; // toggle back to default value
            i = 1;           // will count the number of drops given (3 drops will be given)
            
            //* solenoid on time = reward cue start time! *//
            solenoid_on_time = millis();   // will only be recorded at the begining; not for each drop 
            Serial.print(F("82271:"));     // MIDDLE SOLENOID Timestamp for FC Valid Solenoid On 
            Serial.println(solenoid_on_time);

            // Reward Cue ON (Reward Cue Window ON)
            reward_cue_window = true;
            led_state_M = HIGH;
            digitalWrite(port_led_M, led_state_M);

            Serial.print(F("82171:"));  // Timestamp for FC Valid Light On
            Serial.println(solenoid_on_time);
            
            // reset poke counters to count the pokes that happen during the reward window 
            left_port_counter = 0;
            mid_port_counter = 0;   
            right_port_counter = 0;


            while (i <= 3) {   // changing 3 here can be used to change the number of reward drops dispensed 
            	
            	solenoid_active_M = true;  
            	sol_state_M = HIGH;
            	digitalWrite(port_solenoid_M, sol_state_M);

          		// (SOL_OFF) reward_type = 1; --> After time for each drop expires, turn off solenoid
              // will be executed 3 times! 
          		if ((sol_state_M == HIGH) && (millis() - solenoid_on_time > (i * solenoid_on_duration))) {
             		
             		solenoid_active_M = false;  
             		sol_state_M = LOW;
             		digitalWrite(port_solenoid_M, sol_state_M); 
                                
                i = i + 1;   // move the index (i) forward --> counts the number of drops dispensed 
                
                if (i != 3) {   // will record the time of the final solenoid OFF outside the loop
                  
                  Serial.print(F("82270:")); // MIDDLE SOLENOID Timestamp for Forced Choice Valid Solenoid Off
                  Serial.println(millis()); 
                  
                }
             
                delay(5);    // puts a 5 ms delay between each drop to ensure the reward delivery "clicks" are distinguishable 
             	}
             }

             solenoid_off_time = millis();   // record when the solenoid turns off for the last time 
             // Serial.print(F("valid_solenoid_off:"));

             Serial.print(F("82270:"));   // Timestamp for Valid Solenoid Off --> can be used to count the number of drops given
             Serial.println(solenoid_off_time);

        }

           // REWARD CUE OFF (solenoid_on_time = reward_cue_start_time) --> after reward cue duration expires, turn off the LED 
           if ((reward_cue_window) && (led_state_M == HIGH) && (millis() - solenoid_on_time > reward_cue_duration) ) {
             
             reward_cue_window = false;
             led_state_M = LOW;
             digitalWrite(port_led_M, led_state_M);

             reward_cue_off_time = millis();
             // Serial.print(F("Invalid led Off:"));

             Serial.print(F("82170:"));    // Event Code for Forced Choice Valid LED off
             Serial.println(reward_cue_off_time);

             // start ITI here
             start_iti_window = true;
             iti_start_time = millis();
             count = count + 1;        // count counts the number of VALID FC trials so the first 10 trials are FC

             // POKES during the REWARD Window (Forced Choice Event Code)
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

           // (NO REWARD) If reward_type = 2; --> (don't dispense reward but start iti timer)
           if ((reward_window) && (reward_type == 2)) {
             
             reward_window = false;
             reward_type = 0;   // reset reward_type

             solenoid_active_M = false;

             start_iti_window = true;  // start the ITI window 
             iti_start_time = millis();

             // NO NEED TO PRINT OUT invalid_solenoid (no reward) OR iti_start_time
             // Serial.print(F("invalid_solenoid: "));
             // Serial.print(F("7270:"));   // Timestamp for Invalid Solenoid Off
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
                current_port = 0;  // RESET NEEDED!!

                start_iti_window = false;
                initiate_new_trial = true;  // start the new trial 

              }
        }
    }
}
