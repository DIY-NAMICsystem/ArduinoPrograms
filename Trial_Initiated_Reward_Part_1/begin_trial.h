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
    if ((trial_window == false) && (led_state_L == LOW) && (led_state_M == LOW) && (led_state_R == LOW)){

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
       Serial.println(trial_window_start_time);

       }

    // Poke in Middle Port(IR.h) initiates Valid Trial:

    // Once Valid Trial initiated (by IR) --> LED turns off!
    if ((valid_trial_window) && (led_state_L == HIGH) && (led_state_M == HIGH) && (led_state_R == HIGH)) {

       initiate_new_trial = false; // toggle boolean to false since we DON'T want to enter 'Parent IF' state next time

       // * * DON'T USE for loops for toggling components - always use STATES!! * *
       // for (byte i = 8; i <=10; i++) { digitalWrite(i, LOW);}

       // Turn OFF All three LEDs
       led_state_L = LOW;  digitalWrite(port_led_L, led_state_L);
       led_state_M = LOW;  digitalWrite(port_led_M, led_state_M);
       led_state_R = LOW;  digitalWrite(port_led_R, led_state_R);

       trial_window_end_time = millis();
       Serial.print(F("5520:"));
       Serial.println(trial_window_end_time);

       // Select which port to activate
       get_random_port = true;
       current_port = random_port();

       }

    }
  }
