#include "os.h"

int packagesInstalledCount;
std::vector<std::string> packagesInstalled;
const std::string xdgDataDir = getenv("HOME") + std::string("/.local/share");
const std::string packageFlashbackDir = xdgDataDir + std::string("/package-flashback");
const std::string packageFlashbackFile = packageFlashbackDir + std::string("/packagesInstalled.txt");

void packages(const char *listPackageCount, const char *listPackages, char **argv) {
    std::string packagesCount, packages;
    std::array<char, 80> buffer;

    // Count of installed packages (argv -i)
    FILE *pkgcnt = popen(listPackageCount, "r"); 
    
    if(!pkgcnt) {
        std::cerr << "Cannot access the package manager! Is this system immutable?" << std::endl;
    }

    try {
        while (fgets(buffer.data(), buffer.size(), pkgcnt) != nullptr) {
            packagesCount += buffer.data();
        }
        pclose(pkgcnt);
        packagesCount.erase(std::remove(packagesCount.begin(), packagesCount.end(), '\n'), packagesCount.cend());
        packagesInstalledCount = std::stoi(packagesCount);
        std::cout << "You have " << packagesInstalledCount << " packages installed currently in your system.";
    }
    catch(const std::exception &exception) {
        std::cerr << "\n" << "!!!EXCEPTION!!! \"" << exception.what() << "\"" << '\n';
    }

    // Storing all installed packages in `std::vector packagesInstalled<std::string>`
    FILE *pkgs = popen(listPackages, "r");

    try {
        while (fgets(buffer.data(), buffer.size(), pkgs) != nullptr) {
            packages = buffer.data();
            packages.erase(std::remove(packages.begin(), packages.end(), '\n'), packages.cend());
            packagesInstalled.push_back(packages);
        }
        pclose(pkgs);
    }
    catch(const std::exception &exception) {
        std::cerr << "\n" << "!!!EXCEPTION!!! \"" << exception.what() << "\"" << '\n';
    }

    // Save packages to a file in $XDG_DATA_HOME/package-flashback
    savePackages(packagesInstalled);

    // listing installed packages (argv -p)
    if (strcmp(argv[1], "-p") == 0) {
        
        //Printing packages in a formatted manner (using <iomanip>)
        const char separator    = ' ';
        const int spaceWidth     = 75;

        std::cout << " The packages installed are:\n\n";
        for(int i = 0; i < packagesInstalled.size(); i += 3) {
            std::cout << std::left << std::setw(spaceWidth) << std::setfill(separator) << packagesInstalled[i];
            std::cout << std::left << std::setw(spaceWidth) << std::setfill(separator) << packagesInstalled[i+1];
            std::cout << std::left << std::setw(spaceWidth) << std::setfill(separator) << packagesInstalled[i+2] << std::endl;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // Searching within installed packages (argv -s <"string">)
    if (strcmp(argv[1], "-s") == 0) {
        searchPackages(packagesInstalled, argv);
    }
}

void searchPackages(std::vector<std::string> packagesInstalled, char **argv) {
    std::cout << "Found the package(s): " << std::endl;
    int count = 0;

    for(int i = 0; i < packagesInstalled.size(); i++) {
        std::size_t found = packagesInstalled[i].find(argv[2]);

        if(found != std::string::npos) {
            count++;
            std::cout << count << ". " << packagesInstalled[i] << "\t";
        }
    }

    std::cout << "\nFound " << count << " packages!" << std::endl;
}

void savePackages(std::vector<std::string> packagesInstalled) {
    struct stat info;
    FILE *packagesInstalledFile;

    // Using sys/stat.h to see if the directory is already created
    if(stat(packageFlashbackDir.c_str(), &info) != 0) {
        mkdir(packageFlashbackDir.c_str(), 0777);    
    }
    
    // Check if packagesInstalled.txt has already been created and make it a backup
    else if(packagesInstalledFile = fopen(packageFlashbackFile.c_str(), "r")) {
        int identifier;
        std::cout << "\nThere is already a \"packagesInstalled.txt\" file created by package-flashback. Enter an identifier number for the backup file: ";
        std::cin >> identifier;

        // Handling character inputs
        while (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
            std::cout << "You can only enter identifier numbers. Enter an identifier number for backup file: ";
            std::cin >> identifier;
        }
        
        // Renaming the already generated "packagesInstalled.txt" file to store as backup
        std::filesystem::rename(packageFlashbackFile, packageFlashbackDir + "/packagesInstalled." + std::to_string(identifier) + ".bak");
        fclose(packagesInstalledFile);
    }

    // Writing packagesInstalled vector into "packagesInstalled.txt" file
    std::ofstream packagesTxt(packageFlashbackFile);
    for(auto it: packagesInstalled) {
        packagesTxt << it << std::endl;
    }
    packagesTxt.close();
}