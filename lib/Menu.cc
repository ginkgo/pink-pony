#include "Menu.hh"

Menu* Menu::callback_menu = NULL;

void GLFWCALL menu_mouse_callback(int button, int action)
{
    if (Menu::callback_menu != NULL)
        Menu::callback_menu->mouse_callback(button, action);
}

void GLFWCALL menu_resize_callback(int width, int height)
{
    if (Menu::callback_menu != NULL)
        Menu::callback_menu->resize_callback(width, height);
}

void GLFWCALL menu_key_callback(int key, int state)
{
    if (key == GLFW_KEY_SPACE && 
        state == GLFW_PRESS && 
        Menu::callback_menu != NULL)
        Menu::callback_menu->next_level(1);
}

void Menu::mouse_callback(int button, int action)
{
    int x,y;

    glfwGetMousePos(&x, &y);

    if (action == GLFW_PRESS) {
        V2f pos(x,screen_size.y - y);
        
        mainscreen_layout.area_clicked(pos);
    }
}

void Menu::resize_callback(int width, int height)
{
    float aspect = (float)width/(float)height;

    camera.init(aspect, config->camera_fov,
                config->camera_near, config->camera_far);

    glViewport(0,0,width,height);

    screen_size = V2f(width, height);

    mainscreen_layout.set_available_area(Box2f(V2f(0,0), screen_size));
}

Menu::Menu (Config* config, 
            Skydome* skydome)
    : config(config),
      skydome(skydome),
      heightmap(NULL),
      logo_button("textures/logo.png"),
      prev_level_button("textures/left.png"),
      next_level_button("textures/right.png"),
      level_name_text("Lagoon"),
      start_button("Start"),
      quit_button("textures/quit.png"),
      options_button("textures/settings.png"),
      computer_no("0"),
      human_no("0"),
      human_text("textures/human.png"),
      computer_text("textures/computer.png"),
      computers(config->ai_count),
      humans(config->player_count - config->ai_count)
{

    // Some static test data
    level_names.clear();
    levels["Lagoon"] = Level("Lagoon",
                            "levels/heart.png",
                            V3f(1500, 90, 1500),
                            45);
    level_names.push_back("Lagoon");

    levels["Heart"] = Level("Heart",
                            "levels/heart.png",
                            V3f(1500, 90, 1500),
                            30);
    level_names.push_back("Heart");

    levels["Ring"] = Level("Ring",
                           "levels/ring.png",
                           V3f(1500, 90, 1500),
                           30);
    level_names.push_back("Ring");

    selected_level = 0;

    int w,h;
    glfwGetWindowSize(&w,&h);
    resize_callback(w,h);
    reload_level("Lagoon");

    setup_layout();
    computer_no.set_text(to_string(computers));
    human_no.set_text(to_string(humans));
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
    mainscreen_layout.add_widget(&level_name_text, Box2f(V2f(4/12.0, 1/12.0),
                                                         V2f(8/12.0, 3/12.0)));
    mainscreen_layout.add_widget(&prev_level_button, Box2f(V2f(3/12.0, 1/12.0),
                                                           V2f(4/12.0, 3/12.0)));
    mainscreen_layout.add_widget(&next_level_button, Box2f(V2f(8/12.0, 1/12.0),
                                                           V2f(9/12.0, 3/12.0)));
    mainscreen_layout.add_widget(&logo_button, Box2f(V2f(0.0, 2.0/3.0),
                                                     V2f(1.0,     1.0)));
    mainscreen_layout.add_widget(&start_button, Box2f(V2f(8.0/24.0, 6.0/12.0),
                                                      V2f(16.0/24.0, 17.0/24.0)));
    mainscreen_layout.add_widget(&quit_button, Box2f(V2f(1.0/48.0, 1.0/32.0),
                                                     V2f(5.0/48.0, 5.0/32.0)));
    mainscreen_layout.add_widget(&options_button, Box2f(V2f(42.0/48.0, 1.0/32.0),
                                                        V2f(47.0/48.0, 5.0/32.0)));
    mainscreen_layout.add_widget(&human_slider, Box2f(V2f(13.0/32.0, 8.0/24.0),
                                                      V2f(16.0/32.0,11.0/24.0)));
    mainscreen_layout.add_widget(&computer_slider, Box2f(V2f(16.0/32.0, 8.0/24.0),
                                                         V2f(19.0/32.0,11.0/24.0)));
    mainscreen_layout.add_widget(&human_no, Box2f(V2f(10.0/32.0, 8.0/24.0),
                                                  V2f(13.0/32.0,11.0/24.0)));
    mainscreen_layout.add_widget(&computer_no, Box2f(V2f(19.0/32.0, 8.0/24.0),
                                                     V2f(21.0/32.0,11.0/24.0)));
    mainscreen_layout.add_widget(&human_text, Box2f(V2f(4.0/32.0, 7.0/24.0),
                                                    V2f(9.0/32.0,12.0/24.0)));
    mainscreen_layout.add_widget(&computer_text, Box2f(V2f(22.0/32.0, 7.0/24.0),
                                                       V2f(27.0/32.0,12.0/24.0)));

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
}

void Menu::next_level(int d)
{
    // We add one interval so that the modulo also works when d is negative.
    selected_level = selected_level + level_names.size() + d;
    selected_level = selected_level % level_names.size();

    cout << "Selected level " << selected_level 
         << ": " << level_names[selected_level] << endl;

    reload_level(level_names[selected_level]);
}

void Menu::reload_level(string level)
{
    config->heightmap_file = levels[level].filename;
    config->water_level = levels[level].water_level;
    
    V3f s = levels[level].size;

    config->level_size = Box3f(V3f(-s.x/2,   0,-s.z/2),
                              V3f( s.x/2, s.y, s.z/2));

    heightmap.reset(new Heightmap(config->heightmap_file,
                                  config->level_size,
                                  config->water_level,
                                  config->sand_texture,
                                  config->grass_texture,
                                  config->noise_texture));

    camera_distance = s.length() / 2;


    level_name_text.set_text(level);
}    

Menu::MenuStatus Menu::run(void)
{
    status = START;
    running = true;

    callback_menu = this;
    glfwSetMouseButtonCallback(menu_mouse_callback);
    glfwSetWindowSizeCallback(menu_resize_callback);
    glfwSetKeyCallback(menu_key_callback);


    while (running) {

        glClear(GL_COLOR_BUFFER_BIT |
                GL_DEPTH_BUFFER_BIT |
                GL_STENCIL_BUFFER_BIT);

        draw();
        
        glfwSwapBuffers();

        if (glfwGetKey( GLFW_KEY_ESC ) || 
            !glfwGetWindowParam( GLFW_OPENED )) {
            status = QUIT;
            running = false;
        } else if (glfwGetKey(GLFW_KEY_ENTER)) {
            status = START;
            running = false;
        }
    }

    glfwSetMouseButtonCallback(NULL);
    glfwSetWindowSizeCallback(NULL);
    glfwSetKeyCallback(NULL);
    callback_menu = NULL;

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

    mainscreen_layout.draw();    
}
