#ifndef PONYPOINTS_HH
#define PONYPOINTS_HH

#include "cinquo.hh"
#include "Config.hh"
#include "Texture2D.hh"

class PonyPoints
{
    vector<list<Color4f> > points;

    vector<Texture2D*> digits;

    public:

    PonyPoints(int i, Config* config);
    ~PonyPoints();

    void add_point(int i, Color4f color);
    void draw_hud(int i);

};

#endif
