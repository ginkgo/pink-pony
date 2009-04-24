#ifndef MESH_HH
#define MESH_HH

#include "cinquo.hh"
#include "mesh.pb.h"

using namespace mesh;

bool load_mesh(Mesh& mesh, string filename);
bool save_mesh(Mesh& mesh, string filename);

#endif
