'''
this code is from https://stackoverflow.com/questions/24074914/python-to-arduino-serial-read-write
the goal is to "ping pong" info back and forth between some python code and arduino code
updated 2020.04.27
'''

#!/usr/bin/python
import serial
import syslog
import time

#The following line is for serial over GPIO
port = '/dev/cu.usbmodem144401'
ard = serial.Serial(port,9600,timeout=5)
i = 0
while (i < 4):
    # Serial write section
    setTempCar1 = 63
    setTempCar2 = 37
    ard.flush() #QQQQQQQ. function of this one?
    setTemp1 = str(setTempCar1)
    setTemp2 = str(setTempCar2)
    print ("Python value sent: ")
    print (setTemp1)
    ard.write(setTemp1.encode('utf-8')) #string need to be converted to bytes before write to serial port
    time.sleep(1)
    # Serial read section
    msg = ard.readline() #QQQQQQQQ. function of this one? # read a '\n' terminated line
    print ("Message from arduino: ")
    print (msg)
    i = i + 1
else:
    print ("Exiting")
exit()