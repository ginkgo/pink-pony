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
        cout << "Button clicked at " << pos << "." << endl;
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

    glEnable(GL_LIGHTING);

    glEnable(GL_DEPTH_TEST);   
}

TextArea::TextArea(string initial_text)
    : Widget(1.0), 
      text(initial_text)
{
    int face_size = 72;

    font = new FTBufferFont("fonts/DaveDS_-_Sketchy.ttf");

    if (font->Error()) {
        cerr << "Something went wrong with loading the font." << endl;
    }
    
    font->FaceSize(face_size);

    FTBBox ftbbox = font->BBox(initial_text.c_str());
    Box2f bbox(V2f(ftbbox.Lower().X(), ftbbox.Lower().Y()),
               V2f(ftbbox.Upper().X(), ftbbox.Upper().Y()));

    bbox.min.y = 0;
    bbox.max.y = face_size;

    aspect = bbox.size().x / bbox.size().y;
}

void TextArea::set_available_area(Box2f area)
{
    Widget::set_available_area(area);

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
        cout << "Button clicked at " << pos << "." << endl;
    }    
}

void TextArea::draw(void)
{
    int face_size = 512;

    FTBBox ftbbox = font->BBox(text.c_str());
    Box2f bbox(V2f(ftbbox.Lower().X(), ftbbox.Lower().Y()),
               V2f(ftbbox.Upper().X(), ftbbox.Upper().Y()));
    bbox.min.y = 0;
    bbox.max.y = face_size;

    V2f es = extent.size();

//     bbox.min *= es.y/face_size;
//     bbox.max *= es.y/face_size;
    
    glPushMatrix();

    glTranslatef(extent.center().x - bbox.center().x,
                 extent.min.y,//0,//extent.center().y - bbox.center().y,
                 0);
    // glScalef(es.y/face_size,
//              es.y/face_size,
//              es.y/face_size);    
    
    
    glDisable(GL_LIGHTING);
    glColor4f(1,0,1,1);

    font->Render(text.c_str());

    glPopMatrix();
    
}
