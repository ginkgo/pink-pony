#pragma once

#include "cinquo.hh"
#include "IL/il.h"

/**
 * Texture2D is our image texture class.
 * It features several methods for loading the texel data, like direct file
 * access, or creating a blank texture on construction.
 */
class Texture2D
{
    private:
    
    static bool initialized_IL;

    /**
     * The pixel-data of the texture.
     */

    float* pixels;
    GLenum format;
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

    ~Texture2D();

    //! Returns the size of the texture.
    V2u get_size()
    {
        return size;
    };
    
    float get_value(V2u pos);
    float get_value(V2f pos);
    
    Color4f get_color(V2u pos);
    Color4f get_color(V2f pos);
    
    void set_color(V2u pos, Color4f color);

    /**
     * Load the pixel data as texture.
     * You only have to use this, when the pixel-data has changed.
     * This will be done automatically, at Texture-contruction.
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
