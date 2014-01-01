#include "cinquo.hh"
#include "Mesh.hh"
#include <tinyxml.h>

#include <ImathQuat.h>

bool load_skeleton_ogrexml(Skeleton& skeleton, string filename);

int main(int argc, char** argv)
{
    string infile, outfile;

    if (argc < 2) {
        cout << "Parses an OgreXML skeleton file and converts it"
             << " into a binary format." << endl;
        cout << "Usage: " << argv[0] 
             << " xml_infile [pskeleton_outfile]" << endl;
        return 1;
    }

    infile = argv[1];
    
    if (infile.find(".skeleton.xml") == string::npos) {
        cerr << "Input file not a valid OgreXML skeleton." << endl;
        return 1;
    }

    if (argc > 2) {
        outfile = argv[2];
    } else {
        string::size_type pos = infile.find(".skeleton.xml");
            outfile = infile.substr(0,pos) + ".pskeleton";
    }    

    Skeleton skeleton;
        
    bool loaded = load_skeleton_ogrexml(skeleton, infile);

    if (loaded) {
        cout << "Loaded ogre skeleton file successfully! :>" << endl;
    } else {
        cerr << "Could not load ogre skeleton file! :<" << endl;
        return 1;
    } 

    if (save_protobuf(skeleton, outfile)) {
        cout << "Saved pskeleton file successfully! :>" << endl;
    } else  {
        cerr << "Could not save pskeleton file! :<" << endl;
        return 1;
    }

    return 0;   
}

bool load_OgreXMLSkeleton(Skeleton& skeleton, TiXmlDocument& doc);

bool load_skeleton_ogrexml(Skeleton& skeleton, string filename)
{
    TiXmlDocument doc(filename.c_str());

    if (!doc.LoadFile()) {
        cerr << "Could not load Skeleton file " << filename << ".\n";
        assert(0);
    }

    return load_OgreXMLSkeleton(skeleton, doc);
}

bool load_OgreXMLBones(Skeleton& skeleton, TiXmlElement* elem);
bool load_OgreXMLBoneHierarchy(Skeleton& skeleton, TiXmlElement* elem);
bool load_OgreXMLAnimations(Skeleton& skeleton, TiXmlElement* elem);

bool load_OgreXMLSkeleton(Skeleton& skeleton, TiXmlDocument& doc) 
{
    for (TiXmlNode* n = doc.FirstChild(); n != NULL;
         n = n->NextSibling()) {

        if (n->Type() == TiXmlNode::ELEMENT &&
            string(n->Value()) == "skeleton") {
            bool bones = false;
            bool hierarchy = false;
            bool animations = false;

            for (TiXmlNode* m = n->ToElement()->FirstChild(); m != NULL;
                 m = m->NextSibling()) {
                if (m->Type() == TiXmlNode::ELEMENT &&
                    string(m->Value()) == "bones") {
                    bones = load_OgreXMLBones(skeleton, m->ToElement());
                } 
            }

            for (TiXmlNode* m = n->ToElement()->FirstChild(); m != NULL;
                 m = m->NextSibling()) {
                if (m->Type() == TiXmlNode::ELEMENT &&
                    string(m->Value()) == "bonehierarchy") {
                    hierarchy = load_OgreXMLBoneHierarchy(skeleton, m->ToElement());
                } 
            }

            for (TiXmlNode* m = n->ToElement()->FirstChild(); m != NULL;
                 m = m->NextSibling()) {
                if (m->Type() == TiXmlNode::ELEMENT &&
                    string(m->Value()) == "animations") {
                    animations = load_OgreXMLAnimations(skeleton, m->ToElement());
                }
            }

            return bones && hierarchy && animations;
        }
    }

    assert(0);
}

