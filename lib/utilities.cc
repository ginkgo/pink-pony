#include "utilities.hh"
#include <stdio.h>

using std::ios_base;


void getErrors()
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
}

void calc_fps()
{
    static double last = -1.0;
    static int frames = 0;

    double now = glfwGetTime();
  
    if (last < 0.0) {
        last = now;
    }

    frames += 1;

    if (now - last >= 10.0) {
        printf("%.2f ms/frame (= %d fps)\n", 
               ((now-last)*1000.0/frames),
               (int)(frames/(now-last)));
        last = now;
        frames = 0;
    }
}



void type_convert( GLenum in_type, GLsizei in_size,
                   GLenum& out_type, GLsizei& out_size,
                   GLsizei& byte_size)
{
    switch(in_type) {
    case GL_FLOAT:
        out_type = GL_FLOAT;
        out_size = in_size * 1;
        break;

    case GL_FLOAT_VEC2:
        out_type = GL_FLOAT;
        out_size = in_size * 2;
        break;

    case GL_FLOAT_VEC3:
        out_type = GL_FLOAT;
        out_size = in_size * 3;
        break;

    case GL_FLOAT_VEC4:
        out_type = GL_FLOAT;
        out_size = in_size * 4;
        break;

    case GL_INT:
        out_type = GL_INT;
        out_size = in_size * 1;
        break;

    case GL_INT_VEC2:
        out_type = GL_INT;
        out_size = in_size * 2;
        break;

    case GL_INT_VEC3:
        out_type = GL_INT;
        out_size = in_size * 3;
        break;

    case GL_INT_VEC4:
        out_type = GL_INT;
        out_size = in_size * 4;
        break;

    case GL_UNSIGNED_INT:
        out_type = GL_UNSIGNED_INT;
        out_size = in_size * 1;
        break;

    case GL_UNSIGNED_INT_VEC2_EXT:
        out_type = GL_UNSIGNED_INT;
        out_size = in_size * 2;
        break;

    case GL_UNSIGNED_INT_VEC3_EXT:
        out_type = GL_UNSIGNED_INT;
        out_size = in_size * 3;
        break;

    case GL_UNSIGNED_INT_VEC4_EXT:
        out_type = GL_UNSIGNED_INT;
        out_size = in_size * 4;
        break;

    case GL_FLOAT_MAT2:
        out_type = GL_FLOAT;
        out_size = in_size * 4;
        break;

    case GL_FLOAT_MAT3:
        out_type = GL_FLOAT;
        out_size = in_size * 9;
        break;

    case GL_FLOAT_MAT4:
        out_type = GL_FLOAT;
        out_size = in_size * 16;
        break;

    default:
        assert(0);
    }

    byte_size = 4 * out_size;
}


std::istream& operator>>(std::istream& is, V2f& v)
{
    while(is.peek() == ' ')
        is.ignore(1);
    
    if (is.peek() != '(')
        throw ios_base::failure("Missing opening parentheses");
    is.ignore(1);

    is >> v.x;
    is >> v.y;
    
    while(is.peek() == ' ')
        is.ignore(1);
    
    if (is.peek() != ')')
        throw ios_base::failure("Missing closing parentheses");
    is.ignore(1);

    return is;
}
 
std::istream& operator>>(std::istream& is, V3f& v)
{
    while(is.peek() == ' ')
        is.ignore(1);
    
    if (is.peek() != '(')
        throw ios_base::failure("Missing opening parentheses");
    is.ignore(1);

    is >> v.x;
    is >> v.y;
    is >> v.z;
    
    while(is.peek() == ' ')
        is.ignore(1);
    
    if (is.peek() != ')')
        throw ios_base::failure("Missing closing parentheses");
    is.ignore(1);

    return is;
}

std::istream& operator>>(std::istream& is, Color4f& v)
{
    while(is.peek() == ' ')
        is.ignore(1);
    
    if (is.peek() != '(')
        throw ios_base::failure("Missing opening parentheses");
    is.ignore(1);

    is >> v.r;
    is >> v.g;
    is >> v.b;
    is >> v.a;
    
    while(is.peek() == ' ')
        is.ignore(1);
    
    if (is.peek() != ')')
        throw ios_base::failure("Missing closing parentheses");
    is.ignore(1);
    
    return is;
}
