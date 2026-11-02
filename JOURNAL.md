<div align="center">
  <h1>Buddy</h1>
  <h3>Total Time Spent : 7 hours</h3>
</div>

---

### Journal #1 Setting up the project and the screen
Time spent : 1 hour

To start this new project I set up the KiCad project. For now I only added the MCU I'm going to use, the XIAO ESP32-S3, mainly because it makes it easy to manage a battery (3.7 V). For the screen, after some research I decided on a Waveshare 2 inch LCD display because of the amount of documentation I could find about it. Since this display does not have a symbol in KiCad, I created a custom one. It was my first time with the KiCad symbol editor, but it was pretty easy to understand how it works.

<div align="center">

| custom screen symbol |
| --- |
| <img width="534" height="514" alt="Custom Waveshare screen symbol" src="https://github.com/user-attachments/assets/eb4004ad-8fa9-42ab-a6a2-55837f3a15fd" /> |

</div>

At the end, I just routed the MCU to the screen.

<div align="center">

| MCU routed to the screen |
| --- |
| <img width="514" height="371" alt="MCU routed to the screen" src="https://github.com/user-attachments/assets/0ba9ab62-fb2b-4237-ba2e-d56447493469" /> |

</div>

---

### Journal #2 Adding the IMU and the button
Time spent : 1.5 hours

First of all, I searched for the IMU and the button (a lateral one, in the end) in the JLCPCB component library, to be sure I would be able to get them on the PCB during assembly. After that, and because I wanted to make sure the symbols I was going to use were correct, I found out about [easyeda2kicad](https://github.com/uPesy/easyeda2kicad.py), so I installed it and used it to transform the JLCPCB data into something I could use in KiCad. Then I routed the two new components to the pins of the XIAO.

<div align="center">

| button and IMU connected to the XIAO |
| --- |
| <img width="565" height="330" alt="Button and IMU routed to the XIAO" src="https://github.com/user-attachments/assets/affe5aee-0d13-4ea0-9909-681267d29453" /> |
| <img width="824" height="622" alt="Button and IMU routed to the XIAO" src="https://github.com/user-attachments/assets/6d7ba021-11c5-488c-92f0-709dee81800a" /> |

</div>

In the case of the LIS2DH12TR, I also added its pull-up resistors for the I2C connection.

<div align="center">

| I2C pull-up resistors |
| --- |
| <img width="926" height="411" alt="LIS2DH12TR with I2C pull-up resistors" src="https://github.com/user-attachments/assets/761fb263-deb7-474c-bcf0-3f19e8e3e672" /> |

</div>

My next steps will be to set the footprints, finish solving the last ERC errors and start working on the PCB.

---

### Journal #3 Footprints and first PCB routing
Time spent : 2 hours

Not a lot to say, simply added the footprints, solved a few errors with the custom ones not being there (just ended up restarting KiCad) and did a basic routing of the PCB, added 3V3 and GND layer.

<div align="center">

| first PCB routing |
| --- |
| <img width="857" height="569" alt="Basic PCB routing with 3V3 and GND layers" src="https://github.com/user-attachments/assets/023ae969-2e88-489d-a72c-9cc38876f07e" /> |

</div>

My next step is to try to optimize the layout more, since there are a lot of vias right now; adding a custom silkscreen art, maybe multicolor because I want to see how it works; and measuring the components (by the time this is being written I have already received the screen) to adapt the PCB to them.

---

### Journal #4 Adapting the PCB to the real parts
Time spent : 1 hour

During this last week I did not have a lot of time to work on Buddy. However, since the XIAO and the screen had arrived, I took the measurements of the screen and changed its footprint to be as accurate as possible.

<div align="center">

| measuring the screen |
| --- |
| <img width="350" alt="Measuring the screen" src="https://github.com/user-attachments/assets/ca5fd752-ddff-489f-aebe-386829016535" /> |

</div>

I also modified and re-routed the PCB, added a mounting hole where I'll put a carabiner later and finally defined the space I have to put the silkscreen art on.

<div align="center">

| space for the silkscreen art |
| --- |
| <img width="241" height="250" alt="Space reserved for the silkscreen art" src="https://github.com/user-attachments/assets/d450067a-76d5-456b-8e32-de5ecb8c4a58" /> |

</div>

---

### Journal #5 Multicolor silkscreen
Time spent : 1 hour

It has been hell to get a multicolor silkscreen art on KiCad, but as always a random GitHub repo saved the day. The extension itself was in French, but after a lot of suffering and a translator in my other hand I managed to get a picture on the PCB.

<div align="center">

| multicolor silkscreen on the PCB |
| --- |
| <img width="1156" height="823" alt="Multicolor silkscreen art on the PCB" src="https://github.com/user-attachments/assets/37835e2a-c26e-4de4-865c-14fd6628a2d9" /> |

</div>

---

### Journal #6 Firmware and testing
Time spent : 0.5 hours

Another week of school has not allowed me to work in one continuous block on the only thing I have left to finish the project: doing the code and trying it on the screen and the ESP32 I have at home. Moreover, my laptop was broken for a few days because of a reason I still can't figure out, so I had to do part of the code on another laptop that couldn't track the time. To be honest, the time I spent this week on the project was far more than 30 minutes, since that was only the time soldering the ESP32 pins and trying the code on the microcontroller, but it has been so chaotic that I'm not even sure how much time I spent apart from that.

<div align="center">

| testing the code on the ESP32 and the screen |
| --- |
| <img width="500" alt="Testing the code on the ESP32 and the screen" src="https://github.com/user-attachments/assets/d4d5548e-c858-4684-a7e2-a1c645769409" /> |

</div>

The last thing I have left is to upload the screenshots (that I have been storing on my laptop) and write a proper README.