bool load_OgreXMLBones(Skeleton& skeleton, TiXmlElement* elem)
{
    std::map<int, Skeleton_Bone> bones;
    int maxid = 0;
    

    for (TiXmlNode* n = elem->FirstChild(); n != NULL; 
         n = n->NextSibling()) {

        // Parse bone
        
        if (n->Type() != TiXmlNode::ELEMENT ||
            string(n->Value()) != "bone") {
            assert(0);
        }

        TiXmlElement* e = n->ToElement();

        int id;
        const char* name;
        float x,y,z;
        float angle, rx, ry, rz;

        if (e->QueryIntAttribute("id", &id) != TIXML_SUCCESS)
            assert(0);
        
        if ((name = e->Attribute("name")) == NULL)
            assert(0);

        for (TiXmlNode* m = e->FirstChild(); m != NULL;
             m = m->NextSibling()) {
            if (m->Type() != TiXmlNode::ELEMENT)
                assert(0);

            TiXmlElement* e = m->ToElement();

            if (string(m->Value()) == "position") {
                
                if (e->QueryFloatAttribute("x", &x) != TIXML_SUCCESS)
                    assert(0);
                if (e->QueryFloatAttribute("y", &y) != TIXML_SUCCESS)
                    assert(0);
                if (e->QueryFloatAttribute("z", &z) != TIXML_SUCCESS)
                    assert(0);
                
            } else if (string(m->Value()) == "rotation") {

                if (e->QueryFloatAttribute("angle", &angle) != TIXML_SUCCESS)
                    assert(0);

                if (e->FirstChild()->Type() != TiXmlNode::ELEMENT ||
                    string(e->FirstChild()->Value()) != "axis")
                    assert(0);

                TiXmlElement* f = e->FirstChild()->ToElement();

                if (f->QueryFloatAttribute("x", &rx) != TIXML_SUCCESS)
                    assert(0);
                if (f->QueryFloatAttribute("y", &ry) != TIXML_SUCCESS)
                    assert(0);
                if (f->QueryFloatAttribute("z", &rz) != TIXML_SUCCESS)
                    assert(0);
                
            } else assert(0);            
        }

        maxid = max(maxid, id);


        // convert axis/angle rotation to quaternion

        Imath::Quatf quaternion;
        quaternion.setAxisAngle(V3f(rx,ry,rz), angle);

        // Create bone

        Skeleton_Bone bone;

        bone.set_name(string(name));
        bone.mutable_transform()->mutable_translation()->set_x(x);
        bone.mutable_transform()->mutable_translation()->set_y(y);
        bone.mutable_transform()->mutable_translation()->set_z(z);

        bone.mutable_transform()->mutable_rotation()->set_r(quaternion.r);    
        bone.mutable_transform()->mutable_rotation()->set_i(quaternion.v.x);  
        bone.mutable_transform()->mutable_rotation()->set_j(quaternion.v.y);  
        bone.mutable_transform()->mutable_rotation()->set_k(quaternion.v.z);

        // Insert bone into map.

        bones[id] = bone;
    }

    Skeleton_Bone fallback_bone;

    fallback_bone.set_name(string("missing"));
    fallback_bone.mutable_transform()->mutable_translation()->set_x(0);
    fallback_bone.mutable_transform()->mutable_translation()->set_y(0);
    fallback_bone.mutable_transform()->mutable_translation()->set_z(0);
    fallback_bone.mutable_transform()->mutable_rotation()->set_r(1);    
    fallback_bone.mutable_transform()->mutable_rotation()->set_i(0);  
    fallback_bone.mutable_transform()->mutable_rotation()->set_j(0);  
    fallback_bone.mutable_transform()->mutable_rotation()->set_k(0);

    for (int i = 0; i <= maxid; ++i) {
        if (bones.count(i) > 0) {
            *skeleton.add_bones() = bones[i];
        } else {
            *skeleton.add_bones() = fallback_bone;
        }

//         cout << skeleton.bones(i).name() << "(" << i << ")" << endl;
    }

    return true;
}


