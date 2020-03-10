/*--------------------------------------------------------++
||                    Operate Right Port                   ||
++--------------------------------------------------------*/


// HAVE TO KEEP COMPONENTS RUNNING INDEPENDENTLY (ON / OFF)
// ORDER OF THIS MATTERS!! IF NOT IN THE FOLLOWING ORDER, nosepoke will NOT trigger solenoid on...
// idk WHY...

void led_operate_R () {

     static unsigned long led_on_time = 0;
     static unsigned long led_off_time = 0;

      // solenoid_active_R becomes false only after ITI time expires

     if (solenoid_active_R == false) {
        if (led_state_R == LOW){


          led_state_R = HIGH;
          led_on_time = millis();
          digitalWrite(port_led_R, led_state_R);
          Serial.print(F("9171:"));
          Serial.println(led_on_time);
          }   // led is on HIGH

         // if nose poke was made during the time LED was on --> turn LED off and record time

         if (led_state_R == HIGH && digitalRead(port_ir_R) == 0) {
           led_state_R = LOW;
           led_off_time = millis();
           digitalWrite(port_led_R, led_state_R);
           Serial.print(F("9170:"));
           Serial.println(led_off_time);

           deliver_reward_R = true;

           // RESET ITI_TIMER HERE IF DEPENDENT ON POKE ON

          }
       }
}


// LED turns off immediately after detecting a nosepoke in the port
// ORDER of the if clause matters! (led on duration must expire first --> then nose poke detection must happen)

void solenoid_operate_R () {

    static unsigned long solenoid_on_time = 0;
    static unsigned long solenoid_off_time = 0;
    static unsigned long ITI_start_time = 0;

    static int time_index = 0;

     // solenoid only operates once led is turned off (have to keep solenoid component OFF normally)
    if (led_state_R == LOW) {

         if (deliver_reward_R) {
            deliver_reward_R = false;
            solenoid_active_R = true;  // to prevent from going into the led loop

            sol_state_R = HIGH;
            solenoid_on_time = millis();
            digitalWrite(port_solenoid_R, sol_state_R);

            Serial.print(F("9271:"));
            Serial.println(solenoid_on_time);
            }

            // solenoid turns off after duration elapses:
            // must be in an IF loop (NOT ELIF) b/c arduino has to constantly
            // check the time while going through the loop
            // -> If using ELIF, it won't allow this statement to be run,
            // if any previous IF statements evaluate to true

         if ((sol_state_R == HIGH) && (millis() - solenoid_on_time > solenoid_on_duration)) {
            deliver_reward_R = true;     // toggle
            solenoid_active_R = false;

            sol_state_R = LOW;
            solenoid_off_time = millis();
            digitalWrite(port_solenoid_R, sol_state_R);

            Serial.print(F("9270:"));
            Serial.println(solenoid_off_time);

            // RESET ITI_TIMER HERE IF DEPENDENT ON SOLENOID OFF

            initiate_new_trial = true;
            ITI_start_time = millis();

            }


           if (initiate_new_trial) {

              // NO DURATION INVOLVED!

              initiate_new_trial = false;
              activate_random_gen = true;
              prev_port = current_port;
              // current_port = random_generator();

              // BAck to 1 (left port!)
              current_port = 1;

         }
    }
}
