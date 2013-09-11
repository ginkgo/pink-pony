import os

env = Environment()
env['CC'] = 'g++'
env['CCFLAGS'] = '-Wall -Wextra -Wno-reorder -Wno-unused-parameter -O3 -I/usr/include/OpenEXR -I./lib -I./external/tinyXML'
env['LIBS'] = ['GLU', 'GL', 'protobuf', 'IL']
env.ParseConfig("pkg-config IlmBase --cflags --libs")
env.ParseConfig("pkg-config libglfw --cflags --libs")
env.ParseConfig("pkg-config ftgl --cflags --libs")
env.ParseConfig("pkg-config sigc++-2.0 --cflags --libs")
env.ParseConfig("pkg-config SDL_mixer --cflags --libs")


# conf = Configure(env)
# if not conf.CheckLib('protobuf'):
#     print 'You have to install Google protocol buffers to compile this game.'
#     Exit(1)
# if not conf.CheckLib('audiere'):
#     print 'You have to install the audiere sound library to compile this game.'
#     Exit(1)
# if not conf.CheckLib('IL'):
#     print 'You have to install the DevIL image loading library to compile this game.'
#     Exit(1)
# env = conf.Finish()


env.Command(['lib/mesh.pb.cc', 'lib/mesh.pb.h'], 'mesh.proto', 
            'protoc --cpp_out=lib mesh.proto')


env.Program('mesh_compile', 
            ['mesh_compile.cc', 'lib/GL/GLee.c'] 
            + Glob('lib/*cc') + Glob('external/tinyXML/*cpp'))
env.Program('skeleton_compile', 
            ['skeleton_compile.cc', 'lib/GL/GLee.c'] 
            + Glob('lib/*cc') + Glob('external/tinyXML/*cpp'))

env.Program('Pony', 
            ['Pony.cc', 'lib/GL/GLee.c'] 
            + Glob('lib/*cc') + Glob('external/tinyXML/*cpp'))
env.Program('MapView', 
            ['MapView.cc', 'lib/GL/GLee.c'] 
            + Glob('lib/*cc') + Glob('external/tinyXML/*cpp'))
env.Program('ConfigFile', 
            ['ConfigFile.cc', 'lib/GL/GLee.c'] 
            + Glob('lib/*cc') + Glob('external/tinyXML/*cpp'))
