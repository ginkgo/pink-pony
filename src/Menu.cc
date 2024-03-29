#include "Menu.hh"
#include <tinyxml.h>

// SDL_mixer includes
#include "SDL.h"
#include "SDL_mixer.h"

Menu* Menu::callback_menu = NULL;

void menu_mouse_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (Menu::callback_menu != NULL)
        Menu::callback_menu->mouse_callback(button, action);
}

void menu_resize_callback(GLFWwindow* window, int width, int height)
{
    if (Menu::callback_menu != NULL)
        Menu::callback_menu->resize_callback(width, height);
}

void menu_key_callback(GLFWwindow* window, int key, int scancode, int state, int mods)
{
    if (state != GLFW_PRESS || Menu::callback_menu == NULL ) 
        return;

    if (key == GLFW_KEY_SPACE)
        Menu::callback_menu->next_level(1);
    if (key == GLFW_KEY_F1)
        Menu::callback_menu->toggle_music();
    if (key == GLFW_KEY_F2)
        Menu::callback_menu->toggle_fullscreen();
}

void Menu::toggle_fullscreen(void)
{
    config->window_mode = (config->window_mode == WINDOW)?FULLSCREEN:WINDOW;
    status = RESET;
    running = false;    
}

void Menu::toggle_music(void)
{
    int current_volume = Mix_VolumeMusic(-1);
    Mix_VolumeMusic(std::min(128, current_volume + 63) % 128);
    config->music_volume = Mix_VolumeMusic(-1);
}

void Menu::mouse_callback(int button, int action)
{
    double x,y;

    glfwGetCursorPos(window, &x, &y);

    if (action == GLFW_PRESS) {
        V2f pos(x,screen_size.y - y);
        
        switch (active_screen) {
        case MAIN_SCREEN:
            mainscreen_layout.area_clicked(pos);
            break;
        case SETTINGS_SCREEN:
            settings_layout.area_clicked(pos);
            break;
        }
    }
}

void Menu::resize_callback(int width, int height)
{
    float aspect = (float)width/(float)height;

    camera.init(aspect, config->camera_fov,
                config->camera_near, config->camera_far);

    glViewport(0,0,width,height);

    screen_size = V2f(width, height);

    config->width = width;
    config->height = height;

    mainscreen_layout.set_available_area(Box2f(V2f(0,0), screen_size));
    settings_layout.set_available_area(Box2f(V2f(0,0), screen_size));
}

#define TEXT_COLOR Color4f(1,1,1,0.5)

Menu::Menu (Config* config, 
            Skydome* skydome,
            GLFWwindow* window)
    : active_screen(MAIN_SCREEN),
      config(config),
      skydome(skydome),
      heightmap(NULL),
      logo_button(config->resource_dir + "textures/logo.png"),
      start_button("Start", config),
      quit_button(config->resource_dir + "textures/quit.png"),
      options_button(config->resource_dir + "textures/settings.png"),
      level_name_text("Lagoon", config),
      next_level_button(config->resource_dir + "textures/right.png"),
      prev_level_button(config->resource_dir + "textures/left.png"),
      computer_no("0", config),
      human_no("0", config),
      computer_text(config->resource_dir + "textures/computer.png"),
      human_text(config->resource_dir + "textures/human.png"),
      computers(config->ai_count),
      humans(config->player_count - config->ai_count),
      settings_text("Settings", config),
      settings_done(config->resource_dir + "textures/back.png"),
      particles_text("Some particles", config, TEXT_COLOR),
      prev_particles(config->resource_dir + "textures/left.png"),
      next_particles(config->resource_dir + "textures/right.png"),
      fullscreen_text("Some particles", config, TEXT_COLOR),
      prev_fullscreen(config->resource_dir + "textures/left.png"),
      next_fullscreen(config->resource_dir + "textures/right.png"),
      minimap_text("Some particles", config, TEXT_COLOR),
      prev_minimap(config->resource_dir + "textures/left.png"),
      next_minimap(config->resource_dir + "textures/right.png"),
      antialiasing_text("Some particles", config, TEXT_COLOR),
      prev_antialiasing(config->resource_dir + "textures/left.png"),
      next_antialiasing(config->resource_dir + "textures/right.png"),
      hearts_text("Some particles", config, TEXT_COLOR),
      prev_hearts(config->resource_dir + "textures/left.png"),
      next_hearts(config->resource_dir + "textures/right.png"),
      resolution_text("Some particles", config, TEXT_COLOR),
      prev_resolution(config->resource_dir + "textures/left.png"),
      next_resolution(config->resource_dir + "textures/right.png"),
      water_text("Simple water", config, TEXT_COLOR),
      prev_water(config->resource_dir + "textures/left.png"),
      next_water(config->resource_dir + "textures/right.png"),
      needs_reset(false),
      window(window),
      computer_slider(config),
      human_slider(config)
    
