#include "Pony.hh"
#include <ImathColorAlgo.h>


Color4f hsvColor(const Color4f& rgbColor)
{
    Color4f hsv = rgbColor;
    float Min   = min(min(rgbColor.r, rgbColor.g), rgbColor.b);
    float Max   = max(max(rgbColor.r, rgbColor.g), rgbColor.b);
    float Delta = Max - Min;

    hsv.b = Max;                               
    	
    if(Max != float(0))
	    {
		    hsv.g = Delta / hsv.b;    
			float h = float(0);

		    if(rgbColor.r == Max)
			    // between yellow & magenta
			    h = float(0) + float(60) * (rgbColor.g - rgbColor.b) / Delta;
		    else if(rgbColor.g == Max)
			    // between cyan & yellow
			    h = float(120) + float(60) * (rgbColor.b - rgbColor.r) / Delta;
		    else
			    // between magenta & cyan
			    h = float(240) + float(60) * (rgbColor.r - rgbColor.g) / Delta;
            
		    if(h < float(0)) 
                hsv.r = h + float(360);
			else
				hsv.r = h;
	    }
    else
	    {
		    // If r = g = b = 0 then s = 0, h is undefined
		    hsv.g = float(0);
		    hsv.r = float(0);
	    }

    return hsv;
}

Color4f rgbColor(const Color4f& hsvColor)
{
    Color4f hsv = hsvColor;
    Color4f rgbColor = hsv;

    if(hsv.g == float(0))
        // achromatic (grey)
        rgbColor = Color4f(hsv.b,hsv.b,hsv.b,hsv.a);
    else
	    {
            float sector = floor(hsv.r / float(60));
			float frac = (hsv.r / float(60)) - sector;
            // factorial part of h
            float o = hsv.b * (float(1) - hsv.g);
            float p = hsv.b * (float(1) - hsv.g * frac);
            float q = hsv.b * (float(1) - hsv.g * (float(1) - frac));

            switch(int(sector))
                {
                default:
                case 0:
                    rgbColor.r = hsv.b;
                    rgbColor.g = q;
                    rgbColor.b = o;
                    break;
                case 1:
                    rgbColor.r = p;
                    rgbColor.g = hsv.b;
                    rgbColor.b = o;
                    break;
                case 2:
                    rgbColor.r = o;
                    rgbColor.g = hsv.b;
                    rgbColor.b = q;
                    break;
                case 3:
                    rgbColor.r = o;
                    rgbColor.g = p;
                    rgbColor.b = hsv.b;
                    break;
                case 4:
                    rgbColor.r = q; 
                    rgbColor.g = o; 
                    rgbColor.b = hsv.b;
                    break;
                case 5:
                    rgbColor.r = hsv.b; 
                    rgbColor.g = o; 
                    rgbColor.b = p;
                    break;
                }
	    }

    return rgbColor;
}

Pony::Pony(int i, Config* config, ParticleSystem* particle_system)
    : pos(config->pony_start[i]),
      angle(config->pony_start_angle[i]),
      speed(config->pony_start_speed),
      slope_angle(0),
      camera_pos(pos-V2f(sin(angle), cos(angle))),
      up(config->pony_up[i]),
      down(config->pony_down[i]),
      left(config->pony_left[i]),
      right(config->pony_right[i]),
      shader(config->pony_shader),
      mesh(),
      animation("models/Pony-animated.pskeleton"),
      mesh_drawer(&mesh),
      texture(config->pony_texture.c_str()),
	  out(false), out_delay(false), particle_source(particle_system)
{
    bool loaded = load_mesh(mesh, config->pony_mesh);

    if (!loaded) {
        cerr << "Failed to load mesh file " << config->pony_mesh << endl;
    }

    Color4f pony_color = config->pony_color[i];

    cout << pony_color * 255 << " -> ";

    pony_color = hsvColor(pony_color);

    cout << pony_color << endl;

    float pony_hue = pony_color.r;

    V2u size = texture.get_size();
    V2u pos(0,0);
    for(pos.x = 0; pos.x < size.x; ++pos.x) {
        for (pos.y = 0; pos.y < size.y; ++pos.y) {
            Color4f c = texture.get_color(pos);
            c = hsvColor(c);
            
            c.r += pony_hue;

            if (c.r > 360) c.r -= 360;
            if (c.r < 0)   c.r += 360;

            c = rgbColor(c);
            texture.set_color(pos, c);
        }
    }

    texture.send_to_GPU();

    animation.set_animation("Gallop");
}

