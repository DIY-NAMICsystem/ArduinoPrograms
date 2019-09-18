/*--------------------------------------------------------++
||             TRIAL_INITIATED_REWARD - PART 3            ||
++--------------------------------------------------------*/



/*
 * PARADIGM: TRIAL_INITIATED_REWARD - Part 3
 *
 * DESCRIPTION: Refer to Logic Flow Diagram for more detailed information
 *
 *              1. All three lights on to indicate trial can be initiated
 *              2. Poke in Middle Port initiates Trial
 *              3. Delay of x seconds until Left/Right Port gets activated
 *              4. Valid Poke in Active Port gets Reward in Middle Port! + LED turns off
 *              5. Invalid Poke turns LED off (no reward)
 *              6. y second timeout for LED (Omission Trial)
 *              7. ITI average of 45s
 *
 *
 * KEY CHARACTERISTICS: Delay Window Present
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
 *
 * 0819 UPDATE: 1) Deliver Reward in Middle Port (instead of Left or Right Port)   x
 *              2) Time Out Period of 5 seconds (after the LED goes on)            x
 *                  - (If 5 Seocnds expire, turn light off --> Omission Trial
 *                  - Differentiate between Omission Trial and an Invalid Trial
 *                       with event codes
 *
 *              3) Delay between trial initiation and valid trial                  x
 *
 *
 *              4) IT IS VERY IMPORTANT TO RESET SOME VALUES TO NULL STATE (some_var = 0
 *                 Otherwise, can lead to unexpected results since a variable ALWAYS holds that value until told otherwise!!
 *                       ex) current port --> it will always be a 1 or 2, and thus keep going into the loop!!
 *                       ex) counter variables --> need resetting so that it can evaluate a certain condition
 *
 * 09/16/19:    1) Make sure to RESET the port counters! (before the start of each major segment)
 *                 Counters MUST be resetted after each counter print_out! (for next segment)
 *                     (ex: iti / trial window / delay window etc.)
 *              2) "valid poke" should also be the FIRST poke after head out (just like invalid pokes)
 *                     (No need to set valid_input L/R booleans etc. - just work with counters!)
 *
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
#include "begin_trial.h"
#include "push_button.h"
#include "l_port_operate.h"
#include "r_port_operate.h"

String paradigm = "TRIAL_INITIATED_REWARD_3";

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

    // initialize initiate_trial_window to true to start program
    initiate_new_trial = true;

    // initiate random_idx to pick the first idx for Inter-Trial Interval
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

    // NEED TO RESET current_port AT ONE POINT IN CODE,
    // SO THAT below if statements don't get evaluated!!!
    // (otherwise, current_port will always be either 1 or 2 --> leading to unexpected results!)

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
  
}

// * * * * * * * * * * * L O O P * * * * * * * * * * * * * * * *
