Bossy is an open-source custom general purpose controller based on Arduino.
It uses nrF24l01+ to communicate its commands wirelessly. You can use it to control anything!

|![](https://github.com/mithi/robotics-blog/blob/master/static/images/bossy/bossy-matrix-1.gif)|![](https://github.com/mithi/robotics-blog/blob/master/static/images/bossy/bossy-matrix-3.gif)|
| ---------- | ---------- |


The first prototype is complete, I will start the second prototype
in the next few months once the extreme quarantine lockdown has been lifted in my city.
There are also plans to make a few derivatives of Bossy such as Tiny Bossy and Mini Bossy.

|![](https://mithi.github.io/robotics-blog/tiny-bossy.png)| ![](https://mithi.github.io/robotics-blog/mini-bossy-2.png)|![](https://mithi.github.io/robotics-blog/v2-layout.png)|
| ---------- | ---------- | ---------- |
| Tiny Bossy | Mini Bossy | Bossy |


You can follow the progress of each Bossy. I document them in my
[robotics blog](https://github.com/mithi/bossy) as I make them. My blog also includes the [BOM/Shopping list](https://mithi.github.io/robotics-blog/blog/bossy/02-bill-of-materials/), step-by-step build instructions,
trouble-shooting tips should you wish to make your own Bossy's.
The Bossy library also makes it easy for you to not only to [get started](https://mithi.github.io/robotics-blog/blog/bossy/09-coding-1/) but also to [modify](https://mithi.github.io/robotics-blog/blog/bossy/10-coding-2/), tweak, and hack your own Bossy's to fit your specific needs.



# Dependencies
- [nRF24/RF24](https://github.com/nRF24/RF24)
- [Adafruit libraries such as the [adafruit/Adafruit_LED_Backpack](https://github.com/adafruit/Adafruit_LED_Backpack)

# How to use
Assuming you have a working Bossy:

- Download and Install [Arduino IDE](https://www.arduino.cc/en/Main/Software)
- Go to your Arduino library directory, on a Mac
its `~/Documents/Arduino/libraries/`
- Clone this repo ` $ git clone https://github.com/mithi/bossy.git `

- You should be able to see example sketches that you can
upload on your own Bossy
`File > Examples > Bossy`


