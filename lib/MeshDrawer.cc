#include "MeshDrawer.hh"

using namespace google::protobuf;

void MeshDrawer::make_vbo()
{
    if (using_vbo)
        free_vbo();

    layers.clear();

    glGenBuffers(1,&index_buffer);
    glGenBuffers(1,&layer_buffer);

    int total = 0;

    for (int i = 0; i < mesh->layers_size(); ++i) {
        total += mesh->layers(i).data_size();
    }
    
    getErrors();

    glBindBuffer(GL_ARRAY_BUFFER, layer_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * total, 
                 NULL, GL_STATIC_DRAW);

    getErrors();

    int offset = 0;

    vertex_count = -1;

    for (int i = 0; i < mesh->layers_size(); ++i) {

        if (vertex_count < 0)
            vertex_count = mesh->layers(i).rows();
        else
            assert(vertex_count == mesh->layers(i).rows());

        layers.push_back(LayerBuffer(mesh->layers(i).name(),
                                     mesh->layers(i).columns(),
                                     (float*)0 + offset));

        glBufferSubData(GL_ARRAY_BUFFER, 
                        offset * sizeof(float),
                        mesh->layers(i).data_size() * sizeof(float),
                        mesh->layers(i).data().data());

        offset += mesh->layers(i).data_size();
    }

    assert(total == offset);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    getErrors();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
                 sizeof(uint32) * mesh->indices_size(),
                 mesh->indices().data(), GL_STATIC_DRAW);

    getErrors();
    index_count = mesh->indices_size();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    using_vbo = true;
}

void MeshDrawer::free_vbo()
{
    if (!using_vbo)
        return;

    glDeleteBuffers(1,&index_buffer);
    glDeleteBuffers(1,&layer_buffer);

    index_buffer = 0;
    layer_buffer = 0;

    using_vbo = false;

    index_count = 0;
    vertex_count = 0;

    layers.clear();
}

void MeshDrawer::draw()
{
    if (!using_vbo)
        make_vbo();

    if (using_vbo)
        draw_vertex_buffer_object();
    else
        draw_vertex_array();
}

void MeshDrawer::draw_vertex_buffer_object()
{
    glBindBuffer(GL_ARRAY_BUFFER, layer_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);

    for (unsigned int i = 0; i < layers.size(); ++i) {

        if (layers[i].name == "vertex") {
            glEnableClientState(GL_VERTEX_ARRAY);
            glVertexPointer(layers[i].columns, GL_FLOAT, 0, layers[i].offset);
        } else if (layers[i].name == "normal") {
            glEnableClientState(GL_NORMAL_ARRAY);
            assert(layers[i].columns == 3);
            glNormalPointer(GL_FLOAT, 0, layers[i].offset);
        } else if (layers[i].name == "color") {
            glEnableClientState(GL_COLOR_ARRAY);
            glColorPointer(layers[i].columns, GL_FLOAT, 0, layers[i].offset);
        } else if (layers[i].name == "texcoord") {
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glTexCoordPointer(layers[i].columns, GL_FLOAT, 0, layers[i].offset);
        }
    }

    if (index_count > 0) {
        glDrawElements(mesh->primitive_type(),
                       index_count,
                       GL_UNSIGNED_INT,
                       (void*)0);                       
    } else {
        glDrawArrays(mesh->primitive_type(), 0, vertex_count);
    }

    for (unsigned int i = 0; i < layers.size(); ++i) {

        if (layers[i].name == "vertex") {
            glDisableClientState(GL_VERTEX_ARRAY);
        } else if (layers[i].name == "normal") {
            glDisableClientState(GL_NORMAL_ARRAY);
        } else if (layers[i].name == "color") {
            glDisableClientState(GL_COLOR_ARRAY);
        } else if (layers[i].name == "texcoord") {
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        }
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void MeshDrawer::draw_vertex_array()
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
