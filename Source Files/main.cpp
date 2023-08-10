#include "system.h"
#include "backup.h"
#include "restore.h"

void printWrongUsage(int argc, char **argv) {
    std::cout << "WRONG USAGE: package-flashback";
    for(int i = 1; i < argc; i++) {
        if(i == 1) std::cout << " " << argv[i];
        else std::cout << " \"" << argv[i] << "\"";
    }
    std::cout << "\n\n";
    std::cout << "USAGE: package-flashback <arguments>\n";
    std::cout << "Arguments:\n-i  --> Show installed packages count.\n-p  --> Show all the installed packages.\n";
    std::cout << "-se --> Search the entered string against all the installed packages.\n";
    std::cout << "-sv --> Save the installed packages to \"$XDG_DATA_HOME/package-flashback/packagesInstalled.txt\".\n";
    std::cout << "-re --> Restore packages from \'packagesInstalled.txt\' file found at the location passed as argument." << std::endl;
}

void printHelp() {
    std::cout << "|| Welcome to package-flashback ||\n";
    std::cout << "|| HELP ||\n\n";
    std::cout << "USAGE: package-flashback <arguments>\n";
    std::cout << "Arguments:\n-i  --> Show installed packages count.\n-p  --> Print all the installed packages.\n";
    std::cout << "-se --> Search the entered string against all the installed packages.\n";
    std::cout << "\tExample: package-flashback -se \"kernel\"\n";
    std::cout << "-sv --> Save the installed packages to \"$XDG_DATA_HOME/package-flashback/packagesInstalled.txt\".\n";
    std::cout << "-re --> Restore packages from \'packagesInstalled.txt\' file found at the location passed as argument.\n";
    std::cout << "\tExample: package-flashback -re \"<path/to/packagesInstalled.txt>\"" << std::endl;
}

int main(int argc, char **argv) {
    
    if(argc == 1 || strcmp(argv[1], "-h") == 0) {
        printHelp();
    }

    else if((argc != 3 && (strcmp(argv[1], "-se") == 0 || strcmp(argv[1], "-re") == 0))) {
        printWrongUsage(argc, argv);
    }
    
    else {
        std::cout << "|| Welcome to package-flashback ||\n\n";
        std::string name;
        bool check = operatingSystemCheck(); 
        if(check) name = osName();

        // Backup
        if(strcmp(argv[1], "-i") == 0 || strcmp(argv[1], "-p") == 0 || strcmp(argv[1], "-se") == 0 || strcmp(argv[1], "-sv") == 0) {
            setCommandsAndRedirect(check, name, 'b', argv);
        }

        // Restore
        else if(strcmp(argv[1], "-re") == 0) {
            setCommandsAndRedirect(check, name, 'r', argv);
        }

        else printWrongUsage(argc, argv);
   }

    return 0;
}