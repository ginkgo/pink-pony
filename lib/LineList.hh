#ifndef LINELIST_HH
#define LINELIST_HH

#include "cinquo.hh"
#include "Config.hh"
#include "Line.hh"
#include <set>

class LineList
{
    map<int, vector<V2f> > line_strips;

    std::vector<Line> lines;
    //std::multiset<Line, sort_lines_by_b> lines_b;

    bool intersects(Line& line, V2f* intersection);
    //bool intersects(Line& line, V2f* intersection);
    
    public:

    bool add_point(int i, V2f point);

    void draw_lines(Config* config);
    void draw_trails(PonyGame* game);
};

#endif