{
    getErrors();
    
    // Some static test data
    load_levels(config->resource_dir + config->levels_file);

    int w,h;
    glfwGetWindowSize(window, &w,&h);
    resize_callback(w,h);

    next_level(0);

    setup_layout();
    
    computer_no.set_text(to_string(computers));
    human_no.set_text(to_string(humans));

    setup_settings();
}

void Menu::setup_settings(void)
{
    int modes_found;
    const GLFWvidmode* vidmodes = glfwGetVideoModes(glfwGetPrimaryMonitor(), &modes_found);
    
    resolutions.resize(modes_found);

    for (int i = 0; i < modes_found; ++i) {
        resolutions[i] = V2i(vidmodes[i].width,
                             vidmodes[i].height);
    }

    if(!config->use_particles) {
        particle_setting = 0;
    } else if (config->pony_particle_rate <= 10.0) {
        particle_setting = 1;
    } else if (config->pony_particle_rate <= 100.0) {
        particle_setting = 2;
    } else {
        particle_setting = 3;
    }

    if (config->window_mode == WINDOW) {
        fullscreen_setting = 0;
    } else {
        fullscreen_setting = 1;
    }

    if (config->show_minimap) {
        minimap_setting = 1;
    } else {
        minimap_setting = 0;
    }

    fsaa_setting = config->fsaa_samples;

    heart_setting = config->heart_count;

    for (unsigned i = 0; i < resolutions.size(); ++i) {
        if ((int)(resolutions[i].x * resolutions[i].y) >= config->width*config->height) {
            resolution_setting = i;
            break;
        }
    }

    water_setting = config->use_water_fallback ? 0 : 1;
    
    load_settings();    
}

void Menu::load_settings(void)
{
    if (particle_setting == 0) {
        particles_text.set_text("No particles");
        config->use_particles = false;
    } else if (particle_setting == 1) {
        particles_text.set_text("Some particles");
        config->use_particles = true;
        config->heart_explosion_particles = 1000;
        config->pony_explosion_particles = 5000;
        config->pony_particle_rate = 10.0;
    } else if (particle_setting == 2) {
        particles_text.set_text("Many particles");
        config->use_particles = true;
        config->heart_explosion_particles = 10000;
        config->pony_explosion_particles = 50000;
        config->pony_particle_rate = 100.0;    
    } else {
        particles_text.set_text("Too many particles");
        config->use_particles = true;
        config->heart_explosion_particles = 40000;
        config->pony_explosion_particles = 200000;
        config->pony_particle_rate = 400.0;        
    }

    if (fullscreen_setting == 0) {
        fullscreen_text.set_text("Window");
        config->window_mode = WINDOW;
    } else {
        fullscreen_text.set_text("Fullscreen");
        config->window_mode = FULLSCREEN;
    }

    if (minimap_setting == 0) {
        minimap_text.set_text("Hide minimap");
        config->show_minimap = false;
    } else {
        minimap_text.set_text("Show minimap");
        config->show_minimap = true;
    }

    if (fsaa_setting == 0) {
        antialiasing_text.set_text("No FSAA");
        config->fsaa_samples = fsaa_setting;
    } else {
        antialiasing_text.set_text(to_string(fsaa_setting) + "x FSAA");
        config->fsaa_samples = fsaa_setting;
    }

    if (heart_setting == 0) {
        hearts_text.set_text("No hearts");
        config->heart_count = heart_setting;
    } else {
        hearts_text.set_text(to_string(heart_setting) + " hearts");
        config->heart_count = heart_setting;
    }

    resolution_text.set_text(to_string(resolutions[resolution_setting].x) + "x" +
                             to_string(resolutions[resolution_setting].y));
    config->width = resolutions[resolution_setting].x;
    config->height = resolutions[resolution_setting].y;

    if (water_setting == 0) {
        water_text.set_text("Simple water");
        config->use_water_fallback = true;
    } else {
        water_text.set_text("Fancy water");
        config->use_water_fallback = false;
    }
}

