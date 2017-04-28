The sensor output to the car computer is cut and a spoof line from the car controller is attached to the computer end of 
the cut. The controller has a digital to analog converter (MCP4922T) to send correct amount of voltage. 

An example from OSCC data file:
For maximum torque to left we need to pull to 4.26 volts for the high sensor line.


To dis-engage the autonomous system, we need to add the two torque sensor wires to A0 and A1 pins of Arduino and periodically monitor the values. If both values are near same (2.5V in on the wire) then there is no torque. For different values see if difference is more than a predefined threshold - if yes- dis-engage. For bigger threshold user needs to steer strong.

float torque_sensor_a = ( float )( analogRead( A0 ) << 2 );
float torque_sensor_b = ( float )( analogRead( A1 ) << 2 );

Aonnection between the DAC output and A2, A3 pin of Arduino may be used measure it to see if the command was successful to make it robust- but never used it.
