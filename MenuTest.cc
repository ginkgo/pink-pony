#include "cinquo.hh"
#include "PonyGame.hh"

#include "Menu.hh"

#include <audiere.h>
using namespace audiere;

int main(int argc, char** argv)
{
    string config_file = "menutest.options";
    
    Config config;

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
            // Run game.
            cout << "Run game." << endl;
        } else if (menu_status == Menu::QUIT) {
            cout << "Quit game." << endl;
        }
        

    }
    glfwTerminate();

    return 0;   
}
