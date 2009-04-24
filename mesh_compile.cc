#include "cinquo.hh"
#include "Mesh.hh"
#include <tinyxml.h>

bool load_mesh_ogrexml(Mesh& mesh, string filename);

int main(int argc, char** argv)
{
    string infile, outfile;

    if (argc < 2) {
        cout << "Parses an OgreXML mesh file and converts it into a binary format." << endl;
        cout << "Usage: " << argv[0] << " xml_infile [pmesh_outfile]" << endl;
        return 1;
    }

    infile = argv[1];
    
    if (infile.find(".mesh.xml") == string::npos) {
        cerr << "Input file not a valid OgreXML mesh." << endl;
        return 1;
    }

    if (argc > 2) {
        outfile = argv[2];
    } else {
        string::size_type pos = infile.find(".mesh.xml");
            outfile = infile.substr(0,pos) + ".pmesh";
    }    

    Mesh mesh;
        
    bool loaded = load_mesh_ogrexml(mesh, infile);

    if (loaded) {
        cout << "Loaded ogre mesh file successfully! :>" << endl;
    } else {
        cerr << "Could not load ogre mesh file! :<" << endl;
        return 1;
    } 

    if (save_mesh(mesh, outfile)) {
        cout << "Saved pmesh file successfully! :>" << endl;
    } else  {
        cerr << "Could not save pmesh file! :<" << endl;
        return 1;
    }

    return 0;   
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


    Mesh_Layer* v;
    Mesh_Layer* n;
    Mesh_Layer* tc;
    
    if (has_vertex) {
        v = mesh.add_layers();
        v->set_name("vertex");
        v->set_columns(3);
        v->set_rows(vertexcount);
    }

    if (has_normal) {
        n = mesh.add_layers();
        n->set_name("normal");
        n->set_columns(3);
        n->set_rows(vertexcount);
    }

    if (has_texcoord) {
        tc = mesh.add_layers();
        tc->set_name("texcoord");
        tc->set_columns(2);
        tc->set_rows(vertexcount);
    }

    int i;
    TiXmlNode* node;
    for (i = 0, node = vertexbuffer->FirstChild();
         i < vertexcount && node != 0;
         i++, node = node->NextSibling()) {
        if (string(node->Value()) != "vertex") return false;

        TiXmlElement* e = node->FirstChild()->ToElement();
        
        float f;

        if (has_vertex) {
            if (e == NULL || string(e->Value()) != "position") {
                return false;
            }
        
            if (e->QueryFloatAttribute("x", &f) != TIXML_SUCCESS)
                return false;
            v->add_data(f);
            if (e->QueryFloatAttribute("y", &f) != TIXML_SUCCESS)
                return false;
            v->add_data(f);
            if (e->QueryFloatAttribute("z", &f) != TIXML_SUCCESS)
                return false;
            v->add_data(f);
        }

        if (has_normal) {

            e = e->NextSibling()->ToElement();

            if (e == NULL || string(e->Value()) != "normal") {
                return false;
            }
        
            if (e->QueryFloatAttribute("x", &f) != TIXML_SUCCESS)
                return false;
            n->add_data(f);
            if (e->QueryFloatAttribute("y", &f) != TIXML_SUCCESS)
                return false;
            n->add_data(f);
            if (e->QueryFloatAttribute("z", &f) != TIXML_SUCCESS)
                return false;
            n->add_data(f);

        }
        
        if (has_texcoord) {

            e = e->NextSibling()->ToElement();

            if (e == NULL || string(e->Value()) != "texcoord") {
                return false;
            }
            
            if (e->QueryFloatAttribute("u", &f) != TIXML_SUCCESS)
                return false;
            tc->add_data(f);
            if (e->QueryFloatAttribute("v", &f) != TIXML_SUCCESS)
                return false;
            // Texture Y is flipped in OgreXML.
            f = 1.0 - f;
            tc->add_data(f);
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
    
    for (i = 0, n = elem->FirstChild();
         i < faces && n != 0;
         i++, n = n->NextSibling()) {
        if (string(n->Value()) != "face") return false;

        int tmp;
        
        if (n->ToElement()->QueryIntAttribute("v1", &tmp) != TIXML_SUCCESS)
            return false;
        mesh.add_indices((GLuint)tmp);

        if (n->ToElement()->QueryIntAttribute("v2", &tmp) != TIXML_SUCCESS)
            return false;
        mesh.add_indices((GLuint)tmp);

        if (n->ToElement()->QueryIntAttribute("v3", &tmp) != TIXML_SUCCESS)
            return false;
        mesh.add_indices((GLuint)tmp);
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
    
    for (TiXmlNode* n = elem->FirstChild(); n != NULL;
         n = n->NextSibling()) {

        if (n->Type() == TiXmlNode::ELEMENT &&
            string(n->Value()) == "submeshes") {
            return load_OgreXMLSubmeshes(mesh, n->ToElement());
        }
    }

    return false;
}

bool load_OgreXMLDocument(Mesh& mesh, TiXmlDocument& doc) {
    for (TiXmlNode* n = doc.FirstChild(); n != NULL;
         n = n->NextSibling()) {

        if (n->Type() == TiXmlNode::ELEMENT &&
            string(n->Value()) == "mesh") {
            return load_OgreXMLMesh(mesh, n->ToElement());
        }
    }

    return false;
}

bool load_mesh_ogrexml(Mesh& mesh, string filename)
{
    TiXmlDocument doc(filename.c_str());

    if (!doc.LoadFile()) {
        cerr << "Could not load Mesh file " << filename << ".\n";
        return false;
    }

    mesh.set_primitive_type(GL_TRIANGLES);

    return load_OgreXMLDocument(mesh, doc);   
}
