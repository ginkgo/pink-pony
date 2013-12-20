#ifndef TRANSFORMATION_HH
#define TRANSFORMATION_HH

#include "cinquo.hh"

#include <ImathQuat.h>
using Imath::Quatf;

class Transformation
{
    V3f translation;
    Quatf orientation; 
    public:

    Transformation(V3f translation,
                   Quatf orientation)
        : translation(translation),
          orientation(orientation) {};


    Transformation(float x, float y, float z,
              float r, float i, float j, float k)
        : translation(x,y,z),
          orientation(r,i,j,k) {};

    void to_matrix(M44f& m);

    static Transformation lerp(const Transformation& t1,
                          const Transformation& t2,
                          float t);
    
};

#endif
