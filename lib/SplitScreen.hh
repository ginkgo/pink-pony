#ifndef SPLITSCREEN_HH
#define SPLITSCREEN_HH

#include "cinquo.hh"
#include "Camera.hh"

class SplitScreen
{
    V2i size;

    int subscreen_count;
    vector<Box2i> subscreens;
    vector<Camera> cameras;

    int current;
    
    public:

    SplitScreen(int width, int height, int subscreens);
    ~SplitScreen();

    V2i get_size()
    {
        return size;
    }
    
    void set_glfw_callback();
    void split(int subscreens);
    void resize(int width, int height);
    void set_subscreen(int i);

    void set_map();

    Camera* camera(int i)
    {
        return &cameras[i];
    }
    
};

#endif
