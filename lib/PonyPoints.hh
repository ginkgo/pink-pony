#ifndef PONYPOINTS_HH
#define PONYPOINTS_HH

#include "cinquo.hh"
#include "Config.hh"

class PonyPoints
{
    vector<list<Color4f> > points;

    public:

    PonyPoints(int i) : points(i) {};

    void add_point(int i, Color4f color);
    void draw_hud(int i);

};

#endif
