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

template <class T> T frac (T x)
{
    return x - floor(x);
}

void getErrors();


inline void glColor ( const Imath::Color4f &c )
{
    glColor4f(c.r,c.g,c.b,c.a);
}

void type_convert( GLenum in_type, GLsizei in_size,
                   GLenum& out_type, GLsizei& out_size,
                   GLsizei& byte_size);

std::istream& operator>>(std::istream& is, V2f& v);
std::istream& operator>>(std::istream& is, V3f& v);
std::istream& operator>>(std::istream& is, Color4f& v);

#endif
