#pragma once

#include "cinquo.hh"

class Shader
{
    std::string vertex_source;
    std::string fragment_source;

    GLuint vertex_shader;
    GLuint fragment_shader;
    GLuint program;

    public:

    Shader(std::string file_name);

    ~Shader();

    void print_fragment_source();

    void print_vertex_source();

    void bind();
    void unbind();

    void free();

    void print_info()
    {
        std::cout << program << " " << vertex_shader << " " << fragment_shader << std::endl;
    }
  
    void release()
    {
        glUseProgram(0);
    };

    GLint get_attribute_location(std::string name)
    {
        return glGetAttribLocation(program, name.c_str());
    }

    void set_uniform(const char* uniform, GLint value)
    {
        GLint uniformLocation = glGetUniformLocation(program, uniform);
        glUniform1i(uniformLocation, value);
    };

    void set_uniform(const char* uniform, GLfloat value)
    {
        GLint uniformLocation = glGetUniformLocation(program, uniform);
        glUniform1f(uniformLocation, value);
    };

    void set_uniform(const char* uniform, const Color4f &color)
    {
        GLint uniformLocation = glGetUniformLocation(program, uniform);
        glUniform4fv(uniformLocation, 1, (GLfloat*)&color);
    };

    void set_uniform(const char* uniform, const V2f &vector)
    {
        GLint uniformLocation = glGetUniformLocation(program, uniform);
        glUniform2fv(uniformLocation, 1, (GLfloat*)&vector);
    };

    void set_uniform(const char* uniform, const V3f &vector)
    {
        GLint uniformLocation = glGetUniformLocation(program, uniform);
        glUniform3fv(uniformLocation, 1, (GLfloat*)&vector);
    };

    void set_uniform(const char* uniform, const V3i &vector)
    {
        V3f v(vector.x,vector.y,vector.z);
        GLint uniformLocation = glGetUniformLocation(program, uniform);
        glUniform3fv(uniformLocation, 1, (GLfloat*)&v);
    };

    void set_uniform(const char* uniform, const M44f &matrix)
    {
        GLint uniformLocation = glGetUniformLocation(program, uniform);
        glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, (GLfloat*)&matrix);
    };

    void set_uniform1(const char* uniform, float *elements, int count)
    {
        GLint uniformLocation = glGetUniformLocation(program, uniform);
        glUniform1fv(uniformLocation, count, elements);
    };

    void set_uniform2(const char* uniform, float *elements, int count)
    {
        GLint uniformLocation = glGetUniformLocation(program, uniform);
        glUniform2fv(uniformLocation, count, elements);
    };

    void set_uniform3(const char* uniform, float *elements, int count)
    {
        GLint uniformLocation = glGetUniformLocation(program, uniform);
        glUniform3fv(uniformLocation, count, elements);
    };

    void set_uniform4(const char* uniform, float *elements, int count)
    {
        GLint uniformLocation = glGetUniformLocation(program, uniform);
        glUniform4fv(uniformLocation, count, elements);
    };

};
