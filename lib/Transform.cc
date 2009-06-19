#include "Transform.hh"

#include <ImathFun.h>

void Transformation::to_matrix(M44f& m) 
{
    M33f rot90 = 
        Quatf().setAxisAngle(V3f(1,0,0),90.0 * M_PI/180).toMatrix33();
    m = M44f(orientation.toMatrix33(), translation);
}

Transformation Transformation::lerp(const Transformation& t1,
                                    const Transformation& t2,
                                    float t)
{
    return Transformation(Imath::lerp (t1.translation, t2.translation, t),
                          Imath::slerp(t1.orientation, t2.orientation, t));
}
