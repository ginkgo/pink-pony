#include "Mesh.hh"
#include <fstream>

using namespace std;
using namespace google::protobuf;

bool load_mesh(Mesh& mesh, string filename)
{    
    // Read the Mesh file and create one if necessary
    fstream input(filename.c_str(), ios::in | ios::binary);
    
    cout << "Loading mesh file " << filename << ".. ";
    cout.flush();

    if (!mesh.ParseFromIstream(&input)) {
      cerr << "Failed to parse mesh file." << endl;
      return false;
    }

    cout << "done. " << mesh.layers(0).rows() << " vertices." << endl;

    return true;
}

bool save_mesh(Mesh& mesh, string filename)
{
    fstream output(filename.c_str(), ios::out | ios::trunc | ios::binary);
    if (!mesh.SerializeToOstream(&output)) {
      cerr << "Failed to write mesh file." << endl;
      return false;
    }  

    return true;
}
