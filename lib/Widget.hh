#ifndef WIDGET_HH
#define WIDGET_HH

#include <ImathBox.h>
#include "Texture2D.hh"

class Widget
{    
    protected:

    float aspect;
    Box2f extent;    

    Widget(float aspect) 
        : aspect(aspect) {};

    public:


    virtual void  set_available_area(Box2f area);
    
    Box2f get_extent(void) 
    {
        return extent;
    }

    virtual void area_clicked(V2f pos) = 0;
    virtual void draw(void) = 0;
};

class Button : public Widget
{
    Texture2D texture;

    public:

    Button(string texture_file);

    //    virtual void set_available_area(Box2f area);
    //virtual Box2f get_extent(void);

    virtual void area_clicked(V2f pos);
    virtual void draw(void);
};

#endif
