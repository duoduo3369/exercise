# This code is so you can run the samples without installing the package
import sys
import os
#sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..'))
#

import pyglet
import cocos
from cocos.director import director
from cocos.actions import *
from cocos.layer import *

from pyglet.gl import *

testinfo = "s, t 3, s, t 6, s, t 8.1, s, q"
tags = "OrbitCamera, reuse_grid"

sw,sh = 460,1380
class BackgroundLayer(cocos.layer.Layer):
    def __init__(self):
        super(BackgroundLayer, self).__init__()
        self.img = pyglet.resource.image('aqgy.jpg')

    def draw( self ):
        glColor4ub(255, 255, 255, 255)
        glPushMatrix()
        self.transform()
        self.img.blit(0,0)
        glPopMatrix()

def main():
    director.init(width=sw, height=sh, resizable=True)
    director.set_depth_test()

    main_scene = cocos.scene.Scene()

    main_scene.add( BackgroundLayer(), z=0 )

    # set a 3d grid with a grid3d action
    e = WavesTiles3D( amplitude=60, waves=4, grid=(32,24), duration=4)

    # use the remaining grid and move it's camera
    rot = OrbitCamera( angle_x=45,  angle_z=0, delta_z=360, duration=4 )

    main_scene.do( e )
    # In real code after a sequence of grid actions the StopGrid() action
    # should be called. Omited here to stay in the last grid action render
    main_scene.do( rot + Reverse(rot) )

    director.run (main_scene)

if __name__ == '__main__':
    main()
