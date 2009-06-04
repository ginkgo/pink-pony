#ifndef PARTICLESYSTEM_HH
#define PARTICLESYSTEM_HH

#include "cinquo.hh"
#include <ImathRandom.h>
#include <set>

#include "Shader.hh"
#include "TransformFeedback.hh"
#include "Texture2D.hh"
#include "Config.hh"

class Camera;
class ParticleSource;

struct Particle
{
    V3f pos;
    V3f vel;
    Color4f color;
    float life;
};

class ParticleSystem
{
    friend class ParticleSource;

    double last_stat_print;

    std::set<ParticleSource*> sources;

    bool calculating;

    Shader step_shader, draw_shader;

    GLint vel_attrib, life_attrib;
    TransformFeedback feedback;

    Texture2D particle_tex;
    Texture2D heightmap;

    public:

    ParticleSystem(GLuint max_particles, Config* config);
    ~ParticleSystem();

    void step_simulation(float time_diff);
    void draw(Camera& camera);


    private:


    void add_source(ParticleSource* source);
    void del_source(ParticleSource* source);

};

class ParticleSource
{
    friend class ParticleSystem;
    ParticleSystem* system;

    public:

    ParticleSource(ParticleSystem* system) 
        : system(system) { system->add_source(this);};
    virtual ~ParticleSource() { if (system!=NULL)system->del_source(this);};

    protected:
    
    virtual bool has_particle() = 0;
    virtual void get_particle(Particle& p) = 0;

    private:
    
    void remove_link() {system = NULL;}; 
};

class StaticParticleSource : ParticleSource
{
    double time;
    double rate;

    V3f position;
    Color4f color;

    Imath::Rand32 rand;

    public:

    StaticParticleSource(ParticleSystem* system,
                         V3f position, double rate, Color4f color);

    virtual void add_time(double time) {this->time += time;}

    protected:

    virtual bool has_particle();
    virtual void get_particle(Particle& p);
};

class PonyParticleSource : ParticleSource
{
    double time;
    double rate;

    V3f pos, dir;
    Color4f color;

    int explosion_particles;

    Imath::Rand32 rand;

    public:

    PonyParticleSource(ParticleSystem* system);

    void set_pos(V3f pos);
    void set_dir(V3f dir);
    void set_rate(double rate);
    void set_color(Color4f color);

    void explode(int particles);

    virtual void add_time(double time) {this->time += time;}

    protected:

    virtual bool has_particle();
    virtual void get_particle(Particle& p);
};

class ParticleExplosionSource : ParticleSource
{
    struct Explosion {
        V3f pos;
        Color4f color;
        int count;
        float var;

        Explosion() {};
        Explosion(V3f p, Color4f c, int n, float v)
            : pos(p), color(c), count(n) ,var(v){};
    };

    vector<Explosion> explosions;

    Imath::Rand32 rand;

    public:

    ParticleExplosionSource(ParticleSystem* system);

    void explode(V3f pos,
                 Color4f color,
                 int count,
                 float var);

    protected:

    virtual bool has_particle();
    virtual void get_particle(Particle& p);
};

#endif
