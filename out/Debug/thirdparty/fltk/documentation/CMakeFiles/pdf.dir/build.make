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

# Utility rule file for pdf.

# Include any custom commands dependencies for this target.
include thirdparty/fltk/documentation/CMakeFiles/pdf.dir/compiler_depend.make

# Include the progress variables for this target.
include thirdparty/fltk/documentation/CMakeFiles/pdf.dir/progress.make

thirdparty/fltk/documentation/CMakeFiles/pdf: thirdparty/fltk/documentation/fltk.pdf

thirdparty/fltk/documentation/fltk.pdf: thirdparty/fltk/documentation/Doxybook
thirdparty/fltk/documentation/fltk.pdf: thirdparty/fltk/documentation/fltk-title.tex
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/ivan/Documents/INF/3D-minesweeper/out/Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating PDF documentation"
	cd /home/ivan/Documents/INF/3D-minesweeper/out/Debug/thirdparty/fltk/documentation && /home/ivan/Documents/INF/3D-minesweeper/thirdparty/fltk/documentation/make_header /usr/bin/doxygen /home/ivan/Documents/INF/3D-minesweeper/out/Debug/thirdparty/fltk/documentation/fltk-title.tex /home/ivan/Documents/INF/3D-minesweeper/out/Debug/thirdparty/fltk/documentation/fltk-book.tex
	cd /home/ivan/Documents/INF/3D-minesweeper/out/Debug/thirdparty/fltk/documentation && /usr/bin/doxygen Doxybook
	cd /home/ivan/Documents/INF/3D-minesweeper/out/Debug/thirdparty/fltk/documentation && /home/ivan/Documents/INF/3D-minesweeper/thirdparty/fltk/documentation/make_pdf
	cd /home/ivan/Documents/INF/3D-minesweeper/out/Debug/thirdparty/fltk/documentation && cp -f latex/refman.pdf fltk.pdf

thirdparty/fltk/documentation/Doxybook:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/ivan/Documents/INF/3D-minesweeper/out/Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Converting Doxybook to doxygen version 1.9.8"
	cd /home/ivan/Documents/INF/3D-minesweeper/out/Debug/thirdparty/fltk/documentation && /home/ivan/Documents/INF/3D-minesweeper/thirdparty/fltk/documentation/convert_doxyfile /usr/bin/doxygen Doxybook.in Doxybook /home/ivan/Documents/INF/3D-minesweeper/out/Debug/thirdparty/fltk/documentation/Doxybook_error.log

pdf: thirdparty/fltk/documentation/CMakeFiles/pdf
pdf: thirdparty/fltk/documentation/Doxybook
pdf: thirdparty/fltk/documentation/fltk.pdf
pdf: thirdparty/fltk/documentation/CMakeFiles/pdf.dir/build.make
.PHONY : pdf

# Rule to build all files generated by this target.
thirdparty/fltk/documentation/CMakeFiles/pdf.dir/build: pdf
.PHONY : thirdparty/fltk/documentation/CMakeFiles/pdf.dir/build

thirdparty/fltk/documentation/CMakeFiles/pdf.dir/clean:
	cd /home/ivan/Documents/INF/3D-minesweeper/out/Debug/thirdparty/fltk/documentation && $(CMAKE_COMMAND) -P CMakeFiles/pdf.dir/cmake_clean.cmake
.PHONY : thirdparty/fltk/documentation/CMakeFiles/pdf.dir/clean

thirdparty/fltk/documentation/CMakeFiles/pdf.dir/depend:
	cd /home/ivan/Documents/INF/3D-minesweeper/out/Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ivan/Documents/INF/3D-minesweeper /home/ivan/Documents/INF/3D-minesweeper/thirdparty/fltk/documentation /home/ivan/Documents/INF/3D-minesweeper/out/Debug /home/ivan/Documents/INF/3D-minesweeper/out/Debug/thirdparty/fltk/documentation /home/ivan/Documents/INF/3D-minesweeper/out/Debug/thirdparty/fltk/documentation/CMakeFiles/pdf.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : thirdparty/fltk/documentation/CMakeFiles/pdf.dir/depend

