/*--------------------------------------------------------++
||    Operate Middle Port (for free choice trials)        ||
++--------------------------------------------------------*/


/* 
 *  Function: 
 *  Operate the left and right LED during trial window --> FREE CHOICE TRIAL 
 *  left port is the large reward port! 
 *  Dispense reward from middle port after correct response 
 *  Solenoid Reward will only be from the middle port!
 *  
*/

void activate_middle_led() {  // turn on left and right LEDs during trial window + turn off the LEDs after correct response

     static unsigned long led_on_time = 0;
     static unsigned long led_off_time = 0;
	
     // static unsigned long valid_poke_timer = 0;
     // static unsigned long invalid_poke_timer = 0;

     // solenoid_active_M becomes false only after ITI time expires
     // Valid trial has started: Turn on left & right LED
     if (solenoid_active_M == false) {

       // (PORT LIGHTs ON) Turn on both LEDs if it is a valid trial
         if ((valid_response_window) && (led_state_L == LOW) && (led_state_R == LOW)){

           led_state_L = HIGH;
           led_state_R = HIGH;
           digitalWrite(port_led_L, led_state_L);
           digitalWrite(port_led_R, led_state_R);

           led_on_time = millis();
           // Serial.print(F("Valid led On:"));

           // Both Stimulus Lights ON
           Serial.print(F("71171:"));  // Timestamp for Free Choice Valid Light On
           Serial.println(led_on_time);
           Serial.print(F("91171:"));  // Timestamp for Free Choice Valid Light On 
           Serial.println(led_on_time);

           // reset the poke counters when the response window starts to count the pokes during this window 
           left_port_counter = 0;
           mid_port_counter = 0;   
           right_port_counter = 0;

           }   // LEDs are on HIGH


         // (VALID POKE - LIGHT OFF) if correct nose poke during response window -> start reward window (type 1 = yes reward)
         // BOTH LIGHTS ON, poke in LEFT PORT --> large reward port! 
         if ((valid_response_window) && (led_state_L == HIGH) && (led_state_R == HIGH) && (poke_in_L) && (left_port_counter > 0)) {

		       valid_response_window = false;   // valid response window ends and reward window starts

           led_state_L = LOW;        // turn off the LEDs 
           led_state_R = LOW;
           digitalWrite(port_led_L, led_state_L);
           digitalWrite(port_led_R, led_state_R);

           led_off_time = millis();
           // Serial.print(F("Valid led Off:"));

           Serial.print(F("71170:"));     // Timestamp for free choice Valid Light Off (indicates a poke in which port led to reward) 
           Serial.println(led_off_time);

           // Serial.print("valid_poke_timer");
           // Serial.println(valid_poke_timer);


           // CHANGED HERE (JHL) (2/14/20) --> automatically subtracts one from relevant port to account for poke for reward
           
           // POKES during the TRIAL Window (during when response ports light on) --> use free choice event codes! (allows us to distinguish between trial types) 
            Serial.print("71589::");   // 715xx
            Serial.println(left_port_counter - 1);
            Serial.print("81589::");    // 815xx
            Serial.println(mid_port_counter);
            Serial.print("91589::");  // 915xx
            Serial.println(right_port_counter);


           i = 1;               // 4 - i (i.e. 3) drops of reward will be given 
           give_small_reward = false; 
           reward_window = true;
           reward_type = 1;     // reward_type = 1 --> dispense reward
                                // reward_type = 2 --> no reward (start iti)
         }

         // (VALID POKE - LIGHT OFF) if correct nose poke during valid trial window -> start reward window (type 1 = yes reward)
         // BOTH LIGHTS ON, poke in RIGHT PORT --> small reward port 
         if ((valid_response_window) && (led_state_L == HIGH) && (led_state_R == HIGH) && (poke_in_R) && (right_port_counter > 0)) {

           valid_response_window = false;  // valid response window ends and reward window starts

           led_state_L = LOW;      // turn off the LEDs 
           led_state_R = LOW;
           digitalWrite(port_led_L, led_state_L);
           digitalWrite(port_led_R, led_state_R);

           led_off_time = millis();
           // Serial.print(F("Valid led Off:"));

           Serial.print(F("91170:"));   // Timestamp for Valid Light Off (indicates a poke in which port led to reward) 
           Serial.println(led_off_time);

           // Serial.print("valid_poke_timer");
           // Serial.println(valid_poke_timer);

           // CHANGED HERE (JHL) (2/14/20) --> automatically subtracts one from relevant port to account for poke for reward
           
           // POKES during the TRIAL Window (during when response ports light on) --> use free choice event codes! (allows us to distinguish between trial types) 
            Serial.print("71589::");   // 715xx
            Serial.println(left_port_counter);
            Serial.print("81589::");    // 815xx
            Serial.println(mid_port_counter);
            Serial.print("91589::");  // 915xx
            Serial.println(right_port_counter - 1);

           i = 3;      // 4 - i (i.e. 1) drops of reward will be given 
           give_small_reward = true;  
           reward_window = true;
           reward_type = 1;     // reward_type = 1 --> dispense reward
                                // reward_type = 2 --> no reward (start iti)
         }

         // (NO INVALID/INCORRECT TRIALS as both L and R pokes can lead to reward!!) 

          // OMISSION TRIAL
          // (NO RESPONSE - LIGHT OFF) 
          if ((valid_response_window) && (led_state_L == HIGH) && (led_state_R == HIGH) && (millis() - led_on_time > led_trial_duration)) {

          valid_response_window = false;  // end the response window

          led_state_L = LOW;   // turn off LEDs 
          led_state_R = LOW;
          digitalWrite(port_led_L, led_state_L);
          digitalWrite(port_led_R, led_state_R);

          led_off_time = millis();
          // Serial.print(F("Invalid led Off:"));

          Serial.print(F("81540:"));     // Free Choice Omission Trial END Timestamp ("MIDDLE" PORT OMISSION since it was free choice) 
          Serial.println(led_off_time);

           // POKES during the TRIAL Window (during when response ports light on) --> use free choice event codes! (allows us to distinguish between trial types) 
           Serial.print("71589::");   // 715xx
           Serial.println(left_port_counter);
           Serial.print("81589::");    // 815xx
           Serial.println(mid_port_counter);  
           Serial.print("91589::");  // 915xx
           Serial.println(right_port_counter);

           // RESET PORT COUNTER to count # of pokes during the ITI WINDOW 
           left_port_counter = 0;
           mid_port_counter = 0;   
           right_port_counter = 0;


          // start reward_window (type=2 (no reward))
          reward_window = true;
          reward_type = 2;    // no reward delivery 

        }


       }
}

