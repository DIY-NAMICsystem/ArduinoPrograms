/*--------------------------------------------------------++
||                     Begin New Trial                    ||
++--------------------------------------------------------*/

void begin_new_trial() {

  static unsigned long response_window_start_time = 0;
  static unsigned long response_window_end_time = 0;

  static unsigned long iti_window_start_time = 0;
  static unsigned long iti_window_end_time = 0;

  static unsigned long previous_m_LED_millis=0;

  // Initiate New Trial is toggled on AFTER iti duration expires (from l/R port operate.h)

  // Initiate New Trial (Parent IF)
  if (initiate_new_trial){

      // transition_to_reward = false;  // so that solenoid doesnt'get activated

    // Trial Window hasn't started yet - If all lights are turned OFF, TURN ON Middle light
    if ((response_window == false) && (reward_window == false)){

       // start Trial Window Period
       response_window = true;

       // * * DON'T USE for loops for toggling components - always use STATES!! * *
       // for (byte i = 8; i <=10; i++) { digitalWrite(i, HIGH);}

       response_window_start_time = millis();
       Serial.print(F("5521:"));
       Serial.println(response_window_start_time);

       // Turn ON Left / Right LED (Stimulus Ports)
       led_state_L = HIGH;  digitalWrite(port_led_L, led_state_L);
       led_state_R = HIGH;  digitalWrite(port_led_R, led_state_R);
       Serial.print(F("71171:")); // left LED on 
       Serial.println(response_window_start_time);
       Serial.print(F("91171:")); // right LED on 
       Serial.println(response_window_start_time);


       }


    // Poke in Middle Port(IR.h) initiates Valid Trial:

    // If mouse pokes in MIDDLE port and initiates trial, --> LED turns off!! (all three should turn off!)
    // Also when delay window didn't start
    // (MOUSE CAN POKE REGARDLESS OF BLINK CYCLE - either ON or OFF cycle!) --> goverened by the STATE!

    // (Valid trial window toggles TRUE if poke in middle port (see IR.h))
    // POKE in middle -->  Valid Trial Window

  }
}
