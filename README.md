# enbodied

This is intended to be some kind of SDL project playing with n-body systems, but right now is an almost empty project (using `cmake`, `C++11`, and `SDL2`) that can be used as a template for others.

## Building

This is my first time playing with `cmake`. The information that is used to compile the project is specified in `CMakeLists.txt`, the source is in `src/`, and the executable will be placed in `bin/`---this directory will be created in the process.

Steps:

1. `mkdir build` to create a build directory for out-of-source building (i.e. prevent cluttering the rest of the project with `cmake` spam and object files); this directory can be removed at any time, along with the `bin/` directory, to clean the project. This directory can be called something else, but `build/` is standard.
2. `cd build/` to move to the build directory.
3. `cmake ..` to run `cmake` on the directory above but _in_ this directory. This will create a number of files including a `Makefile` in this directory, and create the `bin/` directory.

    * At this point running `cmake ..` again will additionally create a symlink from the `compile_commands.json` database to the `src/` directory. This is useful for tools such as `YouCompleteMe` which can use it to calculate the flags needed to test compile files. Unfortunately this process does not work on the first invocation of `cmake ..`, as it requires the file to already be present at a stage before it is originally generated, but as it uses a symlink it will remain updated. Note that this second invocation will in fact be faster than the first, and that the `compile_commands.json` file contains absolute paths meaning that it can be copied but cannot be used on different computers.

4. `make` in the `build/` directory will now compile the project and output the binary executable into the `bin/` directory. `make clean` will remove this executable, but will not delete the directory or any of the `cmake` files in the `build/` directory.
