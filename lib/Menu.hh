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

    enum MenuStatus { START, QUIT, RESET };

    private:

    enum ScreenType {SETTINGS_SCREEN, MAIN_SCREEN };
    ScreenType active_screen;

    void go_to_screen(ScreenType screen);

    Config* config;
    Skydome* skydome;
    audiere::OutputStreamPtr music;

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
    
    void load_levels(string levels_file);
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

    SimpleLayout settings_layout;
    
    TextArea settings_text;
    Button settings_done;
    TextArea particles_text;
    Button next_particles, prev_particles;
    TextArea fullscreen_text;
    Button next_fullscreen, prev_fullscreen;
    TextArea minimap_text;
    Button next_minimap, prev_minimap;
    TextArea antialiasing_text;
    Button next_antialiasing, prev_antialiasing;
    TextArea hearts_text;
    Button next_hearts, prev_hearts;
    TextArea resolution_text;
    Button next_resolution, prev_resolution;
    
    
    V2f screen_size;

    void setup_layout(void);
    void setup_settings(void);
    void load_settings(void);

    int particle_setting;
    int fullscreen_setting;
    int minimap_setting;
    int fsaa_setting;
    int heart_setting;
    int resolution_setting;

    vector<V2u> resolutions;

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

    void change_particles(int direction);
    void change_fullscreen(int direction);
    void change_minimap(int direction);
    void change_antialiasing(int direction);
    void change_hearts(int direction);
    void change_resolution(int direction);

    bool needs_reset;

    public:

    void toggle_fullscreen(void);
    void toggle_music(void);

    Menu(Config* config, 
         Skydome* skydome,
         audiere::OutputStreamPtr music);

    MenuStatus run(void);

    void mouse_callback(int button, int action);
    void resize_callback(int width, int height);

    void next_level(int d);

    static Menu* callback_menu;
};

#endif
