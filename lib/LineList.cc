#include "PonyGame.hh"
#include "LineList.hh"

using std::multiset;

bool LineList::add_point(int i, V2f point, Heightmap& heightmap) {
    bool return_value;

    vector<V2f>* v = &line_strips[i];
    vector<V3f>* v3 = &trails[i];

    V2f old_point;
    
    if (v->empty()) {
        v->push_back(point);
        v->push_back(point);

        return_value = false;
    } else {
        if (((*v)[v->size()-2] - point).length() > 2.0) {
            Line new_line((*v)[v->size()-2], point);
            
            v->back() = point;
            v->push_back(point);

            V2f i1(0,0);
        
            if (intersects(new_line, &i1)) {
                lines.push_back(new_line);
                return_value = true;
            } else {
                lines.push_back(new_line);
                return_value = false;
            }
        } else {
            old_point = v->back();
            v->back() = point;
            return_value = false;
        }
    }

    v3->resize(v->size() * 2);

    V3f p1 = heightmap.get_pos(v->at(v->size()-2), false);
    V3f p2 = heightmap.get_pos(v->at(v->size()-1), false);

    v3->at(v3->size()-4) = p1 + V3f(0, 1,0);
    v3->at(v3->size()-3) = p1 + V3f(0,-1,0);
    v3->at(v3->size()-2) = p2 + V3f(0, 1,0);
    v3->at(v3->size()-1) = p2 + V3f(0,-1,0);

    return return_value;
}

bool LineList::intersects(Line& line, V2f* intersection) {

    for (vector<Line>::iterator i = lines.begin();
         i != lines.end();
         i++) {
        if (line.intersects(*i)) {
            *intersection = line.intersection(*i);
            return true;
        }
    }

    return false;

}

void LineList::draw_lines(Config* config)
{
    for (int i; i < 4; i++) {
        int pony_no = i;
        int point_cnt = line_strips[i].size();

        glColor(config->pony_color[pony_no]);
        
        glEnable(GL_VERTEX_ARRAY);
        glVertexPointer(2, GL_FLOAT, 0, &(line_strips[i][0]));

        glDrawArrays(GL_LINE_STRIP, 0, line_strips[i].size());

        glDisable(GL_VERTEX_ARRAY); 
    }
}

void LineList::draw_trails(PonyGame* game)
{
    glDisable(GL_LIGHTING);
    glDisable(GL_CULL_FACE);

    for (int i; i < 4; i++) {
        int pony_no = i;
        int point_cnt = trails[i].size();

        glColor(game->config()->pony_color[pony_no]);
        
        glEnable(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, &(trails[i][0]));

        glDrawArrays(GL_QUAD_STRIP, 0, trails[i].size());

        glDisable(GL_VERTEX_ARRAY); 
    }

    glEnable(GL_LIGHTING);
    glEnable(GL_CULL_FACE);
}
