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
        int count = colors.size();

        GLUquadric *q = gluNewQuadric();

        static double golden_angle = 360. / ((1.+sqrt(5.)) * (1.+sqrt(5.))/4.);

        double off = .25;
        
        int n = 0;
        for (list<Color4f>::iterator i = colors.begin();
             i != colors.end(); i++, n++) {
            glPushMatrix();

            double m = n + off;

            double phi = m * golden_angle;
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

//             gluDisk(q,0,size,16,1);
    
            glPopMatrix();
        }

        gluDeleteQuadric(q);
    }
};

void PonyPoints::add_point(int i, Color4f color)
{
    points[i].push_back(color);
}

void PonyPoints::draw_hud(int i)
{
    glDisable(GL_LIGHTING);
    local::draw_floret_colors(0.33, points[i]);
}
