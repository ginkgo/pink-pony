import os

env = Environment()
env['CC'] = 'g++'
env['CCFLAGS'] = '-Wall -Wextra -Wno-unused-parameter -O2 -ggdb -I/usr/include/OpenEXR -I./lib -I./external/tinyXML'
env['LIBS'] = ['GLU', 'GL', 'protobuf', 'IL', 'ILUT', 'audiere']
env.ParseConfig("pkg-config IlmBase --cflags --libs")
env.ParseConfig("pkg-config libglfw --cflags --libs")
env.ParseConfig("pkg-config ftgl --cflags --libs")
env.ParseConfig("pkg-config sigc++-2.0 --cflags --libs")

env.Command(['lib/mesh.pb.cc', 'lib/mesh.pb.h'], 'mesh.proto', 
            'protoc --cpp_out=lib mesh.proto')


env.Program('mesh_compile', 
            ['mesh_compile.cc', 'lib/GL/GLee.c'] 
            + Glob('lib/*cc') + Glob('external/tinyXML/*cpp'))
env.Program('skeleton_compile', 
            ['skeleton_compile.cc', 'lib/GL/GLee.c'] 
            + Glob('lib/*cc') + Glob('external/tinyXML/*cpp'))

env.Program('Pony', 
            ['PinkPony.cc', 'lib/GL/GLee.c'] 
            + Glob('lib/*cc'))
env.Program('MenuTest', 
            ['MenuTest.cc', 'lib/GL/GLee.c'] 
            + Glob('lib/*cc'))
env.Program('MapView', 
            ['MapView.cc', 'lib/GL/GLee.c'] 
            + Glob('lib/*cc'))
env.Program('ConfigFile', 
            ['ConfigFile.cc', 'lib/GL/GLee.c'] 
            + Glob('lib/*cc'))
