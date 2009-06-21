#include "Animation.hh"
#include "Mesh.hh"

void My::Animation::Keyframe::lerp(const Keyframe& k1,
                                   const Keyframe& k2,
                                   float t, vector<M44f>& matrices)
{
    for (unsigned i = 0; i < matrices.size(); ++i) {
        Transformation::lerp(k1.transformations[i], 
                             k2.transformations[i], t).to_matrix(matrices[i]);
    }
}

My::Animation::Animation(string skeleton_file)
{
    bool success = load_protobuf(skeleton, skeleton_file);

    if (!success) {
        cerr << "Could not load skeleton file \"" << skeleton_file
             << "\"." << endl;
        return;
    }

    for (int i = 0; i < skeleton.hierarchy_size(); ++i) {
        Relationship r;

        r.child = skeleton.hierarchy(i).child();
        r.parent = skeleton.hierarchy(i).parent();
        
        hierarchy.push_back(r);
    }

    for (int a = 0; a < skeleton.animations_size(); ++a) {
        const mesh::Animation& anim = skeleton.animations(a);

        string name = anim.name();

        std::pair<float, vector<Animation::Keyframe> >& p = animations[name];

        p.first = anim.duration();

        vector<Animation::Keyframe>& ks = p.second;

        keyframes = &ks;

        for (int k = 0; k < anim.keyframes_size(); ++k) {
            Animation::Keyframe kf;
            kf.transformations.clear();
            
            const Animation_Keyframe& keyframe = anim.keyframes(k);

            kf.time = anim.keyframes(k).time();

            for (int t = 0; t < keyframe.bone_transforms_size(); ++t) {
                float x,y,z;
                float r,i,j,k;

                x = keyframe.bone_transforms(t).translation().x();
                y = keyframe.bone_transforms(t).translation().y();
                z = keyframe.bone_transforms(t).translation().z();
                r = keyframe.bone_transforms(t).rotation().r();
                i = keyframe.bone_transforms(t).rotation().i();
                j = keyframe.bone_transforms(t).rotation().j();
                k = keyframe.bone_transforms(t).rotation().k();

                Transformation transform(x,y,z,r,i,j,k);
                kf.transformations.push_back(transform);                                
            } 

            ks.push_back(kf);
        }
    }
    current_keyframe = 0;
    current_time = 0.0f;
    
    for (unsigned i = 0; i < keyframes->at(0).transformations.size(); ++i) {
        const Transform& t1 = skeleton.bones(i).transform();

        Quatf q1(t1.rotation().r(),
                 t1.rotation().i(),
                 t1.rotation().j(),
                 t1.rotation().k());

        V3f v1;

        v1.x = t1.translation().x();
        v1.y = t1.translation().y();
        v1.z = t1.translation().z();
        
        bone_positions.push_back(M44f(q1.toMatrix33(), v1));
        inverse_bone_positions.push_back(M44f(q1.toMatrix33(), v1).inverse());
        transformations.push_back(M44f());
    }

    
    for (unsigned int i = 0; i < hierarchy.size(); ++i) {
        Relationship& r = hierarchy[i];
        M44f& parent = inverse_bone_positions[r.parent];
        M44f& child = inverse_bone_positions[r.child];
        

        child =  parent * child;
    }
}


void My::Animation::set_animation(string animation_name)
{
    if (animations.count(animation_name) < 1) {
        cerr << "Could not find animation \"" << animation_name
             << "\"." << endl;
        return;
    }
    
    duration = animations[animation_name].first;
    keyframes = &(animations[animation_name].second);
    
    current_keyframe = 0;
    current_time = 0.0;
}

void My::Animation::step_animation(float timediff) 
{
    current_time += timediff;

    while (current_time >= duration) {
        current_time -= duration;
        current_keyframe = 0;
    } 

    while (keyframes->at(current_keyframe+1).time <= current_time) {
        ++current_keyframe;
    } 

}

void My::Animation::recalculate()
{
    float ta, tb;

    ta = keyframes->at(current_keyframe).time;
    tb = keyframes->at(current_keyframe+1).time;

    Animation::Keyframe::lerp(keyframes->at(current_keyframe),
                              keyframes->at(current_keyframe+1),
                              (current_time-ta)/(tb-ta),
                              transformations);

    for (unsigned i = 0; i < transformations.size(); ++i) {
        transformations[i] =  transformations[i] * bone_positions[i];
    }

    for (unsigned int i = 0; i < hierarchy.size(); ++i) {
        Relationship& r = hierarchy[i];
        M44f& parent = transformations[r.parent];
        M44f& child = transformations[r.child];
        
        child =  child * parent;
    }


    for (unsigned i = 0; i < transformations.size(); ++i) {
        transformations[i] =  inverse_bone_positions[i] * transformations[i];
    }

}

void My::Animation::set_bone_matrices(Shader& shader, string uniform_name)
{
    shader.set_uniform(uniform_name.c_str(), transformations);
}