bool load_OgreXMLBoneHierarchy(Skeleton& skeleton, TiXmlElement* elem)
{
    std::map<int,int> relationships; // child -> parent
    std::vector<int> depths; // id -> depth  in relation graph
    std::map<string,int> ids; // name -> id

    for (int i = 0; i < skeleton.bones_size(); ++i) {
        depths.push_back(0);
        ids[skeleton.bones(i).name()] = i;
    }

    int max_level = 0;

    for (TiXmlNode* n = elem->FirstChild(); n != NULL;
         n = n->NextSibling()) {
        const char *from, *to;

        if (n->Type() != TiXmlNode::ELEMENT ||
            string(n->Value()) != "boneparent")
            assert(0);

        TiXmlElement* e = n->ToElement();

        if ((from = e->Attribute("parent")) == NULL)
            assert(0);

        if ((to = e->Attribute("bone")) == NULL)
            assert(0);

        Skeleton_Relationship r;

        relationships[ids[to]] = ids[from]; 

//         cout << from << "(" << ids[from] << ")"
//              << " -> " 
//              << to << "(" << ids[to] << ")" << endl;
    }

    // Calculate depths

    for (int i = 0; i < skeleton.bones_size(); ++i) {
        int id = i;
        
        while (relationships.count(id) > 0) {
            id = relationships[id];
            depths[i]++;
        }

        max_level = max(max_level, depths[i]);
    }

    // Insert relationships in sorted by depth

    for (int l = 1; l <= max_level; ++l) {
        for (int i = 0; i < skeleton.bones_size(); ++i) {
            if (depths[i] != l) continue;

            Skeleton_Relationship* rel= skeleton.add_hierarchy();
            rel->set_child(i);
            rel->set_parent(relationships[i]);
        }
    }

    return true;
}

bool load_OgreXMLAnimation(Skeleton& skeleton, TiXmlElement* elem);

bool load_OgreXMLAnimations(Skeleton& skeleton, TiXmlElement* elem)
{
    bool success = true;

    for (TiXmlNode* n = elem->FirstChild(); n != NULL;
         n = n->NextSibling()) {
        
        if (n->Type() != TiXmlNode::ELEMENT ||
            string(n->Value()) != "animation") 
            assert(0);
            
        success = success && load_OgreXMLAnimation(skeleton, n->ToElement());
    }

    return success;
}


