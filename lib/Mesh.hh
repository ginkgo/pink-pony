#ifndef MESH_HH
#define MESH_HH

#include "cinquo.hh"

class Mesh
{
    struct Layer {
        string name;
        int columns;
        int rows;
        vector<float> data;
    };

    // Mesh information
    
    map<string, Layer> layers;

    vector<GLuint> indices;

    GLenum primitive_type;

    // Draw information
    
    string vertex_layer;
    string normal_layer;
    string color_layer;
    string texcoord_layer;
    map<int, string> attrib_layers;
    
    public:

    Mesh();

    void add_layer(string name, int columns);
    void remove_layer(string name);
    void resize_layer(string name, int rows);
    float* get_layer(string name);
    int get_layer_rows(string name);
    int get_layer_cols(string name);

    // If index layer has zero length, we will use
    // glDrawArrays instead of glDrawElements.
    void resize_index_layer(int count);
    int get_index_layer_size();
    GLuint* get_index_layer();

    void set_primitive_type(GLenum primitive);
    GLenum get_primitive_type();

    // Bind layers to a specific vertex attribute.
    // To unbind, use the special layer name ""
    void set_vertex_layer(string name);
    void set_normal_layer(string name);
    void set_color_layer(string name);
    void set_texcoord_layer(string name);
    void set_attrib_layer(int attrib_id, string name);
    
    // Draws the mesh.
    void draw();

    static bool load_OgreXML(Mesh& mesh, string filename);
    
};

#endif