void Menu::load_levels(string levels_file)
{
    TiXmlDocument doc(levels_file.c_str());

    level_names.clear();
    levels.clear();

    if (!doc.LoadFile()) {
        cerr << "Could not load levels file " << levels_file << ".\n";
        assert(0);
    }
    
    TiXmlNode* levels_node = doc.FirstChild();

    if (levels_node->Type() != TiXmlNode::ELEMENT ||
        string(levels_node->Value()) != "levels") {
        cerr << "Could not find 'levels' element in " << levels_file << endl;
        assert(0);
    }

    for (TiXmlNode* level_node = levels_node->ToElement()->FirstChild(); level_node != NULL;
         level_node = level_node->NextSibling()) {
        
        if (level_node->Type() != TiXmlNode::ELEMENT ||
            string(level_node->Value()) != "level") {
            cerr << "Could not find 'level' element in " << levels_file << endl;
            assert(0);
        }

        TiXmlElement* level_element = level_node->ToElement();

        const char* name;
        const char* file;
        const char* size_string;
        V3f size;
        float water_level;

        if ((name = level_element->Attribute("name")) == NULL)
            assert(0);
        if ((file = level_element->Attribute("file")) == NULL)
            assert(0);
        if ((size_string = level_element->Attribute("size")) == NULL)
            assert(0);
        if (level_element->QueryFloatAttribute("water_level", &water_level) != TIXML_SUCCESS)
            assert(0);

        try {
            size = parse<V3f>(string(size_string));
        } catch (...) {
            assert(0);
        }

        level_names.push_back(string(name));
        levels[string(name)] = Level(string(name),
                                     string(file),
                                     size,
                                     water_level);
    }
}

void Menu::change_humans(int dir)
{
    humans += dir;

    if (humans < 0) {
        humans = 0;
    }

    if (humans > 4) {
        humans = 4;
    }

    if (humans + computers > 4) {
        computers = 4-humans;
    }

    if (humans + computers < 1) {
        humans = 1;
    }

    config->ai_count = computers;
    config->player_count = humans+computers;

    computer_no.set_text(to_string(computers));
    human_no.set_text(to_string(humans));    
}

void Menu::change_computers(int dir)
{
    computers += dir;

    if (computers < 0) {
        computers = 0;
    }

    if (computers > 4) {
        computers = 4;
    }

    if (humans + computers > 4) {
        humans = 4-computers;
    }

    if (humans + computers < 1) {
        computers = 1;
    }

    config->ai_count = computers;
    config->player_count = humans+computers;

    computer_no.set_text(to_string(computers));
    human_no.set_text(to_string(humans));    
}

