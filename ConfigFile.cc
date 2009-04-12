#include "Config.hh"
#include <sstream>

using namespace std;

int main(int argc, char** argv)
{
    Config config(argc, argv);

    if (argc < 3) {
        cout << "Usage: " << argv[0] << " ifile ofile" << endl;
        return 0;
    }


    if (!config.read_file(argv[1])) {
        return 1;
    }   

    cout << config.width << " "
         << config.height << endl;
    
    if (!config.write_file(argv[2])) {
        return 1;
    }
    
    return 0;
}
