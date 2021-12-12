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

>  **"When plants are not watered properly they wilt."- Luiz de Queiroz College of Agriculture**

To solve this problem, our project is a plant irrigation system that automatically waters a plant when its soil is too dry. It also monitors other important values like light and temperature and all this data is displayed on a remote arduino with an LCD that can be placed on your desk. If the plants soil is too dry, it is too hot or cold, a warning is displayed with a buzzer tone and flashing LED to warn the plants owner.

### Literature & Technology Review

> A literature and technology review. This should help provide evidence for your chosen
> problem area and justification for your development decisions. (approx ½ - 1 page)
> 

To create an effective irrigation system we researched a few factors including optimal temperature, light and water for indoor plants. 

Light is the most important factor for growing plants. We decided it was therefore crucial to include a light sensor to give the plant owner an indication of how much light there is where the plant is located. The amount of light is quickly visibile on the display. As opposed to managing the amount of light the plant receives, the light sensor is more of a tool to help the grower assess and optimise the location of their plant.

Temperature is the second most important factor influencing plant growth. We identified 15°C-25°C to be a healthy range for growing indoor plants. Temperatures outside this range for excessive amounts of time may lead to stunted growth or even death. Our solution provides an up to date accurate temperature on the display and also a warning to alert the grower to suboptimal or dangerous temperatures. Making this valuable information so visible really helps the grower to ensure their plant has the best chance of being healthy. 

Water is the only factor out of the 3 which can't be set and left. Improper watering causes problems and will affect the growth of the plant. 
> "Feel the soil by pushing a finger an inch or so below the surface. If the soil is still moist, no further water is needed."

We used this simple principle when creating the automtic system. If the soil is dry then water until the soil is moist.

V. Pennisi, B., 2006. Growing Indoor Plants with Success | UGA Cooperative Extension. [online] Extension.uga.edu. Available at: <https://extension.uga.edu/publications/detail.html?number=B1318&title=Growing%20Indoor%20Plants%20with%20Success#water> 

W. D., H., 1945. [online] Scholars.unh.edu. Available at: <https://scholars.unh.edu/cgi/viewcontent.cgi?article=1320&context=agbulletin>

### Development Process

> An overview of the development process - what you did, how you did it, what additional
> research you conducted, any problems you encountered and how you overcame
> these. (approx 1 page)

#### Overview

**millis() VS delay()**

Originally the first version of our project used the `delay()` function to limit sensor readings. There were a few problems with this aproach. If one sensor needs to be checked more frequently than another, for example the light and temperature are checked very frequently to update the display, then larger delays for longer wait sensor readings cannot be used. This is becuase the `delay()` function almost completely pauses the board. The solution to this problem is to use the `millis()` function instead. `millis()` returns the milliseconds that the arduino has been running a program for. This can be used to check if enough time has passed to run an event and then set the next time to run that event. This way multiple "delays" can run simultaneously.

**Warnings**

If you have a warning system and a way to dismiss a warning you will have to deal with the problem of when to next allow the same warning. Although we could have used a timer to dismiss a warning for some amount of time, we decided to reset the ability for a warning type to alert the user when it's value returns to a normal range. This way if a user dismisses, for example, a to hot warning, they will next be alerted when the temperature returns to normal before rising again. We used a boolean array `canBeWarning` which tell the program whether a specific type of warning is currently allowed. Warnings also automatically dismiss themselves if sensor readings return to normal.

**Communication**

...

**Watering**

...

#### Additional research

- How dry should the soil be to warrant watering
- How far is typical plant from student in a room (length of wires connecting both arduinos)
- Types of pump (obviously we ended up with submergible)
- Our soil moisture sensors and the better capacitive soil moisture sensor

 ### Final Prototype Implementation

> Description of your final prototype implementation - provide a description of the
> components used in the final prototype and how these interact with one another in your
> system. (approx ½ - 1 page)

#### Description

...

#### Components

2 x Arduino Uno and 3 x 1m wires to connect them

**Sensor/Master Board**

- Soil Moisture Sensor
- Small Submergible Pump
- Temperature Sensor
- Phototransistor
- Resistors (2 x 10K Ohms, 1K Ohms)
- BC548 Transistor
- Button
- Jumper Wires

**Display Board**

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

#### Ideas

- In a real application of this project we would use a better sensor and a large tank of water

### Appendix

> Please add an appendix (as an additional page to the report) which shows a clear
> photo of your solution. Extra marks will be given for the inclusion of a schematic of your
> solution, which can also be included in the appendix. You can use schematic drawing
> tools such as Autodesk Eagle (free for students) or Frtizing (not free). Alternatively you
> may choose to draw this on paper and upload a picture or similar. This appendix should
> not take more than 1 page.

...
