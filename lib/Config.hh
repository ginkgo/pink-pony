#ifndef CONFIG_HH
#define CONFIG_HH

#include "cinquo.hh"

class Config
{
    public:

    // Window properties:

    int width, height;
    int window_mode;
    int fsaa_samples;
    int swap_interval;
    GLenum polygon_mode;
    
    // Level properties:
    
    string heightmap_file;
    Box3f level_size;
    float water_level;
    
    Color4f heightmap_specular;
    Color4f heightmap_diffuse;
    float heightmap_shininess;
    float heightmap_velvet_coeff;
    
    string sand_texture;
    string grass_texture;
    string noise_texture;

    // Light properties:

    Color4f light_specular;
    Color4f light_diffuse;
    Color4f light_ambient;
    V3f light_dir;

    V3f hemilight_pole;
    Color4f hemilight_sky;
    Color4f hemilight_ground;
    
    // Camera properties:

    float camera_fov;
    float camera_near;
    float camera_far;
    float camera_distance;

    float camera_height;
    float pony_height;
    
    // Game properties:

    int ai_count;
    int player_count;
    int heart_count;
    V2f pony_start[4];
    float pony_start_angle[4];
    float pony_start_speed;
    int pony_up[4];
    int pony_down[4];
    int pony_left[4];
    int pony_right[4];
    float pony_min_speed;
    float pony_max_speed;
    float pony_acceleration;
    float pony_turn_speed;
    float water_tolerance;
    bool show_minimap;
    float pony_slope_acceleration;

    bool permute_start_positions;
    bool randomize_start_positions;
    float min_start_distance;

    // General appearance:
    bool use_particles;
    string digit_one;
    string digit_two;
    string digit_three;
    string digit_four;
    string heart_mesh;
    int heart_explosion_particles;

    // Pony appearance:
    Color4f pony_color[4];
    string pony_shader;
    float pony_velvet_coeff;
    string pony_texture;
    string pony_mesh;
    float pony_particle_rate;
    int pony_explosion_particles;

    // Sounds
    string background_music;
    

    Config();

    bool write_file(string filename);
    bool read_file(string filename);

    private:

    void set_value (string name, string value);
};

#endif
