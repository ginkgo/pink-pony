#include "MeshDrawer.hh"

using namespace google::protobuf;

void MeshDrawer::draw()
{
    int count = -1;

    for (RepeatedPtrField<Mesh_Layer>::iterator i = mesh->mutable_layers()->begin();
         i != mesh->mutable_layers()->end(); i++) {
        if (count == -1) {
            count = i->rows();
        } else {
            assert(i->rows() == count);
        }

        if (i->name() == "vertex") {
            glEnableClientState(GL_VERTEX_ARRAY);
            glVertexPointer(i->columns(), GL_FLOAT, 0, i->data().data());
        } else if (i->name() == "normal") {
            glEnableClientState(GL_NORMAL_ARRAY);
            assert(i->columns() == 3);
            glNormalPointer(GL_FLOAT, 0, i->data().data());
        } else if (i->name() == "color") {
            glEnableClientState(GL_COLOR_ARRAY);
            glColorPointer(i->columns(), GL_FLOAT, 0, i->data().data());
        } else if (i->name() == "texcoord") {
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glTexCoordPointer(i->columns(), GL_FLOAT, 0, i->data().data());
        }
    }

    if (mesh->indices().size() > 0) {
        glDrawElements(mesh->primitive_type(),
                       mesh->indices().size(),
                       GL_UNSIGNED_INT,
                       mesh->indices().data());                       
    } else {
        glDrawArrays(mesh->primitive_type(), 0, count);
    }

    for (RepeatedPtrField<Mesh_Layer>::iterator i = mesh->mutable_layers()->begin();
         i != mesh->mutable_layers()->end(); i++) {

        if (i->name() == "vertex") {
            glDisableClientState(GL_VERTEX_ARRAY);
        } else if (i->name() == "normal") {
            glDisableClientState(GL_NORMAL_ARRAY);
        } else if (i->name() == "color") {
            glDisableClientState(GL_COLOR_ARRAY);
        } else if (i->name() == "texcoord") {
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        }
    }
}
