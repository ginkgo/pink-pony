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


class PonyGame
{
    SplitScreen* m_screen;
    Heightmap* m_heightmap;
    Config* m_config;
    Skydome* skydome;
    
    LineList line_list;
    vector<Pony*> ponies;    

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

    bool start(PonyPoints& points);
};

#endif
