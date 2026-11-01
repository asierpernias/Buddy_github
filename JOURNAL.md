**Note: All the photos are in Screenshots.md, so here you will only see the number of the photo.**

Session 1 - 17/10/2026 - 1h

To start this new project I set up the KiCad project. For now I only added the MCU I'm going to use, the XIAO ESP32-C3, mainly because it makes it easy to manage a battery (3.7 V). For the screen, after some research I decided on a Waveshare 2 inch LCD display because of the amount of documentation I could find about it. Since this display does not have a symbol in KiCad, I created a custom one. It was my first time with the KiCad symbol editor, but it was pretty easy to understand how it works (1). At the end, I just routed the MCU to the screen (2).

Session 2 - 17/10/2026 and 18/1S0/2026 -S 1.5h

First of all, I searched for the IMU and the button (a lateral one, in the end) in the JLCPCB component library, to be sure I would be able to get them on the PCB during assembly. After that, and because I wanted to make sure the symbols I was going to use were correct, I found out about [easyeda2kicad](https://github.com/uPesy/easyeda2kicad.py), so I installed it and used it to transform the JLCPCB data into something I could use in KiCad. Then I routed the two new components to the pins of the XIAO (photos 3 and 4). In the case of the LIS2DH12TR, I also added its pull-up resistors for the I2C connection (5). My next steps will be to set the footprints, finish solving the last ERC errors and start working on the PCB.

Session 3 - 18/10/2026 - 2h

Not a lot to say, simply added the footprints, solved a few errors with the custom ones not being there (just ended up restarting KiCad) and did a basic routing of the pcb, added 3v3 and GND layer (6). My next step is to try to optimize more the layout, there's a lot of vias right now; adding a custom silkscreen art, maybie multicolor because I want to try to see how it works; and measuring the components (the time this is beign written I have already recieved the screen) to adapt the PCB to them.

Session 4 - 19/10/2026 to 24/10/2026 - 1h

During this last week I had not had a lot of time to work on Buddy, however, and because of the xiao and the screen arriving after I bought them I took the measures of the screen, changed its footprint to be as accurated as possible (7), modified and re-routed the pcb, added a mounting hole where Ill put a carabin later and finally defined the space I'm having to put the silkscreen art on. (8)

Session 5 - 24/10/2026 - 1h

It has been a hell to get a multicolor silkscreen art on kicad but as always a random Github repo saved the day, the extension itself french but after a lot of suffering and a translator in the other hand I managed to get a picture in the PCB. (9)

Session 6 - 24/20/2026 to 01/11/2026  - 30min

One week more school has not enabled me to work during a continuos time on the only thing I have left to finish the project, doing the code and trying it on the screen and esp32 I have at home. Moreover, my laptop was broken during a few days because of a reason I still cant figure out so I had to do part of the code on another laptop that couldnt track the time. To be honest the time I spent this week on the project was far more than 30 minutes since those where only the time soldering the esp32 pins and trying the code on the microcontroller but it has been so chaotic that I'm not even sure how much time I ever spent apart from that. The last thing I have left is to upload the screenshots (that I have been storing on my laptop) and writting a proper readme