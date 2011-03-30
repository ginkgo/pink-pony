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

#include "Animation.hh"

#include <ImathRandom.h>

class Pony
{
	friend class AIPony;
    protected:

    V2f pos;
    float angle;
    float speed;
    float slope_angle;
    V2f camera_pos;

    int up, down, left, right;

    Shader shader;
    Mesh mesh;
    My::Animation animation;
    MeshDrawer mesh_drawer;
    Texture2D texture;

    bool out;
    bool out_delay;

    PonyParticleSource particle_source;

    struct Decision
    {
        float acceleration;
        float steer;
    };

    virtual Decision decide(PonyGame* game, int i) = 0;

    public:

    //Camera camera;

    Pony(int i, Config* config, ParticleSystem* particle_system);

    virtual ~Pony() {};

    V2f get_pos()
    {
        return pos;
    }
    float get_angle() {
		return angle;
	}
    float get_speed() {
		return speed;
	}

    void move(PonyGame* game, double timeDiff, int i);
    void set_camera(PonyGame* game, Camera* camera, int i);
    void draw(PonyGame* game, int i);

    void set_out(bool out) {
        particle_source.set_rate(0);
        this->out = out;
    }

    bool is_out(void) {
        return out;
    }
};

class PlayerPony : public Pony
{
    protected:

    virtual Decision decide(PonyGame* game, int i);

    public:

    PlayerPony(int i, Config* config, ParticleSystem* particle_system)
        : Pony(i, config, particle_system) {};

};

class AIPony : public Pony
{
    protected:

    virtual Decision decide(PonyGame* game, int i);
	int turning;
	int lastturning;
	const static int LEFT=1,STILL=0,RIGHT=-1;
	V2f* hunting_heart;

    Imath::Rand32 rand;

    public:

    AIPony(int i, Config* config, ParticleSystem* particle_system)
        : Pony(i, config, particle_system),
          turning(STILL), lastturning(LEFT), hunting_heart(NULL) {}
};

#endif
