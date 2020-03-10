

int random_port(){

   if (get_random_port) {
      current_port = random(55, 56);  // picks a number for middle port
                                    // 1 --> Left PORT
                                    // 2 --> Right Port
                                    // 55 --> Middle Port
                                    // LEAVE 0 for null value (needed for resetting)
      }

      // Serial.print("port num: ");
      // Serial.println(current_port);

      get_random_port = false;

      return current_port;
      }

int random_iti(){

    if (get_random_iti){
        random_idx = random(0, 12); // number from 0 to 11  (12 values)
                                    // (random index value to use in the array)

    }

    get_random_iti = false;

    return random_idx;


}
