# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ivan/Documents/INF/3D-minesweeper

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ivan/Documents/INF/3D-minesweeper/out/Debug

# Include any dependencies generated for this target.
include CMakeFiles/fltk_hello_world.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/fltk_hello_world.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/fltk_hello_world.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/fltk_hello_world.dir/flags.make

CMakeFiles/fltk_hello_world.dir/test/fltk_hello_world.cpp.o: CMakeFiles/fltk_hello_world.dir/flags.make
CMakeFiles/fltk_hello_world.dir/test/fltk_hello_world.cpp.o: /home/ivan/Documents/INF/3D-minesweeper/test/fltk_hello_world.cpp
CMakeFiles/fltk_hello_world.dir/test/fltk_hello_world.cpp.o: CMakeFiles/fltk_hello_world.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ivan/Documents/INF/3D-minesweeper/out/Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/fltk_hello_world.dir/test/fltk_hello_world.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/fltk_hello_world.dir/test/fltk_hello_world.cpp.o -MF CMakeFiles/fltk_hello_world.dir/test/fltk_hello_world.cpp.o.d -o CMakeFiles/fltk_hello_world.dir/test/fltk_hello_world.cpp.o -c /home/ivan/Documents/INF/3D-minesweeper/test/fltk_hello_world.cpp

CMakeFiles/fltk_hello_world.dir/test/fltk_hello_world.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/fltk_hello_world.dir/test/fltk_hello_world.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ivan/Documents/INF/3D-minesweeper/test/fltk_hello_world.cpp > CMakeFiles/fltk_hello_world.dir/test/fltk_hello_world.cpp.i

CMakeFiles/fltk_hello_world.dir/test/fltk_hello_world.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/fltk_hello_world.dir/test/fltk_hello_world.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ivan/Documents/INF/3D-minesweeper/test/fltk_hello_world.cpp -o CMakeFiles/fltk_hello_world.dir/test/fltk_hello_world.cpp.s

# Object files for target fltk_hello_world
fltk_hello_world_OBJECTS = \
"CMakeFiles/fltk_hello_world.dir/test/fltk_hello_world.cpp.o"

# External object files for target fltk_hello_world
fltk_hello_world_EXTERNAL_OBJECTS =

bin/fltk_hello_world: CMakeFiles/fltk_hello_world.dir/test/fltk_hello_world.cpp.o
bin/fltk_hello_world: CMakeFiles/fltk_hello_world.dir/build.make
bin/fltk_hello_world: thirdparty/fltk/lib/libfltk.a
bin/fltk_hello_world: /usr/lib/x86_64-linux-gnu/libdl.a
bin/fltk_hello_world: /usr/lib/x86_64-linux-gnu/libSM.so
bin/fltk_hello_world: /usr/lib/x86_64-linux-gnu/libICE.so
bin/fltk_hello_world: /usr/lib/x86_64-linux-gnu/libX11.so
bin/fltk_hello_world: /usr/lib/x86_64-linux-gnu/libXext.so
bin/fltk_hello_world: /usr/lib/x86_64-linux-gnu/libXinerama.so
bin/fltk_hello_world: /usr/lib/x86_64-linux-gnu/libXfixes.so
bin/fltk_hello_world: /usr/lib/x86_64-linux-gnu/libXcursor.so
bin/fltk_hello_world: /usr/lib/x86_64-linux-gnu/libXrender.so
bin/fltk_hello_world: /usr/lib/x86_64-linux-gnu/libpango-1.0.so
bin/fltk_hello_world: /usr/lib/x86_64-linux-gnu/libpangocairo-1.0.so
bin/fltk_hello_world: /usr/lib/x86_64-linux-gnu/libgobject-2.0.so
bin/fltk_hello_world: /usr/lib/x86_64-linux-gnu/libglib-2.0.so
bin/fltk_hello_world: /usr/lib/x86_64-linux-gnu/libharfbuzz.so
bin/fltk_hello_world: /usr/lib/x86_64-linux-gnu/libcairo.so
bin/fltk_hello_world: /usr/lib/x86_64-linux-gnu/libpangoxft-1.0.so
bin/fltk_hello_world: /usr/lib/x86_64-linux-gnu/libpangoft2-1.0.so
bin/fltk_hello_world: /usr/lib/x86_64-linux-gnu/libfontconfig.so
bin/fltk_hello_world: /usr/lib/x86_64-linux-gnu/libfreetype.so
bin/fltk_hello_world: /usr/lib/x86_64-linux-gnu/libXft.so
bin/fltk_hello_world: /usr/lib/x86_64-linux-gnu/libwayland-egl.so
bin/fltk_hello_world: /usr/lib/x86_64-linux-gnu/libwayland-client.so
bin/fltk_hello_world: /usr/lib/x86_64-linux-gnu/libEGL.so
bin/fltk_hello_world: /usr/lib/x86_64-linux-gnu/libgtk-3.so
bin/fltk_hello_world: /usr/lib/x86_64-linux-gnu/libgdk-3.so
bin/fltk_hello_world: /usr/lib/x86_64-linux-gnu/libz.so
bin/fltk_hello_world: /usr/lib/x86_64-linux-gnu/libatk-1.0.so
bin/fltk_hello_world: /usr/lib/x86_64-linux-gnu/libcairo-gobject.so
bin/fltk_hello_world: /usr/lib/x86_64-linux-gnu/libgdk_pixbuf-2.0.so
bin/fltk_hello_world: /usr/lib/x86_64-linux-gnu/libgio-2.0.so
bin/fltk_hello_world: /usr/lib/x86_64-linux-gnu/libwayland-cursor.so
bin/fltk_hello_world: /usr/lib/x86_64-linux-gnu/libxkbcommon.so
bin/fltk_hello_world: /usr/lib/x86_64-linux-gnu/libdbus-1.so
bin/fltk_hello_world: CMakeFiles/fltk_hello_world.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/ivan/Documents/INF/3D-minesweeper/out/Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/fltk_hello_world"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/fltk_hello_world.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/fltk_hello_world.dir/build: bin/fltk_hello_world
.PHONY : CMakeFiles/fltk_hello_world.dir/build

CMakeFiles/fltk_hello_world.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/fltk_hello_world.dir/cmake_clean.cmake
.PHONY : CMakeFiles/fltk_hello_world.dir/clean

CMakeFiles/fltk_hello_world.dir/depend:
	cd /home/ivan/Documents/INF/3D-minesweeper/out/Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ivan/Documents/INF/3D-minesweeper /home/ivan/Documents/INF/3D-minesweeper /home/ivan/Documents/INF/3D-minesweeper/out/Debug /home/ivan/Documents/INF/3D-minesweeper/out/Debug /home/ivan/Documents/INF/3D-minesweeper/out/Debug/CMakeFiles/fltk_hello_world.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/fltk_hello_world.dir/depend

