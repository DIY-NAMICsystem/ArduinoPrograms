/*--------------------------------------------------------++
||                   CONTINUOUS_CUE_TRAINING              ||
++--------------------------------------------------------*/

/*
 * PARADIGM: CONTINUOUS_CUE_TRAINING (NO VOID WINDOW)
 *
 * DESCRIPTION: REWARD IN CUE ACTIVATED PORT FOR EVERY RESPONSE (POKE)
 *
 *              1. Random generator selects a random port to activate LED
 *              2. Cue (LED) is turned on in the selected port for x seconds (led_on_duration)
 *              3. Mouse receives reward every time poke in activated (LED on) port
 *              4. No void window (every poke counts)
 *              5. ITI (between each LED on trial) is 50 ms (close to zero)
 *              6. After ITI expires, new random generator selects a random port
 *              7. Random generator does NOT exclude previous port (single port can be selected multiple times in a row)
 *              8. New trial begins
 *
 *
 * KEY VARIABLES: led_on_duration; in "global_variables.h"
 *                solenoid_on_duration; in "global_variables.h"
 *                wait_interval_L/M/R; in "global_variables.h" (for ITI)
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
 *   07/09/19 Changed baud rate to 115200
 *
 *   07/10/19 Changed code so that CS is ON continuously and mouse receives reward every time it head pokes (only when CS is ON)
 *          New valid_input can be initiated only after mouse head pokes out (valid input dependent on head out)
 *          Fixed bug of a special case when solenoid is turned on indefinitely (see notes in l_port_operate.h)
 *          * NO VOID WINDOW *
 *   
 *   09/15/19 Solved Edge case for "valid_input_L/M/R" boolean states getting "trapped"
 *            (See Edits in l/m/r_port_operate)
 *   
 *
 * COPYRIGHT: JHL/ Nautiyal Lab
 *            + Open Source Arduino Forum
 *
 */


#include "global_variables.h"
#include "random_generator.h"
#include "IR.h"
#include "push_button.h"
#include "l_port_operate.h"
#include "m_port_operate.h"
#include "r_port_operate.h"

String paradigm = "CONTINUOUS_CUE_TRAINING";

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

    select_port = random_generator();

}

// * * * * * * * * * * * S E T U P * * * * * * * * * * * * * * *

// * * * * * * * * * * * L O O P * * * * * * * * * * * * * * * *

void loop() {

    // activate_button();
    record_IR();

    if (select_port == 1) {
      activate_left_led();
      activate_left_solenoid();

      }

    else if (select_port == 2) {
      activate_middle_led();
      activate_middle_solenoid();

      }

    else {
      activate_right_led();
      activate_right_solenoid();


      }
}

// * * * * * * * * * * * L O O P * * * * * * * * * * * * * * * *

// * * * * * * * * * * * * * * * * CUTOFF LINE BTW OLD AND NEW  * * * * * * * * * * *
