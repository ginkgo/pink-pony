#include "Config.hh"
#include <fstream>

Config::Config(int argc, char** argv)
    : width(800),
      height(600),
      window_mode(GLFW_FULLSCREEN),
      fsaa_samples(4),
      swap_interval(1),
      heightmap_file("levels/heightmap-heart.exr"),
      level_size(V3f(-500, 0,-500),
                 V3f( 500,60, 500)),
      water_level(15),
      sand_texture("textures/sand.tga"),
      grass_texture("textures/grass.tga"),
      player_count(1),
      pony_start_speed(15.0),
      pony_min_speed(5.0),
      pony_max_speed(50.0),
      pony_acceleration(25.0),
      pony_turn_speed(1.25),
      water_tolerance(1.0),
      show_minimap(true),
      camera_fov(45.0),
      camera_near(1.0),
      camera_far(2000.0),
      camera_distance(15.0),
      pony_height(3.0),
      camera_height(6.0),
      heightmap_specular(1,1,1,1),
      heightmap_diffuse(1,1,1,1),
      heightmap_shininess(50.0),
      heightmap_velvet_coeff(1.5),
      light_specular(1,1,1,1),
      light_diffuse(1,1,1,1),
      light_ambient(0.05,0.05,0.05,1),
      light_dir(V3f(-1,0.5,-0.75).normalized()),
      pony_shader("GLSL/pony"),
      pony_texture("textures/pony.tga"),
      pony_mesh("models/Pony.mesh.xml"),
      pony_velvet_coeff(2.0),
      hemilight_pole(0,1,0),
      hemilight_sky(1/3.0,1/3.0,1/3.0,1),
      hemilight_ground(1/8.0,1/8.0,1/8.0,1),
      polygon_mode(GL_FILL)
{
    pony_up[0] = GLFW_KEY_UP;
    pony_down[0] = GLFW_KEY_DOWN;
    pony_left[0] = GLFW_KEY_LEFT;
    pony_right[0] = GLFW_KEY_RIGHT;
    pony_start[0] = V2f(0,15);
    pony_start_angle[0] = 0.0 * M_PI;
    pony_color[0] = Color4f(1,0.75,0.792968,1);

    pony_up[1] = 'W';
    pony_down[1] = 'S';
    pony_left[1] = 'A';
    pony_right[1] = 'D';
    pony_start[1] = V2f(0,-15);
    pony_start_angle[1] = 1.0 * M_PI;
    pony_color[1] = Color4f(0.25,0.875,0.8125,1);
    
    pony_up[2] = GLFW_KEY_KP_8;
    pony_down[2] = GLFW_KEY_KP_5;
    pony_left[2] = GLFW_KEY_KP_4;
    pony_right[2] = GLFW_KEY_KP_6;
    pony_start[2] = V2f( 15,0);
    pony_start_angle[2] = 0.5 * M_PI;
    pony_color[2] = Color4f(1,0.83984375,0.0,1);
    
    pony_up[3] = 'I';
    pony_down[3] = 'K';
    pony_left[3] = 'J';
    pony_right[3] = 'L';
    pony_start[3] = V2f(-15,0);
    pony_start_angle[3] = 1.5 * M_PI;
    pony_color[3] = Color4f(0.484375,0.984375,0,1);
    
    // TODO: Parse command line options
    // TODO: Parse config file
}

