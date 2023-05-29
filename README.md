# Final-Project-Acceleration-Sensor-Game
This is puzzle 10's Github  

Description: The handheld arduino creates a fun game that can be taken anywhere you want. In order for the user to win, they must shake the arduino up and down for the specified amount of times in five seconds. The first level will be 5 times and the second level will be 8 times. In order for the arduino to detect a motion and add to the count the user must shake the arduino on the y axis at an acceleration of either greater than 20 g or less than -20 g.

Inputs: Button A starts the whole game (needs to be pressed every time you want to play. It also starts a 5 second timer for the player to shake the arduino 18 times. Controls whether or not the game will start. Also controls when the game will end because it starts a timer countdown. Then the Acceleration Sensor is used to start the counter of how many times the user shakes the arduino. Determines the count based on the amount of shakes the user does. The raw ranges are ...

Outputs: Light (Neo-Pixels) once the user wins, the arduino will light up with a sparkle pattern and if the player loses a red arduino will appear. Next a melody will play when the button is pressed, there is a win, or there is a lose. Finally, a voice output will signal to the user, "Next" for the next level or “Game over” if the correct number of shakes is not achieved.
