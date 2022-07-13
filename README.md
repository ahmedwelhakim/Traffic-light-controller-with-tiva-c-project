# Traffic-light-controller-with-tiva-c-project
## Description:
This was a project for embedded c course. It is a traffic light controller project applied on tiva c Ek-tm4c123gh6pm using Code Composer IDE.

## Project Description:
CSE 316/318 Project
Traffic Light Controller
### Overview
The goal of this project is to design a traffic light control system. The system contains simply
two traffic lights. One allows cars to move from north to south, and the other one allows cars to
move from east to west. Beside each traffic there is also a pedestrian traffic light. The
pedestrian has to press on a button to have his light green to cross the street safely.
### Goals
By the end of this project you have to master the following:
1. Timers: You will be using at least two timers to configure the span of the traffic lights.
2. GPIO: You will be using LEDs as outputs, and push buttons as input.
3. Interrupts: You will use interrupts also in this project for the push buttons and timers.
### Milestones
#### 1. Set the normal traffic Light
Use one of the timers to have the two car traffic lights working. The traffic light shall stay
GREEN for 5 seconds, then YELLOW for 2 seconds, then turns RED. When one of the
traffic lights is set to RED the other one has to go GREEN exactly after 1 second. The
same sequence then is repeated again.
GREEN : 5 seconds
YELLOW: 2 seconds
Then RED.
Wait 1 second, then start the sequence on the other traffic.
#### 2. Implement the pedestrian Traffic Light
Use two push buttons and 4 LEDs for this system. There will be two pedestrian traffics,
each with a push button and 2 LEDS: GREEN and RED. Whenever a pedestrian presses
the button, the traffic light that is green shall be interrupted, and the pedestrian traffic
light will be green for 2 seconds. Then it will be back to RED and the traffic light that was
interrupted will resume from when it was paused.
Example: If the car traffic light was green for 2 seconds and interrupted it will then
resume the remaining 3 seconds to finish the 5 seconds.

BONUS PART :
1) Handle the case if two pedestrians pushed the button together in two different
traffics.
2) Handle the case if the same button was being pressed more than one time during the
same period of pedestrian crossing. (Period of pedestrian crossing is from when the
button is pressed for the first time till the pedestrian traffic gets back to RED again.)
3) Handle the case to delay the request of the pedestrian to cross if the button was
pressed after 1 second from the end of the Period of pedestrian crossing.
#### 3. UART ( Bonus )
Send the current state of the whole system via UART whenever the system changes its
state. The possible states for example are : CARS NORTH SOUTH, CARS EAST WEST,
PEDESTRIAN NORTH SOUTH, PEDESTRIAN EAST WEST.

