import os

env = Environment()
env['CC'] = 'g++'
env['CCFLAGS'] = '-Wall -Wextra -Wno-unused-parameter -O0 -ggdb -msse3 -I/usr/include/OpenEXR -I./lib -I./external/tinyXML'
env['LIBS'] = ['GLU', 'GL', 'protobuf', 'IL', 'ILUT']
env.ParseConfig("pkg-config IlmBase --cflags --libs")
env.ParseConfig("pkg-config libglfw --cflags --libs")


env.Program('mesh_compile', 
            ['mesh_compile.cc', 'lib/GL/GLee.c'] 
            + Glob('lib/*cc') + Glob('external/tinyXML/*cpp'))

env.Program('Pony', 
            ['PinkPony.cc', 'lib/GL/GLee.c'] 
            + Glob('lib/*cc'))
env.Program('MapView', 
            ['MapView.cc', 'lib/GL/GLee.c'] 
            + Glob('lib/*cc'))
env.Program('MeshViewer', 
            ['MeshViewer.cc', 'lib/GL/GLee.c'] 
            + Glob('lib/*cc'))
env.Program('ConfigFile', 
            ['ConfigFile.cc', 'lib/GL/GLee.c'] 
            + Glob('lib/*cc'))
