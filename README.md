# audio-video-sketch-1

This repository contains the files and diagrams for a video installation based on arduino. 

- Arduino sketch
- Connection diagram
- Photos
- Design notes

# Concept

The projects uses the TV-Out library to generate a compoisite video signal for an NTSC video monitor

A rotating plate equiped with a stepper motor and a rottary encoder allows the arduino sketch to precisely control a sequebnce of movements.
On top of the rotating plate, a bunch of carbon contacts will be connecting 5V to several digital inputs. 

the encoder value (angular position of the plate) will be translated into the x coordinate in the screen (horizontal position)
Each active carbon is asociated to a y value (vertical position) on the screen. 
This way, the rotation of the plate, with the adition of a carbon painted surface (paper) will generate some visuals.

# Requirementas

TV-Out
Rotary Encoder
Stepper control
Analog in to read values from the piezoelectric contact microphone

