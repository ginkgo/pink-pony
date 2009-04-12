#ifndef UTILITIES_HH
#define UTILITIES_HH
#include "cinquo.hh"

void calc_fps();

template <class T> T box_map (Box<T> box, T pos) 
{
    return pos * box.size() + box.min;
};

template <class T> T box_unmap (Box<T> box, T pos)
{
    return (pos - box.min) / box.size();
};

inline void getErrors()
{
    static GLenum lastError = GL_NO_ERROR;
    GLenum errCode = GL_NO_ERROR;
    const GLubyte * errString;

    errCode = glGetError();
        
    if (errCode != lastError && errCode != GL_NO_ERROR) {
        errString = gluErrorString(errCode);
        std::cout << "OpenGL Error: " << errString << std::endl;
    }
    
    lastError = errCode;
};


inline void glColor ( const Imath::Color4f &c )
{
    glColor4f(c.r,c.g,c.b,c.a);
};

template <class T> T min(T a, T b)
{
    if (a <= b)
        return a;
    else
        return b;
};

template <class T> T max(T a, T b)
{
    if (a >= b)
        return a;
    else
        return b;
};

std::istream& operator>>(std::istream& is, V2f& v);
std::istream& operator>>(std::istream& is, V3f& v);
std::istream& operator>>(std::istream& is, Color4f& v);

#endif
