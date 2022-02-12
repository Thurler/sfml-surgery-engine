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
- Compute the scalar projection of a vector onto another
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

### 3.9 - Glass Shard Object

A final entity representing a small glass shard, usually associated with a small cut. It is represented by a rectangle in 2D space with fixed dimensions, and it aligns itself based on its associated cut's coordinates and orientation - it will center itself along the cut's axis, and protrude outwards at a 90 degree angle. It will keep track of its current position, as well as its original position, should it need to be reset.

In order to give it the illusion of being lodged in, we need to stop drawing the rectangle at the line where the rectangle intersects the cut. However, this should only be done before the shard is fully removed, to avoid having the player manually put it back in. We thus store a flag that tells the object if it must be hidden or not - which will help it calculate its effective height.

Its interaction with the forceps is simply a check if the forceps point lies within the boundaries of the effective rectangle that is protruding outside the wound. We use a simple scalar projection algorithm to check for that, where the projection of that point on 2 adjacent sides of the rectangle must be within the effective width and height.

## 4 - States (Globals)

### 4.1 - Common State

A basic class that extends the functionality of an object to that of a state. Since states are very diverse, there really isn't anything right now in common between all states, but the groundwork is in place if needed.

### 4.2 - Score State

A state that stores the current operation's score, responsible for updating it whenever an event that gives points is triggered. Instead of just applying the pending score directly, we apply it in increments of 9 to maximize the perceived effect of the score gain.

### 4.3 - Vitals State

A state that stores the current operation's vitals, responsible for updating it whenever an event that restores vitals or deals damage is triggered. Two separate vital counters are stored, one that caps at 99 and another with an arbitrary cap up to 400, that cannot be healed and only decremented.

Damage in the immediate gauge is dealt and healed in increments, to create a "rolling" effect. Whenever the immediate gauge reaches 0, a game over state should be signaled.

Damage in the permanent gauge happens in increments along with the immediate one, and should the permanent value drop below 99, it should drag down the immediate's cap with it, so that the immediate gauge cannot heal past the permanent one.

Gauges should be colored yellow whenever they reach the 50% threshold, and red whenever the 25% threshold is reached.

### 4.4 - Operation State

A state that holds information regarding the "operation" play state. It holds pointers to the vital and score states, as well to the current patient's state and the tool selection's state. It can also display a timer and score counter in the corner, to inform the player of the gameplay state.

Since it merely acts as hub for other states to interact with themselves, this state does little more than just hold all the relevant information.

## 5 - States (Tools)

### 5.1 - Tool Select Tool State

The tool selection state is responsible for initializing and holding a pointer to every tool used in the game, and storing what the current tool being used is. It is also responsible for drawing the tool selection wheel, highlighting the current tool for the player.

During the update loop, it checks for pressed keys, and checks against the keys pressed on the last frame. Whenever a key is pressed, but it wasn't pressed in the previous frame, it will trigger a tool swap to that corresponding tool. Special buffers are in place for the diagonal inputs, to avoid deselecting them
whenever the player lets go of the diagonal without full sync between fingers.

Also during the update loop, it should update each tool state on whether they are the currently active tool, making sure to call the replaced tool's deselect function whenever a switch occurs, to make sure the tool's state is reset properly.

### 5.2 - Common Tool State

The common tool state expands upon the common state, adding abstract update and draw functions that take in a special argument - whether the tool is the active one or not. Since the active tool can change every other frame, tools need to be aware when they are no longer the active tool.

The deselect function signals to the tool that it is no longer active, resetting its internal state back to an inactive state.

### 5.3 - Drain Tool State

The drain tool currently does nothing, except for draw a rectangular tube from the cursor to the top of the screen, signaling to the player where the drain is active at.

### 5.4 - Forceps Tool State

The forceps tool simply checks for collisions against grabbable objects in the patient at the current position, and stores the object it collides with, if any. Every frame, if it is holding something, the forceps tool will update that object's position, which might trigger events in that object. Once the forceps lets go of that object, it will fire an event to that object informing it was released, and go back to holding nothing. Whenever the forceps stops being the active tool, it will automatically drop anything it is holding.

### 5.5 - Gel Tool State

The gel tool uses the ripple object to define a circular area around the cursor to be affected by gel, whenever the tool is active. There are major and minor ripples, each with a specific timing and spatial requirement to be spawned, and with different properties.

Major ripples are spawned every 0.1 seconds (6 frames) the tool is active, and minor ripples every 0.01653 seconds (1 frame). The key being, minor ripples are only spawned if the cursor has moved a specific distance away from the previous ripple's center. Both sizes last for the same amount of time, but major ripples have double radius compared to a minor one. Only major ripples will have a healing effect on the patient, one ripple healing 0.2 vitals over its duration.

