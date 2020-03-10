/*--------------------------------------------------------++
||                   Random Generator                     ||
++--------------------------------------------------------*/


int random_port(){

   if (get_random_port) {
      current_port = random(1, 3);  // picks a number betwwen 1, 2
                                    // 1 --> Left PORT
                                    // 2 --> Right Port
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
