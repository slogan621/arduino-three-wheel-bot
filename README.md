# arduino-three-wheel-bot

Parts
=====

The robot this code supports is an inexpensive three wheeled, 2 servo model 
that can be obtained on ebay or amazon. The part list includes:

DROK L298N Motor Drive Controller
---------------------------------

https://www.amazon.com/gp/product/B00CAG6GX2/ref-oh_aui_detailpage_o03_s00?ie-UTF8&psc-1

Parallax PING Ultrasonic Sensor
-------------------------------

https://www.amazon.com/PARALLAX-Parallax-Ultrasonic-Distance-Sensor/dp/B00C9O00B4/ref-sr_1_cc_1?s-aps&ie-UTF8&qid-1473103890&sr-1-1-catcorr&keywords-Parallax+ultrasonic

You might consider replacing the Parallax part with a cheaper item. I had a
couple of these laying around from before cheaper alternatives existed. The 
Parallax device requires 5V. If you do use another part, you might need to
modify Robot::getDistanceInInches() and/or Robot::microsecondsToInches() to
make it work properly.

Three-wheel Robot Chassis with Motors
-------------------------------------

These are awesome and cheap. Comes with two motors that operate with 3V - 6V.
Assembly instructions were in Chinese, but there are youtube videos that help
you figure out how to put the chassis together if you can't read Chinese.

https://www.amazon.com/INSMA-Chassis-Encoder-Battery-Arduino/dp/B01BXPETQG/ref-sr_1_cc_1?s-aps&ie-UTF8&qid-1473103949&sr-1-1-catcorr&keywords-3+wheel+robot+chassis

Arduino Uno
-----------

Standard Arduino Uno, or a knockoff. 

Power Switch
------------

I mounted a SPDT switch on the chassis  and wired it into the circuit to turn 
the robot on and off.

Battery Holder
--------------

You'll need at least 9V to drive the motors and the Parallax ultrasonic. The 
three wheeled robot comes with a 4-AA holder which gives you 6V. The bot 
won't last 10 minutes with only 6V, the sensor starts giving false readings. 
Replace with a 6-AA holder which provides more than enough voltage (9 volts
on fresh batteries) and works much better.

Pin Assignments
---------------

The control pin for the ultrasonic is wired to pin 5 of the arduino. For the
L298N, I used the wiring as shown in the excellent instructions at
https://tronixlabs.com.au/news/tutorial-l298n-dual-motor-controller-module-2a-and-arduino/

The rest of the wiring should be straightforward to anyone comfortable with
using Arduino in breadboard designs.

Code
====

The logic is simple. The Robot class is in C++ and provides the following 
functions:

    long getDistanceInInches();
    void reverse();
    void forward();
    void setSpeed(int wheel, int speed);
    void stop(int wheel);
    void turnLeft(long seconds);
    void turnRight(long seconds);

The loop() function calls a function named wanderAndWait(). This function
gets the distance sensed by the untrasonic. If less than 8 inches, it 
reverses the bot, then the bot is rotated in a random direction for a small
random number of seconds. Then it then goes forward again. The result is the 
bot will navigate a room avoiding any objects that are able to be sensed
ahead of the robot with the ultrsasonic.

Improvements
============

Add some changes to the logic to try and detect that the robot is stuck in
the forward state but is not moving (if the distance read over time is not 
infinity and is not changing, maybe the device is stuck on something and 
should back away as if it were sensing a close object).
