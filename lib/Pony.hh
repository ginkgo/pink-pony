#ifndef PONY_HH
#define PONY_HH

class Pony;

#include "cinquo.hh"
#include "PonyGame.hh"
#include "Camera.hh"
#include "Texture2D.hh"
#include "Mesh.hh"

class Pony
{
    Shader shader;
    Mesh mesh;
    Texture2D texture;
    
    V2f pos;
    float angle;
    V2f camera_pos;

    float speed;
    float slope_angle;

    int up, down, left, right;

    bool out;
    
    public:

    //Camera camera;
    
    Pony(V2f pos, float angle, float speed,
         int up, int down, int left, int right,
         Config* config);         

    V2f get_pos()
    {
        return pos;
    }
    
    void move(PonyGame* game, double timeDiff, int i);
    void set_camera(PonyGame* game, Camera* camera, int i);
    void draw(PonyGame* game, int i);

    void set_out(bool out) {
        this->out = out;
    }
    
    bool is_out(void) {
        return out;
    }
};

#endif
