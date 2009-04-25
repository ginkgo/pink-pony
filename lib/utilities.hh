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

void getErrors();


inline void glColor ( const Imath::Color4f &c )
{
    glColor4f(c.r,c.g,c.b,c.a);
}

std::istream& operator>>(std::istream& is, V2f& v);
std::istream& operator>>(std::istream& is, V3f& v);
std::istream& operator>>(std::istream& is, Color4f& v);

#endif
