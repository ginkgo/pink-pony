#include "TransformFeedback.hh"
#include <algorithm>
#include <sstream>

using namespace std;

TransformFeedback::TransformFeedback(GLuint program,
                                     GLenum primitive_type,
                                     string varyings,
                                     GLuint max_primitives,
                                     bool   swappable)
    : front_buffer(0),
      back_buffer(0),
      query(0),
      program(program),
      primitive_type(primitive_type),
      primitive_count(0),
      swappable(swappable),
      varyings(),
      attributes()
{
    glGenQueries(1, &query);
    
    glGenBuffers(1, &back_buffer);
    if (swappable) {
        glGenBuffers(1, &front_buffer);
    } else {
        front_buffer = back_buffer;
    }

    stringstream ss(varyings);

    while(!ss.eof()) {
        Parameter varying;

        ss >> varying.name;
        varying.location = 
            glGetVaryingLocationNV(program, varying.name.c_str());
        this->varyings.push_back(varying);
    }

    getErrors();
    GLint active_varyings;
    glGetProgramiv(program, GL_ACTIVE_VARYINGS_NV, &active_varyings);

    for (GLuint i = 0; i < (GLuint)active_varyings; ++i) {

        char name[100];
        GLsizei size;
        GLenum type;
            
        glGetActiveVaryingNV(program, i,
                             100, NULL, &size, &type, name);

        for (unsigned int j = 0; j < this->varyings.size(); ++j) {
            if (this->varyings[j].name == name) {

                type_convert(type, size,
                             this->varyings[j].type,
                             this->varyings[j].size,
                             this->varyings[j].mem_size);
            }
        }

    }
    
    getErrors();    
    GLsizei size = 0;
    vector<GLint> locations;
    for (unsigned int i = 0; i < this->varyings.size(); ++i) {
        this->varyings[i].offset = size;
        size += this->varyings[i].mem_size;
        locations.push_back(this->varyings[i].location);
    }
    for (unsigned int i = 0; i < this->varyings.size(); ++i) {
        this->varyings[i].stride = size;
    }

    getErrors();
    switch (primitive_type) {
    case GL_POINTS:    size *= 1; break;
    case GL_LINES:     size *= 2; break;
    case GL_TRIANGLES: size *= 3; break;
    default:
        assert(0);
    }

    getErrors();
    glBindBuffer(GL_ARRAY_BUFFER, back_buffer);
    glBufferData(GL_ARRAY_BUFFER, max_primitives * size, NULL, GL_STATIC_DRAW);

    getErrors();

    if (swappable) {
        glBindBuffer(GL_ARRAY_BUFFER, front_buffer);
        glBufferData(GL_ARRAY_BUFFER, max_primitives * size, NULL, GL_STATIC_DRAW);
    }

    getErrors();
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    getErrors();

    glUseProgram(program);
    glTransformFeedbackVaryingsNV(program, 
                                  locations.size(), &(locations[0]),
                                  GL_INTERLEAVED_ATTRIBS_NV);

    getErrors();
}

TransformFeedback::~TransformFeedback()
{
    glDeleteQueries(1, &query);
    
    glDeleteBuffers(1, &back_buffer);
    if (swappable) {
        glDeleteBuffers(1, &front_buffer);
    }
}

void TransformFeedback::begin()
{
    glBindBufferOffsetNV(GL_TRANSFORM_FEEDBACK_BUFFER_NV, 0, back_buffer, 0);
    glBeginTransformFeedbackNV(primitive_type);
    glEnable(GL_RASTERIZER_DISCARD_NV);
    glBeginQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN_NV, query);
    getErrors();
}

void TransformFeedback::end()
{
    glEndQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN_NV);
    glEndTransformFeedbackNV();
    glDisable(GL_RASTERIZER_DISCARD_NV);
    getErrors();
}

GLuint TransformFeedback::finish()
{
    glGetQueryObjectuiv(query, GL_QUERY_RESULT, &primitive_count);

    return primitive_count;
} 

GLuint TransformFeedback::get_buffer() {
    return front_buffer;
}

int TransformFeedback::get_primitive_count() {
    return primitive_count;
}

void TransformFeedback::swap() {
    std::swap(back_buffer,front_buffer);
}

