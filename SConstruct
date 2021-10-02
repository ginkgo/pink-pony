import os

#optimization_flags = ['-O3']
optimization_flags = ['-O0', '-ggdb']

env = Environment()
env['CC'] = 'g++'
env['CCFLAGS'] = ['-Wall', '-Wextra', '-Wno-reorder', '-Wno-unused-parameter'] + optimization_flags
env['LIBS'] = ['GLU', 'GL', 'protobuf', 'IL']
env['CPPPATH'] = ['#', '#/src', '#/external/tinyXML', '#/external/flextGL/', '/usr/include/OpenEXR']

env.ParseConfig("pkg-config Imath --cflags --libs")
env.ParseConfig("pkg-config glfw3 --cflags --libs")
env.ParseConfig("pkg-config ftgl --cflags --libs")
env.ParseConfig("pkg-config sigc++-2.0 --cflags --libs")
env.ParseConfig("pkg-config SDL_mixer --cflags --libs")


env.Command(['src/mesh.pb.cc', 'src/mesh.pb.h'], 'src/mesh.proto',
            'protoc --cpp_out=. src/mesh.proto')

env.Program('Pony',
            Glob('src/*cc') + Glob('external/tinyXML/*cpp') + ['external/flextGL/flextGL.c'])
