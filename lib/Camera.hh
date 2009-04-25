#ifndef CAMERA_HH
#define CAMERA_HH

#include "cinquo.hh"

class Camera
{
    V3f position;
    V3f focus;

    float aspect;
    float fov;
    float near_plane;
	float far_plane;
    
    public:

    Camera() {};
    Camera(float aspect, float fov,
           float near_plane, float far_plane);
    
    void init(float aspect, float fov,
              float near_plane, float far_plane) {
        this->aspect = aspect;
        this->far_plane = far_plane;
        this->near_plane = near_plane;
        this->fov = fov;
    };
    
    void look_at(V3f position, V3f focus)
    {
        this->position = position;
        this->focus = focus;
    }
    
    V3f get_position()
    {
        return position;
    }

    V3f get_focus()
    {
        return focus;
    }

    float get_near_plane()
    {
        return near_plane;
    }

    void set_near_plane(float near_plane)
    {
        this->near_plane = near_plane;
    }

    float get_far_plane()
    {
        return far_plane;
    }

    void set_far_plane(float far_plane)
    {
        this->far_plane = far_plane;
    }

    float get_aspect()
    {
        return aspect;
    }

    void set_aspect(float aspect)
    {
        this->aspect = aspect;
    }

    float get_fov()
    {
        return fov;
    }

    void set_fov(float fov)
    {
        this->fov = fov;
    }
    
    void set_matrices();
    
};

#endif
