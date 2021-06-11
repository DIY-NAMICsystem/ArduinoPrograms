/*--------------------------------------------------------++
||                      Record IR                         ||
++--------------------------------------------------------*/

/* Function: 
 * Registers IR beam breaks and advances the program as needed
 * Prints the time of each beam break    
 */

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

  if (read_gate_L != ir_previous_state_L) {  // registers left port IR beam breaks
   
    // low means IR has been broken
    if (read_gate_L == LOW) {
      Poke_On_Time_L = millis();

      Serial.print(F("7071:"));  // poke in event code
      Serial.println(Poke_On_Time_L);
      poke_in_L = true;
      left_port_counter += 1;   // left port counter
    }
    
    if (read_gate_L == HIGH){
      Poke_Off_Time_L = millis();

      Serial.print(F("7070:"));   // poke out event code
      Serial.println(Poke_Off_Time_L);
      poke_in_L = false;
    }
  }

  ir_previous_state_L = read_gate_L;

  if (read_gate_M != ir_previous_state_M) {  // registers middle port IR beam breaks

    if (read_gate_M == LOW) {
      Poke_On_Time_M = millis();

      Serial.print(F("8071:"));  // poke in event code
      Serial.println(Poke_On_Time_M);
      poke_in_M = true;
      mid_port_counter += 1;   // middle port counter

      if (initiation_window){

        // Prints Out number of invalid pokes made during the initiation window (middle light blinking) 
        // (number of pokes in left/right ports before initiation in the middle port)
        // (# of mid port is always going to be 1 (ONE)) --> since trial need to be initiated to print out below statements
        
        // CHANGED HERE (JHL) (2/14/20) --> automatically subtract one from mid_port_counter to account for poke to initiate trial

        // # of poke counts during INITIATION window 
        Serial.print(F("7529::"));   // 75xx
        Serial.println(left_port_counter);
        Serial.print(F("8529::"));    // 85xx
        Serial.println(mid_port_counter - 1);
        Serial.print(F("9529::"));  // 95xx
        Serial.println(right_port_counter);

        initiation_window = false;    // end of initiation window
        valid_response_window = true; // start of the response window 

        // reset all counters once valid_response_window starts (is true)
        // allows me to count the "valid" pokes after trial initiation 
        // --> "valid" pokes used to detect incorrect port choices once valid trial starts (L/R port turns on)
        left_port_counter = 0;
        mid_port_counter = 0;
        right_port_counter = 0;

        }

      }

    if (read_gate_M == HIGH){
      Poke_Off_Time_M = millis();

      Serial.print(F("8070:"));  // poke out event code
      Serial.println(Poke_Off_Time_M);
      poke_in_M = false;

    }

  }

  ir_previous_state_M = read_gate_M;


if (read_gate_R != ir_previous_state_R) {   // registers right port IR beam breaks
  
  if (read_gate_R == LOW) {
    Poke_On_Time_R = millis();

    Serial.print(F("9071:"));  // poke in event code
    Serial.println(Poke_On_Time_R);
    poke_in_R = true;
    right_port_counter += 1;  // right port counter
  }
  if (read_gate_R == HIGH){
    Poke_Off_Time_R = millis();

    Serial.print(F("9070:"));  // poke out event code
    Serial.println(Poke_Off_Time_R);
    poke_in_R = false;

  }
}

ir_previous_state_R = read_gate_R;

}