When updating the ripples, the tool state must also call for the destruction of any expired ripples, freeing up memory in the process. Very important: the ripples are still active when the tool itself is inactive, and must still be drawn until they are expired.

### 5.6 - Healingtouch Tool State

The healing touch tool uses the freeformline object to draw shapes on the screen. The target is a star, but the player is free to draw whatever they like. The tool stores whether it was active in the last frame, and whether it is active now, to know whether it needs to init, process or destroy the current structure.

Initializing the structure will place a pivot wherever the player was pointing at when they clicked. Processing will then happen every other frame, and destroying just zeroes out the pivots.

When processing the new position input, we first wait for the cursor to be sufficiently away from our first base pivot point. When it is, we compute and store a vector from the first pivot to this new position. This will be our current iteration's pivot vector.

After computing the first pivot vector, we wait until the cursor is sufficiently far away from this vector's edge, and whenever it is, we lock in a new vector connecting the tip of your current pivot with the current cursor position.

If the angle between the two vectors is sufficiently large, we lock in our current position as our next pivot point for the freeformline object, and restart the algorithm using this new pivot as our base.

Otherwise, we simply discard the old vector pivot we had, and use our newly computed vector as our pivot. The process will then continue until there is a sudden enough change in the angle between computed pivots.

### 5.7 - Laser Tool State

The laser tool currently does nothing, except for draw an angled rectangular shape from the cursor to the top of the screen, signaling to the player where the laser is active at.

### 5.8 - Scalpel Tool State

The scalpel tool uses the freeformline object to trace the user's raw inputs on the screen, signaling to the player where the scalpel has been active. We simply add a new point to the object every frame.

### 5.9 - Suture Tool State

The suture tool acts much like the healing touch tool in terms of taking the user's input and drawing lines on the screen, taking vector pivots and looking for sudden angle changes. It will also draw for the player the raw input being received, as a small visual aid. While the algorithm is the same, the parameters are ever so slightly different, since the target shape is a zigzag rather than a star.

### 5.10 - Syringe Tool State

The syringe tool has three states it can be in, each with different update and draw properties. The trivial one is when it is the active tool, but with no player input - it just displays the available vials.

Whenever the player clicks one of the vials, the syringe must fill up with whatever is in that vial, so we store how much of it and what it is. The time it takes to fully fill is fixed, and the mouse cursos cannot be updated while the player is drawing liquid from the vial.

If the click was outside the boundaries of all vials, then the syringe will empty itself over time, interacting with whatever is under the cursor. The basic case is stabilizer, which will raise vitals wherever it was injected. Similarly, the mouse cursor cannot be updated while the injection is going on.

### 5.11 - Ultrasound Tool State

The ultrasound tool uses ripples to interact with hidden objects, with a set cooldown between spawns of each ripple. This way, mashing the click button will not spawn multiple ripples. Similarly to the gel tool, this class is responsible for managing the ripples it spawns, destroying them when they have expired.

## 6 - States (Enemies)

### 6.1 - Common Enemy State

A basic class that extends the functionality of a state to that of an enemy. Since enemies are very diverse, there really isn't much common between all enemies, currently only the passive damage and score are applied. A virtual function is used to get how much (permanent) damage per second the enemy should do, and it's applied inside the common's implementation of an apply damage method. A similar flow is used to apply score.

### 6.2 - Small Cut Enemy State

The small cut enemy state is the enemy abstraction of the object small cut, storing its properties that relate to the state, rather than the object itself. These include the HP and damage calculations, as well as handling gel interactions. The damage it takes from a gel's interactions depends on the fraction of the cut that is covered by the gel ripple.

Optionally, the small cut can be associated with another enemy, assumed to be lodged onto the small cut itself. If this association exists, the small cut will not be able to interact with gel ripples until that associated enemy is dealt with.

### 6.3 - Glass Shard Enemy State

The glass shard enemy state is the enemy abstraction of the object glass shard, storing state properties, rather than object properties. This includes score control, what action will be taken when it is dropped, and storing the offset it was grabbed with, to preserve that offset when it is being moved around.

## 7 - States (Patients)

### 7.1 - Common Patient State

Patient states specialize from common states by adding callbacks to tool interactions. The state is aware of the enemies on screen, and must know how to handle the tool interactions with each enemy. It stores and handles interactions with the vital and score states, too.

### 7.2 - Test Patient State

The test patient is the one used to test out various interactions between scenarios, and handles various interactions with the basic tools. Really it's just something simple to test out the code in.
