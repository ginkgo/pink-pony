#include "Line.hh"
#include <limits>

#define EPSILON std::limits<double>::epsilon()

bool Line::intersects(const Line& seg)
{
    double ax = a.x, ay = a.y;
    double bx = b.x, by = b.y;
    double cx = seg.a.x, cy = seg.a.y;
    double dx = seg.b.x, dy = seg.b.y;

    double S = (((cx*(dy - ay)) + (dx*(ay - cy)) + (ax*(cy - dy)))/(((bx - ax)*(dy - cy)) + ((by - ay)*(cx - dx))));
    double T = ((((1.0 - S)*ay) + (S*by) - cy)/(dy - cy));

    return (S > 0.0 && S < 1.0 && T > 0.0 && T < 1.0);
}

V2d Line::intersection(const Line& seg)
{
    double ax = a.x, ay = a.y;
    double bx = b.x, by = b.y;
    double cx = seg.a.x, cy = seg.a.y;
    double dx = seg.b.x, dy = seg.b.y;

    double S = (((cx*(dy - ay)) + (dx*(ay - cy)) + (ax*(cy - dy)))/(((bx - ax)*(dy - cy)) + ((by - ay)*(cx - dx))));
	return (1-S) * a + S * b;
}
