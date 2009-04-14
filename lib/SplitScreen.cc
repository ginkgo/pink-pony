#include "SplitScreen.hh"

SplitScreen* active_screen = NULL;

void GLFWCALL screen_size_callback(int width, int height)
{
    if (active_screen != NULL)
        active_screen->resize(width, height);
}

SplitScreen::SplitScreen(int width, int height, int subscreens)
    : size(width, height),
      subscreen_count(subscreens),
      current(0)
{
    split(subscreens);
}

SplitScreen::~SplitScreen()
{
    if (active_screen == this) {
        active_screen = NULL;
        glfwSetWindowSizeCallback(NULL);
    }
}

void SplitScreen::set_glfw_callback()
{
    active_screen = this;
    glfwSetWindowSizeCallback(screen_size_callback);
}

void SplitScreen::split(int subscreens)
{
    subscreen_count = subscreens;

    cameras.clear();
    cameras.resize(subscreen_count);
    
    resize(size.x, size.y);
}

void SplitScreen::resize(int width, int height)
{
    size = V2i(width, height);

    subscreens.clear();
    
    switch (subscreen_count) {
    case 1:
        //+----+
        //|1111|
        //|1111|
        //+----+
        subscreens.push_back(Box2i(V2i(0,0),
                                   V2i(0,0) + size));
        break;
    case 2:
        //+----+
        //|1111|
        //|2222|
        //+----+
        subscreens.push_back(Box2i(V2i(0,height/2),
                                   V2i(0,height/2) + V2i(width,height/2)));
        subscreens.push_back(Box2i(V2i(0,0),
                                   V2i(0,0) + V2i(width,height/2)));
        break;
    case 3:
    case 4:
        //+----+
        //|1122|
        //|3344|
        //+----+
        subscreens.push_back(Box2i(V2i(0,height/2),
                                   V2i(0,height/2) + size/2));
        subscreens.push_back(Box2i(V2i(width/2,height/2),
                                   V2i(width/2,height/2) + size/2));
        subscreens.push_back(Box2i(V2i(0,0),
                                   V2i(0,0) + size/2));
        subscreens.push_back(Box2i(V2i(width/2,0),
                                   V2i(width/2,0) + size/2));
        break;
    
    default:
        cerr << "No known subdivision scheme for " << subscreen_count
             << " subscreen(s). " << endl;
        break;
            
    }

    for (int i = 0; i < subscreen_count; i++) {
        cameras[i].set_aspect((float)subscreens[i].size().x /
                              (float)subscreens[i].size().y);
    }
}

void SplitScreen::set_subscreen(int i)
{
    current = i;

    Box2i screen = subscreens[i];
    
    glViewport(screen.min.x, screen.min.y,
               screen.size().x, screen.size().y);
}

void SplitScreen::set_map()
{
    V2i start, end;

    int shorter = min(size.x, size.y);
    int longer = max(size.x, size.y);
    
    switch(subscreen_count) {
    case 1:
        end = V2i(size.x,longer/4);
        start = V2i(size.x - longer/4, 0);
        break;
    case 2:
        end = V2i(size.x, (size.y+longer/4)/2);
        start = V2i(size.x - longer/4, (size.y-longer/4)/2);
        break;
    case 3:
        end = V2i((size.x * 3)/4 + shorter/4,
                  shorter/2);
        start = V2i((size.x * 3)/4 - shorter/4,
                    0);
        break;
    case 4:
        end = size/2 + V2i(shorter,shorter)/4;
        start = size/2 - V2i(shorter,shorter)/4;
        break;
    default:
        cerr << "No known subdivision scheme for " << subscreen_count
             << " subscreen(s). " << endl;
        break;        
    }

    glViewport(start.x,start.y,(end-start).x, (end-start).y);
}
