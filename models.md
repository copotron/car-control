# Candidate cars

I was looking at all different cars to use as platform- and in terms of steering what I found is that modern version of even 
the cheaper cars like toyota corolla is equiped with electric steering and cheap control unit. We really can take almost any 
car if we are comfortable with doing some soldering and putting together a separate control bus. The OSCC can be used or 
designing one from scratch should not be a problem at all.

So basically every electrical steering system has a torque sensor that sends the car computer about the drivers 
intention of which way the front wheel will turn. It has no direct connection with the front wheel (except as a fail safe 
which should not engage in normal operation) and work like a joystick. Now if we cut the wire from the sensor to computer 
and start spoofing the signal the car computer has no way to know its fake signal and the car will happily rotate the 
steering column and car will steer.

If we use a relay which closes the cars built in system with the normally closed pin and our controller when the relay is 
turned on we can start sending the signal to car computer and if power failure occurs or we push the big red button to cut 
all power to self driving unit car comes to factory settings and driver can assume control.

The torque from real steering wheel can be measured and be used to dis-engage the autonomous system when driver tries to 
move the wheel.

## Car list

This lists the cars with power steering that is controlled by car computer:

- Toyota Prius Prime (2017...) - Steering, Accelerator, Brake
- Toyota Prius (2017...) - Steering, Accelerator, Brake
- Toyota Corolla (2017...) - Steering, Accelerator, Brake
- Lexus IS series (2012-)  - Steering, Accelerator, Brake
- Nissan Juke (2014-) - Steering, Accelerator
- Kia Soul (2014-...) - Steering, Accelerator - All KIA (without Picanto) 2014+ have same systems (update by karolmajek)
- Ford Fusion (2015-...) - - Steering, Accelerator, Brake
