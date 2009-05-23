#ifndef PONY_HH
#define PONY_HH

class Pony;

#include "cinquo.hh"
#include "PonyGame.hh"
#include "Camera.hh"
#include "Texture2D.hh"
#include "Mesh.hh"
#include "MeshDrawer.hh"
#include "ParticleSystem.hh"

class Pony
{    
    V2f pos;
    float angle;
    float speed;
    float slope_angle;
    V2f camera_pos;

    int up, down, left, right;

    Shader shader;
    Mesh mesh;
    MeshDrawer mesh_drawer;
    Texture2D texture;

    bool out;
    bool out_delay;

    PonyParticleSource particle_source;
    
    public:

    //Camera camera;
    
    Pony(V2f pos, float angle, float speed,
         int up, int down, int left, int right,
         Config* config, ParticleSystem* particle_system);         

    V2f get_pos()
    {
        return pos;
    }
    
    void move(PonyGame* game, double timeDiff, int i);
    void set_camera(PonyGame* game, Camera* camera, int i);
    void draw(PonyGame* game, int i);

    void set_out(bool out) {
        particle_source.explode(50000);
        particle_source.set_rate(0);
        this->out = out;
    }
    
    bool is_out(void) {
        return out;
    }
};

#endif