void Config::set_value(string name, string value)
{    
    
    int ival = 0;
    float fval = 0.0f;
    int winmodeval = GLFW_WINDOW;
    GLenum polymodeval = GL_FILL;
    string sval = "";
    V2f vec2val;
    V3f vec3val;
    Color4f colorval;
    bool bval;

    try {
        std::stringstream ss(value);
        ss >> ival;
    } catch (...) {};

    try {
        std::stringstream ss(value);
        ss >> fval;
    } catch (...) {};

    try {
        std::stringstream ss(value);
        ss >> vec2val;
    } catch (...) {};

    try {
        std::stringstream ss(value);
        ss >> vec3val;
    } catch (...) {};

    try {
        std::stringstream ss(value);
        ss >> colorval;
    } catch (...) {};

    if (value.find("true") != string::npos &&
        value.find("true") < value.find(';')) {
        bval = true;
    } else {
        bval = false;
    }

    if (value.find("window") != string::npos &&
        value.find("window") < value.find(';')) {
        winmodeval = GLFW_WINDOW;
    } else {
        winmodeval = GLFW_FULLSCREEN;
    }

    if (value.find("fill") != string::npos &&
        value.find("fill") < value.find(';')) {
        polymodeval = GL_FILL;
    } else {
        polymodeval = GL_LINE;
    }

    if (value.find('"') != string::npos) {
        int p1 = value.find('"');
        int p2 = value.find('"', p1+1);

        if (p2 != string::npos) {
            sval = value.substr(p1+1,(p2 - p1) - 1);
        }
    }

    
    if (name == "width") width = ival;        
    else if (name == "height") height = ival;
    else if (name == "window_mode") window_mode = winmodeval;
    else if (name == "fsaa_samples") fsaa_samples = ival;
    else if (name == "swap_interval") swap_interval = ival;
    else if (name == "polygon_mode") polygon_mode = polymodeval;
    else if (name == "heightmap_file") heightmap_file = sval;
    else if (name == "level_size") level_size
                                       = Box3f(V3f(-vec3val.x/2, 0, -vec3val.z/2),
                                               V3f( vec3val.x/2, vec3val.y, vec3val.z/2));
    else if (name == "water_level") water_level = fval;
    else if (name == "heightmap_specular") heightmap_specular = colorval;
    else if (name == "heightmap_diffuse") heightmap_diffuse = colorval;
    else if (name == "heightmap_shininess") heightmap_shininess = fval;
    else if (name == "heightmap_velvet_coeff") heightmap_velvet_coeff = fval;
    else if (name == "sand_texture") sand_texture = sval;
    else if (name == "grass_texture") grass_texture = sval;
    else if (name == "light_specular") light_specular = colorval;
    else if (name == "light_diffuse") light_diffuse = colorval;
    else if (name == "light_ambient") light_ambient = colorval;
    else if (name == "light_dir") light_dir = vec3val;
    else if (name == "hemilight_pole") hemilight_pole = vec3val;
    else if (name == "hemilight_sky") hemilight_sky = colorval;
    else if (name == "hemilight_ground") hemilight_ground = colorval;
    else if (name == "camera_fov") camera_fov = fval;
    else if (name == "camera_near") camera_near = fval;
    else if (name == "camera_far") camera_far = fval;
    else if (name == "camera_distance") camera_distance = fval;
    else if (name == "camera_height") camera_height = fval;
    else if (name == "pony_height") pony_height = fval;
    else if (name == "player_count") player_count = ival;
    else if (name == "pony_start[0]") pony_start[0] = vec2val;
    else if (name == "pony_start[1]") pony_start[1] = vec2val;
    else if (name == "pony_start[2]") pony_start[2] = vec2val;
    else if (name == "pony_start[3]") pony_start[3] = vec2val;
    else if (name == "pony_start_angle[0]")
        pony_start_angle[0] = fval * M_PI / 180.0;
    else if (name == "pony_start_angle[1]")
        pony_start_angle[1] = fval * M_PI / 180.0;
    else if (name == "pony_start_angle[2]")
        pony_start_angle[2] = fval * M_PI / 180.0;
    else if (name == "pony_start_angle[3]")
        pony_start_angle[3] = fval * M_PI / 180.0;
    else if (name == "pony_start_speed") pony_start_speed = fval;
    else if (name == "pony_up[0]") pony_up[0] = ival;
    else if (name == "pony_up[1]") pony_up[1] = ival;
    else if (name == "pony_up[2]") pony_up[2] = ival;
    else if (name == "pony_up[3]") pony_up[3] = ival;
    else if (name == "pony_down[0]") pony_down[0] = ival;
    else if (name == "pony_down[1]") pony_down[1] = ival;
    else if (name == "pony_down[2]") pony_down[2] = ival;
    else if (name == "pony_down[3]") pony_down[3] = ival;
    else if (name == "pony_left[0]") pony_left[0] = ival;
    else if (name == "pony_left[1]") pony_left[1] = ival;
    else if (name == "pony_left[2]") pony_left[2] = ival;
    else if (name == "pony_left[3]") pony_left[3] = ival;
    else if (name == "pony_right[0]") pony_right[0] = ival;
    else if (name == "pony_right[1]") pony_right[1] = ival;
    else if (name == "pony_right[2]") pony_right[2] = ival;
    else if (name == "pony_right[3]") pony_right[3] = ival;
    else if (name == "pony_min_speed") pony_min_speed = fval;
    else if (name == "pony_max_speed") pony_max_speed = fval;
    else if (name == "pony_acceleration") pony_acceleration = fval;
    else if (name == "pony_turn_speed") pony_turn_speed = fval;
    else if (name == "water_tolerance") water_tolerance = fval;
    else if (name == "show_minimap") show_minimap = bval;
    else if (name == "pony_color[0]") pony_color[0] = colorval;
    else if (name == "pony_color[1]") pony_color[1] = colorval;
    else if (name == "pony_color[2]") pony_color[2] = colorval;
    else if (name == "pony_color[3]") pony_color[3] = colorval;
    else if (name == "pony_shader") pony_shader = sval;
    else if (name == "pony_velvet_coeff") pony_velvet_coeff = fval;
    else if (name == "pony_texture") pony_texture = sval;
    else if (name == "pony_mesh") pony_mesh = sval;
    else if (name == "pony_slope_acceleration") pony_slope_acceleration = fval;
}

