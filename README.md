# Electric_Skateboard_with_Arduino

## Table of Contents
* [Overview](#overview)
* [User Guide](#user-guide)
* [Complexities](#complexities)
* [Software Libraries Used](#software-libraries-used)
* [Diagram](#diagram)

## Demo
[![DEMO1](https://img.youtube.com/vi/OCLN9xIwYrY/default.jpg)](https://youtu.be/OCLN9xIwYrY)
[![DEMO2](https://img.youtube.com/vi/8VLlF3EO4Mk/default.jpg)](https://youtu.be/8VLlF3EO4Mk)

## Overview
I made an electric skateboard with a motor that has bluetooth connectivity to my phone which controls the speed of the skateboard. The baseline version of the electric skateboard lets a user control the speed with their phone using bluetooth. When the bluetooth gets disconnected, the motor will gradually stop and wait until the bluetooth connection gets recovered. 

## User Guide
A user will use their phone and bluetooth with an app called [ArduinoBlue](https://sites.google.com/stonybrook.edu/arduinoble/).

When the user moves a joystick up, it will send a signal to the arduino and increment the speed variable. Likewise, when the user moves back the joystick middle or down, it will decrement the speed variable.


## Hardware Components
* Computing
  * Elegoo UNO R3

* Inputs
  * Lipo battery 
  * HC-11 Bluetooth Module
  * 80A ESC to control the speed

* Outputs
  * Motor C6374

![IMG_0281](https://user-images.githubusercontent.com/83580034/187519442-6ffd5966-eae9-48bb-a6e9-f148e48b5653.jpg)

## Complexities

1. Used HM-11 Bluetooth Module to receive the inputs: moving fast, slow, and breaking.
2. Used ESC to control the speed.
3. Created a safe system when bluetooth gets disconnected. 

## Software Libraries Used
I used:

```#include<Servo.h>``` and ```#include <SoftwareSerial.h>```.

```#include<Servo.h>``` is to send a pwm signal easily, and

```#include <SoftwareSerial.h>``` is to get a received signal from a bluetooth module.


## Diagram
<img src="https://user-images.githubusercontent.com/83580034/187093401-effa4067-e511-4470-926c-9e6d5f26de69.jpg" width="700">

### State Machine Diagram

<img src="https://user-images.githubusercontent.com/83580034/187093948-5761575a-4be2-48e4-8ffc-d66890491b71.jpg" width="1000">
<img src="https://user-images.githubusercontent.com/83580034/187093990-e35dcde0-2507-4408-a344-2bfcdb4e1098.jpg" width="1000">

