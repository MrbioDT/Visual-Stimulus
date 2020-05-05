'''
updated 2020.05.04
This code communicate with visual_grating_pin.ino(arduino), take the input from arduino digitalPin and control the psychopy to generate visuasl stimulus accordingly

Features
*input from adruino pin not serial monitor
*visual grating is drifting

ReadMe
*modified based on visual_grating_drifting.py
*upload and run the arduino code first and then run the python code
'''


import serial
from psychopy import visual, monitors
import time

def VisGrat_drifting(orientation,off=False):
    #This function generate a drifting visual grating, given the argument of orientation(int)
    NEC = monitors.Monitor('NEC')
    NEC.setDistance(14) # mice is cm from the screen
    NEC.setSizePix([1280,1024])# resolution(pixel) of the monitor
    NEC.setWidth(37.5) # width of monitor, cm
    win0 = visual.Window(screen=1, monitor=NEC, fullscr=True, color=[-1,-1,-1], unit='deg') #create window
    myCentre = visual.Polygon(win=win0, edges=100, radius=100000000000, units='degFlat', lineColor=[-1,-1,-1], fillColor=[-1,-1,-1], pos=[0, 0])
    grat_stim = visual.GratingStim(win=win0, tex='sin', units='deg', pos=(0.0, 0.0), size=100000, sf=0.04, ori=orientation, phase=(0.0, 0.0))
    # sf is spatial frequency, when units == ‘deg’ or ‘cm’ units are in cycles per deg or cm as appropriate
    frametime = win0.getMsPerFrame(nFrames=60, showVisual=False, msg='', msDelay=0.0)[0]  # return the the average time per frame, with unit of ms
    timeout = time.time() + 600  # seconds, duration of visual stimulus
    if not off:
       while True:
        if time.time() > timeout:
            break
        grat_stim.setPhase(2/float(1000/frametime),'+') # advance phase by 0.05 of a cycle, '-' is opposite directions
        #grat_stim.setPhase(0,'+') # advance phase by 0.05 of a cycle, '-' is opposite directions

        # speed of visual stimulus
        grat_stim.draw()
        win0.flip()
    else:
       while True:
         myCentre.draw()
         win0.flip()

    win0.close()
    return 0

if __name__ == "__main__":

    # [USER INPUT HERE] set variables for serial communication
    port = '/dev/cu.usbmodem144401'
    baud_rate = 9600

    # visual stimulus session
    NEC = monitors.Monitor('NEC')
    NEC.setDistance(14)  # mice is cm from the screen
    NEC.setSizePix([1280, 1024])  # resolution(pixel) of the monitor
    NEC.setWidth(37.5)  # width of monitor, cm
    win0 = visual.Window(screen=1, monitor=NEC, fullscr=True, color=[-1, -1, -1], unit='deg')  # create window
    grat_stim = visual.GratingStim(win=win0, tex='sin', units='deg', pos=(0.0, 0.0), size=100000, sf=0.04, ori=180, phase=(0.0, 0.0))
    grat_stim_v = visual.GratingStim(win=win0, tex='sin', units='deg', pos=(0.0, 0.0), size=100000, sf=0.04, ori=90, phase=(0.0, 0.0))
    myCentre = visual.Polygon(win=win0, edges=100, radius=100000000000, units='degFlat', lineColor=[-1, -1, -1], fillColor=[-1, -1, -1], pos=[0, 0])
    frametime = win0.getMsPerFrame(nFrames=60, showVisual=False, msg='', msDelay=0.0)[0]  # return the the average time per frame, with unit of ms


    while True: #This while loop keeps updating the command until visual stimlus is displayed

       ser = serial.Serial(port, baud_rate, timeout=1)  # start serial communication
       command = str(ser.readline().decode('ascii'))
       print("Message from arduino: ", command)
       timeout = time.time() + 3  # seconds, duration of visual stimulus

       if '7' in command:
           while True:
               if time.time() > timeout:
                   break
               grat_stim.setPhase(2 / float(1000 / frametime),'+')  # advance phase by 0.05 of a cycle, '-' is opposite directions
               # speed of visual stimulus
               grat_stim.draw()
               win0.flip()
       elif '23' in command:
           while True:
               if time.time() > timeout:
                   break
               grat_stim_v.setPhase(2 / float(1000 / frametime),'+')  # advance phase by 0.05 of a cycle, '-' is opposite directions
               # speed of visual stimulus
               grat_stim_v.draw()
               win0.flip()
       else:
          myCentre.draw()

       win0.flip()





