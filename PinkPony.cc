#include "cinquo.hh"
#include "PonyGame.hh"

int main(int argc, char** argv)
{
    string config_file = "pony.options";    
    bool run_game = true;
    
    Config config(argc, argv);

    if (argc > 1) {
        config_file = string(argv[1]);
    }
    
    if (!config.read_file(config_file)) {
        cerr << "Could not read config file." << endl;
        return 1;
    }
    
    glfwInit();
    glfwOpenWindowHint(GLFW_FSAA_SAMPLES, config.fsaa_samples);

    glfwOpenWindow(config.width, config.height, // width, height
                   0, 0, 0, 0,                  // R, G, B, A
                   0, 0,                        // depth, stencil
                   config.window_mode);         // GLFW_WINDOW | GLFW_FULLSCREEN

    glfwSwapInterval(config.swap_interval);
    
    // We put everything between glfwOpenWindow & glfwTerminate
    // between braces, so that stack variables that need a GL context
    // are destructed, while the context still exists.
    while (run_game){
        // TODO: Menu screen

        SplitScreen screen(config.width, config.height,
                           config.player_count);
        screen.set_glfw_callback();
    
        Heightmap heightmap(config.heightmap_file,
                            config.level_size,
                            config.water_level,
                            config.sand_texture,
                            config.grass_texture);

        Skydome skydome("textures/sky.tga");

        PonyGame game(&screen,
                      &heightmap,
                      &config,
                      &skydome);

        run_game = game.start();
    }
    
    glfwTerminate();

    return 0;   
}
