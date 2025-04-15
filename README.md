# CON-E: Conical Ocular and Navigation - Explorer

CON-E is a computer vision-enabled robotic traffic cone designed to be more than just a passive roadside object. Built during BitHacks 2025, CON-E explores how expressive robotics and assistive autonomy can bring personality and utility to simple infrastructure. CON-E uses a 2-wheel drive system to move, tracks orange-colored objects using a camera and computer vision, plays audio through a speaker, and changes an RGB LED to reflect its mood or internal state.

CON-E was awarded “Best Meme Hack” at BitHacks 2025.

___

### Components

CON-E is built inside a real traffic cone with tightly integrated electronics and 3D printed mounting. The system includes:

#### Electronics & Control

- RGB LED – system state indication
- 6V DC Gearbox Motors (x2) – cone movement
- Webcam – camera input for vision tracking
- L298N Motor Driver – drives motors from ESP32
- Raspberry Pi 4 – computer vision and state logic
- ESP32-S3 Dev Board – motors, RGB LED, and audio control
- DFPlayer Mini and Speaker – audio playback module, voice and sound effects

#### Power

- 9V Battery – powers ESP32 subsystem
- USB Power Bank – powers Raspberry Pi

#### Mechanical and Design

- Traffic Cone – cone body for housing
- 3D Prints - custom designs for base plate and internal hardware housing

___

### Software & Technologies

- C++
- Python
- OpenCV
- ESP-IDF
- VSCode
- Raspberry Pi OS
- Arduino and PlatformIO
- Onshape – CAD design for 3D parts
- Bambu Studio – slicing and printing

___

### What’s Next

This is just the beginning. CON-E is a prototype—an early proof of concept. Future directions include:

- AI and ML integration
- Voice control and speech recognition
- Omnidirectional wheels for improved mobility
- An LCD screen for dynamic facial expressions
- Swarm functionality for multi-cone deployments
- A mobile app for remote control and coordination

___

### Media

#### Meet the Team

<div style="text-align: center;">
  <img src="/media/li.jpg" alt="Li Keller" width="200"/><br/>
  Li Keller
</div>
<br>

<div style="text-align: center;">
  <img src="/media/david.jpg" alt="David" width="200"/><br/>
  Erik David Piolo
</div>
<br>

<div style="text-align: center;">
  <img src="/media/morgan.jpg" alt="Erik David Piolo" width="200"/><br/>
  Morgan Olivia Newton
</div>
<br>

<div style="text-align: center;">
  <img src="/media/sebastian.jpg" alt="Sebastian Ala Torre" width="200"/><br/>
  Sebastian Ala Torre
</div>
<br>

<br>
<img src="/media/group1.jpg" alt="Group Photo 1" width="300"/>
<img src="/media/group2.jpg" alt="Group Photo 2" width="300"/>
<img src="/media/group3.jpg" alt="Group Photo 3" width="300"/>
<img src="/media/group4.jpg" alt="Group Photo 4" width="300"/>

#### Internal Components

<img src="/media/internal-components1.jpg" alt="Internal View 1" width="400"/>
<img src="/media/internal-components2.jpg" alt="Internal View 2" width="400"/>

#### Demo

- [Startup Sound Test](/media/startup-test.mov)
- [Demo Clip 1](/media/demo1.mov)
- [Demo Clip 2](/media/demo2.mov)