void TransformFeedback::add_draw_bindings(GLuint program, 
                                          string attributes)
{
    stringstream ss(attributes);

    vector<Parameter>& att = this->attributes[program];
    att.clear();
    
    GLint active_attributes;
    glGetProgramiv(program, GL_ACTIVE_ATTRIBUTES, &active_attributes);

    vector<Parameter>& var = this->varyings;

    getErrors();
    while(!ss.eof()) {
        Parameter attribute;
        ss >> attribute.name;
        attribute.location = 
            glGetAttribLocation(program, attribute.name.c_str());

        bool found = false;
        for (GLuint i = 0; i < (GLuint)active_attributes; ++i) {

            char name[100];
            GLsizei size;
            GLenum type;
            
            glGetActiveAttrib(program, i,
                              100, NULL, &size, &type, name);

            if (attribute.name == name) {
                type_convert(type, size,
                             attribute.type,
                             attribute.size,
                             attribute.mem_size);
                found = true;
            }

        }
        
        if (!found) {
            if (attribute.name != "_" &&
                attribute.name != "gl_Vertex" && 
                attribute.name != "gl_Color" && 
                attribute.name != "gl_Normal") 
                cerr << "Could not find vertex attrib " 
                     << "\"" << attribute.name << "\"" << "." << endl;
            attribute.type = var[att.size()].type;
            attribute.size = var[att.size()].size;
            attribute.mem_size = var[att.size()].mem_size;
        }

        att.push_back(attribute);
    }
       
    getErrors(); 
    GLsizei size = 0;
    for (unsigned int i = 0; i < att.size(); ++i) {
        att[i].offset = size;
        size += att[i].mem_size;
    }
    for (unsigned int i = 0; i < att.size(); ++i) {
        att[i].stride = size;
    }

    getErrors();

    assert(att.size() == var.size());

    for (GLuint i = 0; i < att.size(); ++i) {
        if (att[i].type != var[i].type ||
            att[i].size != var[i].size ||
            att[i].mem_size != var[i].mem_size ||
            att[i].stride != var[i].stride ||
            att[i].offset != var[i].offset) {
            
            cerr << "TransformFeedback: varying " 
                 << var[i].name << " and attribute " << att[i].name
                 << " are incompatible." << endl;
        }
    } 

    getErrors();
}

void TransformFeedback::del_draw_bindings(GLuint program)
{
    attributes.erase(program);
}

void TransformFeedback::draw(GLuint program)
{
    glBindBuffer(GL_ARRAY_BUFFER, front_buffer);

    getErrors();
    vector<Parameter>& att = attributes[program];

    for (GLuint i = 0; i < att.size(); ++i) {
        if (att[i].location != -1) {
            glEnableVertexAttribArray(att[i].location);
            glVertexAttribPointer(att[i].location,
                                  att[i].size, att[i].type,
                                  GL_FALSE, att[i].stride,
                                  ((char*)0) + att[i].offset);
        } else if (att[i].name == "gl_Vertex") {
            glEnableClientState(GL_VERTEX_ARRAY);
            glVertexPointer(att[i].size, att[i].type, att[i].stride, 
                            ((char*)0) + att[i].offset);
        } else if (att[i].name == "gl_Color") {
            glEnableClientState(GL_COLOR_ARRAY);
            glColorPointer(att[i].size, att[i].type, att[i].stride, 
                           ((char*)0) + att[i].offset);
        } else if (att[i].name == "gl_Normal") {
            glEnableClientState(GL_NORMAL_ARRAY);
            glNormalPointer(att[i].type, att[i].stride, 
                            ((char*)0) + att[i].offset);
        }
        getErrors();
    }

    getErrors();
    int n = 0;
    switch (primitive_type) {
    case GL_POINTS: n = 1; break;
    case GL_LINES: n = 2; break;
    case GL_TRIANGLES: n = 3; break;
    default: assert(0);
    }

    getErrors();
    glDrawArrays(primitive_type,
                 0, n * primitive_count);

    for (GLuint i = 0; i < att.size(); ++i) {
        if (att[i].location != -1) {
            glDisableVertexAttribArray(att[i].location);
        } else if (att[i].name == "gl_Vertex") {
            glDisableClientState(GL_VERTEX_ARRAY);
        } else if (att[i].name == "gl_Color") {
            glDisableClientState(GL_COLOR_ARRAY);
        } else if (att[i].name == "gl_Normal") {
            glDisableClientState(GL_NORMAL_ARRAY);
        }
    }
    getErrors();
}
