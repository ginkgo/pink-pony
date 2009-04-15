#include "Heightmap.hh"

Heightmap::Heightmap(string filename,
                     Box3f extent, float water_level,
                     string sand, string grass, string noise)
    : heightmap(filename.c_str(),
                GL_CLAMP, GL_CLAMP, GL_LINEAR, GL_LINEAR),
      terrain_shader("GLSL/heightmap"),
      water_shader("GLSL/water"),
      sand_texture(sand.c_str()),
      grass_texture(grass.c_str(), GL_REPEAT, GL_REPEAT),
      noise_texture(noise.c_str(), GL_REPEAT, GL_REPEAT),
      extent(extent),
      water_level(water_level)
{
    heightmap.normalize();
    buffers[0] = 0;
    buffers[1] = 0;
    set_resolution (heightmap.get_size() / 2);
}

Heightmap::~Heightmap()
{
    glDeleteBuffers(2, buffers);
}

void Heightmap::set_resolution(V2u new_resolution)
{
    resolution = new_resolution;

    glDeleteBuffers(2, buffers);
    glGenBuffers(2,buffers);

    glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);

    int cnt = resolution.x * resolution.y;
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(V3f) * cnt * 2,
                 NULL, GL_STATIC_DRAW);;

    void* buffer = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
    V3f* vertices = (V3f*)buffer;
    V3f* normals = ((V3f*)buffer)+cnt;

    V2f m = V2f(extent.min.x,extent.min.z);
    V2f range = V2f(extent.size().x,extent.size().z);
    
    for (int x = 0; x < resolution.x; ++x) {
        for (int z = 0; z < resolution.y; ++z) {
            V2f uv = V2f((float)x/resolution.x,
                         1-(float)z/resolution.y);
            
            vertices[x + resolution.x * z] = get_pos(uv * range + m, false);
        }
    }

    Box<V2u> win(V2u(0,0), resolution-V2u(1,1));
    for (int x = 0; x < resolution.x; ++x) {
        for (int z = 0; z < resolution.y; ++z) {
            V2u p1 = clip(V2u(x,z) - V2u(1,0),win);
            V2u p2 = clip(V2u(x,z) + V2u(1,0),win);
            V3f du = (vertices[p2.x + resolution.x * p2.y] -
                      vertices[p1.x + resolution.x * p1.y]);
            
            p1 = clip(V2u(x,z) - V2u(0,1),win);
            p2 = clip(V2u(x,z) + V2u(0,1),win);
            V3f dv = (vertices[p2.x + resolution.x * p2.y] -
                      vertices[p1.x + resolution.x * p1.y]);

            normals[x+resolution.x * z] = (du % dv).normalize();
        }
    }

    
    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);

   std::vector<GLuint> indices;
    
    for (int z = 1; z < resolution.y - 2; z++) {
        indices.push_back (1 + z * resolution.x);
        for (int x = 1; x < resolution.x - 1; x++) {
            indices.push_back (x +   z   * resolution.x);
            indices.push_back (x + (z+1) * resolution.x);
        }
        indices.push_back (resolution.x - 2 + (z+1) * resolution.x);
    }

    index_cnt = indices.size();

    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 indices.size() * sizeof(GLuint),
                 &indices[0],
                 GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    
}        

V3f Heightmap::get_pos(V2f position, bool with_water)
{
    V3f unmapped = box_unmap(extent, V3f(position.x,
                                         0,
                                         position.y));

    float value = heightmap.get_color(V2f(unmapped.x, 1-unmapped.z)).r;
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

//     glEnable(GL_LIGHTING);

//     GLdouble clip_equation[4] = {0,1,0,-water_level};
//     glPushMatrix();
//     glLoadIdentity();
//     glClipPlane(GL_CLIP_PLANE0, clip_equation);
//     glPopMatrix();
//     glEnable(GL_CLIP_PLANE0);
    // Draw terrain.
    
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);

//     heightmap.bind(GL_TEXTURE0);
    sand_texture.bind(GL_TEXTURE1);
    grass_texture.bind(GL_TEXTURE2);
    noise_texture.bind(GL_TEXTURE0);

    terrain_shader.bind();

    terrain_shader.set_uniform("start", extent.min);
    terrain_shader.set_uniform("end",   extent.max);

//     terrain_shader.set_uniform("heightmap", 0);
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
    
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    int cnt = resolution.x * resolution.y;
    
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glNormalPointer(GL_FLOAT, 0, ((V3f*)0)+cnt);

    
    glDrawElements(GL_TRIANGLE_STRIP,
                   index_cnt,    
                   GL_UNSIGNED_INT,
                   0);


    glBegin(GL_QUADS);

    glNormal3f(0.0,1.0,0.0);
    glVertex3f(area.min.x, 0, area.max.y); // front left
    glVertex3f(area.max.x, 0, area.max.y); // front right
    glVertex3f(area.max.x, 0, area.min.y); // back  right
    glVertex3f(area.min.x, 0, area.min.y); // back left
    
    glEnd();
    
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

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
      
                
