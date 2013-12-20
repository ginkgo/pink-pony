#ifndef LINELIST_HH
#define LINELIST_HH

#include "cinquo.hh"
#include "Config.hh"
#include "Line.hh"
#include <set>

class LineList
{
    vector<V2f> line_strips[4];
    vector<V3f> trails[4];

    std::vector<Line> lines;
    //std::multiset<Line, sort_lines_by_b> lines_b;

    public:

    bool intersects(Line& line, V2f* intersection);
    bool intersects(Line& line, Line* intersection);

    bool add_point(int i, V2f point, Heightmap& heightmap);

    void draw_lines(Config* config);
    void draw_trails(PonyGame* game);
};

#endif
