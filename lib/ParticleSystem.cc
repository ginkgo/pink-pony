#include "ParticleSystem.hh"
#include <ImathRandom.h>
#include "Camera.hh"
#include <ImathColorAlgo.h>

using std::set;

ParticleSystem::ParticleSystem(GLuint max_particles,
                               Config* config)
    : last_stat_print(glfwGetTime()),sources(), calculating(false),
      step_shader("GLSL/step_particles",
                  "GLSL/step_particles",
                  "GLSL/step_particles",
                  GL_POINTS, GL_POINTS, 1),
      draw_shader("GLSL/draw_particles",
                  "GLSL/draw_particles",
                  "GLSL/draw_particles",
                  GL_POINTS, GL_TRIANGLE_STRIP, 4),
      feedback(step_shader, GL_POINTS,
               "out_pos out_color out_vel out_life",
               max_particles, true),
      particle_tex("textures/heart-particle.png"),
      heightmap(config->heightmap_file.c_str())
{
    heightmap.normalize();
    heightmap.send_to_GPU();

    feedback.add_draw_bindings(step_shader,
                               "gl_Vertex gl_Color vel life");
    feedback.add_draw_bindings(draw_shader,
                               "gl_Vertex gl_Color _ _");

    vel_attrib = step_shader.get_attribute_location("vel");
    life_attrib = step_shader.get_attribute_location("life");

    step_shader.bind();
    step_shader.set_uniform("water_level", config->water_level);
    step_shader.set_uniform("level_size", config->level_size.size());
    step_shader.unbind();
}

ParticleSystem::~ParticleSystem()
{
    for (set<ParticleSource*>::iterator i = sources.begin();
         i != sources.end(); ++i) {
        (*i)->remove_link();
    }
}

void ParticleSystem::step_simulation(float time_diff)
{
    step_shader.bind();
    step_shader.set_uniform("time_diff", time_diff);

    heightmap.bind(GL_TEXTURE0);

    step_shader.set_uniform("heightmap", 0);

    feedback.begin();

    glBegin(GL_POINTS);

    Particle p;

    for (set<ParticleSource*>::iterator i = sources.begin();
         i != sources.end(); ++i) {
        while ((*i)->has_particle()) {
            (*i)->get_particle(p);

            glVertexAttrib3f(vel_attrib, p.vel.x, p.vel.y, p.vel.z);
            glVertexAttrib1f(life_attrib, p.life);
            glColor(p.color);
            glVertex(p.pos);
        }
    }
    
    glEnd();

    feedback.draw(step_shader);
    feedback.end();

    heightmap.unbind(GL_TEXTURE0);

    step_shader.unbind();

    calculating = true;


    // Statistics output

    if (glfwGetTime() - last_stat_print > 10.0) {
        last_stat_print = glfwGetTime();

        cout << feedback.get_primitive_count() << " particles." << endl;
    }
}

void ParticleSystem::draw(Camera& camera)
{
    if (calculating) {
        GLuint i = feedback.finish();
        feedback.swap();
        calculating = false;
    }
    
    V3f up, right;
    
    camera.get_billboard_axes(up, right);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE,GL_ONE);
    glBlendEquation(GL_FUNC_ADD);

    glDepthMask(GL_FALSE);
    
    draw_shader.bind();
    
    particle_tex.bind(GL_TEXTURE0);

    draw_shader.set_uniform("up", up);
    draw_shader.set_uniform("right", right);
    draw_shader.set_uniform("texture", 0);

    feedback.draw(draw_shader);

    draw_shader.unbind();

    particle_tex.unbind(GL_TEXTURE0);


    glDisable(GL_BLEND);

    glDepthMask(GL_TRUE);
}

void ParticleSystem::add_source(ParticleSource* source) 
{
    sources.insert(source);
}

void ParticleSystem::del_source(ParticleSource* source) 
{
    sources.erase(source);
}

StaticParticleSource::StaticParticleSource(ParticleSystem* system,
                                           V3f position,
                                           double rate, 
                                           Color4f color)
    : ParticleSource(system),
      time(0.0), rate(1.0/rate), position(position), color(color),
      rand((unsigned long)(100000*glfwGetTime())){}

bool StaticParticleSource::has_particle()
{
    return (time > rate);
}

void StaticParticleSource::get_particle(Particle& p) {
    time -= rate;

    p.pos = position + Imath::solidSphereRand<V3f, Rand32>(rand) * 10;
    V3f c = hsv2rgb(V3f(rand.nextf(0.75,0.95),
                        rand.nextf(0.8,1.0),
                        rand.nextf(0.4,0.6)));
    p.color = Color4f(c.x,c.y,c.z,1);
    p.life = 10.0f + rand.nextf(0.0,20.0);
    
    p.vel = V3f(0,0,0);

    p.vel = (Imath::hollowSphereRand<V3f, Rand32>(rand)  
             * (fabs(Imath::gaussRand(rand)) + 2)
             * 50);


} 

PonyParticleSource::PonyParticleSource(ParticleSystem* system)
    : ParticleSource(system),
      time(0.0), rate(1.0/rate),
      pos(0,0,0), dir(0,1,0), color(1,0,0,1),
      explosion_particles(0),
      rand((unsigned long)(100000*glfwGetTime())){}

bool PonyParticleSource::has_particle()
{
    return (explosion_particles > 0 || 
            (rate > 0.0 && time > rate));
}

void PonyParticleSource::get_particle(Particle& p) {
    if (explosion_particles > 0) {
        --explosion_particles;
        p.pos = pos - V3f(0,4,0) + Imath::solidSphereRand<V3f, Rand32>(rand) * 2;
        V3f hsv = rgb2hsv(V3f(color.r,color.g,color.b));
        
        V3f c   = hsv2rgb(V3f(frac(hsv.x + gaussRand(rand) / 8.0),
                              1.0,
                              rand.nextf(0.4,0.6)));
        p.color = Color4f(c.x,c.y,c.z,1);
        p.life = 10.0f + rand.nextf(0.0,20.0);
        
        p.vel = V3f(0,0,0);
        
        p.vel = (Imath::hollowSphereRand<V3f, Rand32>(rand)  
                 * (fabs(Imath::gaussRand(rand)) + 2)
                 * 10);

    } else if (rate > 0.0) {
        time -= rate;
        
        V3f offset = Imath::solidSphereRand<V3f, Rand32>(rand) * 3;

        p.pos   = pos + offset;   
        V3f hsv = rgb2hsv(V3f(color.r,color.g,color.b));
        
        V3f c   = hsv2rgb(V3f(frac(hsv.x + gaussRand(rand) / 8.0),
                              1.0,
                              rand.nextf(0.4,0.6)));
        p.color = Color4f(c.x,c.y,c.z,1);
        p.life  = 10.0f + rand.nextf(0.0,20.0);
    
        p.vel   = -dir * 10 + offset * 1;

    }
}

void PonyParticleSource::set_pos(V3f pos) {
    this->pos = pos;
}

void PonyParticleSource::set_dir(V3f dir) {
    this->dir = dir;
}

void PonyParticleSource::set_color(Color4f color) {
    this->color = color;
}

void PonyParticleSource::set_rate(double rate) {
    if (rate > 0.0) {
        this->rate = 1.0/rate;
    } else {
        this->rate = -1.0;
    }
}

void PonyParticleSource::explode(int particles) {
    explosion_particles += particles;
}
