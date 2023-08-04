#include "system.h"
#include "os.h"

int main(int argc, char **argv) {

    if(argc < 2 || (strcmp(argv[1], "-se") == 0 && (argc > 3 || argc < 3))) {
        std::cout << "WRONG USAGE ";
        for(int i = 1; i < argc; i++) {
            std::cout << argv[i]<< " ";
        }
        std::cout << "\n\n";
        std::cout << "USAGE: package-flashback <arguments>\n";
        std::cout << "Arguments:\n-c --> Check the OS.\n-i --> Show installed packages count.\n-p --> Show all the installed packages.\n";
        std::cout << "-se --> Search the entered string against all the installed packages.\n";
        std::cout << "-sv --> Save the installed packages to \"packagesInstalled.txt\" file in $XDG_DATA_HOME." << std::endl;
    }

    else if(strcmp(argv[1], "-h") == 0) {
        std::cout << "|| Welcome to package-flashback ||\n";
        std::cout << "|| HELP ||\n\n";
        std::cout << "USAGE: package-flashback <arguments>\n";
        std::cout << "Arguments:\n-c --> Check the OS.\n-i --> Show installed packages count.\n-p --> Print all the installed packages.\n";
        std::cout << "-se --> Search the entered string against all the installed packages.\n";
        std::cout << "-sv --> Save the installed packages to \"packagesInstalled.txt\" file in $XDG_DATA_HOME.\n\n";
        std::cout << "Example: package-flashback -se \"kernel\" [for searching the installed packages and printing the packages containing the term \"kernel\"]" << std::endl;
    }
    
    else {
        std::cout << "|| Welcome to package-flashback ||\n\n";
        
        std::string name;
        bool check = operatingSystemCheck();
        
        if(check)
            name = osName();
        
        
        if(strcmp(argv[1], "-i") == 0 || strcmp(argv[1], "-p") == 0 || strcmp(argv[1], "-se") == 0 || strcmp(argv[1], "-sv") == 0) {
            linuxSystem(check, name, argv);
        }
   }

    return 0;
}