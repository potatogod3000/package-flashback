# package-flashback (CLI Tool)
---
## About
This is a CLI tool for Linux-based operating systems to backup currently installed packages as a list and then restore the same selection of packages in a fresh install of the OS.\
NOTE: This tool currently only supports Arch Linux, Debian GNU/Linux, Fedora Linux and Ubuntu (its derivatives).

##Usage
package-flashback <arguments>
*Arguments:
  *-i  --> Show installed packages count.
  *-p  --> Print all the installed packages.
  *-se --> Search the entered string against all the installed packages. Example: ```package-flashback -se "kernel"```
  *-sv --> Save the installed packages to "$XDG_DATA_HOME/package-flashback/packagesInstalled.txt.
  *-re --> Restore packages from 'packagesInstalled.txt' file found at the location passed as argument. Example: ```package-flashback -re "<path/to/packagesInstalled.txt>"```
