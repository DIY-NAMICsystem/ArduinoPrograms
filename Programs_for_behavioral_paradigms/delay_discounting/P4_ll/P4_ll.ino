 /*-------------------------------------------------------------------------++
||    DD_P4_ll (large reward port introduced + with Force Choice Trials)    ||
++--------------------------------------------------------------------------*/



/*
 * 05/30/2021 Update: add comments 
 * 
 * 11/21/2020 Update: Updated event codes & window names 
 * 
 * 11/09/2020 Update: Reorganized the code and comments 
 * 
 * 10/29/2020 Update: debugged m_port_operate & finalized the code  
 * 
 * 10/15/2020 Update: added the trial_type_array to ensure exactly 2 out of 20 trials are FC
 * 
 * 10/8/2020 Update: added large reward port + forced choice (FC) + free choice trials (where both L and R port turn on during the trial window)
 * 
 * 1/15/2020 Update (JHL): Included # of incorrect poke counts during trial window
 * (when reponse ports light up)
 *
 * PARADIGM: Delay Discounting 
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
 *
 * COPYRIGHT: SC/JHL/ Nautiyal Lab
 *            + Open Source Arduino Forum
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
#include "m_port_operate.h"  
#include "l_port_operate.h" //used in Forced Choice (FC) trials
#include "r_port_operate.h" //used in Forced Choice (FC) trials

String paradigm = "DD_P4_ll_vf";  // ll = left large (left port is the large reward port) 

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

    // initialize initiate_new_trial to true to start program
    initiate_new_trial = true;

    // initiate random_idx to pick the first idx for Inter-Trial Interval
    random_idx = random_iti();
    
    //randomize the trial_type array to randomize the order of free choice and forced choice trials 
    randomize_trial_type_array();

    // FOR DEBUGGING PURPOSES: 
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

    // Once begin_new_trial (in begin_trial.h) finishes running, should be right HERE!
    // Next Step is to pick the activation port!!!

    // NEED TO RESET current_port AT ONE POINT IN CODE (current_port = 0), 
    // SO THAT below if statements don't get evaluated!!!

    if (current_port == 1) {      // a FC trial with left port on (large reward) 
      // delay(1);
      activate_left_led();
      activate_left_sol();
      }

    else if (current_port == 2) { // a FC trial with right port on (small reward) 
      // delay(1);
      activate_right_led();
      activate_right_sol();
      }
      
    else if (current_port > 2) {  // a free choice P4 trial with both ports on 
      // delay(1);
      activate_middle_led();
      activate_middle_sol();
      }
}

// * * * * * * * * * * * L O O P * * * * * * * * * * * * * * * *
