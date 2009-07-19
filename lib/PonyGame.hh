#ifndef PONYGAME_HH
#define PONYGAME_HH

class PonyGame;

#include "cinquo.hh"
#include "Config.hh"
#include "Heightmap.hh"
#include "SplitScreen.hh"
#include "Pony.hh"
#include "Skydome.hh"
#include "LineList.hh"
#include "PonyPoints.hh"
#include "Mesh.hh"
#include "MeshDrawer.hh"
#include "ParticleSystem.hh"


class PonyGame
{
    ParticleSystem* particle_system;

    SplitScreen* m_screen;
    Heightmap* m_heightmap;
    Config* m_config;
    Skydome* skydome;

    LineList line_list;
    vector<Pony*> ponies;

    Mesh heart;
    MeshDrawer heart_drawer;
    Shader heart_shader;

    list<V2f> heart_positions;

    public:

    PonyGame(SplitScreen* screen,
             Heightmap* heightmap,
             Config* config,
             Skydome* skydome);

    ~PonyGame();

    Heightmap* terrain()
    {
        return m_heightmap;
    }

    SplitScreen* screen()
    {
        return m_screen;
    }

    Config* config()
    {
        return m_config;
    }

    LineList* linelist()
    {
        return &line_list;
    }

    list<V2f>* hearts()
    {
        return &heart_positions;
    }
    
    vector<Pony*>* ponies()
    {
        return &ponies;
    }

    bool start(PonyPoints& points);
};

#endif