void Menu::setup_layout(void)
{

    mainscreen_layout.add_widget(&logo_button, Box2f(V2f(0.0, 2.0/3.0),
                                                     V2f(1.0,     1.0)));

    mainscreen_layout.add_widget(&start_button, Box2f(V2f(6.0/24.0, 11.0/24.0),
                                                      V2f(18.0/24.0, 17.0/24.0)));

    mainscreen_layout.add_widget(&human_slider, Box2f(V2f(13.0/32.0, 8.0/24.0),
                                                      V2f(16.0/32.0,11.0/24.0)));
    mainscreen_layout.add_widget(&computer_slider, Box2f(V2f(16.0/32.0, 8.0/24.0),
                                                         V2f(19.0/32.0,11.0/24.0)));
    mainscreen_layout.add_widget(&human_no, Box2f(V2f(9.0/32.0, 6.0/24.0),
                                                  V2f(14.0/32.0,12.0/24.0)));
    mainscreen_layout.add_widget(&computer_no, Box2f(V2f(19.0/32.0, 6.0/24.0),
                                                     V2f(23.0/32.0,12.0/24.0)));
    mainscreen_layout.add_widget(&human_text, Box2f(V2f(5.0/32.0, 7.0/24.0),
                                                    V2f(10.0/32.0,12.0/24.0)));
    mainscreen_layout.add_widget(&computer_text, Box2f(V2f(23.0/32.0, 7.0/24.0),
                                                       V2f(28.0/32.0,12.0/24.0)));

    mainscreen_layout.add_widget(&level_name_text, Box2f(V2f(4/12.0, 0.5/32.0),
                                                         V2f(8/12.0, 4.5/32.0)));
    mainscreen_layout.add_widget(&prev_level_button, Box2f(V2f(3/12.0, 1/32.0),
                                                           V2f(4/12.0, 5/32.0)));
    mainscreen_layout.add_widget(&next_level_button, Box2f(V2f(8/12.0, 1/32.0),
                                                           V2f(9/12.0, 5/32.0)));

    mainscreen_layout.add_widget(&quit_button, Box2f(V2f(1.0/48.0, 1.0/32.0),
                                                     V2f(5.0/48.0, 5.0/32.0)));
    mainscreen_layout.add_widget(&options_button, Box2f(V2f(43.0/48.0, 1.0/32.0),
                                                        V2f(47.0/48.0, 5.0/32.0)));

    next_level_button.on_click()
        .connect(sigc::bind(sigc::mem_fun(this,&Menu::next_level), 1)); 
    prev_level_button.on_click()
        .connect(sigc::bind(sigc::mem_fun(this,&Menu::next_level), -1)); 
    level_name_text.on_click()
        .connect(sigc::bind(sigc::mem_fun(this,&Menu::next_level), 1)); 
    start_button.on_click()
        .connect(sigc::mem_fun(this,&Menu::start));  
    quit_button.on_click()
        .connect(sigc::mem_fun(this,&Menu::quit)); 
    computer_slider.on_click()
        .connect(sigc::mem_fun(this,&Menu::change_computers)); 
    human_slider.on_click()
        .connect(sigc::mem_fun(this,&Menu::change_humans)); 
    options_button.on_click()
        .connect(sigc::bind(sigc::mem_fun(this,&Menu::go_to_screen), SETTINGS_SCREEN));


    settings_layout.add_widget(&settings_done, Box2f(V2f(1.0/48.0, 1.0/32.0),
                                                     V2f(5.0/48.0, 5.0/32.0)));

    settings_layout.add_widget(&settings_text, Box2f(V2f( 4/16.0, 9/12.0),
                                                     V2f(12/16.0,11/12.0)));

    settings_layout.add_widget(&particles_text, Box2f(V2f( 3/32.0, 7/12.0),
                                                      V2f(13/32.0, 8/12.0)));
    settings_layout.add_widget(&prev_particles, Box2f(V2f( 1/32.0, 7/12.0),
                                                      V2f( 3/32.0, 8/12.0)));
    settings_layout.add_widget(&next_particles, Box2f(V2f(13/32.0, 7/12.0),
                                                      V2f(15/32.0, 8/12.0)));

    settings_layout.add_widget(&minimap_text, Box2f(V2f( 3/32.0, 5/12.0),
                                                    V2f(13/32.0, 6/12.0)));
    settings_layout.add_widget(&prev_minimap, Box2f(V2f( 1/32.0, 5/12.0),
                                                    V2f( 3/32.0, 6/12.0)));
    settings_layout.add_widget(&next_minimap, Box2f(V2f(13/32.0, 5/12.0),
                                                    V2f(15/32.0, 6/12.0)));

    settings_layout.add_widget(&hearts_text, Box2f(V2f( 3/32.0, 3/12.0),
                                                   V2f(13/32.0, 4/12.0)));
    settings_layout.add_widget(&prev_hearts, Box2f(V2f( 1/32.0, 3/12.0),
                                                   V2f( 3/32.0, 4/12.0)));
    settings_layout.add_widget(&next_hearts, Box2f(V2f(13/32.0, 3/12.0),
                                                   V2f(15/32.0, 4/12.0)));

    settings_layout.add_widget(&fullscreen_text, Box2f(V2f(19/32.0, 7/12.0),
                                                       V2f(29/32.0, 8/12.0)));
    settings_layout.add_widget(&prev_fullscreen, Box2f(V2f(17/32.0, 7/12.0),
                                                       V2f(19/32.0, 8/12.0)));
    settings_layout.add_widget(&next_fullscreen, Box2f(V2f(29/32.0, 7/12.0),
                                                       V2f(31/32.0, 8/12.0)));

    settings_layout.add_widget(&antialiasing_text, Box2f(V2f(19/32.0, 5/12.0),
                                                         V2f(29/32.0, 6/12.0)));
    settings_layout.add_widget(&prev_antialiasing, Box2f(V2f(17/32.0, 5/12.0),
                                                         V2f(19/32.0, 6/12.0)));
    settings_layout.add_widget(&next_antialiasing, Box2f(V2f(29/32.0, 5/12.0),
                                                         V2f(31/32.0, 6/12.0)));

    settings_layout.add_widget(&resolution_text, Box2f(V2f(19/32.0, 3/12.0),
                                                       V2f(29/32.0, 4/12.0)));
    settings_layout.add_widget(&prev_resolution, Box2f(V2f(17/32.0, 3/12.0),
                                                       V2f(19/32.0, 4/12.0)));
    settings_layout.add_widget(&next_resolution, Box2f(V2f(29/32.0, 3/12.0),
                                                       V2f(31/32.0, 4/12.0)));

    settings_layout.add_widget(&water_text, Box2f(V2f(19/32.0, 1/12.0),
                                                  V2f(29/32.0, 2/12.0)));
    settings_layout.add_widget(&prev_water, Box2f(V2f(17/32.0, 1/12.0),
                                                  V2f(19/32.0, 2/12.0)));
    settings_layout.add_widget(&next_water, Box2f(V2f(29/32.0, 1/12.0),
                                                  V2f(31/32.0, 2/12.0)));


    settings_done.on_click()
        .connect(sigc::bind(sigc::mem_fun(this,&Menu::go_to_screen), MAIN_SCREEN));

    particles_text.on_click()
        .connect(sigc::bind(sigc::mem_fun(this,&Menu::change_particles), 1));
    prev_particles.on_click()
        .connect(sigc::bind(sigc::mem_fun(this,&Menu::change_particles),-1));
    next_particles.on_click()
        .connect(sigc::bind(sigc::mem_fun(this,&Menu::change_particles), 1));

    fullscreen_text.on_click()
        .connect(sigc::bind(sigc::mem_fun(this,&Menu::change_fullscreen), 1));
    prev_fullscreen.on_click()
        .connect(sigc::bind(sigc::mem_fun(this,&Menu::change_fullscreen),-1));
    next_fullscreen.on_click()
        .connect(sigc::bind(sigc::mem_fun(this,&Menu::change_fullscreen), 1));

    minimap_text.on_click()
        .connect(sigc::bind(sigc::mem_fun(this,&Menu::change_minimap), 1));
    prev_minimap.on_click()
        .connect(sigc::bind(sigc::mem_fun(this,&Menu::change_minimap),-1));
    next_minimap.on_click()
        .connect(sigc::bind(sigc::mem_fun(this,&Menu::change_minimap), 1));

    antialiasing_text.on_click()
        .connect(sigc::bind(sigc::mem_fun(this,&Menu::change_antialiasing), 1));
    prev_antialiasing.on_click()
        .connect(sigc::bind(sigc::mem_fun(this,&Menu::change_antialiasing),-1));
    next_antialiasing.on_click()
        .connect(sigc::bind(sigc::mem_fun(this,&Menu::change_antialiasing), 1));

    hearts_text.on_click()
        .connect(sigc::bind(sigc::mem_fun(this,&Menu::change_hearts), 1));
    prev_hearts.on_click()
        .connect(sigc::bind(sigc::mem_fun(this,&Menu::change_hearts),-1));
    next_hearts.on_click()
        .connect(sigc::bind(sigc::mem_fun(this,&Menu::change_hearts), 1));

    resolution_text.on_click()
        .connect(sigc::bind(sigc::mem_fun(this,&Menu::change_resolution), 1));
    prev_resolution.on_click()
        .connect(sigc::bind(sigc::mem_fun(this,&Menu::change_resolution),-1));
    next_resolution.on_click()
        .connect(sigc::bind(sigc::mem_fun(this,&Menu::change_resolution), 1));

    water_text.on_click()
        .connect(sigc::bind(sigc::mem_fun(this,&Menu::change_water), 1));
    prev_water.on_click()
        .connect(sigc::bind(sigc::mem_fun(this,&Menu::change_water),-1));
    next_water.on_click()
        .connect(sigc::bind(sigc::mem_fun(this,&Menu::change_water), 1));
    
}

