#include "PonyPoints.hh"


namespace local
{

    void draw_heart(float x)
    {
            glVertex2f(0 * x,2 * x);
            glVertex2f(1 * x,3 * x);
            glVertex2f(2 * x,3 * x);
            glVertex2f(3 * x,2 * x);
            glVertex2f(3 * x,0 * x);
            glVertex2f(0 * x,-3 * x);
            glVertex2f(-3 * x,0 * x);
            glVertex2f(-3 * x,2 * x);
            glVertex2f(-2 * x,3 * x);
            glVertex2f(-1 * x,3 * x);
    }

    void draw_floret_colors(float c, list<Color4f>& colors) {
      
        static double golden_angle = 360. / ((1.+sqrt(5.)) * (1.+sqrt(5.))/4.);

        double off = .25;
        
        int n = 20;
        for (list<Color4f>::iterator i = colors.begin();
             i != colors.end(); i++, n++) {
            glPushMatrix();

            double m = n + off;

            double phi = m * golden_angle + glfwGetTime() * 10;
            double r = c * sqrt(m+(m+1)*off);

            double size = c * .5;

            glColor(*i);
    
            glRotated(phi,0,0,1);
            glTranslated(0,r,0);
            glRotated(-phi,0,0,1);

            float x = size / 3.0;
    
            glBegin(GL_TRIANGLE_FAN);
            draw_heart(x);
            glEnd();

            glColor3f(1,1,1);
            glBegin(GL_LINE_LOOP);
            draw_heart(x);
            glEnd();
    
            glPopMatrix();
        }

    }
};


PonyPoints::PonyPoints(int i, Config* config) : points(i)
{

    digits.push_back(new Texture2D((config->resource_dir + "textures/one.png").c_str()));
    digits.push_back(new Texture2D((config->resource_dir + "textures/two.png").c_str()));
    digits.push_back(new Texture2D((config->resource_dir + "textures/three.png").c_str()));
    digits.push_back(new Texture2D((config->resource_dir + "textures/four.png").c_str()));
}

PonyPoints::~PonyPoints()
{
    for (unsigned int i = 0; i < digits.size(); i++)
        delete digits[i];
}

void PonyPoints::add_point(int i, Color4f color)
{
    points[i].push_back(color);
}

void PonyPoints::draw_hud(int i)
{
    int rank = 0;

    for (unsigned int j = 0; j < points.size(); j++) {
        if (points[i].size() < points[j].size())
            rank++;
    }
    
    glDisable(GL_LIGHTING);


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation(GL_FUNC_ADD);
    glEnable(GL_TEXTURE_2D);
    digits[rank]->bind(GL_TEXTURE0);
    
    glColor4f(1,1,1,1);

    glPushMatrix();

    glScalef(2,2,1);

    glBegin(GL_QUADS);

    glTexCoord2f(0, 0);
    glVertex2f( -1,-1);
    glTexCoord2f(1, 0);
    glVertex2f(  1,-1);
    glTexCoord2f(1, 1);
    glVertex2f(  1, 1);
    glTexCoord2f(0, 1);
    glVertex2f( -1, 1);

    glEnd();

    glPopMatrix();

    glDisable(GL_BLEND);

    digits[rank]->unbind(GL_TEXTURE0);
    local::draw_floret_colors(0.33, points[i]);
}
