# package-flashback (CLI Tool)
## About
This is a CLI tool for Linux-based operating systems to backup currently installed packages as a list and then restore the same selection of packages in a fresh install of the OS.

NOTE: This tool currently only supports Arch Linux, Debian GNU/Linux, Fedora Linux and Ubuntu (its derivatives).

## Usage
```package-flashback <argument>```

A list of all the arguments are given in the table.
| Argument  | Description                                                                                                                                                                      |
|:---------:|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| -i        | Shows installed packages count.                                                                                                                                                  |
| -p        | Prints all the installed packages.                                                                                                                                               |
| -se       | Searches the entered string (passed as an argument) against all the currently installed packages.<br/> Example: ```package-flashback -se "kernel"```                             |
| -sv       | Saves the installed packages to '$XDG_DATA_HOME/package-flashback/packagesInstalled.txt'.<br/> NOTE: XDG_DATA_HOME is located at '$HOME/.local/share'.                           |
| -re       | Restores packages from 'packagesInstalled.txt' file found at the location (passed as an argument).<br/> Example: ```package-flashback -re "~/Documents/packagesInstalled.txt"``` |
| -h        | Displays help and exits.                                                                                                                                                         |
