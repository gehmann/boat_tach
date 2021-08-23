# boat_tach
Arduino based tachometer

This program reads in a wave on an Arduino pin and calculates the RPM of the engine. It then outputs a PWM signal to a gauge to display the RPM. The gauge reads current so a 10k resistor is in series with a coil and a function maps the PWM duty cycle to the displayed RPM. 
