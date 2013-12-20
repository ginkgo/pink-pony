#ifndef SKYDOME_HH
#define SKYDOME_HH

#include "cinquo.hh"
#include "Texture2D.hh"

class Skydome
{
    Texture2D texture;

    public:

    Skydome(string texture_file);

    void draw();
};

#endif
