import os

#optimization_flags = ['-O3']
optimization_flags = ['-O0', '-ggdb']

env = Environment()
env['CC'] = 'g++'
env['CCFLAGS'] = ['-Wall', '-Wextra', '-Wno-reorder', '-Wno-unused-parameter'] + optimization_flags
env['LIBS'] = ['GLU', 'GL', 'protobuf', 'IL']
env['CPPPATH'] = ['#/src', '#/external/tinyXML', '#/flextGL/', '/usr/include/OpenEXR']

env.ParseConfig("pkg-config IlmBase --cflags --libs")
env.ParseConfig("pkg-config libglfw --cflags --libs")
env.ParseConfig("pkg-config ftgl --cflags --libs")
env.ParseConfig("pkg-config sigc++-2.0 --cflags --libs")
env.ParseConfig("pkg-config SDL_mixer --cflags --libs")


env.Command(['src/mesh.pb.cc', 'src/mesh.pb.h'], 'mesh.proto', 
            'protoc --cpp_out=src mesh.proto')

env.Program('Pony', 
            ['Pony.cc', 'flextGL/flextGL.c'] 
            + Glob('src/*cc') + Glob('external/tinyXML/*cpp'))
