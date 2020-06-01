

int random_req(){

   if (get_random_req) {
      current_req = random(2,7);  
      }
      // Serial.print("port num: ");
      // Serial.println(current_port);

      get_random_req = false;

      return current_req;
      }

int random_iti(){

    if (get_random_iti){
        random_idx = random(0, 12); // number from 0 to 11  (12 values)
                                    // (random index value to use in the array)

    }

    get_random_iti = false;

    return random_idx;


}
