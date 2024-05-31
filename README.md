# Nerdland
![nerdland](/img/nerdland.png)
*Made with* ❤ *by Lore Brosens, Bas Baccarne, Yannick Christiaens & Simon De Boever*   

This repo covers the set-up of the [UGent Campus Kortrijk](https://www.ugent.be/campus-kortrijk/) [Nerdland](https://www.nerdlandfestival.be/) installation. This introduces nerds into 4 domains:
- [**Interaction Design**](#interaction-design):   
Visitors can create their own paramertric design with an Arduino-controlled input device
- [**Computational Design**](#computational-design):   
This device feeds a firefly + grasshopper script that generates patterns in a predefined format
- [**Advanced Manufacturing**](#advanced-manufacturing):   
These shapes are exported as dxf files and laser cutted
- [**Design for Assembly**](#design-for-assembly):   
These personalised fragments can be assembled into a night lamp

These domains illustrate some of the key components of the [Ghent University](https://www.ugent.be/) programs [Machine & Production Automation](https://www.ugent.be/campus-kortrijk/nl/opleidingen/mpa) and [Industrial Design Engineering](https://www.ugent.be/campus-kortrijk/nl/opleidingen/industrieel-ontwerpen)

![live](/img/live.png)

## Interaction Design
### Components
- [Arduino Nano](https://store.arduino.cc/products/arduino-nano)
- [Grove Shield for Arduino Nano](https://wiki.seeedstudio.com/Grove_Shield_for_Arduino_Nano/)
- [Grove Thumbstick](https://wiki.seeedstudio.com/Grove-Thumb_Joystick/)
- [Grove Gesture Sensor 1.0](https://wiki.seeedstudio.com/Grove-Gesture_v1.0/)
- [Grove UltraSonic Ranger](https://wiki.seeedstudio.com/Grove-Ultrasonic_Ranger/)
- [4 arcade buttons](https://www.gotron.be/componenten/schakelmateriaal/schakelaars-en-drukknoppen/arcade-knoppen/lichtgevende-arcade-drukknop-30mm-groen.html)
- [Mini USB Cable](https://www.allekabels.be/usb-mini-kabel/176/4207900/mini-usb-kabel.html?lang=nl-be)
- [Case](https://a360.co/4drFMZX)
- [Joystick](https://a360.co/3WSIDWa)
### Set-up
- Connect the thumbstick to A0
- Connect the gesture sensor to I2C
- Connect the distance sensor to D2
- Connect button 1 to D5
- Connect button 2 to D7
- Connect button 3 to A3
- Connect button 4 to A2 
- Upload the [Arduino code](nerdland.ino)
### Input
- The interface changes the ```thumb stick``` values when the ```first button``` is pressed
- The interface changes the ```gestures``` when the ```second button``` is pressed
- The interfaces changes the ```distance``` when the ```third button``` is pressed
- The interface ```resets``` the values when the ```blue (fourth) button``` is pressed
### Output
- The arduino writes the data to the Serial Port in the folowing format   
  ```x_axis_thumb|y_axis_thumb|x_axis_gesture|y_axis_gesture|distance```

  ![console](img/console.jpg)
      
## Computational Design
- This Serial Data is read by [Firefly](https://www.food4rhino.com/en/app/firefly) and translated into computaional commands in [Grasshopper](https://www.grasshopper3d.com/)
- [This Grasshopper script](grasshopper.gh) shows how the data is processed in Grasshopper
- Parameters: ```size```, ```orientation```, ```pattern```, ```count``` & ```shape```
- The results are 5 copies of personalized segment designs
  
![grasshopper](img/grasshopper.png)   

## Advanced Manufacturing
- The Grasshopper result is baked and exported to a .dxf file
- The dxf file is printed on a laser cutter using [lightburn](https://lightburnsoftware.com/)
- Material: [Akyplen® wit 460 g/m²](https://igepa.nl/06-0007-0007-akyplenr-wit-460-g-m-700-mm-x-1000-mm-500)
- If you want to use the pregenerated design: this is the [file with the base segments](samples/Basis_File_10_sides_en_bodem.dxf) & this is a [pregenerated file with the parts with a pattern](samples/Accent_file_5_sides.dxf)
  
**Curious about the math behind this lamp?**
- The general shape is a [Rhombic triacontahedron](https://en.wikipedia.org/wiki/Rhombic_triacontahedron), with 30 rhombic (diamond-shaped) faces
- From this shape, we remove 20 faces in the middle
- See the video below for a basic visualization
  
https://github.com/basbaccarne/nerdland/assets/7208557/56421a35-1992-435b-bc12-0767cc13a605

## Design for Assembly
- The five segments are printed in the laser cutter
- Visitors get a enveloppe with
  - a preprinted [bottom part](samples/Basis_File_10_sides_en_bodem.dxf)
  - 10 preprinted [segments without a pattern](samples/Basis_File_10_sides_en_bodem.dxf)
  - a small led light that fits in the bottom > [small led tea light](https://www.amazon.com.be/-/en/Afoosoo-Flameless-Battery-Waterproof-Christmas/dp/B0BV1HZ5NH/ref=asc_df_B0BV1HZ5NH/)
- How to put everything together? Watch this movie
[![assembly](img/assembly.png)](https://www.youtube.com/watch?v=dlgAcVDjcDM)

## End result
![light hanging](img/light_hanging.jpg)
![prototype](img/productv1.png)
