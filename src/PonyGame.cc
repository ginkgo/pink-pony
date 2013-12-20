#include "PonyGame.hh"
#include "ParticleSystem.hh"
#include <ImathRandom.h>


// SDL_mixer includes
#include "SDL.h"
#include "SDL_mixer.h"

PonyGame::PonyGame(SplitScreen* screen,
                   Heightmap* heightmap,
                   Config* config,
                   Skydome* skydome)
    : particle_system(ParticleSystem::make_particle_system(2000000, config)),
      m_screen(screen),
      m_heightmap(heightmap),
      m_config(config),
      skydome(skydome),
      heart(),
      heart_drawer(&heart),
      heart_shader(config->resource_dir + "GLSL/heart")
{
    int human_count = m_config->player_count - m_config->ai_count;
    if (human_count == 0) human_count = m_config->player_count;
    // Init OpenGL states

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glShadeModel(GL_SMOOTH);

    // Init light source
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_DIFFUSE,
              (GLfloat*)&config->light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR,
              (GLfloat*)&config->light_specular);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,
                   (GLfloat*)&config->light_ambient);

    // TODO: I will likely have to move these material properties..
    
    glMaterialfv(GL_FRONT, GL_SPECULAR,
                 (GLfloat*)&config->heightmap_specular);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,
                 (GLfloat*)&config->heightmap_diffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, config->heightmap_shininess);
    
    for (int i = 0; i < m_config->player_count; i++) {

        if ( i < (config->player_count - config->ai_count)) {
            ponies.push_back(new PlayerPony(i, m_config, particle_system));  
        } else {
            ponies.push_back(new AIPony(i, m_config, particle_system)); 

        }       
        
        if (i < human_count) {
            m_screen->camera(i)->init(1.0,
                                      m_config->camera_fov,
                                      m_config->camera_near,
                                      m_config->camera_far);
        }
                                     
        m_screen->resize(m_screen->get_size().x,
                         m_screen->get_size().y);

        line_list.add_point(i, m_config->pony_start[i], *heightmap);
    }


    if (!load_mesh(heart, config->resource_dir + config->heart_mesh)) {
        cerr << "Could not load " << config->heart_mesh << "." << endl;
    };

    heart_shader.bind();
    heart_shader.set_uniform("hemi_pole", config->hemilight_pole);
    heart_shader.set_uniform("hemi_sky", config->hemilight_sky);
    heart_shader.set_uniform("hemi_ground", config->hemilight_ground);
    heart_shader.unbind();

    Rand32 rand((long)(glfwGetTime() * 1000));

    for (int i = 0; i < config->heart_count; i++) {
        V2f size = V2f(config->level_size.size().x, 
                       config->level_size.size().z);

        bool found = false;

        while (!found) {
            V2f pos = V2f(rand.nextf(-size.x/2, size.x/2),
                          rand.nextf(-size.y/2, size.y/2));

            if (!heightmap->below_water(pos, config->water_tolerance)) {
                // Valid position found.
                // Searching local maximum..
                bool found_maximum = false;
                float delta = 1;
                while (!found_maximum) {
                    float height = heightmap->get_pos(pos, false).y;
                    if (height < heightmap->get_pos(pos+V2f(delta,0), false).y) {
                        pos += V2f(delta,0);
                        continue;
                    }
                    if (height < heightmap->get_pos(pos+V2f(-delta,0), false).y) {
                        pos += V2f(-delta,0);
                        continue;
                    }
                    if (height < heightmap->get_pos(pos+V2f(0,delta), false).y) {
                        pos += V2f(0,delta);
                        continue;
                    }
                    if (height < heightmap->get_pos(pos+V2f(0,-delta), false).y) {
                        pos += V2f(0,-delta);
                        continue;
                    }
                    found_maximum = true;
                }
                heart_positions.push_back(pos);

                
                found = true;
            }                    
        }
    }
}

PonyGame::~PonyGame()
{
    for (int i = 0; i < m_config->player_count; i++) {
        delete ponies[i];
    }

    ponies.clear();

    delete particle_system;
}

