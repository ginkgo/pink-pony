#ifndef WIDGET_HH
#define WIDGET_HH

#include <ImathBox.h>
#include <FTGL/ftgl.h>

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

class TextArea : public Widget
{
    FTFont* font;

    string text;
    
    public:

    TextArea(string initial_text);
    ~TextArea();

    void set_text(string text);

    virtual void  set_available_area(Box2f area);

    virtual void area_clicked(V2f pos);
    virtual void draw(void);
};

#endif
