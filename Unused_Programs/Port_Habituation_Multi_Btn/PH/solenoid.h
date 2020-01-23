/*--------------------------------------------------------++
||                     Solenoid Operation                 ||
++--------------------------------------------------------*/
// refactor code by making smaller functions (using parameters and arguments)
// reocrding part

void solenoid_on() {

   unsigned long currentMillis = millis();

   static unsigned long sol_on_L = 0;
   static unsigned long sol_off_L = 0;

   static unsigned long sol_on_M = 0;
   static unsigned long sol_off_M = 0;

   static unsigned long sol_on_R = 0;
   static unsigned long sol_off_R = 0;

   if (poke_in_L) {
       poke_in_L = false;
       sol_state_L = HIGH;
       digitalWrite(port_solenoid_L, sol_state_L);
       sol_on_L = millis();
       // Serial.print("L001: ");
       // Serial.print("solenoid On at L: ");
       Serial.print(F("7271:"));
       Serial.println(sol_on_L); // time solenoid was turned on
       // theoretically, currentMillis output and sol_on_L output time should be the same!
      }

       // can't come in to this loop in the first place bc its nested in the if() above!!
       // only turn on solenoid for the solenoid interval
    if (sol_state_L == HIGH && currentMillis - sol_on_L >= sol_reward_DUR) {  //poke_in_8 = false &&
        sol_state_L = LOW;
        digitalWrite(port_solenoid_L, sol_state_L);
        sol_off_L = millis();
        // Serial.print("3001: ");
        // Serial.print("solenoid Off at L: ");
        Serial.print(F("7270:"));
        Serial.println(sol_off_L);
        // theoretically currentMillis should be sol_off_L + sol_reward_DUR value
    }

   if (poke_in_M) {
       poke_in_M = false;
       sol_state_M = HIGH;
       digitalWrite(port_solenoid_M, sol_state_M);
       sol_on_M = millis();
       // Serial.print("4100: ");
       // Serial.print("solenoid On at M: ");
       Serial.print(F("8271:"));
       Serial.println(sol_on_M);
       // theoretically, currentMillis output and sol_on_4 output time should be the same!
       }

       // breaking out of above loop is crucial!!!

       // can't come in to this loop in the first place bc its nested in the if() above!!
    if (sol_state_M == HIGH && currentMillis - sol_on_M >= sol_reward_DUR) {  //poke_in_8 = false &&
        sol_state_M = LOW;
        digitalWrite(port_solenoid_M, sol_state_M);
        sol_off_M = millis();
        // Serial.print("4001: ");
        // Serial.print("solenoid Off at M: ");
        Serial.print(F("8270:"));
        Serial.println(sol_off_M);
        // theoretically currentMillis should be sol_off_L + sol_reward_DUR value
       }

    if (poke_in_R) {
       poke_in_R = false;
       sol_state_R = HIGH;
       digitalWrite(port_solenoid_R, sol_state_R);
       sol_on_R = millis();
       // Serial.print("5100: ");
       // Serial.print("solenoid On at R: ");
       Serial.print(F("9271:"));
       Serial.println(sol_on_R);
       // can't come in to this loop in the first place bc its nested in the if() above!!
    }

    if (sol_state_R == HIGH && currentMillis - sol_on_R >= sol_reward_DUR) {  //poke_in_8 = false &&
        sol_state_R = LOW;
        digitalWrite(port_solenoid_R, sol_state_R);
        sol_off_R = millis();
        // Serial.print("5001: ");
        // Serial.print("solenoid Off at R: ");
        Serial.print(F("9270:"));
        Serial.println(sol_off_R);
        // theoretically currentMillis should be sol_off_L + sol_reward_DUR value
       }
     }
