#include "system.h"
#include "os.h"

int main(int argc, char **argv) {
    
    //  || strcmp(argv[1], "-h") == 0
    if(argc < 2 || (strcmp(argv[1], "-s") == 0 && (argc > 3 || argc < 3))) {
        std::cout << "WRONG USAGE" << "\n\n";
        std::cout << "USAGE: package-flashback <arguments>\n";
        std::cout << "Arguments:\n-c --> Check the OS.\n-i --> Show installed packages count.\n-p --> Show all the installed packages.\n";
        std::cout << "-s --> Search the entered string against all the installed packages." << std::endl;
    }

    else if(strcmp(argv[1], "-h") == 0) {
        std::cout << "|| Welcome to package-flashback ||\n";
        std::cout << "|| HELP ||\n\n";
        std::cout << "USAGE: package-flashback <arguments>\n";
        std::cout << "Arguments:\n-c --> Check the OS.\n-i --> Show installed packages count.\n-p --> Show all the installed packages.\n";
        std::cout << "-s --> Search the entered string against all the installed packages.\n\n";
        std::cout << "Example: package-flashback -s \"kernel\" [for searching the installed packages and printing the packages containing the term \"kernel\"]" << std::endl;
    }
    
    else {
        std::cout << "|| Welcome to package-flashback ||\n\n";
        
        std::string name;
        bool check = operatingSystemCheck();
        
        if(check)
            name = osName();
        
        
        if(strcmp(argv[1], "-i") == 0 || strcmp(argv[1], "-p") == 0 || strcmp(argv[1], "-s") == 0) {
            linuxSystem(check, name, argv);
        }
   }

    return 0;
}