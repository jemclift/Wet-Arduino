# Automatically Watering a Plant

 *Jake Andrews, Jem Clift, Joshua Peachey, Matthew Snell*

> A report (4 to 5 pages) which explains your motivation, process and implementation.
> Report must be in PDF format.

### Introduction

> An introduction to the problem area that you have identified. You should indicate your
> motivation for selecting this problem area. (approx ½ page)

University students love to decorate their rooms with plants as it makes their room feel more homely. Some students opt for fake plants but real ones give life to a room with the downside of requiring some care.

Unfortunately, as most university students do not live in their university accommodation all year round, they often leave their plants unattended unable to water them. Students are also busy so can often forget to water their plants.

Most plants require regular watering and will wilt and eventually die if neglected.

>  **INSERT STUDENT QUOTE ABOUT DEAD/DYING PLANTS**

To solve this problem, our project is a plant irrigation system that automatically waters a plant when its soil is too dry. It also monitors other important values like light and temperature and all this data is displayed on a remote arduino with an LCD that can be placed on your desk. If the plants soil is too dry, it is too hot or cold, a warning is displayed with a buzzer tone and flashing LED to warn the plants owner.

### Literature & Technology Review

> A literature and technology review. This should help provide evidence for your chosen
> problem area and justification for your development decisions. (approx ½ - 1 page)

...

### Development Process

> An overview of the development process - what you did, how you did it, what additional
> research you conducted, any problems you encountered and how you overcame
> these. (approx 1 page)

**Overview**

...

**Additional research (Ideas)**

- How dry should the soil be to warrant watering
- How far is typical plant from student in a room (length of wires connecting both arduinos)
- Types of pump (obviously we ended up with submergible)
- Our soil moisture sensors and the better capacitive soil moisture sensor

 ### Final Prototype Implementation

> Description of your final prototype implementation - provide a description of the
> components used in the final prototype and how these interact with one another in your
> system. (approx ½ - 1 page)

**Description**

...

**Components**

2 x Arduino Uno and 3 x 1m wires to connect them

Sensor/Master Board

- Soil Moisture Sensor
- Small Submergible Pump
- Temperature Sensor
- Phototransistor
- Resistors (2 x 10K Ohms, 1K Ohms)
- BC548 Transistor
- Button
- Jumper Wires

Display Board

- 16 Column 2 Row LCD
- Button
- Piezo Buzzer
- Resistors (2 x 10K Ohms)
- Red LED
- Potentiometer
- Jumper Wires

### Summary & Conclusions

> Short summary and conclusions (approx ½ page)

...

**Ideas**

- In a real application of this project we would use a better sensor and a large tank of water

### Appendix

> Please add an appendix (as an additional page to the report) which shows a clear
> photo of your solution. Extra marks will be given for the inclusion of a schematic of your
> solution, which can also be included in the appendix. You can use schematic drawing
> tools such as Autodesk Eagle (free for students) or Frtizing (not free). Alternatively you
> may choose to draw this on paper and upload a picture or similar. This appendix should
> not take more than 1 page.

...