Pony::Decision PlayerPony::decide(PonyGame* game, int i)
{
    Decision decision = {0.0f, 0.0f};
    float& accel = decision.acceleration;
    float& steer = decision.steer;

    if (glfwGetKey(up) == GLFW_PRESS)
        accel += 1.0;
    if (glfwGetKey(down) == GLFW_PRESS)
        accel -= 1.0;

    if (glfwGetKey(left) == GLFW_PRESS)
        steer += 1.0;
    if (glfwGetKey(right) == GLFW_PRESS)
        steer -= 1.0;

    if (glfwGetJoystickParam(i,GLFW_PRESENT) == GL_TRUE) {

        float axes[10];

        int n = glfwGetJoystickPos(i,axes,10);

        if (n >= 2) {

            if (fabs(axes[0]) < 0.2) axes[0] = 0.0;
            //accel += axes[1];
            steer -= axes[0]*2;
        }

        unsigned char buttons[20];

        int button_count = glfwGetJoystickButtons(i, buttons, 20);

        if (button_count >= 2) {
            if (buttons[0] == GLFW_PRESS)
                accel += 1.0;
            if (buttons[1] == GLFW_PRESS)
                accel -= 1.0;
        }

        if (accel > 1.0) accel = 1.0;
        if (accel < -1.0) accel = -1.0;
        if (steer > 1.0) steer = 1.0;
        if (steer < -1.0) steer = -1.0;

    }

    accel *= game->config()->pony_acceleration;
    steer *= game->config()->pony_turn_speed;

    return decision;
};

Pony::Decision AIPony::decide(PonyGame* game, int i)
{
    float angle = this->angle + rand.nextf(-0.1, 0.1);

    Decision decision = {0.0f, 0.0f};
    float& accel = decision.acceleration;
    float& steer = decision.steer;
	Line intersection(pos,pos);
	V2f pony_dir(sin(angle), cos(angle));
	V2f nextpos = pos + pony_dir * speed * 2;
	V2f waterpos;
	Line nextline(pos,nextpos);
	V2f per_dir = V2f(cos(angle), -sin(angle));
	V2f intersection_point;
	bool water_collision = game->terrain()->intersects_with_water(nextline, game->config()->water_tolerance, &waterpos);
	bool wall_collision = game->linelist()->intersects(nextline, &intersection_point);

	if (((water_collision)&&((!wall_collision)||(wall_collision && (intersection_point - pos).length() > (waterpos - pos).length())))&&(!hunting_heart)) {
		accel -= game->config()->pony_acceleration;
		if(turning==STILL) {
			bool r = game->terrain()->below_water(waterpos+per_dir, game->config()->water_tolerance);
			bool l = game->terrain()->below_water(waterpos-per_dir, game->config()->water_tolerance);
			if (r&&!l) turning = RIGHT;
			else if (l&&!r) turning = LEFT;
			else turning = lastturning;
		} else turning = lastturning;
	} else if ((game->linelist()->intersects(nextline, &intersection))&&(!hunting_heart)) {
		V2f inter_dir = intersection.b-intersection.a;
		accel -= game->config()->pony_acceleration;
		if((pony_dir^inter_dir) < 0) inter_dir = -inter_dir;
		if((per_dir^inter_dir) > 0) {
			turning = LEFT;
		} else if((per_dir^inter_dir) < 0)  {
			turning = RIGHT;
		} else {
			turning = lastturning;
		}
	} else {
		vector<Pony*>* ponies = game->get_ponies();
		bool cut_road = false;
		for (unsigned int i = 0; i < ponies->size(); i++) {
			V2f pony_pony_dir(sin(ponies->at(i)->angle), cos(ponies->at(i)->angle));
			V2f pony_nextpos = ponies->at(i)->pos + pony_pony_dir * ponies->at(i)->speed * 1;
			Line pony_nextline(ponies->at(i)->pos,pony_nextpos);
			if(pony_nextline.intersects(nextline)) {
				V2f inter_dir = pony_nextline.b-pony_nextline.a;
				accel = -1*game->config()->pony_acceleration;
				if((pony_dir^inter_dir) < 0) inter_dir = -inter_dir;
				if((per_dir^inter_dir) > 0) {
					turning = LEFT;
				} else if((per_dir^inter_dir) < 0)  {
					turning = RIGHT;
				} else {
					turning = lastturning;
				}
				cut_road = true;
			}
		}
		if (!cut_road) {
			if(!game->linelist()->intersects(nextline, &intersection)) accel = game->config()->pony_acceleration;
			else accel -= game->config()->pony_acceleration;
			turning = STILL;
			list<V2f>* hearts = game->hearts();
			int minlength = 301;
			V2f minheart_dir(1.0,0.0);
			for(list<V2f>::iterator heart = hearts->begin(); heart != hearts->end(); heart++) {
				V2f heart_dir = *heart - pos;
				Line heart_line(pos, *heart);
				if((heart_dir.length()<300)&&!game->linelist()->intersects(heart_line, &intersection)) {
					int length = heart_dir.length();
					heart_dir.normalize();
					if((pony_dir^heart_dir) > cos(M_PI/4)) {
						if (length < minlength) {
							minheart_dir = heart_dir;
							minlength = length;
							hunting_heart = &(*heart);
						}
					}
				}
			}
			if(minlength<301) {
				if((per_dir^minheart_dir) > 0.1) {
					turning = LEFT;
				} else if((per_dir^minheart_dir) < -0.1){
					turning = RIGHT;
				} else {
					turning = STILL;
				}
			} else {
				hunting_heart = NULL;
			}
		}
	}
	steer = turning*game->config()->pony_turn_speed;
	if(turning!=STILL) lastturning = turning;

    return decision;
}

