#include "Skydome.hh"

Skydome::Skydome(string texture_file)
    : texture(texture_file.c_str())
{
    
}

void Skydome::draw()
{    
    texture.bind(GL_TEXTURE0);
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    
    glDepthMask(GL_FALSE);
    glDisable(GL_DEPTH_TEST);
    glCullFace(GL_FRONT);
    

    glMatrixMode(GL_TEXTURE);
    //     glScalef(1,-1,1);
    glMatrixMode(GL_MODELVIEW);
    

    glPushMatrix();

    glColor3f(1,1,1);

    glRotatef(90.0, 1,0,0);
    
    GLUquadric* sphere = gluNewQuadric();
    gluQuadricTexture(sphere, GL_TRUE);
    gluSphere(sphere, 1000.0, 16, 16);
    gluDeleteQuadric(sphere);    

    glPopMatrix();

    texture.unbind(GL_TEXTURE0);

    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    
    glDepthMask(GL_TRUE);
    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_BACK);
    
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);

}
