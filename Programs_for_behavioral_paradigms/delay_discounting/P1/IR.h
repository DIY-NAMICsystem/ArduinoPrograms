/*--------------------------------------------------------++
||                      Record IR                         ||
++--------------------------------------------------------*/


void record_IR() {

  static unsigned long Poke_On_Time_L = 0;
  static unsigned long Poke_Off_Time_L = 0;

  static unsigned long Poke_On_Time_M = 0;
  static unsigned long Poke_Off_Time_M = 0;

  static unsigned long response_window_end_time = 0;

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

      if (response_window){
        
        // # of poke counts during response window (Forced choice event code, since only middle pokes are valid) 
        Serial.print(F("72589::"));   // 75xx
        Serial.println(left_port_counter);
        Serial.print(F("82589::"));    // 85xx
        Serial.println(mid_port_counter - 1);
        Serial.print(F("92589::"));  // 95xx
        Serial.println(right_port_counter);

        left_port_counter = 0;
        mid_port_counter = 0;
        right_port_counter = 0;

        response_window = false;   // end of trial window
        reward_window = true; // start of valid trial

        // Originally from "begin_trial.h"
        // Nominally turns light off (bc its going to get turned on anyways)
        led_state_M = LOW;  digitalWrite(port_led_M, led_state_M);

        response_window_end_time = millis();
        Serial.print(F("5520:"));
        Serial.println(response_window_end_time);

        // random_port WILL ALWAYS RETURN 55 (code for middle port)
        get_random_port = true;
        current_port = random_port();

        }
      }

    if (read_gate_M == HIGH){
      Poke_Off_Time_M = millis();

      Serial.print(F("8070:"));
      Serial.println(Poke_Off_Time_M);
      poke_in_M = false;

    }


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
