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
CMAKE_SOURCE_DIR = /home/goncaloaguiar/Desktop/IC_rep/IC/sndfile-example-src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/goncaloaguiar/Desktop/IC_rep/IC/sndfile-example-src/build

# Include any dependencies generated for this target.
include CMakeFiles/BitStreamDecoder.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/BitStreamDecoder.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/BitStreamDecoder.dir/flags.make

CMakeFiles/BitStreamDecoder.dir/BitStreamDecoder.cpp.o: CMakeFiles/BitStreamDecoder.dir/flags.make
CMakeFiles/BitStreamDecoder.dir/BitStreamDecoder.cpp.o: ../BitStreamDecoder.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/goncaloaguiar/Desktop/IC_rep/IC/sndfile-example-src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/BitStreamDecoder.dir/BitStreamDecoder.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/BitStreamDecoder.dir/BitStreamDecoder.cpp.o -c /home/goncaloaguiar/Desktop/IC_rep/IC/sndfile-example-src/BitStreamDecoder.cpp

CMakeFiles/BitStreamDecoder.dir/BitStreamDecoder.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BitStreamDecoder.dir/BitStreamDecoder.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/goncaloaguiar/Desktop/IC_rep/IC/sndfile-example-src/BitStreamDecoder.cpp > CMakeFiles/BitStreamDecoder.dir/BitStreamDecoder.cpp.i

CMakeFiles/BitStreamDecoder.dir/BitStreamDecoder.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BitStreamDecoder.dir/BitStreamDecoder.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/goncaloaguiar/Desktop/IC_rep/IC/sndfile-example-src/BitStreamDecoder.cpp -o CMakeFiles/BitStreamDecoder.dir/BitStreamDecoder.cpp.s

# Object files for target BitStreamDecoder
BitStreamDecoder_OBJECTS = \
"CMakeFiles/BitStreamDecoder.dir/BitStreamDecoder.cpp.o"

# External object files for target BitStreamDecoder
BitStreamDecoder_EXTERNAL_OBJECTS =

/home/goncaloaguiar/Desktop/IC_rep/IC/sndfile-example-bin/BitStreamDecoder: CMakeFiles/BitStreamDecoder.dir/BitStreamDecoder.cpp.o
/home/goncaloaguiar/Desktop/IC_rep/IC/sndfile-example-bin/BitStreamDecoder: CMakeFiles/BitStreamDecoder.dir/build.make
/home/goncaloaguiar/Desktop/IC_rep/IC/sndfile-example-bin/BitStreamDecoder: CMakeFiles/BitStreamDecoder.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/goncaloaguiar/Desktop/IC_rep/IC/sndfile-example-src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /home/goncaloaguiar/Desktop/IC_rep/IC/sndfile-example-bin/BitStreamDecoder"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/BitStreamDecoder.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/BitStreamDecoder.dir/build: /home/goncaloaguiar/Desktop/IC_rep/IC/sndfile-example-bin/BitStreamDecoder

.PHONY : CMakeFiles/BitStreamDecoder.dir/build

CMakeFiles/BitStreamDecoder.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/BitStreamDecoder.dir/cmake_clean.cmake
.PHONY : CMakeFiles/BitStreamDecoder.dir/clean

CMakeFiles/BitStreamDecoder.dir/depend:
	cd /home/goncaloaguiar/Desktop/IC_rep/IC/sndfile-example-src/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/goncaloaguiar/Desktop/IC_rep/IC/sndfile-example-src /home/goncaloaguiar/Desktop/IC_rep/IC/sndfile-example-src /home/goncaloaguiar/Desktop/IC_rep/IC/sndfile-example-src/build /home/goncaloaguiar/Desktop/IC_rep/IC/sndfile-example-src/build /home/goncaloaguiar/Desktop/IC_rep/IC/sndfile-example-src/build/CMakeFiles/BitStreamDecoder.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/BitStreamDecoder.dir/depend

