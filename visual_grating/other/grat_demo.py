'''
demo code, from youtube video: https://www.youtube.com/watch?v=B_vRxgbnoaM
updated 2020.04.26

This program will generate a window
generate a grating stimulus
'''

from psychopy import visual, core, event

# create window
win0 = visual.Window([800,600],screen=0,monitor='testMonitor',fullscr=False,color=[0,0,0], unit='pix')

grat_stim = visual.GratingStim(win=win0, tex='sin', units='pix', pos=(0.0,0.0), size=800, sf=0.02, ori=90.0, phase=(0.0,0.0))

while(1):

    grat_stim.draw()
    win0.flip()

    if len(event.getKeys()) > 0:
        break
    event.clearEvents()

#tidy up
win0.close()
