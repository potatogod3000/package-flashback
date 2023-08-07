#include "system.h"
#include "backup.h"

void printWrongUsage(int argc, char **argv) {
    std::cout << "WRONG USAGE: package-flashback";
    for(int i = 1; i < argc; i++) {
        if(i == 1) std::cout << " " << argv[i];
        else std::cout << " \"" << argv[i] << "\"";
    }
    std::cout << "\n\n";
    std::cout << "USAGE: package-flashback <arguments>\n";
    std::cout << "Arguments:\n-c  --> Check the OS.\n-i  --> Show installed packages count.\n-p  --> Show all the installed packages.\n";
    std::cout << "-se --> Search the entered string against all the installed packages.\n";
    std::cout << "-sv --> Save the installed packages to \"$XDG_DATA_HOME/package-flashback/packagesInstalled.txt\"." << std::endl;
}

void printHelp() {
    std::cout << "|| Welcome to package-flashback ||\n";
    std::cout << "|| HELP ||\n\n";
    std::cout << "USAGE: package-flashback <arguments>\n";
    std::cout << "Arguments:\n-c  --> Check the OS.\n-i  --> Show installed packages count.\n-p  --> Print all the installed packages.\n";
    std::cout << "-se --> Search the entered string against all the installed packages.\n";
    std::cout << "-sv --> Save the installed packages to \"$XDG_DATA_HOME/package-flashback/packagesInstalled.txt\".\n\n";
    std::cout << "Example: package-flashback -se \"kernel\"" << std::endl;
}

int main(int argc, char **argv) {

    if(argc != 2 || (strcmp(argv[1], "-se") == 0 && argc != 3)) {
        printWrongUsage(argc, argv);
    }

    else if(strcmp(argv[1], "-h") == 0) {
        printHelp();
    }
    
    else {
        if(strcmp(argv[1], "-i") == 0 || strcmp(argv[1], "-p") == 0 || strcmp(argv[1], "-se") == 0 || strcmp(argv[1], "-sv") == 0) {
            std::cout << "|| Welcome to package-flashback ||\n\n";
            
            std::string name;
            bool check = operatingSystemCheck(); 
            if(check) name = osName();
            
            linuxSystem(check, name, argv);
        }

        else printWrongUsage(argc, argv);
   }

    return 0;
}