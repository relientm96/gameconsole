# Gane Console Project

A game console project on a self made embedded system.
1. Designed PCB in Altium Designer
2. Programmed in AVR Studio and C language
3. Uses SPI for serial communication between microcontroller peripheral devices

This was done on an 8 bit AVR microcontroller ATMEGA16 chip.
Documentation: https://www.gme.cz/data/attachments/dsh.958-112.1.pdf

# Menu Scroll Through
Buttons navigating through game console. Timer implemented on welcome screen.
![](images/menuScrollThrough.gif)

# Brightness PWM:
Controlled using fast PWM Mode on ATMEGA16 chip
![](images/pwmBrightness.gif)

# Games:

## Flappy Bird
Simple Version with obstacles only from the bottom
![](images/flappybirdexp.gif)

## Pong
Simple Pong Game with two programmed AI.
![](images/pongDemo.gif)

## Guess
1. Three Options are given, one will be right.
2. If right answer selected, you move on.
3. If wrong answer selected, you go into Monty Hall Mode (one wrong answer is removed giving you a second chance)
![](images/guessGame.gif)

## Etch A Sketch
A Digital implementation of the traditional etch a sketch game
![](images/etchASketchDemo.gif)

# Front View:
![](images/front.jpg)

# Back View:
![](images/back.jpg)