bool load_OgreXMLAnimation(Skeleton& skeleton, TiXmlElement* elem)
{
    Animation* anim = skeleton.add_animations();

    const char* name;
    float duration;

    std::map<string,int> ids; // name -> id
    
    // id -> time -> transform
    std::map<int, std::map<float, Transform> > tracks;


    for (int i = 0; i < skeleton.bones_size(); ++i) {
        ids[skeleton.bones(i).name()] = i;
    }

    if (elem->QueryFloatAttribute("length", &duration) != TIXML_SUCCESS)
        assert(0);

    if ((name = elem->Attribute("name")) == NULL)
        assert(0);

    anim->set_name(string(name));
    anim->set_duration(duration);

    if (elem->FirstChild()->Type() != TiXmlNode::ELEMENT ||
        string(elem->FirstChild()->Value()) != "tracks")
        assert(0);
    
    for (TiXmlNode* n = elem->FirstChild()->ToElement()->FirstChild(); n != NULL;
         n = n->NextSibling()) {
        
        if (n->Type() != TiXmlNode::ELEMENT || 
            string(n->Value()) != "track")
            assert(0);

        TiXmlElement* e = n->ToElement();

        const char* bone;
        int bone_id;

        if ((bone = e->Attribute("bone")) == NULL)
            assert(0);

        bone_id = ids[string(bone)];


        if (e->FirstChild()->Type() != TiXmlNode::ELEMENT ||
            string(e->FirstChild()->Value()) != "keyframes")
            assert(0);
        
        TiXmlElement* f = e->FirstChild()->ToElement();

        for (TiXmlNode* o = f->FirstChild(); o != NULL;
             o = o->NextSibling()) {

            float time;
            float x,y,z;
            float angle, rx, ry, rz;
            float sx,sy,sz;


            if (o->Type() != TiXmlNode::ELEMENT ||
                string(o->Value()) != "keyframe")
                assert(0);


            
            TiXmlElement* e = o->ToElement();

            if (e->QueryFloatAttribute("time", &time) != TIXML_SUCCESS)
                assert(0);

            for (TiXmlNode* m = e->FirstChild(); m != NULL;
                 m = m->NextSibling()) {
                if (m->Type() != TiXmlNode::ELEMENT)
                    assert(0);

                TiXmlElement* e = m->ToElement();

                if (string(m->Value()) == "translate") {
                
                    if (e->QueryFloatAttribute("x", &x) != TIXML_SUCCESS)
                        assert(0);
                    if (e->QueryFloatAttribute("y", &y) != TIXML_SUCCESS)
                        assert(0);
                    if (e->QueryFloatAttribute("z", &z) != TIXML_SUCCESS)
                        assert(0);
                
                } else if (string(m->Value()) == "rotate") {

                    if (e->QueryFloatAttribute("angle", &angle) != TIXML_SUCCESS)
                        assert(0);

                    if (e->FirstChild()->Type() != TiXmlNode::ELEMENT ||
                        string(e->FirstChild()->Value()) != "axis")
                        assert(0);

                    TiXmlElement* f = e->FirstChild()->ToElement();

                    if (f->QueryFloatAttribute("x", &rx) != TIXML_SUCCESS)
                        assert(0);
                    if (f->QueryFloatAttribute("y", &ry) != TIXML_SUCCESS)
                        assert(0);
                    if (f->QueryFloatAttribute("z", &rz) != TIXML_SUCCESS)
                        assert(0);
                
                } else if (string(m->Value()) == "scale"){
                
                    if (e->QueryFloatAttribute("x", &sx) != TIXML_SUCCESS)
                        assert(0);
                    if (e->QueryFloatAttribute("y", &sy) != TIXML_SUCCESS)
                        assert(0);
                    if (e->QueryFloatAttribute("z", &sz) != TIXML_SUCCESS)
                        assert(0);
                
                } else assert(0);
                    
            }

            assert(sx == 1.0);
            assert(sy == 1.0);
            assert(sz == 1.0);
        
            Imath::Quatf quaternion;
            quaternion.setAxisAngle(V3f(rx,ry,rz), angle);

        
            Transform t;
            t.mutable_translation()->set_x(x);
            t.mutable_translation()->set_y(y);
            t.mutable_translation()->set_z(z);
            t.mutable_rotation()->set_r(quaternion.r);
            t.mutable_rotation()->set_i(quaternion.v.x);
            t.mutable_rotation()->set_j(quaternion.v.y);
            t.mutable_rotation()->set_k(quaternion.v.z);

            tracks[bone_id][time] = t;
        }         
    }
    
    Imath::Quatf quaternion;
    quaternion.setAxisAngle(V3f(0,1,0), 0);
    
        
    Transform fallback_transform;
    fallback_transform.mutable_translation()->set_x(0);
    fallback_transform.mutable_translation()->set_y(0);
    fallback_transform.mutable_translation()->set_z(0);
    fallback_transform.mutable_rotation()->set_r(quaternion.r);
    fallback_transform.mutable_rotation()->set_i(quaternion.v.x);
    fallback_transform.mutable_rotation()->set_j(quaternion.v.y);
    fallback_transform.mutable_rotation()->set_k(quaternion.v.z);

    for (std::map<float, Transform>::iterator i = tracks[0].begin();
         i != tracks[0].end(); ++i) {
        float t = i->first;
        Animation_Keyframe* keyframe = anim->add_keyframes();
        keyframe->set_time(t);
        for (int i = 0; i < skeleton.bones_size(); ++i) {
            Transform* transform = keyframe->add_bone_transforms();

            if (tracks.count(i) < 1 ||tracks[i].count(t) < 1) {
                *transform = fallback_transform;
            } else {
                *transform = tracks[i][t];
            }

        }
    }    
    
    return true;
}
