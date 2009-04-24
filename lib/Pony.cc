#include "Pony.hh"

Pony::Pony(V2f pos, float angle,
           float speed,
           int up, int down,
           int left, int right,
           Config* config)
    : pos(pos),
      angle(angle),
      speed(speed),
      slope_angle(0),
      camera_pos(pos-V2f(sin(angle), cos(angle))),
      up(up),
      down(down),
      left(left),
      right(right),
      shader(config->pony_shader),
      mesh(),
      mesh_drawer(&mesh),
      texture(config->pony_texture.c_str()),
	  out(false)
{
    bool loaded = load_mesh(mesh, config->pony_mesh);

    if (!loaded) {
        cerr << "Failed to load mesh file " << config->pony_mesh << endl;
    }
}

void Pony::move(PonyGame* game, double timeDiff, int i)
{
    if (!out) {
        float accel = 0.0;
        float steer = 0.0;

        if (glfwGetKey(up) == GLFW_PRESS)
            accel += 1.0;
        if (glfwGetKey(down) == GLFW_PRESS)
            accel -= 1.0;

        if (glfwGetKey(left) == GLFW_PRESS)
            steer += 1.0;
        if (glfwGetKey(right) == GLFW_PRESS)
            steer -= 1.0;

        float slope =
            game->terrain()->get_pos(pos + V2f(sin(angle),
                                               cos(angle)),false).y
            - game->terrain()->get_pos(pos,false).y;
        accel -= game->config()->pony_slope_acceleration * slope;

        // TODO: Modify dir and speed

        float min = game->config()->pony_min_speed;
        float max = game->config()->pony_max_speed;

        speed += accel * game->config()->pony_acceleration * timeDiff;
        if (speed < min) speed = min;
        if (speed > max) speed = max;
    
        angle += steer * timeDiff * game->config()->pony_turn_speed;
        //     dir = dir * M33f().rotate(steer * timeDiff
        //                               * game->config()->pony_turn_speed);

        V2f dir(sin(angle), cos(angle));
    
	pos += dir * speed * timeDiff;
    
	// Calculate new camera position
    
        V2f offset = pos - camera_pos;
        camera_pos = pos - offset * (game->config()->camera_distance
                                     / offset.length());
    }    
}

void Pony::set_camera(PonyGame* game, Camera* camera, int i)
{
    V2f dir(sin(angle), cos(angle));
    V3f pony_height(0, game->config()->pony_height, 0);
    V3f camera_height(0, game->config()->camera_height, 0);

    V3f p = pony_height + game->terrain()->get_pos(pos,false);
    V3f c = camera_height + game->terrain()->get_pos(camera_pos,true);
    
    camera->look_at(c,p);                   
}

void Pony::draw(PonyGame* game, int i)
{
    if (!out) {
        
        V3f position = game->terrain()->get_pos(pos,false);

        texture.bind(GL_TEXTURE0);
        shader.bind();
    
        shader.set_uniform("hemi_pole",
                           game->config()->hemilight_pole);
        shader.set_uniform("hemi_sky",
                           game->config()->hemilight_sky);
        shader.set_uniform("hemi_ground",
                           game->config()->hemilight_ground);
        shader.set_uniform("velvet_coeff",
                           game->config()->pony_velvet_coeff);
        shader.set_uniform("texture", 0);
    
        glColor(game->config()->pony_color[i]);
        glPushMatrix();

        glTranslate(position);
        glRotatef(180 + angle * 180.0/M_PI, 0, 1, 0);

        V3f slope =
            game->terrain()->get_pos(pos + V2f(sin(angle),
                                               cos(angle)),false)
            - game->terrain()->get_pos(pos,false);


        // We smooth the x angle to reduce shakiness
        slope_angle *= 31./32.;
        slope_angle += asin(slope.y/ slope.length()) / M_PI * 180 * 1./32.;

        glRotatef(slope_angle,1,0,0);
    
        mesh_drawer.draw();

        glPopMatrix();

        shader.unbind();
        texture.unbind(GL_TEXTURE0);
    }
    
}
