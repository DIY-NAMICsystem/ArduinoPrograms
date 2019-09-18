/*--------------------------------------------------------++
||                   PORT_HABITUATION                     ||
++--------------------------------------------------------*/


/*
* PARADIGM: PORT_HABITUATION (MULTI_BTN)
*
* DESCRIPTION: NOSE POKE INTO PORT TRIGGERS SOLENOID REWARD (for x seconds) IN THAT PORT ONLY
*              Ex) Nose Poke into Port A triggers solenoid reward in Port A
*
* KEY VARIABLES: sol_reward_DUR; in "global_variables.h"
*                holdTime; in "global_variables.h" (for buttons)
*
* PUSH BUTTON BEHAVIOR: single short push toggles solenoid valve operation
*                       push and hold (for 2s) toggles LED operation
*
* EVENT CODE STATUS: Compatible
*
* EDIT HISTORY:
*   06/03/19 - new eventcode system
*       _ _ _ _ _ (5 digit code)
*     1. L,M,R  (0, 1, 2) // 2. Components - IR, LED, solenoid: (0, 1, 2) //
*     3. Filler (7) // 4. Filler (7) // 5. State - on, off (0, 1)
*
*   06/06/19 - added new button functions for initial box testing
*
*   06/17/19 - standardized global variable names
*   06/17/19 - added push_button functionality (single click vs. hold)
*          --> allows testing of output components (solenoids + LEDs) with single input (button)
*
* COPYRIGHT: JHL/ Nautiyal Lab
*            + Open Source Arduino Forum
*
*/

#include "global_variables.h"
#include "IR.h"
#include "solenoid.h"
#include "push_button.h"

String paradigm = "PORT_HABITUATION";
// * * * * * * * * * * * S E T U P * * * * * * * * * * * * * * *

void setup() {

  // INPUT_PULLUP unnecessary because I've externally soldered 10K resistor
  pinMode (button_pin, INPUT);

  // solenoids initialization
  for (byte i = 4; i <=6; i++) { pinMode(i, OUTPUT);}

  // LEDs initialization
  for (byte i = 8; i <=10; i++) { pinMode(i, OUTPUT);}

  // IRs initialization
  for (byte i = 11; i <=13; i++) { pinMode(i, INPUT);}

  Serial.begin(115200);


  Serial.print("Paradigm:");
  Serial.println(paradigm);

  Serial.print("reward_in_ms:");
  Serial.println(sol_reward_DUR);

}

// * * * * * * * * * * * S E T U P * * * * * * * * * * * * * * *

// * * * * * * * * * * * L O O P * * * * * * * * * * * * * * *

void loop() {

  record_IR();
  solenoid_on();
  activate_button();

}

// * * * * * * * * * * * L O O P * * * * * * * * * * * * * * *