void activate_middle_sol () {  // controls Reward Window functionality (reward cue presentation + reward delivery) 

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
			      
            //* solenoid on time = reward cue start time! *//
            solenoid_on_time = millis();   // will only be recorded at the begining; not for each drop 
            Serial.print(F("81271:"));     // MIDDLE SOLENOID Timestamp for Free Choice Valid Solenoid On
            Serial.println(solenoid_on_time);

            // Reward Cue ON (Reward Cue Window ON)
            reward_cue_window = true;
            led_state_M = HIGH;
            digitalWrite(port_led_M, led_state_M); 

            Serial.print(F("81171:"));     // Timestamp for free choice Valid Light On
            Serial.println(solenoid_on_time);

            // reset poke counters to count the pokes that happen during the reward window 
            left_port_counter = 0;
            mid_port_counter = 0;   
            right_port_counter = 0;
			      
			      while (i <= 3) {   // value of i determined when there is a left or right poke (4-i drops of reward will be given)
                
            	   solenoid_active_M = true;  
            	   sol_state_M = HIGH;
            	   digitalWrite(port_solenoid_M, sol_state_M);
                 
                 // FOR LARGE REWARD TRIAL: (SOL_OFF) reward_type = 1; --> After time for each drop expires, turn off solenoid 
                 // will be executed 3 times since the large reward was chosen
                 if ((give_small_reward == false) && (sol_state_M == HIGH) && (millis() - solenoid_on_time > (i * solenoid_on_duration))) {

             		   solenoid_active_M = false;   
             		   sol_state_M = LOW;
             		   digitalWrite(port_solenoid_M, sol_state_M);
                    
                   i = i + 1;   // move the index (i) forward --> counts the number of drops dispensed 

                  if (i != 3) {  // will record the time of the final solenoid OFF outside the loop!
                    Serial.print(F("81270:"));  // MIDDLE SOLENOID Timestamp for Free Choice Valid Solenoid Off
                    Serial.println(millis()); 
                  }
                  
                   delay(5);  // puts a 5 ms delay between each drop to ensure the reward delivery "clicks" are distinguishable 
          		   }

                 // FOR SMALL REWARD POKE: (SOL_OFF) reward_type = 1; --> After time expires, turn off solenoid 
                 // since small reward trials start with i == 3; we can't use i * solenoid_on_duration for reward dispensing!
                 if ((give_small_reward == true) && (sol_state_M == HIGH) && (millis() - solenoid_on_time > (solenoid_on_duration))) {

                    solenoid_active_M = false;   
                    sol_state_M = LOW;
                    digitalWrite(port_solenoid_M, sol_state_M);
                    
                    i = i + 1;   // move the index (i) forward --> counts the number of drops dispensed 
                    give_small_reward = false;  
                 } 
			      }
           
			      // once the while loop is over, record when the solenoid turned off 
            solenoid_off_time = millis();
            // Serial.print(F("valid_solenoid_off:"));

            Serial.print(F("81270:"));   // MIDDLE SOLENOID Timestamp for Free Choice Valid Solenoid Off
            Serial.println(solenoid_off_time);

        }

           // REWARD CUE OFF (solenoid_on_time = reward_cue_start_time) --> after reward cue duration expires, turn off the LED 
           if ((reward_cue_window) && (led_state_M == HIGH) && (millis() - solenoid_on_time > reward_cue_duration) ) {
             
             reward_cue_window = false;
             led_state_M = LOW;  // turn off LED
             digitalWrite(port_led_M, led_state_M);

             reward_cue_off_time = millis();
             // Serial.print(F("Invalid led Off:"));

             Serial.print(F("81170:"));   // Event Code for Free Choice Valid LED off
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

           
           // (NO REWARD) If reward_type = 2; --> (don't dispense reward but start ITI timer)
           // used after omission trials
           if ((reward_window) && (reward_type == 2)) {
            
             reward_window = false;  // end reward window 
             reward_type = 0;   // reset reward_type 

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

                // # of poke counts during ITI window  (free choice ITI poke event codes) 
                Serial.print("71519::");   // 715xx
                Serial.println(left_port_counter);
                Serial.print("81519::");    // 815xx
                Serial.println(mid_port_counter);
                Serial.print("91519::");  // 915xx
                Serial.println(right_port_counter);

                // get the ITI length for the next trial 
                get_random_iti = true;
                random_idx = random_iti();

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
