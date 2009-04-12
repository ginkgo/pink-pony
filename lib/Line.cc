#include "Line.hh"
#include <ImathLimits.h>

#define EPSILON limits<double>::epsilon()

bool Line::intersects(const Line& seg)
{    
    double ax = a.x, ay = a.y;
    double bx = b.x, by = b.y;
    double cx = seg.a.x, cy = seg.a.y;
    double dx = seg.b.x, dy = seg.b.y;
    
    double S = (((cx*(dy - ay)) + (dx*(ay - cy)) + (ax*(cy - dy)))/(((bx - ax)*(dy - cy)) + ((by - ay)*(cx - dx))));
    double T = ((((1.0 - S)*ay) + (S*by) - cy)/(dy - cy));

    return (S > 0.0 && S < 1.0 && T > 0.0 && T < 1.0);
//     V2d u = b - a;
//     V2d v = seg.b - seg.a;
    
//     double k1 = u.y/u.x;
//     double k2 = v.y/v.x;

//     double d = (k1 - k2);

//     // d == 0 => parallel 
//     if (fabs(d) < EPSILON) {
//         return false;
//     }

//     double d1 = a.y - a.x * k1;
//     double d2 = seg.a.y - seg.a.x * k2;

//     double x = (d2 - d1) / (k1 - k2);

//     bool ret = true;

//     if (a.x != b.x)
//         ret = ret && x > a.x && x < b.x;
//     else {
//         double y = k1 * x + d1;    
//         ret = ret &&
//               y > min(a.y,b.y) &&
//               y < max(a.y,b.y);
//     }

            
//     if (seg.a.x != seg.b.x)
//         ret = ret && x > seg.a.x && x < seg.b.x;
//     else {
//         double y = k1 * x + d1;    
//         ret = ret &&
//               y > min(seg.a.y,seg.b.y) &&
//               y < max(seg.a.y,seg.b.y);
//     }
    
//     return ret;
}

V2d Line::intersection(const Line& seg)
{
    double ax = a.x, ay = a.y;
    double bx = b.x, by = b.y;
    double cx = seg.a.x, cy = seg.a.y;
    double dx = seg.b.x, dy = seg.b.y;
    
    double S = (((cx*(dy - ay)) + (dx*(ay - cy)) + (ax*(cy - dy)))/(((bx - ax)*(dy - cy)) + ((by - ay)*(cx - dx))));
    double T = ((((1.0 - S)*ay) + (S*by) - cy)/(dy - cy));
    
	return (1-S) * a + S * b;
}
