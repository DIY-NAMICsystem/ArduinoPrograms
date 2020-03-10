/*--------------------------------------------------------++
||                      Record IR                         ||
++--------------------------------------------------------*/


void record_IR() {

  static unsigned long Poke_On_Time_L = 0;
  static unsigned long Poke_Off_Time_L = 0;

  static unsigned long Poke_On_Time_M = 0;
  static unsigned long Poke_Off_Time_M = 0;

  static unsigned long Poke_On_Time_R = 0;
  static unsigned long Poke_Off_Time_R = 0;

  byte read_gate_L = digitalRead(port_ir_L);
  byte read_gate_M = digitalRead(port_ir_M);
  byte read_gate_R = digitalRead(port_ir_R);

  if (read_gate_L != ir_previous_state_L) {
    // low means IR has been broken
    if (read_gate_L == LOW) {
      Poke_On_Time_L = millis();

      Serial.print(F("7071:"));
      Serial.println(Poke_On_Time_L);
      poke_in_L = true;
      left_port_counter += 1;        // left port counter
    }
    if (read_gate_L == HIGH){
      Poke_Off_Time_L = millis();

      Serial.print(F("7070:"));
      Serial.println(Poke_Off_Time_L);
      poke_in_L = false;
    }
  }

  ir_previous_state_L = read_gate_L;

  if (read_gate_M != ir_previous_state_M) {
    if (read_gate_M == LOW) {
      Poke_On_Time_M = millis();

      Serial.print(F("8071:"));
      Serial.println(Poke_On_Time_M);
      poke_in_M = true;
      mid_port_counter += 1;       // mid port counter

      if (trial_initiation_window){

        // Prints Out number of invalid pokes made during pre-trial phase (when 3 lights are ON)
        // (number of pokes in left/right ports before initiation in the middle port)
        // (# of mid port is always going to be 1 (ONE))
        //    --> since trial need to be initiated to print out below statements

        // # of poke counts during trial window (before VALID trial window)
        Serial.print(F("7529::"));   // 75xx
        Serial.println(left_port_counter);
        Serial.print(F("8529::"));    // 85xx
        Serial.println(mid_port_counter);
        Serial.print(F("9529::"));  // 95xx
        Serial.println(right_port_counter);

        trial_initiation_window = false;   // end of trial window
        valid_trial_window = true; // start of valid trial

        // reset all counters once valid_trial_window starts (is true)
        // allows me to count the "valid" pokes after trial initiation (valid trial window)
        // --> "valid" pokes used to detect incorrect port choices once valid trial starts (L/R port turns on)
        // ex) if # of pokes in L/M/R port > 0,
        //        --> I know that the mouse made an incorrect decision so I can invalidate the whole trial (turn off lights)

        left_port_counter = 0;
        mid_port_counter = 0;
        right_port_counter = 0;

        }

      }

    if (read_gate_M == HIGH){
      Poke_Off_Time_M = millis();

      Serial.print(F("8070:"));
      Serial.println(Poke_Off_Time_M);
      poke_in_M = false;

    }

    // 11-11-19 UPDATE; TRIAL WINDOW IS NOW A WINDOW with alternating on/off cycles
    // thus must be reactive to both on--> off and off--> on cases
    // If mouse pokes in the MIDDLE port during the trial window period, activate VALID TRIAL



  }

  ir_previous_state_M = read_gate_M;


if (read_gate_R != ir_previous_state_R) {
  if (read_gate_R == LOW) {
    Poke_On_Time_R = millis();

    Serial.print(F("9071:"));
    Serial.println(Poke_On_Time_R);
    poke_in_R = true;
    right_port_counter += 1;        // right port counter
  }
  if (read_gate_R == HIGH){
    Poke_Off_Time_R = millis();

    Serial.print(F("9070:"));
    Serial.println(Poke_Off_Time_R);
    poke_in_R = false;

  }
}

ir_previous_state_R = read_gate_R;

}
