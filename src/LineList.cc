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

bool LineList::intersects(Line& line, Line* intersection) {

    bool found = false;
    float distance = 10000000.0;

    for (vector<Line>::iterator i = lines.begin();
         i != lines.end();
         i++) {
        if (line.intersects(*i)) {
            if (!found) {
                *intersection = *i;
                found = true;

                distance = (line.intersection(*i)-line.a).length();
            } else {
                float new_distance = 
                    (line.intersection(*i)-line.a).length();
                
                if (new_distance < distance) {
                    distance = new_distance;
                    *intersection = *i;
                }
            }
        }
    }

    return found;

}

void LineList::draw_lines(Config* config)
{
    for (int i = 0; i < 4; i++) {
		if (line_strips[i].size() < 1)
			continue;

        int pony_no = i;

        glLineWidth(2.0f);
        
        glColor(config->pony_color[pony_no]);

        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(2, GL_FLOAT, 0, &(line_strips[i][0]));

        glDrawArrays(GL_LINE_STRIP, 0, line_strips[i].size());

        glDisableClientState(GL_VERTEX_ARRAY);
        
        glLineWidth(1.0f);
    }
}

void LineList::draw_trails(PonyGame* game)
{
    glDisable(GL_LIGHTING);
    glDisable(GL_CULL_FACE);
    glDepthMask(GL_TRUE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    for (int i = 0; i < 4; i++) {
		if (trails[i].size() < 1)
			continue;

        Color4f c = game->config()->pony_color[i];

        glColor4f(c.r, c.g, c.b, 0.75);

        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, &(trails[i][0]));

        glDrawArrays(GL_QUAD_STRIP, 0, trails[i].size());

        glDisableClientState(GL_VERTEX_ARRAY);
    }

    glDisable(GL_BLEND);

    glEnable(GL_LIGHTING);
    glEnable(GL_CULL_FACE);
    glDepthMask(GL_TRUE);
}
