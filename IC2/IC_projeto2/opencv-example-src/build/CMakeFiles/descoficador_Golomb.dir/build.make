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
CMAKE_SOURCE_DIR = /home/goncaloaguiar/Desktop/IC_rep/IC2/IC_projeto2/opencv-example-src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/goncaloaguiar/Desktop/IC_rep/IC2/IC_projeto2/opencv-example-src/build

# Include any dependencies generated for this target.
include CMakeFiles/descoficador_Golomb.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/descoficador_Golomb.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/descoficador_Golomb.dir/flags.make

CMakeFiles/descoficador_Golomb.dir/descoficador_Golomb.cpp.o: CMakeFiles/descoficador_Golomb.dir/flags.make
CMakeFiles/descoficador_Golomb.dir/descoficador_Golomb.cpp.o: ../descoficador_Golomb.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/goncaloaguiar/Desktop/IC_rep/IC2/IC_projeto2/opencv-example-src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/descoficador_Golomb.dir/descoficador_Golomb.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/descoficador_Golomb.dir/descoficador_Golomb.cpp.o -c /home/goncaloaguiar/Desktop/IC_rep/IC2/IC_projeto2/opencv-example-src/descoficador_Golomb.cpp

CMakeFiles/descoficador_Golomb.dir/descoficador_Golomb.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/descoficador_Golomb.dir/descoficador_Golomb.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/goncaloaguiar/Desktop/IC_rep/IC2/IC_projeto2/opencv-example-src/descoficador_Golomb.cpp > CMakeFiles/descoficador_Golomb.dir/descoficador_Golomb.cpp.i

CMakeFiles/descoficador_Golomb.dir/descoficador_Golomb.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/descoficador_Golomb.dir/descoficador_Golomb.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/goncaloaguiar/Desktop/IC_rep/IC2/IC_projeto2/opencv-example-src/descoficador_Golomb.cpp -o CMakeFiles/descoficador_Golomb.dir/descoficador_Golomb.cpp.s

# Object files for target descoficador_Golomb
descoficador_Golomb_OBJECTS = \
"CMakeFiles/descoficador_Golomb.dir/descoficador_Golomb.cpp.o"

# External object files for target descoficador_Golomb
descoficador_Golomb_EXTERNAL_OBJECTS =

/home/goncaloaguiar/Desktop/IC_rep/IC2/IC_projeto2/opencv-example-bin/descoficador_Golomb: CMakeFiles/descoficador_Golomb.dir/descoficador_Golomb.cpp.o
/home/goncaloaguiar/Desktop/IC_rep/IC2/IC_projeto2/opencv-example-bin/descoficador_Golomb: CMakeFiles/descoficador_Golomb.dir/build.make
/home/goncaloaguiar/Desktop/IC_rep/IC2/IC_projeto2/opencv-example-bin/descoficador_Golomb: CMakeFiles/descoficador_Golomb.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/goncaloaguiar/Desktop/IC_rep/IC2/IC_projeto2/opencv-example-src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /home/goncaloaguiar/Desktop/IC_rep/IC2/IC_projeto2/opencv-example-bin/descoficador_Golomb"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/descoficador_Golomb.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/descoficador_Golomb.dir/build: /home/goncaloaguiar/Desktop/IC_rep/IC2/IC_projeto2/opencv-example-bin/descoficador_Golomb

.PHONY : CMakeFiles/descoficador_Golomb.dir/build

CMakeFiles/descoficador_Golomb.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/descoficador_Golomb.dir/cmake_clean.cmake
.PHONY : CMakeFiles/descoficador_Golomb.dir/clean

CMakeFiles/descoficador_Golomb.dir/depend:
	cd /home/goncaloaguiar/Desktop/IC_rep/IC2/IC_projeto2/opencv-example-src/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/goncaloaguiar/Desktop/IC_rep/IC2/IC_projeto2/opencv-example-src /home/goncaloaguiar/Desktop/IC_rep/IC2/IC_projeto2/opencv-example-src /home/goncaloaguiar/Desktop/IC_rep/IC2/IC_projeto2/opencv-example-src/build /home/goncaloaguiar/Desktop/IC_rep/IC2/IC_projeto2/opencv-example-src/build /home/goncaloaguiar/Desktop/IC_rep/IC2/IC_projeto2/opencv-example-src/build/CMakeFiles/descoficador_Golomb.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/descoficador_Golomb.dir/depend
