**Note: All the photos are in Screenshots.md, so here you will only see the number of the photo.**

Session 1 - 17/10/2026 - 1h

To start this new project I set up the KiCad project. For now I only added the MCU I'm going to use, the XIAO ESP32-C3, mainly because it makes it easy to manage a battery (3.7 V). For the screen, after some research I decided on a Waveshare 2 inch LCD display because of the amount of documentation I could find about it. Since this display does not have a symbol in KiCad, I created a custom one. It was my first time with the KiCad symbol editor, but it was pretty easy to understand how it works (1). At the end, I just routed the MCU to the screen (2).

Session 2 - 17/10/2026 and 18/10/2026 - 1.5h

First of all, I searched for the IMU and the button (a lateral one, in the end) in the JLCPCB component library, to be sure I would be able to get them on the PCB during assembly. After that, and because I wanted to make sure the symbols I was going to use were correct, I found out about [easyeda2kicad](https://github.com/uPesy/easyeda2kicad.py), so I installed it and used it to transform the JLCPCB data into something I could use in KiCad. Then I routed the two new components to the pins of the XIAO (photos 3 and 4). In the case of the LIS2DH12TR, I also added its pull-up resistors for the I2C connection (5). My next steps will be to set the footprints, finish solving the last ERC errors and start working on the PCB.