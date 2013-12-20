#ifndef TRANSFORMFEEDBACK_HH
#define TRANSFORMFEEDBACK_HH

#include "cinquo.hh"

class TransformFeedback
{
    // front_buffer: The buffer we use for drawing
    // back_buffer: The buffer that receives the transformed primitives.
    // if swappable = false, front- and backbuffer are identical.
    GLuint front_buffer;
    GLuint back_buffer;
    
    GLuint query;
    
    GLuint program;

    GLenum primitive_type;
    GLuint primitive_count;

    bool swappable;

    struct Parameter
    {
        string name;
        GLint location;
        GLenum type;
        GLsizei size;
        GLsizei stride;
        GLsizei mem_size;
        GLsizei offset;
    };

    vector<Parameter> varyings;
    map<GLuint,vector<Parameter> > attributes;

    public:

    TransformFeedback(GLuint program,
                      GLenum primitive_type,
                      string varyings,
                      GLuint max_primitives,
                      bool   swappable = false);

    ~TransformFeedback();

    void begin();
    void end();

    GLuint finish();
    
    GLuint get_buffer();
    GLint get_primitive_count();

    void swap();

    void add_draw_bindings(GLuint program,
                           string attributes);
    void del_draw_bindings(GLuint program);
    void draw(GLuint program);
};

#endif
