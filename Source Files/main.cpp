#include "system.h"
#include "os.h"

int main(int argc, char **argv) {

    if(argc != 2 || argc > 2) {
        std::cout << "USAGE: package-flashback <arguments>\n\n";
        std::cout << "Arguments:\n-c --> Check the OS.\n-i --> Show installed packages count.\n-p --> Show all the installed packages." << std::endl;
    }
    
    else {
        std::cout << "|| Welcome to package-flashback ||\n\n";
        
        std::string name;
        bool check = operatingSystemCheck();
        
        if(check)
            name = osName();
        
        if(strcmp(argv[1], "-i") == 0 || strcmp(argv[1], "-p") == 0) {
            linuxSystem(check, name, argv);
        }
    }

    return 0;
}