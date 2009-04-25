#include "utilities.hh"

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
        printf("%.2f ms/frame\n", ((now-last)*1000.0/frames));
        last = now;
        frames = 0;
    }
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

}
