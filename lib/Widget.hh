#ifndef WIDGET_HH
#define WIDGET_HH

#include <ImathBox.h>
#include <FTGL/ftgl.h>

#include "Texture2D.hh"

#include <sigc++/sigc++.h>

class Widget
{    
    protected:

    float aspect;
    Box2f extent;    

    Widget(float aspect) 
        : aspect(aspect) {};

    sigc::signal<void> signal_clicked;

    public:

    virtual void  set_available_area(Box2f area);
    
    Box2f get_extent(void) 
    {
        return extent;
    }

    virtual void area_clicked(V2f pos) = 0;
    virtual void draw(void) = 0;

    sigc::signal<void>& on_click()
    {
        return signal_clicked;
    }
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

class SimpleLayout : public Widget
{
    Box2f own_size;
    map<Widget*, Box2f> widgets;

    public:

    SimpleLayout() 
        : Widget(1.0) {}

    void add_widget(Widget* widget, Box2f rel_pos);
    void remove_widget(Widget* widget);

    virtual void set_available_area(Box2f area);

    virtual void area_clicked(V2f pos);
    virtual void draw(void);
};

#endif
