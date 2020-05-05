'''
updated 2020.05.01
This code communicate with visual_grating_pin.ino(arduino), take the input from arduino digitalPin and control the psychopy to generate visuasl stimulus accordingly

Features
*input from adruino pin not serial monitor
*visual grating is drifting

ReadMe
*modified based on visual_grating_drifting.py
*upload and run the arduino code first and then run the python code
'''


import serial
from psychopy import visual, core
import time


def VisGrat_drifting(orientation):
    #This function generate a drifting visual grating, given the argument of orientation(int)
    win0 = visual.Window([800, 600], screen=0, monitor='testMonitor', fullscr=False, color=[0, 0, 0], unit='pix') #create window
    grat_stim = visual.GratingStim(win=win0, tex='sin', units='pix', pos=(0.0, 0.0), size=1000, sf=0.02, ori=orientation, phase=(0.0, 0.0))

    timeout = time.time() + 5  # seconds, duration of visual stimulus
    while True:
        if time.time() > timeout:
            break
        grat_stim.setPhase(0.01,'+') # 0.01 and '+' controls the speed and direction of drafting
        grat_stim.draw()
        win0.flip()

    win0.close()
    return 0

if __name__ == "__main__":

    # [USER INPUT HERE] set variables for serial communication
    port = '/dev/cu.usbmodem141301'
    baud_rate = 9600

    ser = serial.Serial(port, baud_rate, timeout=1)  # start serial communication

    while True: #This while loop keeps updating the command until visual stimlus is displayed
       command = str(ser.read().decode('ascii'))
       print("Message from arduino: ", command)

       if command == '1':
           VisGrat_drifting(45)
           break
