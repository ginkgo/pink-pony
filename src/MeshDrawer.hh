#ifndef MESHDRAWER_HH
#define MESHDRAWER_HH

#include "cinquo.hh"
#include "Mesh.hh"

class Shader;

class MeshDrawer
{
    private:

    Mesh* mesh;

    bool using_vbo;
    
    GLuint index_buffer;
    int index_count;
    int vertex_count;
    GLuint layer_buffer;

    struct LayerBuffer
    {
        string name;
        int columns;
        void* offset;

        GLint attribute_location;

        LayerBuffer();
        LayerBuffer(string n, int c, void* o) 
            : name(n), columns(c), offset(o) {};
    };

    vector<LayerBuffer> layers;

    void draw_vertex_array(Shader* shader);
    void draw_vertex_buffer_object(Shader* shader);

    public:

    MeshDrawer(Mesh* mesh) 
        : mesh(mesh), 
          using_vbo(false),
          index_buffer(0),
          index_count(0),
          layer_buffer(0) {};

    ~MeshDrawer() {
        free_vbo();
    }
    
    bool has_vbo() { return using_vbo;};
    void make_vbo();
    void free_vbo();

    void draw(Shader* shader);    
};

#endif
