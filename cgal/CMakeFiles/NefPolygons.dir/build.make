# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/reno/Documents/sphericalpolygon/cgal

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/reno/Documents/sphericalpolygon/cgal

# Include any dependencies generated for this target.
include CMakeFiles/NefPolygons.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/NefPolygons.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/NefPolygons.dir/flags.make

CMakeFiles/NefPolygons.dir/NefPolygons.cpp.o: CMakeFiles/NefPolygons.dir/flags.make
CMakeFiles/NefPolygons.dir/NefPolygons.cpp.o: NefPolygons.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/reno/Documents/sphericalpolygon/cgal/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/NefPolygons.dir/NefPolygons.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/NefPolygons.dir/NefPolygons.cpp.o -c /home/reno/Documents/sphericalpolygon/cgal/NefPolygons.cpp

CMakeFiles/NefPolygons.dir/NefPolygons.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NefPolygons.dir/NefPolygons.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/reno/Documents/sphericalpolygon/cgal/NefPolygons.cpp > CMakeFiles/NefPolygons.dir/NefPolygons.cpp.i

CMakeFiles/NefPolygons.dir/NefPolygons.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NefPolygons.dir/NefPolygons.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/reno/Documents/sphericalpolygon/cgal/NefPolygons.cpp -o CMakeFiles/NefPolygons.dir/NefPolygons.cpp.s

# Object files for target NefPolygons
NefPolygons_OBJECTS = \
"CMakeFiles/NefPolygons.dir/NefPolygons.cpp.o"

# External object files for target NefPolygons
NefPolygons_EXTERNAL_OBJECTS =

NefPolygons: CMakeFiles/NefPolygons.dir/NefPolygons.cpp.o
NefPolygons: CMakeFiles/NefPolygons.dir/build.make
NefPolygons: /home/reno/Documents/sphericalpolygon/lib/extern/gmatutil/libgmatutil.a
NefPolygons: /home/reno/Documents/sphericalpolygon/build/libpoly.a
NefPolygons: /usr/lib/x86_64-linux-gnu/libgmpxx.so
NefPolygons: /usr/lib/x86_64-linux-gnu/libmpfr.so
NefPolygons: /usr/lib/x86_64-linux-gnu/libgmp.so
NefPolygons: CMakeFiles/NefPolygons.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/reno/Documents/sphericalpolygon/cgal/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable NefPolygons"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/NefPolygons.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/NefPolygons.dir/build: NefPolygons

.PHONY : CMakeFiles/NefPolygons.dir/build

CMakeFiles/NefPolygons.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/NefPolygons.dir/cmake_clean.cmake
.PHONY : CMakeFiles/NefPolygons.dir/clean

CMakeFiles/NefPolygons.dir/depend:
	cd /home/reno/Documents/sphericalpolygon/cgal && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/reno/Documents/sphericalpolygon/cgal /home/reno/Documents/sphericalpolygon/cgal /home/reno/Documents/sphericalpolygon/cgal /home/reno/Documents/sphericalpolygon/cgal /home/reno/Documents/sphericalpolygon/cgal/CMakeFiles/NefPolygons.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/NefPolygons.dir/depend

