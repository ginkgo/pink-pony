#ifndef HEIGHTMAP_HH
#define HEIGHTMAP_HH

class Heightmap;

#include "cinquo.hh"
#include "Texture2D.hh"
#include "Shader.hh"
#include "Config.hh"
#include <vector>
#include "Mesh.hh"
#include "MeshDrawer.hh"

class Heightmap
{
    Mesh mesh;
    MeshDrawer mesh_drawer;

    Shader terrain_shader;
    Shader water_shader;
    
    Texture2D heightmap;
    Texture2D sand_texture;
    Texture2D grass_texture;
    Texture2D noise_texture;

    
    Box3f extent;
    float water_level;
    
    V2u resolution;
    
    public:

    Heightmap(string filename,
              Box3f extent, float water_level,
              string sand, string grass, string noise);
    virtual ~Heightmap();

    V2u size()
    {
        return heightmap.get_size();
    }
    
    void set_resolution(V2u new_resolution);
    
    virtual void draw(Config* config);
    V3f get_pos(V2f position, bool with_water=true);

    bool below_water(V2f position, float tolerance) {
        V3f p = get_pos(position, false);
        
        return (p.y + tolerance <= water_level);
    }
};

#endif
