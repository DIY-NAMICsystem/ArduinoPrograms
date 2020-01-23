/*--------------------------------------------------------++
||                   Random Generator                     ||
++--------------------------------------------------------*/

int random_generator(){

   if (activate_random_gen) {
      select_port = random(1, 4);
      
      //Serial.println("random");
      activate_random_gen = false;

      }

  return select_port;
}
