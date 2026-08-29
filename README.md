# <code style="color : green"> 5776V Override (Harbor Bot) </code>

## <code style="color : green"> Cascade </code>
### <code style="color : greenyellow"> Variables </code>

<code style="color : orange">**bool cascadePressed**</code> *State boolean to detect if cascade control was just pressed*

<code style="color : aqua">**int cascadeState**</code> *State integer to represent the current state of the cascade (0: cascade stop, 1: cascade up, 2: cascade down, 3: cascade down incrementing)*

<code style="color : orange">**bool chainBarPressed**</code>  *State boolean to detect if chain bar control was just pressed*

<code style="color : aqua">**int chainBarPressed**</code> *State integer to represent the current state of the chain bar (0: chain bar load, 1: chain bar score)*

<code style="color : orange">**bool resetPressed**</code> *State boolean to detect if reset control was just pressed*

<code style="color : aqua">**int resetState**</code> *State integer to represent the current state of cascade reset toggle (0: cascade not resetting, 1: cascade resetting)*

<code style="color : orange">**bool switchPressed**</code>  *State boolean to detect if cascade control switch control was just pressed*

<code style="color : aqua">**int controlType**</code> *State integer to represent the current state of the cascade control (0: manual controls, 1: incrementing PID controls)*

<code style="color : magenta">**std::int32_t chainBarPID_target**</code> *32-bit integer to represent the set target of chain bar's PID*

<code style="color : magenta">**std::int32_t cascadePID_target**</code> *32-bit integer to represent the set target of cacade's PID*

<code style="color : magenta">**float chainBarLoad**</code> *float value to represent the position of the chain bar in its loading state*

<code style="color : magenta">**float chainBarScore**</code> *float value to represent the position of the chain bar in its scoring state*

<code style="color : magenta">**float cascadeIncrement**</code> *float value to represent the position of the chain bar in its incrementing state*

<code style="color : aqua">**int incrementWorks**</code> *Oorja's increment testing integer*

### Functions
<code style="color : greenyellow">**void chainBarEasy(float target)**</code>

Takes in a target value for the position of the chain bar to move to using PID and feeds in a voltage to the chain bar based on PID voltage. Chain bar will repeatedly acquire the voltage and move accordingly until it reaches the target.

<code style="color : greenyellow">**void updateCascade()**</code>

Updates the states of variables *<code style="color : aqua">controlType, resetState, cascadeState</code>* after recieving button input.

<code style="color : greenyellow">**void updateChainBar()**</code>

Updates the states of variable *<code style="color : aqua">chainBarState</code>* after recieving button input.

<code style="color : greenyellow">**void runCascade()**</code>

Based on the values of variables *<code style="color : aqua">controlType, resetState, cascadeState, chainBarState</code>*, the associated commands run:

**<code style="color : greenyellow">controlType</code>** *controls cascade's incrementation type (either manual or incremental PID)*

**<code style="color : greenyellow">resetState</code>** *resets cascade to tared zero position in <code style="color : gold">util.cpp</code> and moves chain bar to <code style="color : magenta">chainBarLoad</code>*

**<code style="color : greenyellow">cascadeState</code>** based on *<code style="color : aqua">controlType</code>*, cascade will either move incrementally based on a certain value or move manually with driver control

**<code style="color : greenyellow">chainBarState</code>** toggles between the chain bar's position to load and score

## Claw
**<code style="color : greenyellow">rollerState</code>** 
Toggles between the roller's state of intaking and outtaking

## Pin From Wall

## Utilities