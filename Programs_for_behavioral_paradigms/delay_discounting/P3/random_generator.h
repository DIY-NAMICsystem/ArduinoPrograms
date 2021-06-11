/*--------------------------------------------------------------++
||   Generate Random Values for Port Assignment and ITI length  ||
++--------------------------------------------------------------*/

// determines trial type 
int random_port(){

   if (get_random_port) {
      current_port = random(55, 56);  // all choices lead to the same trial in this case 
                                      // LEAVE 0 for null value (needed for resetting)
      }
      
      // FOR DEBUGGING PURPOSES: 
      // Serial.print("port num: ");
      // Serial.println(current_port);

      get_random_port = false;

      return current_port;
      }


// determines ITI length 
int random_iti(){

    if (get_random_iti){
        random_idx = random(0, 12); // number from 0 to 11 (12 values)
                                    // (random index value to use in the array)
                                    // array with ITI lengths in globals_time.h 

    }

    get_random_iti = false;

    return random_idx;


}
