#ifndef LINE_HH
#define LINE_HH

#include <cinquo.hh>

class Line
{
    public:

    V2d a,b;

    Line(V2d start, V2d end)
        : a(start),
          b(end)
    {
        // Always make sure that a is the left point.
        if (a.x > b.x) {
            a = end;
            b = start;            
        }
    }

//     // Comparator definition for trees..
//     bool operator< (const Line& seg) const {
//         return b.x < seg.b.x;
//     }
    
//     bool operator> (const Line& seg) const {
//         return a.x < seg.a.x;
//     }
    
    bool operator== (const Line& seg) const {
        return a == seg.a && b == seg.b;
    }
    
    bool intersects(const Line& seg);
    V2d intersection(const Line& seg);
    
    bool operator& (const Line& seg) {
        return intersects(seg);
    }

};


struct sort_lines_by_a {
    bool operator() (const Line &l1, const Line &l2) {
        return l1.a.x < l2.a.x;
    }
};

struct sort_lines_by_b {
    bool operator() (const Line &l1, const Line &l2) {
        return l1.b.x < l2.b.x;
    }
};

#endif
