 /*--------------------------------------------------------++
||             NEW_P5 (delay_duration = 1ms)              ||
++--------------------------------------------------------*/



/*
 *
 *
 * PARADIGM:
 *
 * DESCRIPTION: Refer to Logic Flow Diagram for more detailed information
 *
 *              1.
 *              2.
 *              3.
 *              4.
 *              5.
 *              6.
 *              7.
 *
 *
 * KEY CHARACTERISTICS:
 *
 *
 *
 *
 * PUSH BUTTON BEHAVIOR: single short push toggles solenoid valve operation
 *                       push and hold (for 2s) toggles LED operation
 *
 * EVENT CODE STATUS: Compatible
 *
 * EDIT HISTORY:
 *
 * COPYRIGHT: JHL/ Nautiyal Lab
 *            + Open Source Arduino Forum
 *
 *  ## CHANGED IN G5 (group 5)
 * NOTES::: automatically subtracts one from the final count for relevant windows!!
 *     1) incorrect pokes before trial initiation
 *     2) Pokes during the trial window --> Remember that P5 DOES NOT have this (instead we have the omission trial!!)
 *
 * FIX ONLY (CODE: xx29)
 *
 *
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

String paradigm = "G5_P5.5_v2";

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
    // pinMode (9, INPUT);  // modified pin #s
    // pinMode (11, INPUT); // modified pin #s
    // pinMode (13, INPUT); // modified pin #s

    Serial.begin(115200);
    Serial.print("Paradigm:");
    Serial.println(paradigm);
    
    Serial.print("Trial_Duration:");
    Serial.println(led_trial_duration);
    Serial.print("Delay_Window:");
    Serial.println(delay_duration);

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
      // delay(1);
      activate_left_led();
      activate_left_sol();

      }

    else if (current_port == 2) {
      // delay(1);
      activate_right_led();
      activate_right_sol();

      }

}

// * * * * * * * * * * * L O O P * * * * * * * * * * * * * * * *
