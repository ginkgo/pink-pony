#ifndef MESH_HH
#define MESH_HH

#include "cinquo.hh"
#include "mesh.pb.h"

#include <fstream>

using namespace mesh;

template<class T> bool load_protobuf(T& object, string filename);
template<class T> bool save_protobuf(T& object, string filename);

bool load_mesh(Mesh& mesh, string filename);
bool save_mesh(Mesh& mesh, string filename);

// Template implementation

template<class T> bool load_protobuf(T& object, string filename)
{    
    // Read the Mesh file and create one if necessary
    std::fstream input(filename.c_str(), 
                       std::ios::in | std::ios::binary);
   
    if (!object.ParseFromIstream(&input)) {
      return false;
    }

    return true;
}


template<class T> bool save_protobuf(T& object, string filename)
{
    std::fstream output(filename.c_str(), 
                        std::ios::out | std::ios::trunc | std::ios::binary);
    if (!object.SerializeToOstream(&output)) {
      return false;
    }  

    return true;
}

#endif
