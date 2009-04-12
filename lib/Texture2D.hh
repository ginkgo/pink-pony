#pragma once

#include "cinquo.hh"
#include <ImathBox.h>
#include <ImfArray.h>
#include <ImathBoxAlgo.h>

/**
 * Texture2D is our RGBA image texture class.
 * It features several methods for loading the texel data, like direct file
 * access, or creating a blank texture on construction.
 */
class Texture2D
{
    private:
    /**
     * The pixel-data of the texture.
     */
    Imf::Array2D<Color4f> pixels;
    GLenum min_filter;
    GLenum mag_filter;
    GLuint texture_name;

    /**
     * The size of the texture.
     */
    V2u size;

    public:

    /**
     * Loads a texture from a file.
     * The loader will check the file-extension, to find out the format of the
     * image.
     * At the moment, only OpenEXR ist supported.
     */
    Texture2D(	const char* path,
                GLenum wrapS = GL_REPEAT,
                GLenum wrapT = GL_REPEAT,
                GLenum magFilter = GL_LINEAR,
                GLenum minFilter = GL_LINEAR_MIPMAP_LINEAR);

    /**
     * Creates a blank texture.
     * This can be useful for procedural textures e.g. for effects or for the
     * preparation of a renderbuffer.
     */
    Texture2D(	V2u size,
                Color4f color = Color4f(0.0),
                GLenum wrapS = GL_REPEAT,
                GLenum wrapT = GL_REPEAT,
                GLenum magFilter = GL_LINEAR,
                GLenum minFilter = GL_LINEAR_MIPMAP_LINEAR);

    ~Texture2D();

    //! Returns the size of the texture.
    V2u get_size()
    {
        return size;
    };

    //! Returns a reference to the pixel data
    Color4f* get_pixels()
    {
        return &(pixels[0][0]);
    };

    Color4f get_color(V2u pos)
    {
        Box<V2u> box(V2u(0,0), size - V2u(1,1));
        pos = clip(pos, box);
        return pixels[pos.y][pos.x];
    };
    
    Color4f get_color(V2f pos);
    
    /**
     * Load the pixel data as texture.
     * You only have to use this, when the pixel-data has changed.
     * This will be done automatically, a Texture-contruction.
     */
    void send_to_GPU();

    /**
     * Rebuild the mipmap-Levels of the texture.
     */
    void build_mipmaps();

    /**
     * Bind/unbind a texture to a texture unit
     */
    void bind(GLuint texUnit);
    void unbind(GLuint texUnit);

    /**
     * Returns the openGL texture name of this texture.
     */
    GLuint get_texture_name()
    {
        return texture_name;
    };

    void normalize();

    private:

    void setup(	GLenum wrapS,
                GLenum wrapT,
                GLenum magFilter,
                GLenum minFilter);
};
