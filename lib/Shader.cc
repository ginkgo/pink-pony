#include "Shader.hh"

#include <fstream>
#include <sstream>

#define LOG_BUFFER_SIZE 1024

using namespace std;
string read_file(string file_name)
{
    ifstream is;
    string tmp;
    stringstream buffer;
 
    is.open(file_name.c_str());

    while(getline(is, tmp)) {
        buffer << tmp << endl;
    };

    is.close();
  
    return buffer.str(); 
};

void program_log(GLuint program)
{
    char logBuffer[LOG_BUFFER_SIZE];
    GLsizei length;
  
    logBuffer[0] = '\0';
    glGetProgramInfoLog(program, LOG_BUFFER_SIZE, &length,logBuffer);
  
    if (length > 0) {
        cout << logBuffer << endl;
    }
};

void shader_log(GLuint shader)
{
    char logBuffer[LOG_BUFFER_SIZE];
    GLsizei length;
  
    logBuffer[0] = '\0';
    glGetShaderInfoLog(shader, LOG_BUFFER_SIZE, &length,logBuffer);

    if (length > 0) {
        cout << logBuffer << endl;
    }
};

GLuint compile_shader(const char* source, string name, GLenum type)
{
    GLint status;
    GLuint shader = GL_FALSE;
  
    shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if (!status || !glIsShader(shader)) {
        cout << name << ": Compilation failed." << endl;
        shader_log(shader);
    };

    return shader;
};

Shader::Shader(string file_name)
    : vertex_source(""),
      geometry_source(""),
      fragment_source(""),
      vertex_shader(0),
      geometry_shader(0),
      fragment_shader(0),
      program(0)
{
    program = 0;
    vertex_shader = 0;
    fragment_shader = 0;
 
    GLint status = GL_FALSE;
  
    vertex_source = read_file(file_name + string(".vert"));
    fragment_source = read_file(file_name + string(".frag"));

    vertex_shader = compile_shader(vertex_source.c_str(),
                                   file_name + string(".vert"),
                                   GL_VERTEX_SHADER);
  
    fragment_shader = compile_shader(fragment_source.c_str(),
                                     file_name + string(".frag"),
                                     GL_FRAGMENT_SHADER);
  
    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);

    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &status);

    if (!status || !glIsProgram(program)) {
        cout << "Linking failed." << endl;
        program_log(program);
    };

    getErrors();
};

Shader::Shader(string vertex_shader_file,
               string fragment_shader_file)
    : vertex_source(""),
      geometry_source(""),
      fragment_source(""),
      vertex_shader(0),
      geometry_shader(0),
      fragment_shader(0),
      program(0)
{
    program = 0;
    vertex_shader = 0;
    fragment_shader = 0;
 
    GLint status = GL_FALSE;
  
    vertex_source = read_file(vertex_shader_file + string(".vert"));
    fragment_source = read_file(fragment_shader_file + string(".frag"));

    vertex_shader = compile_shader(vertex_source.c_str(),
                                   vertex_shader_file + string(".vert"),
                                   GL_VERTEX_SHADER);
  
    fragment_shader = compile_shader(fragment_source.c_str(),
                                     fragment_shader_file + string(".frag"),
                                     GL_FRAGMENT_SHADER);
  
    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);

    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &status);

    if (!status || !glIsProgram(program)) {
        cout << "Linking failed." << endl;
        program_log(program);
    };

    getErrors();
};

Shader::Shader(string vertex_shader_file,
               string geometry_shader_file,
               string fragment_shader_file,
               GLenum geometry_input_type,
               GLenum geometry_output_type,
               GLint  geometry_vertex_out)
    : vertex_source(""),
      geometry_source(""),
      fragment_source(""),
      vertex_shader(0),
      geometry_shader(0),
      fragment_shader(0),
      program(0)
{
    program = 0;
    vertex_shader = 0;
    fragment_shader = 0;
 
    GLint status = GL_FALSE;
  
    vertex_source = read_file(vertex_shader_file + string(".vert"));
    geometry_source = read_file(geometry_shader_file + string(".geom"));
    fragment_source = read_file(fragment_shader_file + string(".frag"));


    vertex_shader = compile_shader(vertex_source.c_str(),
                                   vertex_shader_file + string(".vert"),
                                   GL_VERTEX_SHADER);
  
    geometry_shader = compile_shader(geometry_source.c_str(),
                                     geometry_shader_file + string(".geom"),
                                     GL_GEOMETRY_SHADER_EXT);
  
    fragment_shader = compile_shader(fragment_source.c_str(),
                                     fragment_shader_file + string(".frag"),
                                     GL_FRAGMENT_SHADER);
  
    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, geometry_shader);
    glAttachShader(program, fragment_shader);

    glProgramParameteriEXT(program, 
                           GL_GEOMETRY_INPUT_TYPE_EXT, 
                           geometry_input_type);
    glProgramParameteriEXT(program, 
                           GL_GEOMETRY_OUTPUT_TYPE_EXT, 
                           geometry_output_type);
    glProgramParameteriEXT(program,
                           GL_GEOMETRY_VERTICES_OUT_EXT, 
                           geometry_vertex_out);

    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &status);

    if (!status || !glIsProgram(program)) {
        cerr << "Linking failed." << endl;
        program_log(program);
    };

    getErrors();
};

Shader::~Shader()
{
    glDeleteProgram(program);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

void Shader::bind()
{
    glUseProgram(program);
    getErrors();
};

void Shader::unbind()
{
    glUseProgram(0);
};

void Shader::print_fragment_source()
{
    cout << fragment_source;
};

void Shader::print_vertex_source()
{
    cout << vertex_source;
};
