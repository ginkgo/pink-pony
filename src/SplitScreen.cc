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
    point_huds.clear();

    
    Box2i box;
    V2i p1,p2;
    
    switch (subscreen_count) {
    case 1:
        //+----+
        //|1111|
        //|p111|
        //+----+
        subscreens.push_back(Box2i(V2i(0,0),
                                   V2i(0,0) + size));

        

        // We hide the points-HUD by moving it out of the screen.
        p1 = V2i(size.y/12, size.y/12);
        p2 = V2i(size.y/4, size.y/4);
        box.makeEmpty();
        box.extendBy(V2i(0,0) + p1 * V2i(+1,+1));
        box.extendBy(V2i(0,0) + p2 * V2i(+1,+1));
        point_huds.push_back(box);
        break;
    case 2:
        //+----+
        //|p111|
        //|p222|
        //+----+
        subscreens.push_back(Box2i(V2i(0,height/2),
                                   V2i(0,0) + V2i(width,height)));
        subscreens.push_back(Box2i(V2i(0,0),
                                   V2i(0,0) + V2i(width,height/2)));

        p1 = V2i(size.y/24, size.y/24);
        p2 = V2i(size.y/4, size.y/4);
        box.makeEmpty();
        box.extendBy(V2i(0,height) + p1 * V2i(+1,-1));
        box.extendBy(V2i(0,height) + p2 * V2i(+1,-1));
        point_huds.push_back(box);
        box.makeEmpty();
        box.extendBy(V2i(0,0) + p1 * V2i(+1,+1));
        box.extendBy(V2i(0,0) + p2 * V2i(+1,+1));
        point_huds.push_back(box);

        break;
    case 3:
    case 4:
        //+----+
        //|p12p|
        //|p34p|
        //+----+
        subscreens.push_back(Box2i(V2i(0,height/2),
                                   V2i(0,height) + V2i(size.x/2,0)));
        subscreens.push_back(Box2i(V2i(width/2,height/2),
                                   V2i(width/2,height) + V2i(size.x/2,0)));
        subscreens.push_back(Box2i(V2i(0,0),
                                   V2i(0,0) + size/2));
        subscreens.push_back(Box2i(V2i(width/2,0),
                                   V2i(width/2,0) + size/2));



        p1 = V2i(size.y/48, size.y/48);
        p2 = V2i(size.y/8, size.y/8);
        // 1
        box.makeEmpty();
        box.extendBy(V2i(0,height) + p1 * V2i(+1,-1));
        box.extendBy(V2i(0,height) + p2 * V2i(+1,-1));
        point_huds.push_back(box);
        // 2
        box.makeEmpty();
        box.extendBy(V2i(width,height) + p1 * V2i(-1,-1));
        box.extendBy(V2i(width,height) + p2 * V2i(-1,-1));
        point_huds.push_back(box);
        // 3
        box.makeEmpty();
        box.extendBy(V2i(0,0) + p1 * V2i(+1,+1));
        box.extendBy(V2i(0,0) + p2 * V2i(+1,+1));
        point_huds.push_back(box);
        // 4
        box.makeEmpty();
        box.extendBy(V2i(width,0) + p1 * V2i(-1,+1));
        box.extendBy(V2i(width,0) + p2 * V2i(-1,+1));
        point_huds.push_back(box);;
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

void SplitScreen::set_whole_screen()
{
    glViewport(0,0, size.x, size.y);
}

void SplitScreen::set_point_hud(int i)
{
    current = i;

    Box2i hud = point_huds[i];
    
    glViewport(0, 0,
               size.x, size.y);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glTranslatef(2.0 * hud.center().x/(float)size.x - 1.0,
                 2.0 * hud.center().y/(float)size.y - 1.0,
                 0);
    glScalef(hud.size().x/((float)size.x * 2.0),
             hud.size().y/((float)size.y * 2.0),
             1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void SplitScreen::set_map()
{
    V2i start(0,0), end(0,0);

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
