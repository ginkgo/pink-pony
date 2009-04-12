#include "Texture2D.hh"
#include <ImfRgbaFile.h>
#include <ImfArray.h>
#include <memory>

using namespace Imf;


void read_exr(const char* path, Array2D<Color4f> &pixels, V2u &size)
{
    RgbaInputFile file(	path);

    Box2i dw = file.dataWindow();

    Array2D<Color4h> halfPixels;

    size.x = dw.max.x - dw.min.x + 1;
    size.y = dw.max.y - dw.min.y + 1;
    halfPixels.resizeErase(size.x, size.y);
    pixels.resizeErase(size.x, size.y);

    file.setFrameBuffer((Rgba*)&halfPixels[0][0]
                        - dw.min.x - dw.min.y * size.x,
                        1, size.y);
    file.readPixels (dw.min.y, dw.max.y);

    for (int y = 0; y < size.y; y++) {
        for (int x = 0; x < size.x; x++) {
            pixels[y][x] = Color4f(halfPixels[y][x].r,
                                   halfPixels[y][x].g,
                                   halfPixels[y][x].b,
                                   halfPixels[y][x].a);	  
        }
    }

};

void write_exr(const char* path, Array2D<Color4f> &pixels, V2u &size)
{
    RgbaOutputFile file(path, size.x, size.y, WRITE_RGBA);

    Array2D<Color4h> half_pixels;
    half_pixels.resizeErase(size.x, size.y);

    for (int y = 0; y < size.y; y++) {
        for (int x = 0; x < size.x; x++) {
            half_pixels[y][x] = Color4h(pixels[y][x].r,
                                        pixels[y][x].g,
                                        pixels[y][x].b,
                                        pixels[y][x].a);
                                        
        }
    }

    file.setFrameBuffer((Rgba*)&half_pixels[0][0],1,size.x);
    file.writePixels(size.y);       
}

void read_tga(const char* path, Array2D<Color4f> &pixels, V2u &size)
{
    GLFWimage image;

    glfwReadImage(path, &image, GLFW_NO_RESCALE_BIT);

    size.x = image.Width;
    size.y = image.Height;
    pixels.resizeErase(size.y, size.x);

    switch (image.Format){
    case GL_RGB:
        for (int x = 0; x < image.Width; x++)
            for (int y = 0; y < image.Height; y++)
                pixels[y][x] =
                    Color4f(((float)image.Data[y*image.Width*3+x*3+0])/255.0f,
                            ((float)image.Data[y*image.Width*3+x*3+1])/255.0f,
                            ((float)image.Data[y*image.Width*3+x*3+2])/255.0f,
                            1.0f);
        break;
    case GL_RGBA:
        for (int x = 0; x < image.Width; x++)
            for (int y = 0; y < image.Height; y++)
                pixels[y][x] =
                    Color4f(((float)image.Data[y*image.Width*4+x*4+0])/255.0f,
                            ((float)image.Data[y*image.Width*4+x*4+1])/255.0f,
                            ((float)image.Data[y*image.Width*4+x*4+2])/255.0f,
                            ((float)image.Data[y*image.Width*4+x*4+3])/255.0f);
        break;
    };

    glfwFreeImage(&image);

};


void Texture2D::bind(GLenum texUnit)
{
    glActiveTexture(texUnit);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_name);
    glActiveTexture(GL_TEXTURE0);
};


void Texture2D::unbind(GLenum texUnit)
{
    glActiveTexture(texUnit);
    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE0);
};

Texture2D::Texture2D(const char* path,
                     GLenum wrapS,
                     GLenum wrapT,
                     GLenum mag_filter,
                     GLenum min_filter)
  : pixels(),
    min_filter(min_filter),
    mag_filter(mag_filter)
{
    cout << "Loading file \"" << path << "\"";
    cout.flush();
    
    std::string path_string;
    path_string = std::string(path);
    std::string::size_type start = path_string.rfind(".");
    
    if (path_string.substr(start) == ".exr")
      read_exr(path, pixels, size);
    else if (path_string.substr(start) == ".tga")
      read_tga(path, pixels, size);
    
    setup(wrapS, wrapT, mag_filter, min_filter);

    cout << " - Done: " << size.x << "x" << size.y << " pixels." << endl;
};

