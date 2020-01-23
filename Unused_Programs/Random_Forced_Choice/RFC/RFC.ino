/*--------------------------------------------------------++
||                  RANDOM_FORCED_CHOICE                  ||
++--------------------------------------------------------*/

/*
 * PARADIGM: RANDOM_FORCED_CHOICE (exclude previous port)
 *
 * DESCRIPTION: REWARD DELIVERED AT CUED (LED ON) PORT
 *
 *              1. Random generator selects a random port to activate LED
 *              2. Cue (LED) is turned on in the selected port for x seconds (led_on_duration)
 *              3. Mouse receives reward if poke in activated (LED on) port
 *              4. Cue goes off
 *              5. New cue turns on in different port (same port doesn't get selected in a row)
 *              6. No ITI between trials
 *
 *              Note: Cue stays on until the mouse makes a response
 *
 * KEY VARIABLES: solenoid_on_duration; in "global_variables.h"
 *                holdTime; in "global_variables.h" (for buttons)
 *
 * PUSH BUTTON BEHAVIOR: single short push toggles solenoid valve operation
 *                       push and hold (for 2s) toggles LED operation
 *
 * EVENT CODE STATUS: Compatible
 *
 * EDIT HISTORY:
 *   06/21/19 Randomized the nose port activation (see random_generator.h)
 *
 *   07/24/19 "initiate_new_trial" is a global variable
 *
 * COPYRIGHT: JHL/ Nautiyal Lab
 *            + Open Source Arduino Forum
 *
 */

#include "globals_main.h"
#include "globals_button.h"
#include "globals_time.h"
#include "random_generator.h"
#include "IR.h"
#include "push_button.h"
#include "l_port_operate.h"
#include "m_port_operate.h"
#include "r_port_operate.h"


String paradigm = "RANDOM_FORCED_CHOICE";

// * * * * * * * * * * * S E T U P * * * * * * * * * * * * * * *

void setup(){

    // randomize the start of the random generator
    randomSeed(analogRead(0));

    pinMode (button_pin, INPUT);

    // solenoids initialization
    for (byte i = 4; i <=6; i++) { pinMode(i, OUTPUT);}

    // LED initialization
    for (byte i = 8; i <=10; i++) { pinMode(i, OUTPUT);}

    // IRs initialization
    for (byte i = 11; i <=13; i++) { pinMode(i, INPUT);}

    Serial.begin(115200);

    Serial.print("Paradigm:");
    Serial.println(paradigm);

    current_port = random_generator();

}

// * * * * * * * * * * * S E T U P * * * * * * * * * * * * * * *

// * * * * * * * * * * * L O O P * * * * * * * * * * * * * * * *

void loop() {

    // activate_button();
    record_IR();

    if (current_port == 1) {
      led_operate_L();
      solenoid_operate_L();

      }

    else if (current_port == 2) {
      led_operate_M();
      solenoid_operate_M();

      }

    else {
      led_operate_R();
      solenoid_operate_R();

      }
}

// * * * * * * * * * * * L O O P * * * * * * * * * * * * * * * *

// * * * * * * * * * * * * * * * * CUTOFF LINE BTW OLD AND NEW  * * * * * * * * * * *
