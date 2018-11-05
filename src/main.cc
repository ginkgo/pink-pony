#include "cinquo.hh"
#include "PonyGame.hh"

#include "Menu.hh"

#include <algorithm>
#include "ImathRandom.h"

// SDL_mixer includes
#include "SDL.h"
#include "SDL_mixer.h"

void permute_start_positions(Config& config);
void randomize_start_positions(Config& config, Heightmap& heightmap);

void start_music(Mix_Music** music, const string& music_file);
void stop_music(Mix_Music** music);

Config config;

int main(int argc, char** argv)
{
    string config_file = "pony.options";
    bool running = true;
    
    if (argc > 1) {
        config_file = string(argv[1]);
    }
    
    if (!config.read_file(config_file)) {
        cerr << "Could not read config file." << endl;
        return 1;
    }
    
    glfwInit();

    glfwWindowHint(GLFW_SAMPLES, config.fsaa_samples);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
    
    GLFWwindow* window = glfwCreateWindow(config.width, config.height,
                                          "Pink Pony <3",
                                          config.window_mode==FULLSCREEN ? glfwGetPrimaryMonitor() : NULL,
                                          NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(config.swap_interval);

    if (!flextInit(window)) {
        return 1;
    }
    
    bool reset_video = false;

    Mix_Music* music = NULL;
    start_music(&music, config.resource_dir + config.background_music);
    
    while (running) {

        if (reset_video) {

            glfwDestroyWindow(window);
            
            window = glfwCreateWindow(config.width, config.height,
                                      "Pink Pony <3",
                                      config.window_mode==FULLSCREEN ? glfwGetPrimaryMonitor() : NULL,
                                      NULL);

            reset_video = false;

            getErrors();
        }

        // We put everything between glfwOpenWindow & glfwTerminate
        // between braces, so that stack variables that need a GL context
        // are destructed, while the context still exists.
        {
            Skydome skydome(config.resource_dir + config.sky_texture);

            getErrors();
            
            Menu::MenuStatus menu_status;
        
            {
                Menu menu(&config, &skydome, window);

                menu_status = menu.run();
            }

            if (!config.write_file(config_file)) {
                cerr << "Could not write config file." << endl;
            }

            if (menu_status == Menu::RESET) {
                reset_video = true;
                continue;
            }

            if (menu_status == Menu::START) {        
                Heightmap heightmap(config.resource_dir + config.heightmap_file,
                                    config.level_size,
                                    config.water_level,
                                    config.sand_texture,
                                    config.grass_texture,
                                    config.noise_texture,
                                    config.sky_texture,
                                    &config);
    
                PonyPoints points(config.player_count, &config);

                bool run_game = true;

                while (run_game){

                    if (config.randomize_start_positions)
                        randomize_start_positions(config, heightmap);
                    else if (config.permute_start_positions)
                        permute_start_positions(config);

                    
                    int human_count = config.player_count - config.ai_count;
                    if (human_count == 0) human_count = config.player_count;

                    SplitScreen screen(window, config.width, config.height, human_count);
                    screen.set_glfw_callback();

                    PonyGame game(&screen,
                                  &heightmap,
                                  &config,
                                  &skydome,
                                  window);

                    run_game = game.start(points);
                }
            } else if (menu_status == Menu::QUIT) {
                cout << "Quit game." << endl;
                running = false;
            }
        
            if (glfwWindowShouldClose( window )) {
                running = false;
            }
        }

    }

    stop_music(&music);

    glfwTerminate();

    return 0;   
}


void permute_start_positions(Config& config)
{
    for (int i = 0; i < 3; i++) {
        std::swap(config.pony_start[i], config.pony_start[i+1]);
        std::swap(config.pony_start_angle[i], config.pony_start_angle[i+1]);
    }
}

void randomize_start_positions(Config& config, Heightmap& heightmap)
{

    Rand32 rand((unsigned long int)(glfwGetTime() * 100000));

    V2f size = V2f(config.level_size.size().x, 
                   config.level_size.size().z);

    for (int i = 0; i < config.player_count; i++) {
        bool found = false;

        while (!found) {
            found = true;
            V2f pos = V2f(rand.nextf(-size.x/2, size.x/2),
                          rand.nextf(-size.y/2, size.y/2));
            float angle = rand.nextf(0, 2 * M_PI);

            if (heightmap.below_water(pos, config.water_tolerance)) {
                found = false;
                continue;
            }

            for (int j = 0; j < i; j++) {
                if ((config.pony_start[j] - pos).length() < config.min_start_distance) {
                    found = false;
                    break;
                }
            }

            if (!found) continue;

            V2f dir = V2f(sin(angle),cos(angle));
                          
            for (int j = 0; j < config.min_start_distance; j++) {
                if (heightmap.below_water(pos + (dir * j), 
                                          config.water_tolerance)) {
                    found = false;
                    break;
                }
            }

            if (found) {
                config.pony_start[i] = pos;
                config.pony_start_angle[i] = angle;
            }                          
            
        }
        
    }
}


void start_music(Mix_Music** music, const string& music_file)
{
    
    int audio_rate = 44100;
    Uint16 audio_format = MIX_DEFAULT_FORMAT; /* 16-bit stereo */
    int audio_channels = 2;
    int audio_buffers = 4096;


    // start SDL with audio support
    if(SDL_Init(SDL_INIT_AUDIO)==-1) {
        printf("SDL_Init: %s\n", SDL_GetError());
        exit(1);
    }

    // Open audio device
    if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers)) {
        printf("Unable to open audio!\n");
        exit(1);
    }

    // Query audio properties
    Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);

    // Load music file
    *music = Mix_LoadMUS(music_file.c_str());

    // Play music in infinite loop
    Mix_PlayMusic(*music, -1);

    
    Mix_VolumeMusic(config.music_volume);
    
}


void stop_music(Mix_Music** music)
{
    Mix_HaltMusic();
    Mix_FreeMusic(*music);
    *music = NULL;
    Mix_CloseAudio();
    SDL_Quit();
}