bool Config::read_file(string filename)
{
    std::ifstream is(filename.c_str());

    if (!is) {
        cerr << "Could not open file " << filename
             << " for reading." << endl;
        return false;
    }

    while (!is.eof()) {
        string line;
        std::getline(is, line);

        if (line.size() < 2)
            continue;
        if (line.substr(0,2) == "//")
            continue;

        string::size_type p = line.find(' ');

        string name = line.substr(0,p);

        p = line.find('=');
        string value = line.substr(p+1);

        set_value(name, value);
    }
}

bool Config::write_file(string filename)
{
    std::ofstream os(filename.c_str());

    if (!os) {
        cerr << "Could not open file " << filename
             << "for writing." << endl;
        return false;
    }

    os << "// Window properties" << endl << endl;
    os << "width = " << width << ";" << endl;
    os << "height = " << height << ";" << endl;
    os << "swap_interval = " << swap_interval <<  ";" << endl;
    os << "window_mode = ";
    if (window_mode == GLFW_WINDOW)
        os << "window;" << endl;
    else
        os << "fullscreen;" << endl;
    os << "fsaa_samples = " << fsaa_samples <<  ";" << endl;
    os << "polygon_mode = ";
    if (polygon_mode == GL_LINE)
        os << "line;" << endl;
    else
        os << "fill;" << endl;


    os << endl << "// Level properties" << endl << endl;
    os << "heightmap_file = \"" << heightmap_file << "\";" << endl;
    os << "level_size = " << level_size.size() << ";" << endl;
    os << "water_level = " << water_level << ";" << endl;
    os << "heightmap_specular = " << heightmap_specular << ";" << endl;
    os << "heightmap_diffuse = " << heightmap_diffuse << ";" << endl;
    os << "heightmap_shininess = " << heightmap_shininess << ";" << endl;
    os << "heightmap_velvet_coeff = " << heightmap_velvet_coeff << ";" << endl;
    os << "sand_texture = \"" << sand_texture << "\";" << endl;
    os << "grass_texture = \"" << grass_texture << "\";" << endl;
    for (int i = 0; i < 4; i++) {
        os << "pony_start[" << i << "] = " << pony_start[i]
           << ";" << endl;
        os << "pony_start_angle[" << i << "] = "
           << pony_start_angle[i] * 180/M_PI << ";" << endl;
    }
    

    os << endl << "// Light properties" << endl << endl;    
    os << "light_specular = " << light_specular << ";" << endl;
    os << "light_diffuse = " << light_diffuse << ";" << endl;
    os << "light_ambient = " << light_ambient << ";" << endl;
    os << "light_dir = " << light_dir << ";" << endl;
    os << "hemilight_pole = " << hemilight_pole << ";" << endl;
    os << "hemilight_sky = " << hemilight_sky << ";" << endl;
    os << "hemilight_ground = " << hemilight_ground << ";" << endl;

    os << endl << "// Camera properties" << endl << endl;    
    os << "camera_fov = " << camera_fov << ";" << endl;
    os << "camera_near = " << camera_near << ";" << endl;
    os << "camera_far = " << camera_far << ";" << endl;
    os << "camera_distance = " << camera_distance << ";" << endl;

    os << "camera_height = " << camera_height << ";" << endl;
    os << "pony_height = " << pony_height << ";" << endl;

    os << endl << "// Game properties" << endl << endl;   
    os << "player_count = " << player_count << ";" << endl;
    os << "pony_start_speed = " << pony_start_speed << ";" << endl;
    os << "pony_min_speed = " << pony_min_speed << ";" << endl;
    os << "pony_max_speed = " << pony_max_speed << ";" << endl;
    os << "pony_acceleration = " << pony_acceleration << ";" << endl;
    os << "pony_turn_speed = " << pony_turn_speed << ";" << endl;
    os << "water_tolerance = " << water_tolerance << ";" << endl;
    os << "show_minimap = " << (show_minimap?"true":"false") << ";" << endl;
    for (int i = 0; i < 4; i++) {
        os << "pony_up[" << i << "] = " << pony_up[i] << ";" << endl;
        os << "pony_down[" << i << "] = " << pony_down[i] << ";" << endl;
        os << "pony_left[" << i << "] = " << pony_left[i] << ";" << endl;
        os << "pony_right[" << i << "] = " << pony_right[i] << ";" << endl;
    }
    os << "pony_slope_acceleration = " << pony_slope_acceleration << ";" << endl;

    

    os << endl << "// Pony appearance" << endl << endl;   
    os << "pony_shader = \"" << pony_shader << "\";" << endl;
    os << "pony_velvet_coeff = " << pony_velvet_coeff << ";" << endl;
    os << "pony_texture = \"" << pony_texture << "\";" << endl;
    os << "pony_mesh = \"" << pony_mesh << "\";" << endl;
    for (int i = 0; i < 4; i++) {
        os << "pony_color[" << i << "] = " << pony_color[i] << ";" << endl;
    }
    return true;
}