void Menu::change_particles(int direction)
{
    particle_setting = (particle_setting + 4 + direction) % 4;


    load_settings();
}

void Menu::change_fullscreen(int direction) {
    
    if (fullscreen_setting == 0)
        fullscreen_setting = 1;
    else 
        fullscreen_setting = 0;
    
    needs_reset = true;


    load_settings();
}

void Menu::change_minimap(int direction) {
    
    if (minimap_setting == 0)
        minimap_setting = 1;
    else 
        minimap_setting = 0;


    load_settings();
}

void Menu::change_antialiasing(int direction) {
    int modes[] = {0, 2, 4, 8, 16};

    int current = 4;

    for (int i = 0; i < 5; ++i) {
        if (fsaa_setting <= modes[i]) {
            current = i;
            break;
        }
    }

    current = (current + 5 + direction) % 5;

    fsaa_setting = modes[current];

    needs_reset = true;

    load_settings();    
}

void Menu::change_hearts(int direction) {
    heart_setting += direction;

    if (heart_setting < 0) heart_setting = 0;

    load_settings();
}

void Menu::change_resolution(int direction) {
    resolution_setting = (resolution_setting + 
                          resolutions.size() + 
                          direction) % resolutions.size();

    needs_reset = true;

    load_settings();    
}

void Menu::change_water(int direction) {
    water_setting = (water_setting + direction + 2) % 2;

    needs_reset = true;

    load_settings();    
}

