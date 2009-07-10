#include "Texture2D.hh"
#include <memory>
#include <ImathBoxAlgo.h>

using namespace Imath;

bool Texture2D::initialized_IL = false;

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
  : pixels(0),
    min_filter(min_filter),
    mag_filter(mag_filter)
{
    if (!initialized_IL) {
        initialized_IL = true;
        ilInit();
        ilutInit();
        ilEnable(IL_ORIGIN_SET);
        ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
    }

    cout << "Loading file \"" << path << "\"";
    cout.flush();

    ILuint image;

    ilGenImages(1, &image);
    ilBindImage(image);

    bool success = ilLoadImage(path);

    if (!success) {
        cerr << " Failed";
    }
    
    size.x = ilGetInteger(IL_IMAGE_WIDTH);
    size.y = ilGetInteger(IL_IMAGE_HEIGHT);
    ILenum il_format = ilGetInteger(IL_IMAGE_FORMAT);

    if (il_format == IL_LUMINANCE) {
        pixels = new float[size.x * size.y];
        ilCopyPixels(0,0,0,
                     size.x,size.y,1,
                     IL_LUMINANCE, IL_FLOAT,
                     pixels);
        format = GL_LUMINANCE;
    } else {
        pixels = new float[size.x * size.y * 4];
        ilCopyPixels(0,0,0,
                     size.x,size.y,1,
                     IL_RGBA, IL_FLOAT,
                     pixels);
        format = GL_RGBA;
    }

    ilDeleteImages(1, &image);
    
    setup(wrapS, wrapT, mag_filter, min_filter);

    cout << " - Done: " << size.x << "x" << size.y << " pixels." << endl;
};

Texture2D::~Texture2D()
{
    glDeleteTextures(1, &texture_name);
    delete pixels;
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
                          format,         // format
                          GL_FLOAT,        // type
                          pixels);  // *pixels
    } else {
        glTexImage2D(GL_TEXTURE_2D,   // target
                     0,               // level
                     GL_LUMINANCE32F_ARB,  // internalFormat
                     size.x,          // width
                     size.y,          // height
                     0,               // border
                     format,         // format
                     GL_FLOAT,        // type
                     pixels);  // *pixels
    }
    
    glBindTexture(GL_TEXTURE_2D, active_texture);
};

void Texture2D::build_mipmaps()
{
    GLint active_texture;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &active_texture);

    if (active_texture == (GLint)texture_name) {
        glGenerateMipmapEXT(GL_TEXTURE_2D);
    } else {
        glBindTexture(GL_TEXTURE_2D, texture_name);
        glGenerateMipmapEXT(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, active_texture);
    }
};


Color4f Texture2D::get_color(V2u pos)
{
    Box<V2u> box(V2u(0,0), size - V2u(1,1));
    pos = clip(pos, box);
    return ((Color4f*)pixels)[pos.y * size.x + pos.x];
};

float Texture2D::get_value(V2u pos)
{
    Box<V2u> box(V2u(0,0), size - V2u(1,1));
    pos = clip(pos, box);
    return pixels[pos.y * size.x + pos.x];
};

Color4f Texture2D::get_color(V2f pos)
{
    if (format == GL_LUMINANCE) {
        float v = get_value(pos);
        return Color4f(v,v,v,v);
    }

    V2f uv(pos.x * size.x, pos.y * size.y);
    V2f ab(frac(uv.x - 0.5), frac(uv.y - 0.5));
    V2u ij(floor(uv.x - 0.5), floor(uv.y - 0.5));

    Color4f ll = get_color(ij+V2u(0,0));
    Color4f lr = get_color(ij+V2u(1,0));
    Color4f ul = get_color(ij+V2u(0,1));
    Color4f ur = get_color(ij+V2u(1,1));
    
    Color4f r = (ll * ((1 - ab.x) * (1 - ab.y)) +
               lr * (  (ab.x) *   (1 - ab.y)) +
               ul * ((1 - ab.x) * (ab.y)) +
               ur * (  (ab.x) *   (ab.y)));
    
    return r;
}

float Texture2D::get_value(V2f pos)
{
    if (format == GL_RGBA) {
        return get_color(pos).r;
    }

    V2f uv(pos.x * size.x, pos.y * size.y);
    V2f ab(frac(uv.x - 0.5), frac(uv.y - 0.5));
    V2u ij(floor(uv.x - 0.5), floor(uv.y - 0.5));

    float ll = get_value(ij+V2u(0,0));
    float lr = get_value(ij+V2u(1,0));
    float ul = get_value(ij+V2u(0,1));
    float ur = get_value(ij+V2u(1,1));
    
    float r = (ll * ((1 - ab.x) * (1 - ab.y)) +
               lr * (  (ab.x) *   (1 - ab.y)) +
               ul * ((1 - ab.x) * (ab.y)) +
               ur * (  (ab.x) *   (ab.y)));
    
    return r;
}

void Texture2D::normalize()
{

    if (format == GL_RGBA) {
        Color4f max_color(0,0,0,0);
        Color4f* rgba_pixels = (Color4f*)pixels;
    
        for (unsigned int i = 0; i < size.x * size.y; i++) {
            max_color.r = max(max_color.r, rgba_pixels[i].r);
            max_color.g = max(max_color.g, rgba_pixels[i].g);
            max_color.b = max(max_color.b, rgba_pixels[i].b);
            max_color.a = max(max_color.a, rgba_pixels[i].a);
        }
    
        for (unsigned int i = 0; i < size.x * size.y; i++) {                
            rgba_pixels[i].r = rgba_pixels[i].r / max_color.r;
            rgba_pixels[i].g = rgba_pixels[i].g / max_color.g;
            rgba_pixels[i].b = rgba_pixels[i].b / max_color.b;
            rgba_pixels[i].a = rgba_pixels[i].a / max_color.a;
        }
    } else {
        float max_value = 0;
    
        for (unsigned int i = 0; i < size.x * size.y; i++) {
            max_value = max(max_value, pixels[i]);
        }
    
        for (unsigned int i = 0; i < size.x * size.y; i++) {                
            pixels[i] = pixels[i] / max_value;
        }
    }
    
}
