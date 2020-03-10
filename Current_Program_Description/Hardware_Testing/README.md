
# All Component Testing (Solenoid Valves + LEDs + IRs)


### Simple Description

- Cue light in each port will turn on sequentially and stay on until a poke is made.
- Poke into the lit port will trigger the solenoid for 360ms (x5 the normal dispensing time), allowing for patency check of needles and turn off the light.
- This allows testing for all three components (LED / IR / solenoid) since solenoid is activated upon correct trigger from the IR. For example, if an IR (input) is malfunctioning or misplaced then the, light (outputs) are not triggered


### Objectives

- To test ALL the components (LED / IR / solenoid valves) in the cage

### Use Cases

- To troubleshoot components (LEDs / IR / solenoid valves)
