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
