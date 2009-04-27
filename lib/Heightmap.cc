#include "Heightmap.hh"
#include <ImathBoxAlgo.h>

Heightmap::Heightmap(string filename,
                     Box3f extent, float water_level,
                     string sand, string grass, string noise)
    : mesh(),
      mesh_drawer(&mesh),
      terrain_shader("GLSL/heightmap"),
      water_shader("GLSL/water"),
      heightmap(filename.c_str(),
                GL_CLAMP, GL_CLAMP, GL_LINEAR, GL_LINEAR),
      sand_texture(sand.c_str()),
      grass_texture(grass.c_str()),
      noise_texture(noise.c_str()),
      extent(extent),
      water_level(water_level)
{
    heightmap.normalize();
    set_resolution (heightmap.get_size() / 2);
}

Heightmap::~Heightmap()
{
}

void Heightmap::set_resolution(V2u new_resolution)
{
    mesh.set_primitive_type(GL_TRIANGLE_STRIP);

    mesh.mutable_layers()->Clear();
    mesh.mutable_indices()->Clear();

    resolution = new_resolution;

    Mesh_Layer* normal_layer = mesh.add_layers();
    Mesh_Layer* vertex_layer = mesh.add_layers();

    int cnt = resolution.x * resolution.y;

    normal_layer->set_name("normal");
    normal_layer->set_columns(3);
    normal_layer->set_rows(cnt);
    normal_layer->mutable_data()->Reserve(3 * cnt);

    vertex_layer->set_name("vertex");
    vertex_layer->set_columns(3);
    vertex_layer->set_rows(cnt);
    //vertex_layer->mutable_data()->Reserve(3 * cnt);


    V2f m = V2f(extent.min.x,extent.min.z);
    V2f range = V2f(extent.size().x,extent.size().z);
    
    for (unsigned int z = 0; z < resolution.y; ++z) {
        for (unsigned int x = 0; x < resolution.x; ++x) {
            V2f uv = V2f((float)x/resolution.x,
                         1-(float)z/resolution.y);
            V3f v = get_pos(uv * range + m, false); 
            vertex_layer->add_data(v.x);
            vertex_layer->add_data(v.y);
            vertex_layer->add_data(v.z);
        }
    }

    V3f* vertices = (V3f*)vertex_layer->mutable_data()->data();

    Box<V2u> win(V2u(0,0), resolution-V2u(1,1));
    for (unsigned int z = 0; z < resolution.y; ++z) {
        for (unsigned int x = 0; x < resolution.x; ++x) {
            V2u p1 = clip(V2u(x,z) - V2u(1,0),win);
            V2u p2 = clip(V2u(x,z) + V2u(1,0),win);
            V3f du = (vertices[p2.x + resolution.x * p2.y] -
                      vertices[p1.x + resolution.x * p1.y]);
            
            p1 = clip(V2u(x,z) - V2u(0,1),win);
            p2 = clip(V2u(x,z) + V2u(0,1),win);
            V3f dv = (vertices[p2.x + resolution.x * p2.y] -
                      vertices[p1.x + resolution.x * p1.y]);

            V3f n = (du % dv).normalize();
            normal_layer->add_data(n.x);
            normal_layer->add_data(n.y);
            normal_layer->add_data(n.z);
            
        }
    }

    for (unsigned int z = 1; z < resolution.y - 2; z++) {
        mesh.add_indices (1 + z * resolution.x);
        for (unsigned int x = 1; x < resolution.x - 1; x++) {
            mesh.add_indices (x +   z   * resolution.x);
            mesh.add_indices (x + (z+1) * resolution.x);
        }
        mesh.add_indices (resolution.x - 2 + (z+1) * resolution.x);
    }

    mesh_drawer.make_vbo();
}        

V3f Heightmap::get_pos(V2f position, bool with_water)
{
    V3f unmapped = box_unmap(extent, V3f(position.x,
                                         0,
                                         position.y));

    float value = heightmap.get_value(V2f(unmapped.x, 1-unmapped.z));
    float y;

    if (with_water)
        y = max(water_level, value * extent.size().y + extent.min.y);
    else
        y = value * extent.size().y + extent.min.y;
    
    V3f result(position.x,
               y,
               position.y); 
    
    return result;  
}

void Heightmap::draw(Config* config)
{

    V2f center((extent.min.x + extent.max.x)/2,
               (extent.min.z + extent.max.z)/2);
    V2f size(extent.size().x, extent.size().z);        
               
    Box2f area(center - size * 6, center + size * 6);

    sand_texture.bind(GL_TEXTURE1);
    grass_texture.bind(GL_TEXTURE2);
    noise_texture.bind(GL_TEXTURE0);

    terrain_shader.bind();

    terrain_shader.set_uniform("start", extent.min);
    terrain_shader.set_uniform("end",   extent.max);

    terrain_shader.set_uniform("sand", 1);
    terrain_shader.set_uniform("grass", 2);
    terrain_shader.set_uniform("noise", 0);

    terrain_shader.set_uniform("water_level", water_level);

    terrain_shader.set_uniform("hemi_pole",
                               config->hemilight_pole);
    terrain_shader.set_uniform("hemi_sky",
                               config->hemilight_sky);
    terrain_shader.set_uniform("hemi_ground",
                               config->hemilight_ground);
    terrain_shader.set_uniform("velvet_coeff",
                               config->heightmap_velvet_coeff);

    mesh_drawer.draw();


    glBegin(GL_QUADS);

    glNormal3f(0.0,1.0,0.0);
    glVertex3f(area.min.x, 0, area.max.y); // front left
    glVertex3f(area.max.x, 0, area.max.y); // front right
    glVertex3f(area.max.x, 0, area.min.y); // back  right
    glVertex3f(area.min.x, 0, area.min.y); // back left
    
    glEnd();

    terrain_shader.unbind();

//     heightmap.unbind(GL_TEXTURE0);
    sand_texture.unbind(GL_TEXTURE1);
    grass_texture.unbind(GL_TEXTURE2);
    noise_texture.unbind(GL_TEXTURE0);

//     glDisable(GL_CLIP_PLANE0);
    
    // Draw ocean
    
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);

    water_shader.bind();

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation(GL_FUNC_ADD);

    glDisable(GL_LIGHTING);
    
    glBegin(GL_QUADS);

    glNormal3f(0.0,1.0,0.0);
    glColor4f(0.2,0.4,0.85,0.125);
    glVertex3f(0.125 * area.min.x, water_level, 0.125 * area.max.y); // front left
    glVertex3f(0.125 * area.max.x, water_level, 0.125 * area.max.y); // front right
    glVertex3f(0.125 * area.max.x, water_level, 0.125 * area.min.y); // back  right
    glVertex3f(0.125 * area.min.x, water_level, 0.125 * area.min.y); // back left
    
    glEnd();

    water_shader.unbind();
    
    glEnable(GL_LIGHTING);
    glDisable(GL_BLEND);
}
      
                
