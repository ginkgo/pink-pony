#ifndef MESHDRAWER_HH
#define MESHDRAWER_HH

#include "cinquo.hh"
#include "Mesh.hh"

class MeshDrawer
{
    private:

    Mesh* mesh;

    public:

    MeshDrawer(Mesh* mesh) : mesh(mesh) {};
    
    void draw();    
};

#endif