void Pony::move(PonyGame* game, double timeDiff, int i)
{
    if (!out) {
        Decision decision = this->decide(game, i);

        float accel = decision.acceleration;
        float steer = decision.steer;

        if (accel > game->config()->pony_acceleration)
            accel = game->config()->pony_acceleration;
        if (accel < -game->config()->pony_acceleration)
            accel = -game->config()->pony_acceleration;
        if (steer > game->config()->pony_turn_speed)
            steer = game->config()->pony_turn_speed;
        if (steer < -game->config()->pony_turn_speed)
            steer = -game->config()->pony_turn_speed;

        float min = game->config()->pony_min_speed;
        float max = game->config()->pony_max_speed;

        speed += accel * timeDiff;
        if (speed < min) speed = min;
        if (speed > max) speed = max;

        angle += steer * timeDiff;

        V2f dir(sin(angle), cos(angle));

        pos += dir * speed * timeDiff;

        // Calculate new camera position

        V2f offset = pos - camera_pos;
        camera_pos = pos - offset * (game->config()->camera_distance
                                     / offset.length());

        V3f pos3 = game->terrain()->get_pos(pos,false);
        V3f dir3 = game->terrain()->get_pos(pos+dir,false)-pos3;

        particle_source.set_pos(pos3 + V3f(0,2,0) + dir3 * 4);
        particle_source.set_dir(dir3);
        particle_source.set_rate(pow(speed/5.0,3)
                                 * game->config()->pony_particle_rate / 100.0);
        particle_source.set_color(game->config()->pony_color[i]);

        particle_source.add_time(timeDiff);

        if (speed < 20) {
            animation.set_animation("Trot");
            animation.step_animation(timeDiff * speed / 12.5);
        } else {
            animation.set_animation("Gallop");
            animation.step_animation(timeDiff * speed / 50);
        }

        animation.recalculate();
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
    if (!out_delay) {

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

        animation.set_bone_matrices(shader, "bone_transforms");

        glColor(game->config()->pony_color[i]);
        glPushMatrix();


        V3f slope =
            game->terrain()->get_pos(pos + V2f(sin(angle),
                                               cos(angle)),false)
            - game->terrain()->get_pos(pos,false);


        // We smooth the x angle to reduce shakiness
        slope_angle *= 31./32.;
        slope_angle += asin(slope.y/ slope.length()) / M_PI * 180 * 1./32.;


        glTranslate(position);
        glRotatef(180 + angle * 180.0/M_PI, 0, 1, 0);
        glRotatef(slope_angle,1,0,0);
        glRotatef(270,1,0,0);


        mesh_drawer.draw(&shader);

        glPopMatrix();

        shader.unbind();
        texture.unbind(GL_TEXTURE0);

        if (out) out_delay = true;
    }

}
