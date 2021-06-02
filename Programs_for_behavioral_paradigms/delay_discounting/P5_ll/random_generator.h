/*-------------------------------------------------------------------------++
||   Generate Random Values for Port/Trial Type Assignment and ITI length  ||
++-------------------------------------------------------------------------*/


// randomizes the list of trial types so the timing of the FC trials are random 
int randomize_trial_type_array() {
  
    // FOR DEBUGGING PURPOSES: 
    //Serial.println("randomizing"); 
    
    for (int x = 0; x < 50; x++) {   // shuffles the trial_type array 50 times  
      int loc_1 = random(0,20);
      int loc_2 = random(0,20); 
      int temp = trial_type[loc_1];
      trial_type[loc_1] = trial_type[loc_2];
      trial_type[loc_2] = temp; 
    }
    
}

int random_port(){

   if (get_random_port and count < 10) {  // if it's within the first 10 trials 
      current_port = random(1,3);         // picks a number between 1 and 2
                                          // 1 --> Left PORT (FC)
                                          // 2 --> Right Port (FC) 
                                    
    }
    
    // selects a trial type from list of trial types (shuffled); allows exactly 2/20 trials to be forced choice
    else if (get_random_port) {
      
      current_port = trial_type[trial_type_idx];  // picks a number between 1 and 20
                                                  // 1 --> Left PORT FC
                                                  // 2 --> Right Port FC 
                                                  // any other value --> regular trial 
                                                  // LEAVE 0 for null value (needed for resetting)
                                                  
      trial_type_idx = trial_type_idx + 1;        // goes through each index of the shuffled array 
      
      if (trial_type_idx == 20) {                 // if we have gone through the array, re-shuffle it and start indexing from the beginning 
        randomize_trial_type_array();
        trial_type_idx = 0; 
      }
      
    }
      // FOR DEBUGGING PURPOSES
      // Serial.print("port num: ");
      // Serial.println(current_port);

      get_random_port = false;

      return current_port;
  }


// determines ITI length 
int random_iti(){

    if (get_random_iti){
        random_idx = random(0, 12); // number from 0 to 11  (12 values)
                                    // (random index value to use in the array)
                                    // array with ITI lengths in globals_time.h 

    }

    get_random_iti = false;

    return random_idx;


}
