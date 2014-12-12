## Lab 7 Robot Sensing

Objective: to utilize the IR sensors on the robot at certain thresholds.

### Prelab

What pins will I use? Some pins are already taken by my motor sensors, and I need to use pins that have ADC inputs. I also don't want to use P1.0 or P1.6 because those are my LED pins - the LED pins are useful for inidcating results of tests. For this lab, then, I will use P1.3, P1.4, and P1.5. The full hardware diagram, in a logic format, is shown below.

![alt text](https://raw.githubusercontent.com/ChrisMKiernan/ECE382_Lab8/master/HardwarePinDiagram.png "The logical hardware diagram of my robot")

### Design

I started my code from the shell provided by Dr Coulston. In the shell code, the ADC input pin was polled on P1.4, and the value collected from P1.4 was tested against a threshold value. If the input was high enough (in other words, close enough) the LED would be lit. From the provided code, it was simple to modify it to take three separate inputs from the 3 separate pins. Each of these functions could have its own threshold value, and its own test against the threshold value. I decided to light up different LEDs depending on which sensor was close to a surface. If the right sensor was close, the right LED would light up, and the same condition would occur for the left sensor and LED. for the center sensor, both LEDs would light up.

### Potential Problems

Polling is inefficient, and takes time to complete. If I were to use a similar approach on my robot for Lab 8, my robot could run into a wall before a polling loop is complete. However, when we look at the clock speed and the relatively small size (10 bit) of the digital value, we can see that polling the sensor takes a matter of milliseconds to complete, and is not entirely an issue.

When my robot senses a wall, the correspoding light(s) turn on. However, the light(s) do not turn off until all three sensor values are below the threshold. This means that I could cause the center sensor to detect a close object, then cause the right sensor to detect, then remove the center object, and both LEDs would still be on. However, this is a cause of using 2 outputs for 3 sensors, and should not affect Lab 8.
