#ifndef ANIMATION_HH
#define ANIMATION_HH

#include "cinquo.hh"
#include "mesh.pb.h"

using namespace mesh;

#include "Shader.hh"
#include "Transform.hh"

namespace My {

class Animation 
{
    struct Keyframe {
        float time;
        vector<Transformation> transformations;

        static void lerp (const Keyframe& k1, 
                          const Keyframe& k2, 
                          float t, vector<M44f>& matrices);
                          
    };

    struct Relationship {
        unsigned parent, child;
    };

    Skeleton skeleton;

    // animation name -> duration, keyframes
    map<string, std::pair<float, vector<Keyframe> > > animations;

    vector<Keyframe>* keyframes;
    vector<Relationship> hierarchy;

    float duration;

    unsigned current_keyframe;
    float current_time;
    vector<M44f> transformations;

    vector<M44f> bone_positions;

    public:

    Animation(string skeleton_file);

    void set_animation(string animation_name);
    
    void step_animation(float timediff);

    void recalculate();
             
    void set_bone_matrices(Shader& shader, string uniform_name);
};

}

using namespace My;

#endif
