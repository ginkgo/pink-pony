#ifndef UTILITIES_HH
#define UTILITIES_HH
#include "cinquo.hh"

#include <sstream>

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

inline V3f reflect (V3f I, V3f N) 
{
    return I - 2 * (N^I) * N;
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

template<class T> T parse(string s)
{
    T t;
    std::stringstream ss(s);
    ss >> t;
    return t;
}

template<class T> string to_string(T t)
{
    std::stringstream ss;
    ss << t;
    return ss.str();
}

void read_tokens(const string& input, vector<const char*>& token_list);
void free_tokens(vector<const char*>& token_list);

bool file_exists(const string& filename);
void make_screenshot();

#endif
