#include "PonyGame.hh"
#include "LineList.hh"

using std::multiset;

bool LineList::add_point(int i, V2f point) {
    vector<V2f>* v = &line_strips[i];

    V2f old_point;
    
    if (v->empty()) {
        v->push_back(point);
        v->push_back(point);
        return false;
    } else if (((*v)[v->size()-2] - point).length() > 2.0) {
        Line new_line((*v)[v->size()-2], point);
        
        v->back() = point;
        v->push_back(point);

        V2f i1(0,0);
        
        if (intersects(new_line, &i1)) {
            lines.push_back(new_line);
            return true;
        } else {
            lines.push_back(new_line);
            return false;
        }
    } else {
        old_point = v->back();
        v->back() = point;
        return false;
    }
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
    for (map<int, vector<V2f> >::iterator i = line_strips.begin();
         i != line_strips.end(); i++) {
        int pony_no = i->first;
        int point_cnt = i->second.size();

        glColor(config->pony_color[pony_no]);
        
        glBegin(GL_LINE_STRIP);
        for (vector<V2f>::iterator j = i->second.begin();
             j != i->second.end(); j++) {
            glVertex2f(j->x, j->y);
        }
        glEnd();        
    }
}

void LineList::draw_trails(PonyGame* game)
{
    glDisable(GL_LIGHTING);
    glDisable(GL_CULL_FACE);
    for (map<int, vector<V2f> >::iterator i = line_strips.begin();
         i != line_strips.end(); i++) {
        int pony_no = i->first;
        int point_cnt = i->second.size();

        glColor(game->config()->pony_color[pony_no]);
        
        glBegin(GL_QUAD_STRIP);
        for (vector<V2f>::iterator j = i->second.begin();
             j != i->second.end(); j++) {
            V3f pos = game->terrain()->get_pos(*j,false);
            glVertex(pos + V3f(0,1,0));
            glVertex(pos + V3f(0,-1,0));
        }
        glEnd();        
    }
    glEnable(GL_LIGHTING);
    glEnable(GL_CULL_FACE);
}
