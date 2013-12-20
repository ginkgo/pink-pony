#include "Camera.hh"

Camera::Camera(float aspect, float fov,
               float near_plane, float far_plane)
{
    init(aspect, fov, near_plane, far_plane);
}

void Camera::set_matrices()
{
    
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov, aspect, near_plane, far_plane);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(position.x, position.y, position.z,
              focus.x, focus.y, focus.z,
              0, 1, 0);
}
    
void Camera::get_billboard_axes(V3f& up, V3f& right)
{
    V3f n = (focus - position).normalize();
    right = -(V3f(0,1,0) % n).normalize();
    up = right % n;
}
