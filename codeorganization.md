# Code Organization

```
|- 1. main.cpp
|- 2. global.h
|- 3. objects
|  |- 1. common
|  |- 2. pointer
|  |- 3. text
|  |- 4. fpstext
|  |- 5. mousetext
|  |- 6. freeformline
|  |- 7. ripple
|  |- 8. smallcut
|- 4. states (globals)
|  |- 1. common
|  |- 2. score
|  |- 3. vitals
|  |- 4. operation
|- 5. states (tools)
|  |- 1. common
|  |- 2. toolselect
|  |- 3. drain
|  |- 4. forceps
|  |- 5. gel
|  |- 6. healingtouch
|  |- 7. laser
|  |- 8. scalpel
|  |- 9. suture
|  |- 10. syringe
|  |- 11. ultrasound
|- 6. states (enemies)
|  |- 1. common
|  |- 2. smallcut
|- 7. states (patients)
|  |- 1. common
|  |- 2. test
```

## 1 - Main Entrypoint

Graphics settings and basic window settings are set right on startup. Removing the cursor is important as we implement our own pointer. Framerate can be capped or uncapped, good for doing stress tests on different hardware. An instance of GlobalValues is made that will be shared all throughout the app. Think of this as a singleton, but instead you pass it along down the initialization of objects. A global pointer to act as the mouse within the window is also instantiated, to be present throughout the app's life cycle. Optionally, debug texts can be instantiated at this moment as well.

A state is then loaded, be it some state that needs testing or the application's main state, that will then call other states based on player input. The main loop is then started, where actions need to taken following a rigorous order:
- Restart the application's clock, fetching the elapsed time from the last frame
- Set the elapsed time in seconds, as a double, in the global struct
- Poll for window events:
  - Close the window if event received
  - If lost focus, set focus to false on global struct to break input reception
  - If regained focus, set focus to true and restart the clock
  - Mouse updates should only happen when it is inside the window boundaries
- Set whole frame to black to redraw image
- Update inputs, only if there is focus
  - Update mouse position, only if inside borders
  - Check if relevant keyboard keys pressed
- Update states and objects with elapsed time
- Draw states and objects on screen
- Display the frame

## 2 - Global Structure

Holds the following information, along with a getter and setter for each. This information should be available for EVERY object in the code:
- An internal clock for time keeping, to be used by main loop
- The mouse's position relative to the top left corner
- Is the window in focus?
- Should the mouse coordinates be updated?
- Is the mouse button pressed?
- Is the up direction pressed? (defaults to W)
- Is the left direction pressed? (defaults to A)
- Is the down direction pressed? (defaults to S)
- Is the right direction pressed? (defaults to D)
- Is the special button pressed? (defaults to F)

## 3 - Objects

### 3.1 - Common Object

The basic entity inside the code, this is something that will keep an internal state that is updated every frame and is drawn into the screen every frame. Since the common object is a mere abstraction, the update and draw functions are left blank, to be implemented by more specialized objects. The common object also holds some auxiliary functions accessible to all, mostly relating to geometry and linear algebra problem solving. A brief summary of the functions provided:
- Generate a unit vector pointing at a specific angle
- Compute the distance between 2 points
- Compute the angle between 2 vectors
- Solve the quadratic equation Ax^2 + Bx + C = 0
- Find the 0/1/2 points where a line intersects a circle in 2d space
- Convert an integer to a string, padding with zeroes

### 3.2 - Pointer Object

A final entity that is drawn at the mouse's current position, to tell the player where their actions will take place on the screen. Every frame, its position is set to the mouse's position. The draw function is as simple as drawing a circle centered on the mouse's position.

### 3.3 - Text Object

A basic entity that is given a position in 2d space, a color and a size. Since this is rendered with a font instead of a tilemap, the font needs to be loaded when this object is instantiated. The content and color of the text can be updated at will, and there is no need to update its internal state every frame. The position given will be used as the text's center, instead of aligning it to the left/right.

### 3.4 - FPS Text Object

A final entity that inherits from Text Object, its position, color and size are hardcoded since it is only used for debugging purposes. Since the information being displayed changes every frame, the update function is actually implemented to take the moving average of the time elapsed between frames, and using that as a reference when displaying the fps.

### 3.5 - Mouse Text Object

A final entity that inherits from Text Object, its position, color and size are hardcoded since it is only used for debugging purposes. Since the information being displayed changes every frame, the update function is actually implemented to convert the mouse position to a string representation in coordinates "X, Y".

### 3.6 - Freeform Line Object

A final entity representing a linestrip in 2d space. It is given a color and 100 memory slots to store pivot points. There is no need to update the internal state every frame, so only the draw function is implemented, to connect the stored pivot points with straight lines. A few helper functions are provided to add pivots to the internal state:
- Add the current mouse position as a pivot (but only if it's different from the last pivot)
- Add the current mouse position as a pivot twice (but only if it's different from the last pivot)
- Replace the last pivot with the current mouse position
- Replace the last pivor with the current mouse position and add a duplicate of it

### 3.7 - Ripple Object

A final entity representing a circle expanding its radius uniformly over time. It is given a position in 2d space as its center, a color, a total duration D in seconds, an expanding duration E in seconds, a starting radius R, a radius increment RI, and a properties struct. Once created, the circle will expand uniformly from radius R to R+RI, over E seconds. After D seconds, the ripple will despawn. It follows that D must be strictly equal to or larger than E. It is also possible to make a ripple shrink by providing a negative value to RI. The update function simply increments the interal timer, so that the draw function can compute the effective radius based on how much time has elapsed since the ripple's spawn.

### 3.8 - Small Cut Object

A final entity representing a small cut (small line in 2d space). It has a fixed length, so it is given a starting point in 2d space and an angle to render the line in. During instantiation, we compute the unit vector at the given angle and the position for the second point, to ease calculations. We also compute the line equation parameters defined by this line segment, taking special care with vertical lines. Drawing the line is thus trivial since we know both points' coordinates, and there is no need to update it every frame. This object is meant to interact with ripples, computing how much of it is contained inside a ripple so that the game's state can take actions based on that number.

In order to compute such interaction, we can enumerate the 3 ways a line segment's points can be placed in relation to a circle:
- Both points are contained inside the circle
- Neither point is contained inside the circle
- Only one of point A or point B is contained inside the circle

By taking the distance between the ripple's center and each point A and B, we can know which points are contained in the circle by comparing the distance to the radius. The interaction must return a number in the range [0, 1], specifying how much of the line is contained in the circle. For simplicity, we will discard the edge case where neither point is inside the circle, but there is an intersection nonetheless. It thus follows that:
- If both points are contained in the circle, return 1
- If neither point is contained in the circle, return 0
- If only one point is inside the circle, take it as a pivot and compute the distance from it to the circle's edge, return that distance divided by the segment's length

## 4 - States (Globals)

### 4.1 - Common State
### 4.2 - Score State
### 4.3 - Vitals State
### 4.4 - Operation State

## 5 - States (Tools)

### 5.1 - Common Tool State
### 5.2 - Tool Select Tool State
### 5.3 - Drain Tool State
### 5.4 - Forceps Tool State
### 5.5 - Gel Tool State
### 5.6 - Healingtouch Tool State
### 5.7 - Laser Tool State
### 5.8 - Scalpel Tool State
### 5.9 - Suture Tool State
### 5.10 - Syringe Tool State
### 5.11 - Ultrasound Tool State

## 6 - States (Enemies)

### 6.1 - Common Enemy State
### 6.2 - Small Cut Enemy State

## 7 - States (Patients)

### 7.1 - Common Patient State
### 7.2 - Test Patient State
