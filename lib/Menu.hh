#ifndef MENU_HH
#define MENU_HH

#include "cinquo.hh"
#include "Config.hh"
#include "Skydome.hh"
#include "Camera.hh"
#include "Heightmap.hh"
#include "Texture2D.hh"

#include "Widget.hh"

#include <map>

class Menu
{
    Config* config;
    Skydome* skydome;

    auto_ptr<Heightmap> heightmap;

    Camera camera;

    float camera_distance;

    struct Level {
        string name;
        string filename;
        V3f size;
        float water_level;
        
        Level() {};

        Level(string n, string f, V3f s, float w)
            : name(n), 
              filename(f), 
              size(s), 
              water_level(w) {};
    };

    map<string, Level> levels;
    vector<string> level_names;
    int selected_level;
    
    void reload_level(string level);
    void draw(void);
    
    Button logo_button;
    TextArea start_text;

    V2f screen_size;

    public:

    Menu(Config* config, 
         Skydome* skydome);

    enum MenuStatus { START, QUIT };

    MenuStatus run(void);

    void mouse_callback(int button, int action);
    void resize_callback(int width, int height);

    void next_level(void);

    static Menu* callback_menu;
};

#endif
