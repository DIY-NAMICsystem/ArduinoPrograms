/*--------------------------------------------------------++
||             TRIAL_INITIATED_REWARD - PART 1            ||
++--------------------------------------------------------*/


/*
 * PARADIGM: TRIAL_INITIATED_REWARD - Part 1
 *
 * DESCRIPTION: Refer to Logic Flow Diagram for more detailed information
 *
 *              1. All three lights on to indicate trial can be initiated
 *              2. Poke in Middle Port initiates Trial
 *              3. Left/Right Port gets activated
 *              4. Valid Poke in Active Port gets reward + LED turns off
 *              5. Invalid Poke turns LED off (no reward)
 *              6. LED stays on until mouse pokes
 *              7. ITI average of 45s
 *
 *
 * KEY CHARACTERISTICS: NO Delay Window
 *                      NO Omission Trials (Cue stays on until response)
 *                      Reward in L/R port
 *                      ITI: average of 45 seconds
 *
 * PUSH BUTTON BEHAVIOR: single short push toggles solenoid valve operation
 *                       push and hold (for 2s) toggles LED operation
 *
 * EVENT CODE STATUS: Compatible
 *
 * EDIT HISTORY:
 *     9/15/19: Added "valid_input" functionality so that mice actually need to POKE to get reward
                (instead of being lucky to "predict" which port will be on)
                (this functionality doesn't really matter in TIR - Part 1 (since no delay window present))
 *
 * THINGS I LEARNED:
 *
 *  1) Don't use function calls within other functions to switch between states
 *      (If you do so, the function call will be forever stuck in a limbo state unless a state changes)
 *      (Also, you won't be able to check for duration expirations ex: led duration / solenoid duration etc.)
 *    --> Always use boolean states and millis() to activate the next state
 *
 *  2) Use two nested if statements 'capture' a state (especially critical for setting timers)
 *      (I guess I don't have to use nested if statements if I use state machines by considering
 *       every single component state + boolean state, but haven't tried that yet. )
 *
 *  2.b) Always toggle states from the if statement inside if statement IF you want to
 *        'capture' a state. (so that a particular state only gets evaluated once)
 *
 *  3) Using counters complements immensely in state changes
 *     (ex.) If I want to change state after the '1st' or the 'nth' event
 *
 *  4) Using counters and resetting them at certain points before/after a state will help me
 *    identify the # of events within a certain state frame
 *     ex) 1st counter reset when trial window STARTS --> print out counter results --> 2nd counter reset before trial window ENDS
 *         --> will be able to evaluate the number of events DURING trial window
 *
 *  Finally) ALWAYS REMEMBER THAT PROGRAMS RUN LINE BY LINE (in a serial manner)
          --> This tip will be helpful in determining at which point to reset variables
 *
 *
 *  NOTE: Counters get Double Colons (::) (for analysis in pandas)
 *      (1st column -> timestamp / 2nd column -> counter)
 *
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

String paradigm = "TRIAL_INITIATED_REWARD_1";

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
