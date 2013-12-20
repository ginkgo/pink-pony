#ifndef DRAWABLE_HH
#define DRAWABLE_HH

#include "DrawResource.hh"

class Drawable
{
    public:

    virtual void get_resources(list<DrawResource*>& resources) {};

    virtual void draw_depth() = 0;
    virtual void draw() = 0;
    
    virtual ~Drawable() {};
}


#endif
