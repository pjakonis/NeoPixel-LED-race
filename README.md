# LED Race Game

[GAMEPLAY VIDEO](https://www.youtube.com/shorts/HLi5Bn_9Hs8)


## Overview
This LED Race Game is an interactive, two-player game designed for microcontrollers, leveraging the FastLED library to control addressable RGB LED strips. Players compete in a simple racing game where they advance their "cars" (represented by LEDs) along the strip by pressing buttons. The game incorporates colorful visual effects, including a rainbow effect for the introduction and a distinctive display for the winning and losing LEDs.

## How It Works
- **Initialization**: When the game starts, an introductory rainbow effect is displayed on the LED strips.
- **Game Start**: The game begins when both players press their respective buttons simultaneously. A traffic light countdown is displayed, transitioning from red to green, to signal the start.
- **Gameplay**: Players press their buttons to advance their cars along the LED strip. Each button press moves the player's car one LED forward. The cars are represented by LEDs lighting up in specific colors (red for Player 1, blue for Player 2).
- **Winning Condition**: The first player to reach the end of the LED strip wins. The game displays a winning effect, flashing the winner's LEDs.
- **Reset**: The game can be reset and started again by pressing both buttons simultaneously.

## Hardware Setup
- Two addressable RGB LED strips connected to specified data pins on the microcontroller.
- Two buttons for player input, each connected to a designated pin.
- The microcontroller runs the provided C++ code, utilizing the FastLED library to control the LED strips.
