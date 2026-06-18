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


static M44f gen_perspective_mat(
    float fovy,
    float aspect,
    float zNear,
    float zFar)
{
    float f = 1.0f / std::tan(fovy * M_PI / 360.0f);

    M44f m(0.0f);
    m[0][0] = f / aspect;
    m[1][1] = f;
    m[2][2] = (zFar + zNear) / (zNear - zFar);
    m[2][3] = -1.0f;
    m[3][2] = (2.0f * zFar * zNear) / (zNear - zFar);

    return m;
}

static M44f gen_look_at_mat(
    const V3f& eye,
    const V3f& center,
    const V3f& up)
{
	Imath::V3f f = (center - eye).normalized();
    Imath::V3f s = f.cross(up).normalized();
    Imath::V3f u = s.cross(f);

    Imath::M44f m;
    m[0][0] = s.x; m[0][1] = u.x; m[0][2] = -f.x; m[0][3] = 0.0f;
    m[1][0] = s.y; m[1][1] = u.y; m[1][2] = -f.y; m[1][3] = 0.0f;
    m[2][0] = s.z; m[2][1] = u.z; m[2][2] = -f.z; m[2][3] = 0.0f;
    m[3][0] = -s.dot(eye);
    m[3][1] = -u.dot(eye);
    m[3][2] = f.dot(eye);
    m[3][3] = 1.0f;

    return m;
}



M44f Camera::gen_mvp()
{
    M44f p = gen_perspective_mat(fov, aspect, near_plane, far_plane);
    M44f v = gen_look_at_mat(position, focus, V3f(0,1,0));

    return v * p;
}
