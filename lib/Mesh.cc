#include "Mesh.hh"
#include <fstream>

using namespace std;
using namespace google::protobuf;

bool load_mesh(Mesh& mesh, string filename)
{
<<<<<<< HEAD:lib/Mesh.cc
    // Read the Mesh file and create one if necessary
    fstream input(filename.c_str(), ios::in | ios::binary);
=======
    color_layer = name;
}


void Mesh::set_texcoord_layer(string name)
{
    texcoord_layer = name;
}

void Mesh::set_attrib_layer(int attrib_id, string name)
{
    if (name == "")
        attrib_layers.erase(attrib_id);
    else
        attrib_layers[attrib_id] = name;
}

void Mesh::draw()
{
    if (vertex_layer == "") {
        cerr << "No vertex layer specified" << endl;
        return;
    }

    Layer* v = &layers[vertex_layer];

    if (normal_layer != "") {
        glEnableClientState(GL_NORMAL_ARRAY);
        Layer* l= &layers[normal_layer];
        assert (l->rows >= v->rows);
        assert(l->columns == 3);
        glNormalPointer(GL_FLOAT, 0,
                        &(l->data[0]));
    }
    
    if (color_layer != "") {
        glEnableClientState(GL_COLOR_ARRAY);
        Layer* l = &layers[color_layer];
        assert (l->rows >= v->rows);
        glColorPointer(l->columns,
                       GL_FLOAT, 0,
                       &(l->data[0]));
    }
    
    if (texcoord_layer != "") {
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        Layer* l = &layers[texcoord_layer];
        assert (l->rows >= v->rows);
        glTexCoordPointer(l->columns,
                          GL_FLOAT, 0,
                          &(l->data[0]));
    }

    // TODO: implement attrib layers.

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(v->columns,
                    GL_FLOAT, 0,
                    &(v->data[0]));

    if (indices.size() > 0) {
        glDrawElements(primitive_type,
                       indices.size(),
                       GL_UNSIGNED_INT,
                       &(indices[0]));                       
    } else {
        glDrawArrays(primitive_type,
                     0, get_layer_rows(vertex_layer));
    }
    

    glDisableClientState(GL_VERTEX_ARRAY);
    if (normal_layer != "")
        glDisableClientState(GL_NORMAL_ARRAY);
    if (color_layer != "")
        glDisableClientState(GL_COLOR_ARRAY);
    if (texcoord_layer != "")
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

bool load_OgreXMLGeometry(Mesh& mesh, TiXmlElement* elem) {
    int vertexcount;

    if (elem->QueryIntAttribute("vertexcount", &vertexcount) != TIXML_SUCCESS) {
        return false;
    }

    if (string(elem->FirstChild()->Value()) != "vertexbuffer") {
        return false;
    }

    TiXmlElement* vertexbuffer = elem->FirstChild()->ToElement();

    if (vertexbuffer == NULL)
        return false;

    
    bool has_vertex = (string(vertexbuffer->Attribute("positions"))=="true"); 
    bool has_normal = (string(vertexbuffer->Attribute("normals"))=="true");
    // TODO: I should probably fix this for multitexturing:
    bool has_texcoord =(string(vertexbuffer->Attribute("texture_coords"))=="1");


    float* v;
    float* n;
    float* tc;
    
    if (has_vertex) {
        mesh.add_layer("vertex", 3);
        mesh.resize_layer("vertex", vertexcount);
        v = mesh.get_layer("vertex");
        mesh.set_vertex_layer("vertex");
    }

    if (has_normal) {
        mesh.add_layer("normal", 3);
        mesh.resize_layer("normal", vertexcount);
        n = mesh.get_layer("normal");
        mesh.set_normal_layer("normal");
    }

    if (has_texcoord) {
        mesh.add_layer("texcoord", 2);
        mesh.resize_layer("texcoord", vertexcount);
        tc = mesh.get_layer("texcoord");
        mesh.set_texcoord_layer("texcoord");
    }

    int i;
    TiXmlNode* node;
    for (i = 0, node = vertexbuffer->FirstChild();
         i < vertexcount && node != 0;
         i++, node = node->NextSibling()) {
        if (string(node->Value()) != "vertex") return false;

        TiXmlElement* e = node->FirstChild()->ToElement();

        if (has_vertex) {
            if (e == NULL || string(e->Value()) != "position") {
                return false;
            }
        
            if (e->QueryFloatAttribute("x", v) != TIXML_SUCCESS)
                return false;
            v++;
            if (e->QueryFloatAttribute("y", v) != TIXML_SUCCESS)
                return false;
            v++;
            if (e->QueryFloatAttribute("z", v) != TIXML_SUCCESS)
                return false;
            v++;
        }

        if (has_normal) {

            e = e->NextSibling()->ToElement();

            if (e == NULL || string(e->Value()) != "normal") {
                return false;
            }
        
            if (e->QueryFloatAttribute("x", n) != TIXML_SUCCESS)
                return false;
            n++;
            if (e->QueryFloatAttribute("y", n) != TIXML_SUCCESS)
                return false;
            n++;
            if (e->QueryFloatAttribute("z", n) != TIXML_SUCCESS)
                return false;
            n++;

        }
        
        if (has_texcoord) {

            e = e->NextSibling()->ToElement();

            if (e == NULL || string(e->Value()) != "texcoord") {
                return false;
            }
            
            if (e->QueryFloatAttribute("u", tc) != TIXML_SUCCESS)
                return false;
            tc++;
            if (e->QueryFloatAttribute("v", tc) != TIXML_SUCCESS)
                return false;
            // Texture Y is flipped in OgreXML.
            *tc = 1.0 - *tc;
            tc++;
        }
    }

    return (i >= vertexcount);
}

bool load_OgreXMLFaces(Mesh& mesh, TiXmlElement* elem) {
    int faces;

    if (elem->QueryIntAttribute("count", &faces) != TIXML_SUCCESS) {
        return false;
    }

    int i;
    TiXmlNode* n;

    mesh.set_primitive_type(GL_TRIANGLES);
    mesh.resize_index_layer(faces * 3);
    GLuint* indices = mesh.get_index_layer();
    
    for (i = 0, n = elem->FirstChild();
         i < faces && n != 0;
         i++, n = n->NextSibling()) {
        if (string(n->Value()) != "face") return false;

        int tmp;
        
        if (n->ToElement()->QueryIntAttribute("v1", &tmp) != TIXML_SUCCESS)
            return false;
        *indices = (GLuint)tmp;
        indices++;

        if (n->ToElement()->QueryIntAttribute("v2", &tmp) != TIXML_SUCCESS)
            return false;
        *indices = (GLuint)tmp;
        indices++;

        if (n->ToElement()->QueryIntAttribute("v3", &tmp) != TIXML_SUCCESS)
            return false;
        *indices = (GLuint)tmp;
        indices++;
    }

    if (i < faces)
        return false;
    else
        return true;
}

bool load_OgreXMLSubmesh(Mesh& mesh, TiXmlElement* elem) {

    bool faces = false;
    bool geometry = false;
    
    for (TiXmlNode* n = elem->FirstChild(); n != NULL;
         n = n->NextSibling()) {

        if (n->Type() == TiXmlNode::ELEMENT) {
            if (string(n->Value()) == "faces") {
                faces = load_OgreXMLFaces(mesh, n->ToElement());
            } else if (string(n->Value()) == "geometry") {
                geometry = load_OgreXMLGeometry(mesh, n->ToElement());
            }
        }
    }

    return faces && geometry;
}


bool load_OgreXMLSubmeshes(Mesh& mesh, TiXmlElement* elem) {
    // ATM we only use the first Submesh in the file.
    for (TiXmlNode* n = elem->FirstChild(); n != NULL;
         n = n->NextSibling()) {

        if (n->Type() == TiXmlNode::ELEMENT &&
            string(n->Value()) == "submesh") {
            return load_OgreXMLSubmesh(mesh, n->ToElement());
        }
    }

    return false;
}

bool load_OgreXMLMesh(Mesh& mesh, TiXmlElement* elem) {
>>>>>>> 01e91dbcf44793bc4f6656fbae7b34ac4b63d466:lib/Mesh.cc
    
    cout << "Loading mesh file " << filename << ".. ";
    cout.flush();

    if (!mesh.ParseFromIstream(&input)) {
      cerr << "Failed to parse mesh file." << endl;
      return false;
    }

    cout << "done." << endl;

    return true;
}

bool save_mesh(Mesh& mesh, string filename)
{
    fstream output(filename.c_str(), ios::out | ios::trunc | ios::binary);
    if (!mesh.SerializeToOstream(&output)) {
      cerr << "Failed to write mesh file." << endl;
      return false;
    }  

    return true;
}