void Menu::go_to_screen(ScreenType screen)
{
    active_screen = screen;

    if (needs_reset) {
        status = RESET;
        running = false;
    }
}

void Menu::next_level(int d)
{
    // We add one interval so that the modulo also works when d is negative.
    config->selected_level = config->selected_level + level_names.size() + d;
    config->selected_level = config->selected_level % level_names.size();

    cout << "Selected level " << config->selected_level 
         << ": " << level_names[config->selected_level] << endl;

    reload_level(level_names[config->selected_level]);
}

void Menu::reload_level(string level)
{
    getErrors();
    
    config->heightmap_file = levels[level].filename;
    config->water_level = levels[level].water_level;
    
    V3f s = levels[level].size;

    config->level_size = Box3f(V3f(-s.x/2,   0,-s.z/2),
                              V3f( s.x/2, s.y, s.z/2));

    getErrors();
    heightmap.reset(new Heightmap(config->resource_dir + config->heightmap_file,
                                  config->level_size,
                                  config->water_level,
                                  config->sand_texture,
                                  config->grass_texture,
                                  config->noise_texture,
                                  config->sky_texture,
                                  config));

    camera_distance = s.length() / 2;


    level_name_text.set_text(level);
}    

Menu::MenuStatus Menu::run(void)
{
    if (config->window_mode == FULLSCREEN)
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    status = START;
    running = true;

    callback_menu = this;
    glfwSetMouseButtonCallback(window, menu_mouse_callback);
    glfwSetWindowSizeCallback(window, menu_resize_callback);
    glfwSetKeyCallback(window, menu_key_callback);

    while (running) {

        glClear(GL_COLOR_BUFFER_BIT |
                GL_DEPTH_BUFFER_BIT |
                GL_STENCIL_BUFFER_BIT);

        draw();

        glfwPollEvents();
        glfwSwapBuffers(window);

        if (glfwGetKey( window, GLFW_KEY_ESCAPE ) || 
            glfwWindowShouldClose( window )) {
            status = QUIT;
            running = false;
        } else if (glfwGetKey( window, GLFW_KEY_ENTER)) {
            status = START;
            running = false;
        }
    }

    glfwSetMouseButtonCallback(window, NULL);
    glfwSetWindowSizeCallback(window, NULL);
    glfwSetKeyCallback(window, NULL);
    callback_menu = NULL;

    if (config->window_mode == FULLSCREEN)
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    return status;
}

void Menu::draw(void)
{
    glEnable(GL_LIGHTING);

    float rotation_speed = 15.0 * M_PI/180.0; // degree/second

    float x_angle = 30.0 * M_PI/180.0;
    float y_angle = rotation_speed * glfwGetTime();

    camera.look_at(V3f(cos(x_angle) * sin(y_angle) * camera_distance,
                       sin(x_angle) * camera_distance,
                       cos(x_angle) * cos(y_angle) * camera_distance),
                   V3f(0,config->water_level,0));

    camera.set_matrices();

    glPushMatrix();
    glTranslatef(cos(x_angle) * sin(y_angle) * camera_distance,
                 sin(x_angle) * camera_distance * 0.9, // ugly hack
                 cos(x_angle) * cos(y_angle) * camera_distance);
    skydome->draw();
    glPopMatrix();

    heightmap->draw(config);

    glDisable(GL_LIGHTING);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,screen_size.x,
            0,screen_size.y,
            -1,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    switch (active_screen) {
    case MAIN_SCREEN:
        mainscreen_layout.draw();    
        break;
    case SETTINGS_SCREEN:
        settings_layout.draw();
        break;
    }
}
