# boat_tach
Arduino based tachometer

This program reads in a wave on an Arduino pin and calculates the RPM of the engine. It then outputs a PWM signal to a gauge to display the RPM. The gauge reads current so a 10k resistor is in series with a coil and a function maps the PWM duty cycle to the displayed RPM. 

The program also includes a class to control a 4 digit 7 segment display but that is currently unused.
