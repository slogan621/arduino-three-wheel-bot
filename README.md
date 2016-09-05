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

You might be able to replace the Parallax part with a cheaper item. However,
I also bought the mounting kit, but it doesn't appear to be available anymore
so this may favor getting the cheaper sensors available and making your own 
mount. The Parallax requires 5V.

Three-wheel Robot Chassis with Motors
-------------------------------------

These are awesome and cheap. Come with two motors that operate with 3V - 6V.
Assembly instructions were in Chinese but there are youtube videos that help
you figure out how to put the chassis together.

https://www.amazon.com/INSMA-Chassis-Encoder-Battery-Arduino/dp/B01BXPETQG/ref-sr_1_cc_1?s-aps&ie-UTF8&qid-1473103949&sr-1-1-catcorr&keywords-3+wheel+robot+chassis

Arduino Uno
-----------

Standard Arduino Uno or a knockoff. 

Power Switch
------------

I mounted a SPDT switch to turn the robot on and off.

Battery Holder
--------------

You need at least 9V to drive the motors and the Parallax ultrasonic. The 
three wheeled robot comes with a 4-AA holder which gives you 6V. The bot 
won't last 10 minutes with only 6V. Replace with a 6-AA holder which works
much better.

Pin Assignments
---------------

The control pin for the ultrasonic is wired to pin 5 of the arduino. For the
L298N, refer to the excellent instructions at
https://tronixlabs.com.au/news/tutorial-l298n-dual-motor-controller-module-2a-and-arduino/

I'll leave the rest to you to figure out. 

Code
====

The logic is simple. The Robot class provides the following functions:

  long getDistanceInInches();
  void reverse();
  void forward();
  void setSpeed(int wheel, int speed);
  void stop(int wheel);
  void turnLeft(long seconds);
  void turnRight(long seconds);

The loop() function calls a function named wanderAndWait(). This function
gets the distance sensed by the untrasonic. If less than 8 inches, it 
reverses the bot, then the bot rotates in a random direction for a small
random number of seconds. Then it goes forward again. The result is the 
bot will navigate a room avoiding any objects that are able to be sensed
ahead of the robot with the ultrsasonic.
