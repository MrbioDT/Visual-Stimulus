'''
updated 2020.04.28
This code communicate with visual_grating.ino(arduino), take the input from arduino serial monitor and control the psychopy to generate visuasl stimulus accordingly

Features
*visual grating is drifting
*catch the exception when port is occupied by serial monitor

ReadMe
*modified based on visual_grating.py
*upload and run the arduino code first and then run the python code
*(arduino) ask for a char type input from serial monitor and store this input as "command"
*close the arduino serial monitor and the command will be send to python
*(python) if command is A, then trigger visual grating with orientation of 45degree
*(python) if command is B, then trigger visual grating with orientation of 135degree
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


#[USER INPUT HERE] set variables for serial communication
port = '/dev/cu.usbmodem144301'
baud_rate = 9600

while True: #This while loop keeps the program running until visual stimulus is displayed

  try:
    ser = serial.Serial(port, baud_rate, timeout=1)     #start serial communication
    while True: #This while loop keeps updating the command until visual stimlus is displayed
       command = str(ser.read().decode('ascii'))
       print("Message from arduino: ", command, "(type A or B in arduino serial monitor to initiate visual grating)")
       core.wait(2)  # seconds to wait

       if command == 'A':
          VisGrat_drifting(45)
          break

       if command == 'B':
          VisGrat_drifting(135)
          break #inner while loop

    break #outer while loop

  except:
     print ('exception')
     core.wait(2)  # seconds to wait



