/*--------------------------------------------------------++
||                      Operate Left Port                 ||
++--------------------------------------------------------*/


// HAVE TO KEEP COMPONENTS RUNNING INDEPENDENTLY (ON / OFF)
// ORDER OF THIS MATTERS!! IF NOT IN THE FOLLOWING ORDER, nosepoke will NOT trigger solenoid on...
// idk WHY...   (0624 --> maybe because of single = instad of double == ??? )


void activate_middle_led (){

   static unsigned long led_on_time = 0;
   static unsigned long led_off_time = 0;

   static unsigned long ITI_start_time = 0;
   static int time_index = 0;
   
   if (start_ITI_M == false){
      
      if (led_state_M == LOW) {
          led_state_M = HIGH;
          led_on_time = millis();
          digitalWrite(port_led_M, led_state_M);
          Serial.print(F("8171:"));
          Serial.println(led_on_time);
          }
      

      if((led_state_M = HIGH) && (millis() - led_on_time > led_on_duration)) {
        led_state_M = LOW;
        start_ITI_M = true;
        ITI_start_time = millis();
        led_off_time = millis();
        digitalWrite(port_led_M, led_state_M);
        Serial.print(F("8170:"));
        Serial.println(led_off_time);
        
      }
   }

   if (start_ITI_M) {
    
       // start_ITI_M = false;
       // ^changing state here will enable the following if clause Just ONCE
       // because duration is involved, need to check the if clause multiple times!! (due to nature of microprocessors)

       if ((millis() - ITI_start_time) >= wait_interval_M[time_index]) {
           start_ITI_M= false;
           time_index += 1;

           if (time_index >= NUM_TIMES) {
               time_index = 0;
               }

           activate_random_gen = true;
           select_port = random_generator();

          }
      }  
}


void activate_middle_solenoid(){
  
    static unsigned long solenoid_on_time = 0;
    static unsigned long solenoid_off_time = 0;
    
    // valid poke is when mouse responds while LED is turned on
    
    if (led_state_M == HIGH) {
      
      if (poke_in_M && valid_input_M) {   // if valid_input is true
          sol_state_M = HIGH;
          valid_input_M = false;
          solenoid_on_time = millis();
          digitalWrite(port_solenoid_M, sol_state_M);

          Serial.print(F("8271:"));
          Serial.println(solenoid_on_time);
          }

      if ((sol_state_M == HIGH) && (millis() - solenoid_on_time > solenoid_on_duration)) {
          sol_state_M = LOW;
          solenoid_off_time = millis();
          digitalWrite(port_solenoid_M, sol_state_M);

          Serial.print(F("8270:"));
          Serial.println(solenoid_off_time);

          }
          
       if (poke_in_M == false){   //later change to ! after logic works
          valid_input_M = true; 
        
          }    
      }

    // WITHOUT else if CLAUSE BELOW, FOLLOWING BUG OCCURS: 
    // when mouse pokes its head just before the led turns off and the solenoid turns on to dispense water, 
    // if the solenoid duration goes over the point of time at which LED turns off, 
    // then the solenoid is kept at HIGH indefinitely until the port LED turns on again 
    // (b/c the solenoid only turns off when LED is on)  ^ check if conditional logic above 
 
    // ** (led_on_time + solenoid_duration > led_off_time) ** 
    
    // experiment this by changing the duration of the solenoid reward (increase to see more effect) & 
    // poking your finger just before the LED turns off 
    
    else if (led_state_M == LOW) {
       if (sol_state_M == HIGH){
          sol_state_M = LOW;
          solenoid_off_time = millis();
          digitalWrite(port_solenoid_M, sol_state_M);

          Serial.print(F("8270:"));
          Serial.println(solenoid_off_time);
        
       }

       // 09/15/19 EDIT: 
       // If valid_input_L is trapped as FALSE state because poke out didn't occur within the "LED on window",
       // toggle to TRUE once head pokes out! 
      
       if (poke_in_M == false){  
          valid_input_M = true;
      
          }
       
      
    }
            
  }
