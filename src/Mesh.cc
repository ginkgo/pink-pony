#include "Mesh.hh"

using namespace std;
using namespace google::protobuf;

bool load_mesh(Mesh& mesh, string filename)
{    
    //    cout << "Loading mesh file \"" << filename << "\". ";
    bool success = load_protobuf(mesh, filename);

    // if (success) {
    //     cout << "Success " << mesh.layers(0).rows() << " vertices." << endl; 
    // } else {
    //     cerr << "Failed to parse mesh file." << endl;
    // }

    return success;
}

bool save_mesh(Mesh& mesh, string filename)
{
    return save_protobuf(mesh, filename);
}
