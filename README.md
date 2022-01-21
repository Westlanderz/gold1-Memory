# gold1-Memory

A project by Dennis Bonke and Noah Knegt.

This is a memory viewer written in a combination of c and c++.

To use this you need to change to the build directory first, from there you can either run the Windows build `memviewer.exe` or the linux build `memview`. Although it is made to run on Windows so thats where it will work for sure.

Once you run the program it will ask for the amount of bytes on one line, after that it will ask for the amount of bytes you would like to display from program start (type 0 for 0xFF bytes).

If you want to compile the source yourself, we can provide the known working command line. Tested on ubuntu 20.04 LTS and Debian sid.
For linux, one can simply type `ninja` in the `build` directory and assuming you have a working c++ compiler and ninja, it will build.
For windows, install `g++-mingw-w64-x86-64` and run `x86_64-w64-mingw32-g++ --std=c++2a -o memviewer -ggdb -fno-omit-frame-pointer -Wextra -Wall ../src/main.cpp` from the `build` directory.