Texture2D::Texture2D(V2u size,
                     Color4f color,
                     GLenum wrapS,
                     GLenum wrapT,
                     GLenum mag_filter,
                     GLenum min_filter)
    : pixels(),
      min_filter(min_filter),
      mag_filter(mag_filter),
      size(size)
{
    pixels.resizeErase(size.x, size.y);
  
    for (unsigned int x = 0; x < size.x; x++) {
        for (unsigned int y = 0; y < size.y; y++) {
            pixels[y][x] = color;
        }
    }
  
    setup(wrapS, wrapT, mag_filter, min_filter);
};

void Texture2D::setup( GLenum wrapS,
                       GLenum wrapT,
                       GLenum mag_filter,
                       GLenum min_filter)
{
    GLint active_texture;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &active_texture);

    glGenTextures(1, &texture_name);
    glBindTexture(GL_TEXTURE_2D, texture_name);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);

    send_to_GPU();

    glBindTexture(GL_TEXTURE_2D, active_texture);
};

void Texture2D::send_to_GPU()
{
    GLint active_texture;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &active_texture);
    
    glBindTexture(GL_TEXTURE_2D, texture_name);
    

    if (min_filter != GL_LINEAR && min_filter != GL_NEAREST) {
        gluBuild2DMipmaps(GL_TEXTURE_2D,
                          GL_RGBA8,  // internalFormat
                          size.x,          // width
                          size.y,          // height
                          GL_RGBA,         // format
                          GL_FLOAT,        // type
                          &pixels[0][0]);  // *pixels
    } else {
        glTexImage2D(GL_TEXTURE_2D,   // target
                     0,               // level
                     GL_RGBA8,  // internalFormat
                     size.x,          // width
                     size.y,          // height
                     0,               // border
                     GL_RGBA,         // format
                     GL_FLOAT,        // type
                     &pixels[0][0]);  // *pixels
    }
    
    glBindTexture(GL_TEXTURE_2D, active_texture);
};

void Texture2D::build_mipmaps()
{
    GLint active_texture;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &active_texture);

//     glMatrixMode(GL_COLOR);
//     glLoadIdentity();
//     glMatrixMode(GL_MODELVIEW);

    if (active_texture == (GLint)texture_name) {
        glGenerateMipmapEXT(GL_TEXTURE_2D);
    } else {
        glBindTexture(GL_TEXTURE_2D, texture_name);
        glGenerateMipmapEXT(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, active_texture);
    }
};

Texture2D::~Texture2D()
{
    glDeleteTextures(1, &texture_name);
};

Color4f Texture2D::get_color(V2f pos)
{
    V2f p = V2f(pos.x * size.x, pos.y * size.y);
    V2f i = p - V2f(floor(p.x), floor(p.y));

    Color4f ll = get_color(V2u(floor(p.x), floor(p.y)));
    Color4f lr = get_color(V2u(1+floor(p.x), floor(p.y)));
    Color4f ul = get_color(V2u(floor(p.x), 1+floor(p.y)));
    Color4f ur = get_color(V2u(1+floor(p.x), 1+floor(p.y)));
    
    Color4f r = (ll * ((1 - i.x) * (1 - i.y)) +
                 lr * (  (i.x) *   (1 - i.y)) +
                 ul * ((1 - i.x) * (i.y)) +
                 ur * (  (i.x) *   (i.y)));
    
    return r;
}

void Texture2D::normalize()
{

    Color4f max_color(0,0,0,0);
    
    for (unsigned int x = 0; x < size.x; x++) {
        for (unsigned int y = 0; y < size.y; y++) {

            max_color.r = max(max_color.r, pixels[y][x].r);
            max_color.g = max(max_color.g, pixels[y][x].g);
            max_color.b = max(max_color.b, pixels[y][x].b);
            max_color.a = max(max_color.a, pixels[y][x].a);
        }
    }
    
    for (unsigned int x = 0; x < size.x; x++) {
        for (unsigned int y = 0; y < size.y; y++) {

            pixels[y][x].r = pixels[y][x].r / max_color.r;
            pixels[y][x].g = pixels[y][x].g / max_color.g;
            pixels[y][x].b = pixels[y][x].b / max_color.b;
            pixels[y][x].a = pixels[y][x].a / max_color.a;
        }
    }
    
}
