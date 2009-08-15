#include "cinquo.hh"
#include "PonyGame.hh"

#include "Menu.hh"

#include <audiere.h>
using namespace audiere;

#include <algorithm>
#include "ImathRandom.h"

void permute_start_positions(Config& config);
void randomize_start_positions(Config& config, Heightmap& heightmap);

int main(int argc, char** argv)
{
    string config_file = "pony.options";
    
    Config config;

    if (argc > 1) {
        config_file = string(argv[1]);
    }
    
    if (!config.read_file(config_file)) {
        cerr << "Could not read config file." << endl;
        return 1;
    }
    
    AudioDevicePtr device(OpenDevice());
    if (!device) {
        cerr << "Could not open audio device. :<" << endl;
    }
    
    OutputStreamPtr music(OpenSound(device, 
                                    config.background_music.c_str(), 
                                    true));
    
    if (!music) {
        cerr << "Could not load music file. :<" << endl;
    } else {
        
        music->setRepeat(true);
        music->setVolume(1.0);
        music->play();
        
    }

    glfwInit();
    glfwOpenWindowHint(GLFW_FSAA_SAMPLES, config.fsaa_samples);

    glfwOpenWindow(config.width, config.height, // width, height
                   0, 0, 0, 0,                  // R, G, B, A
                   24, 8,                       // depth, stencil
                   config.window_mode);         // GLFW_WINDOW | GLFW_FULLSCREEN

    glfwSetWindowTitle("Pink Pony <3");
    glfwSwapInterval(config.swap_interval);
    
    // We put everything between glfwOpenWindow & glfwTerminate
    // between braces, so that stack variables that need a GL context
    // are destructed, while the context still exists.
    {
        Skydome skydome("textures/sky.png");
        Menu::MenuStatus menu_status;
        
        {
            Menu menu(&config, &skydome);

            menu_status = menu.run();
        }

        if (!config.write_file(config_file)) {
            cerr << "Could not write config file." << endl;
        }

        if (menu_status == Menu::START) {        
            Heightmap heightmap(config.heightmap_file,
                                config.level_size,
                                config.water_level,
                                config.sand_texture,
                                config.grass_texture,
                                config.noise_texture);
    
            PonyPoints points(config.player_count);

            bool run_game = true;

            while (run_game){

                if (config.randomize_start_positions)
                    randomize_start_positions(config, heightmap);
                else if (config.permute_start_positions)
                    permute_start_positions(config);

                SplitScreen screen(config.width, config.height,
                                   config.player_count);
                screen.set_glfw_callback();

                PonyGame game(&screen,
                              &heightmap,
                              &config,
                              &skydome);

                run_game = game.start(points);
            }
        } else if (menu_status == Menu::QUIT) {
            cout << "Quit game." << endl;
        }
        

    }
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