#include "Widget.hh"

void Widget::set_available_area(Box2f area) 
{
    V2f s = area.size();
    float area_aspect = s.x/s.y;


    if (area_aspect >= this->aspect) {
        // area wider than widget
        extent.min.y = area.min.y;
        extent.max.y = area.max.y;

        float w = area.size().y * this->aspect;

        extent.min.x = area.center().x - w/2;
        extent.max.x = area.center().x + w/2;

    } else {
        // area higher than widget
        extent.min.x = area.min.x;
        extent.max.x = area.max.x;

        float h = area.size().x / this->aspect;

        extent.min.y = area.center().y - h/2;
        extent.max.y = area.center().y + h/2;
    }
}

Button::Button(string texture_file)
    : Widget(1.0), 
      texture(texture_file.c_str())
{
    V2u s = texture.get_size();

    aspect = (float)s.x / (float)s.y;
}

void Button::area_clicked(V2f pos) 
{
    if (extent.intersects(pos)) {
        signal_clicked.emit();
        //cout << "Button clicked at " << pos << "." << endl;
    }
}

void Button::draw(void)
{
    
    glDisable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation(GL_FUNC_ADD);
    glEnable(GL_TEXTURE_2D);

    glDisable(GL_LIGHTING);

    texture.bind(GL_TEXTURE0);

    glColor4f(1,1,1,1);
    glBegin(GL_QUADS);
    
    glTexCoord2f(0, 0);
    glVertex2f(extent.min.x, extent.min.y);
    glTexCoord2f(1, 0);
    glVertex2f(extent.max.x, extent.min.y);
    glTexCoord2f(1, 1);
    glVertex2f(extent.max.x, extent.max.y);
    glTexCoord2f(0, 1);
    glVertex2f(extent.min.x, extent.max.y);

    glEnd();

    glDisable(GL_BLEND);

    texture.unbind(GL_TEXTURE0);

    //glEnable(GL_LIGHTING);

    glEnable(GL_DEPTH_TEST);   
}

TextArea::TextArea(string initial_text, Color4f bgcolor)
    : Widget(1.0), 
      text(initial_text), bgcolor(bgcolor)
{
    int face_size = 72;

    font = new FTBufferFont("fonts/dijkstra.ttf");

    if (font->Error()) {
        cerr << "Something went wrong with loading the font." << endl;
    }
    
    font->FaceSize(face_size);

    FTBBox ftbbox = font->BBox(initial_text.c_str());
    Box2f bbox(V2f(ftbbox.Lower().X(), ftbbox.Lower().Y()),
               V2f(ftbbox.Upper().X(), ftbbox.Upper().Y()));

    // bbox.min.y = 0;
    // bbox.max.y = face_size;

    aspect = bbox.size().x / bbox.size().y;
}

void TextArea::set_available_area(Box2f area)
{
    Widget::set_available_area(area);

    bgarea = area;

    font->FaceSize((int)extent.size().y);
}

TextArea::~TextArea()
{
    delete font;
}



void TextArea::set_text(string text)
{
    this->text = text; 
}

void TextArea::area_clicked(V2f pos)
{
    if (extent.intersects(pos)) {
        signal_clicked.emit();
        //cout << "Button clicked at " << pos << "." << endl;
    }    
}

void TextArea::draw(void)
{
    FTBBox ftbbox = font->BBox(text.c_str());
    Box2f bbox(V2f(ftbbox.Lower().X(), ftbbox.Lower().Y()),
               V2f(ftbbox.Upper().X(), ftbbox.Upper().Y()));

    bbox.min.y = 0;
    bbox.max.y = 72;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation(GL_FUNC_ADD);
    glDisable(GL_DEPTH_TEST);

    // glColor(bgcolor);

    // glBegin(GL_QUADS);
    
    // glTexCoord2f(0, 0);
    // glVertex2f(bgarea.min.x, bgarea.min.y);
    // glTexCoord2f(1, 0);
    // glVertex2f(bgarea.max.x, bgarea.min.y);
    // glTexCoord2f(1, 1);
    // glVertex2f(bgarea.max.x, bgarea.max.y);
    // glTexCoord2f(0, 1);
    // glVertex2f(bgarea.min.x, bgarea.max.y);

    // glEnd();
    
    glPushMatrix();


    glTranslatef(extent.center().x - bbox.center().x,
                 extent.center().y - bbox.center().y,
                 0);
  
    glTranslatef(bbox.center().x, bbox.center().y, 0);
    glScalef(0.7f, 0.7f, 0.7f);
    glTranslatef(-bbox.center().x, -bbox.center().y, 0);
    
    glDisable(GL_LIGHTING);
    glColor4f(255/255.f,134/255.f,255/255.f,1);

    font->Render(text.c_str());

    glPopMatrix();

    glDisable(GL_BLEND);
    
}

void SimpleLayout::add_widget(Widget* widget, Box2f rel_pos)
{
    widgets[widget] = rel_pos;

    set_available_area(own_size);
}

void SimpleLayout::remove_widget(Widget* widget)
{
    widgets.erase(widget);
}

void SimpleLayout::set_available_area(Box2f area)
{
    own_size = area;

    for (map<Widget*, Box2f>::iterator i = widgets.begin();
         i != widgets.end(); ++i) {
        V2f t_min = i->second.min,
            t_max = i->second.max;
        
        Box2f new_widget_area = Box2f((t_min * area.max) + ((V2f(1,1)-t_min) * area.min),
                                      (t_max * area.max) + ((V2f(1,1)-t_max) * area.min));
        i->first->set_available_area(new_widget_area);
    }
}

void SimpleLayout::area_clicked(V2f pos) 
{
    for (map<Widget*, Box2f>::iterator i = widgets.begin();
         i != widgets.end(); ++i) {
        i->first->area_clicked(pos);
    }    
}

void SimpleLayout::draw(void)
{
    for (map<Widget*, Box2f>::iterator i = widgets.begin();
         i != widgets.end(); ++i) {
        // glPushMatrix();
        // glTranslatef(own_size.min.x, own_size.min.y, 0);
        // glScalef(own_size.size().x, own_size.size().y,1);
        // V2f p1 = i->second.min,
        //     p2 = i->second.max;
        // glColor3f(1,1,0);
        // glLineWidth(2.0);
        // glBegin(GL_LINE_LOOP);
        // glVertex2f(p1.x, p1.y);
        // glVertex2f(p2.x, p1.y);
        // glVertex2f(p2.x, p2.y);
        // glVertex2f(p1.x, p2.y);
        // glEnd();
        // glLineWidth(1.0);
        // glPopMatrix();

        i->first->draw();
    }    
}

Slider::Slider()
    : Widget(1.0),
      up_button("textures/up.png"),
      down_button("textures/down.png")
{
    up_button.on_click()
        .connect(sigc::bind(sigc::mem_fun(this, &Slider::change), 1));
    down_button.on_click()
        .connect(sigc::bind(sigc::mem_fun(this, &Slider::change),-1));
}

void Slider::change(int dir)
{
    signal_clicked.emit(dir);
}

void Slider::set_available_area(Box2f area)
{
    extent = area;

    up_button.set_available_area(Box2f(V2f(area.min.x,area.center().y),
                                       area.max));
    down_button.set_available_area(Box2f(area.min,
                                         V2f(area.max.x,area.center().y)));
}

void Slider::area_clicked(V2f pos)
{
    if (extent.intersects(pos)) {
        up_button.area_clicked(pos);
        down_button.area_clicked(pos);
    }
}

void Slider::draw(void)
{
    up_button.draw();
    down_button.draw();
}
