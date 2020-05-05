'''
updated 2020.05.04
This code communicate with visual_grating_pin.ino(arduino), take the input from arduino digitalPin and control the psychopy to generate visuasl stimulus accordingly

Features
*start with black screen
*in master arduino serial monitor, type 'v'/'h' and this python program give vertical/horizontal stimulus
*visual grating is drifting

ReadMe
*modified based on visual_grating_drifting.py
*upload and run the arduino code first and then run the python code
'''


import serial
from psychopy import visual, monitors
import time

if __name__ == "__main__":

    #set variables for serial communication
    port = '/dev/cu.usbmodem144401'
    baud_rate = 9600

    # visual stimulus session
    NEC = monitors.Monitor('NEC')
    NEC.setDistance(14)  # mice is cm from the screen
    NEC.setSizePix([1280, 1024])  # resolution(pixel) of the monitor
    NEC.setWidth(37.5)  # width of monitor, cm
    win0 = visual.Window(screen=1, monitor=NEC, fullscr=True, color=[-1, -1, -1], unit='deg')  # create window
    grat_stim_h = visual.GratingStim(win=win0, tex='sin', units='deg', pos=(0.0, 0.0),         # horizontal grating
                                     size=100000, sf=0.04, ori=180, phase=(0.0, 0.0))
    grat_stim_v = visual.GratingStim(win=win0, tex='sin', units='deg', pos=(0.0, 0.0),         # vertical grating
                                     size=100000, sf=0.04, ori=90, phase=(0.0, 0.0))
    myCentre = visual.Polygon(win=win0, edges=100, radius=100000000000, units='degFlat',       # blackscreen visual stimulus
                              lineColor=[-1, -1, -1], fillColor=[-1, -1, -1], pos=[0, 0])
    frametime = win0.getMsPerFrame(nFrames=60, showVisual=False, msg='', msDelay=0.0)[0]       # return the time(ms) per frame


    while True: #This while loop keeps updating the command until visual stimlus is displayed

       ser = serial.Serial(port, baud_rate, timeout=1)  # start serial communication
       command = str(ser.readline().decode('ascii'))
       print("Message from arduino: ", command)
       timeout = time.time() + 3  # seconds, duration of visual stimulus

       if '7' in command:  #display horizontal stimulus
           while True:
               if time.time() > timeout:
                   break
               grat_stim_h.setPhase(2/float(1000/frametime),'+')  # speed of visual stimulus: advance phase by '2/float(1000/frametime)' of a cycle, '-' is opposite directions
               grat_stim_h.draw()
               win0.flip()
       elif '23' in command: #display vertical stimulus
           while True:
               if time.time() > timeout:
                   break
               grat_stim_v.setPhase(2 / float(1000 / frametime),'+')  # speed of visual stimulus: advance phase by '2/float(1000/frametime)' of a cycle, '-' is opposite directions
               grat_stim_v.draw()
               win0.flip()
       else:
          myCentre.draw() #just black screen

       win0.flip()
