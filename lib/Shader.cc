#include "Shader.hh"

#include <fstream>
#include <sstream>

#define LOG_BUFFER_SIZE 1024

using namespace std;
string read_file(string fileName)
{
    ifstream is;
    string tmp;
    stringstream buffer;
 
    is.open(fileName.c_str());

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

Shader::Shader(string fileName)
{

    GLint status = GL_FALSE;

    free();
  
    vertex_source = read_file(fileName + string(".vert"));
    fragment_source = read_file(fileName + string(".frag"));

    vertex_shader = compile_shader(vertex_source.c_str(),
                                   fileName + string(".vert"),
                                   GL_VERTEX_SHADER);
  
    fragment_shader = compile_shader(fragment_source.c_str(),
                                     fileName + string(".frag"),
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
};

Shader::~Shader()
{
    free();
}

void Shader::bind()
{
    if (glIsProgram(program)) {
        glUseProgram(program);
    } else {
        cerr << "program is no valid GLSL program" << endl;
    }
};

void Shader::unbind()
{
    glUseProgram(0);
};

void Shader::free()
{
    if (glIsProgram(program)) {
        glDeleteProgram(program);
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);

        program = 0;
    }
};

void Shader::print_fragment_source()
{
    cout << fragment_source;
};

void Shader::print_vertex_source()
{
    cout << vertex_source;
};
