/*--------------------------------------------------------++
||                   Random Generator                     ||
++--------------------------------------------------------*/


// Used RECURSION to prevent multiple port activation in a row
// (exclude previous port)
int random_generator(){

   if (activate_random_gen) {
      current_port = random(1, 4);  // picks a number betwwen 1, 2, 3
//      Serial.println(prev_port);

      if (current_port == prev_port){
        random_generator(); // trying out recursion --> hopefully no stack overflow error occurs...
      }

      //Serial.println("random");
      activate_random_gen = false;

      }

  return current_port;
}