bool PonyGame::start(PonyPoints& points)
{
    int human_count = m_config->player_count - m_config->ai_count;
    if (human_count == 0) human_count = m_config->player_count;

    int humans_alive = human_count;

    bool run_game = true;

    bool running = true;
    double delay = 10.0;

    double then = glfwGetTime();

    int ponies_alive = m_config->player_count;

    cout << m_config->player_count << " ponies." << endl;

    GLboolean space_pressed = glfwGetKey(GLFW_KEY_SPACE);
    GLboolean f1_pressed = glfwGetKey(GLFW_KEY_F1);

    ParticleExplosionSource explosion_source(particle_system);

    while (running || delay > 0.0) {

        double now = glfwGetTime();
        double timeDiff = now - then;
        then = now;
        
        if (humans_alive < 1)
            timeDiff *= 8;

        if (!running) {
            delay -= timeDiff;
        }

        // Step simulation

        if (humans_alive < 1)
            particle_system->step_simulation(timeDiff/8);
        else 
            particle_system->step_simulation(timeDiff);

        for (int i = 0; i < m_config->player_count; i++) {
            ponies[i]->move(this, timeDiff,i);

            if (i < human_count)
                ponies[i]->set_camera(this, m_screen->camera(i),i);

            if (!ponies[i]->is_out()) {
                bool has_intersected =
                    line_list.add_point(i, ponies[i]->get_pos(), *m_heightmap);
                bool below_water =
                    m_heightmap->below_water(ponies[i]->get_pos(),
                                             m_config->water_tolerance);
                if( has_intersected || below_water) {

                    ponies_alive--;

                    if (m_config->player_count == 1) {
                        if (ponies_alive == 0) {
                            running = false;
                            delay = 2.0;
                        }
                    } else {
                        if (ponies_alive < 2) {
                            running = false;
                        }

                        if (ponies_alive == 0) {
                            delay = min(delay, 2.0);
                        }
                    }

                    cout << "Pony " << i+1 << " out because ";
                    if (has_intersected) {
                        cout << "it ran into a trail." << endl;
                    } else {
                        cout << "it ran in the water." << endl;
                    }
                    ponies[i]->set_out(true);
                    explosion_source.explode
                        (m_heightmap->get_pos(ponies[i]->get_pos()) + V3f(0,4,0),
                         m_config->pony_color[i],
                         m_config->pony_explosion_particles,
                         1/8.0);

                    if (i < human_count)
                        --humans_alive;

                    for (int j = 0; j < m_config->player_count; j++) {
                        if (!ponies[j]->is_out()) {
                            points.add_point(j, m_config->pony_color[i]);
                        }
                    } 
                };

                list<V2f>::iterator j = heart_positions.begin();
                while(j != heart_positions.end()) {
                    if ((*j - ponies[i]->get_pos()).length() < 3.0) {
                        points.add_point(i, Color4f(1,0,0,1));
                        explosion_source.explode
                            (m_heightmap->get_pos(*j) + V3f(0,2,0),
                             Color4f(1,0,0,1),
                             m_config->heart_explosion_particles,
                             1/32.0);
                        j = heart_positions.erase(j);
                    } else {
                        ++j;
                    }
                }
            }
        }

        // Draw state        
        
        glClear(GL_COLOR_BUFFER_BIT | 
                GL_DEPTH_BUFFER_BIT | 
                GL_STENCIL_BUFFER_BIT);
        glPolygonMode(GL_FRONT_AND_BACK, m_config->polygon_mode);

        
        for (int i = 0; i < human_count; i++) {

            m_screen->set_subscreen(i);
            m_screen->camera(i)->set_matrices();

            GLfloat light_dir[] = {m_config->light_dir.x,
                                   m_config->light_dir.y,
                                   m_config->light_dir.z,
                                   0};
            
            glLightfv(GL_LIGHT0, GL_POSITION, light_dir);

            glPushMatrix();
            glTranslate(m_screen->camera(i)->get_position());
            skydome->draw();
            glPopMatrix();

            for (int j = 0; j < m_config->player_count; j++) {
                ponies[j]->draw(this,j);
            }

            for (list<V2f>::iterator j = heart_positions.begin();
                 j != heart_positions.end(); ++j) {
                V3f pos = m_heightmap->get_pos(*j, false);

                heart_shader.bind();

                glPushMatrix();
                
                glTranslate(pos + V3f(0,1,0));
                glRotatef(-90,1,0,0);
                glRotatef(glfwGetTime() * 30, 0, 0, 1);
                glScalef(1,2,1);

                heart_drawer.draw(&heart_shader);                
                
                glPopMatrix();

                heart_shader.unbind();

            }

            m_heightmap->draw(m_config);

            particle_system->draw(*(m_screen->camera(i)));


            line_list.draw_trails(this);
            
        }

        // Draw point HUD

        for (int i = 0; i < human_count; i++) {
            m_screen->set_point_hud(i);
            glDisable(GL_DEPTH_TEST);
            glDisable(GL_CULL_FACE);
            points.draw_hud(i);
        }

        // Draw minimap
        if (m_config->show_minimap) {
            glDisable(GL_CULL_FACE);
            glDisable(GL_DEPTH_TEST);
            
            Box3f extent = m_config->level_size;
            
            m_screen->set_map();
            
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(extent.max.x, extent.min.x,
                    extent.max.z, extent.min.z,
                    extent.min.y-3, extent.max.y-m_config->water_level-0.1);
            glMatrixMode(GL_MODELVIEW);

            glLoadIdentity();
            glPushMatrix();

            glRotatef(90.0,1,0,0);
            glTranslatef(0,-m_config->level_size.max.y,0);


            GLfloat light_dir[] = {m_config->light_dir.x,
                                   m_config->light_dir.y,
                                   m_config->light_dir.z,
                                   0};
    
            glLightfv(GL_LIGHT0, GL_POSITION, light_dir);

            // Temporarily disable velvet shader
            float tmp_velvet = m_config->heightmap_velvet_coeff;
            m_config->heightmap_velvet_coeff = 0.0;
                
            m_heightmap->draw(m_config);

            m_config->heightmap_velvet_coeff = tmp_velvet;
    
            glPopMatrix();

            glDisable(GL_LIGHTING);
            
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(extent.max.x, extent.min.x,
                    extent.min.z, extent.max.z,
                    -1, 1);
            glMatrixMode(GL_MODELVIEW);

            line_list.draw_lines(m_config);


            glEnable(GL_CULL_FACE);
        }

        getErrors();
        calc_fps();
        glfwSwapBuffers();

        // Check if still running
        
        if(glfwGetKey( GLFW_KEY_ESC ) ||
           !glfwGetWindowParam( GLFW_OPENED )) {
            running = false;
            run_game = false;
            delay = 0.0;
        }


        if (glfwGetKey(GLFW_KEY_F1) && !f1_pressed) {
            int current_volume = Mix_VolumeMusic(-1);
            Mix_VolumeMusic(std::min(128, current_volume + 64) % 128);
            m_config->music_volume = Mix_VolumeMusic(-1);
        }

        space_pressed = glfwGetKey(GLFW_KEY_SPACE);
        f1_pressed = glfwGetKey(GLFW_KEY_F1);
    }

    return run_game;
}
