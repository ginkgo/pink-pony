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
    public:

    enum MenuStatus { START, QUIT };

    private:

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
    TextArea start_button;
    Button quit_button;
    Button options_button;
    TextArea level_name_text;
    Button next_level_button, prev_level_button;
    Slider computer_slider, human_slider;
    TextArea computer_no, human_no;
    Button computer_text, human_text;
    SimpleLayout mainscreen_layout;

    V2f screen_size;

    void setup_layout(void);

    MenuStatus status;
    bool running ;

    void quit() {
        status = QUIT;
        running = false;
    }

    void start() {
        status = START;
        running = false;
    }

    int computers, humans;
    void change_computers(int dir);
    void change_humans(int dir);

    public:

    Menu(Config* config, 
         Skydome* skydome);

    MenuStatus run(void);

    void mouse_callback(int button, int action);
    void resize_callback(int width, int height);

    void next_level(int d);

    static Menu* callback_menu;
};

#endif
