/*--------------------------------------------------------++
||             TRIAL_INITIATED_REWARD - PART 2            ||
++--------------------------------------------------------*/


/*
 * PARADIGM: TRIAL_INITIATED_REWARD - Part 2
 *
 * DESCRIPTION: Refer to Logic Flow Diagram for more detailed information
 *
 *              1. All three lights on to indicate trial can be initiated
 *              2. Poke in Middle Port initiates Trial
 *              3. Left/Right Port gets activated
 *              4. Valid Poke in Active Port gets Reward in Middle Port! + LED turns off
 *              5. Invalid Poke turns LED off (no reward)
 *              6. 5 second timeout for LED (Omission Trial)
 *              7. ITI average of 45s
 *
 *
 * KEY CHARACTERISTICS: NO Delay Window
 *                      Omission Trial Present
 *                      Reward in Middle port
 *                      ITI: average of 45 seconds
 *
 * PUSH BUTTON BEHAVIOR: single short push toggles solenoid valve operation
 *                       push and hold (for 2s) toggles LED operation
 *
 * EVENT CODE STATUS: Compatible
 *
 * EDIT HISTORY:
 *    08/19/19  1) Deliver Reward in Middle Port (instead of Left or Right Port)   x
 *              2) Time Out Period of 5 seconds (after the LED goes on)
 *                  -  (If 5 Seocnds expire, turn light off --> Omission Trial
 *                  - Differentiate between Omission Trial and an Invalid Trial
 *
 *              3) Delay between trial initiation and valid trial --> Implement Later
 *
 *    9/15/19: Added "valid_input" functionality so that mice actually need to POKE to get reward
 *              (instead of being lucky to "predict" which port will be on)
 *                (this functionality doesn't really matter in TIR - Part 1 (since no delay window present))
 *
 * COPYRIGHT: JHL/ Nautiyal Lab
 *            + Open Source Arduino Forum
 */




#include "globals_main.h"
#include "globals_button.h"
#include "globals_time.h"
#include "random_generator.h"
#include "IR.h"
#include "begin_trial.h"
#include "push_button.h"
#include "l_port_operate.h"
#include "r_port_operate.h"

String paradigm = "Trial_Initiated_Reward_Part_2";

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
    Serial.print("Paradigm: ");
    Serial.println(paradigm);

    // initialize initiate_trial_window to TRUE to start program
    initiate_new_trial = true;

    // initiate random_idx to pick the first idx for iti_interval
    random_idx = random_iti();


    // Serial.print("idx: ");
    // Serial.println(random_idx);
    // Serial.println(iti_interval[random_idx]);
}

// * * * * * * * * * * * S E T U P * * * * * * * * * * * * * * *

// * * * * * * * * * * * L O O P * * * * * * * * * * * * * * * *

void loop() {

    // activate_button();
    record_IR();
    begin_new_trial();

    // Once begin_new_trial finishes running, should be right HERE!
    // Next Step is to pick the activation port!!!

    if (current_port == 1) {
      delay(1);
      activate_left_led();
      activate_left_sol();

      }

    else if (current_port == 2) {
      delay(1);
      activate_right_led();
      activate_right_sol();

      }

    // EDIT: 9/15/19 - toggle valid_input (one "real" poke (instead of just nose inside port)) to true for next valid poke)
    if (poke_in_L == false){
              valid_input_L = true;
          }

    if (poke_in_R == false){
              valid_input_R = true;
          }

}

// * * * * * * * * * * * L O O P * * * * * * * * * * * * * * * *
