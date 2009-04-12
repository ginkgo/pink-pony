import os

env = Environment()
env['CC'] = 'g++'
env['CCFLAGS'] = '-Os -msse3 -I/usr/include/OpenEXR -I./lib -I./external/tinyXML'
env['LIBS'] = ['GLU', 'GL']
env.ParseConfig("pkg-config OpenEXR --cflags --libs")
env.ParseConfig("pkg-config libglfw --cflags --libs")

env.Program('Pony', 
            ['PinkPony.cc', 'lib/GL/GLee.c'] 
            + Glob('lib/*cc') + Glob('external/tinyXML/*cpp'))
env.Program('MapView', 
            ['MapView.cc', 'lib/GL/GLee.c'] 
            + Glob('lib/*cc') + Glob('external/tinyXML/*cpp'))
env.Program('MeshViewer', 
            ['MeshViewer.cc', 'lib/GL/GLee.c'] 
            + Glob('lib/*cc') + Glob('external/tinyXML/*cpp'))
env.Program('ConfigFile', 
            ['ConfigFile.cc', 'lib/GL/GLee.c'] 
            + Glob('lib/*cc') + Glob('external/tinyXML/*cpp'))
