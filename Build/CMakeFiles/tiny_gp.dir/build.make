# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.15.4/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.15.4/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/phill/Documents/Git/tiny_gp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/phill/Documents/Git/tiny_gp/Build

# Include any dependencies generated for this target.
include CMakeFiles/tiny_gp.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tiny_gp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tiny_gp.dir/flags.make

CMakeFiles/tiny_gp.dir/schema.cpp.o: CMakeFiles/tiny_gp.dir/flags.make
CMakeFiles/tiny_gp.dir/schema.cpp.o: ../schema.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/phill/Documents/Git/tiny_gp/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/tiny_gp.dir/schema.cpp.o"
	/usr/local/bin/g++-9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tiny_gp.dir/schema.cpp.o -c /Users/phill/Documents/Git/tiny_gp/schema.cpp

CMakeFiles/tiny_gp.dir/schema.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tiny_gp.dir/schema.cpp.i"
	/usr/local/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/phill/Documents/Git/tiny_gp/schema.cpp > CMakeFiles/tiny_gp.dir/schema.cpp.i

CMakeFiles/tiny_gp.dir/schema.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tiny_gp.dir/schema.cpp.s"
	/usr/local/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/phill/Documents/Git/tiny_gp/schema.cpp -o CMakeFiles/tiny_gp.dir/schema.cpp.s

CMakeFiles/tiny_gp.dir/genetic.cpp.o: CMakeFiles/tiny_gp.dir/flags.make
CMakeFiles/tiny_gp.dir/genetic.cpp.o: ../genetic.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/phill/Documents/Git/tiny_gp/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/tiny_gp.dir/genetic.cpp.o"
	/usr/local/bin/g++-9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tiny_gp.dir/genetic.cpp.o -c /Users/phill/Documents/Git/tiny_gp/genetic.cpp

CMakeFiles/tiny_gp.dir/genetic.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tiny_gp.dir/genetic.cpp.i"
	/usr/local/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/phill/Documents/Git/tiny_gp/genetic.cpp > CMakeFiles/tiny_gp.dir/genetic.cpp.i

CMakeFiles/tiny_gp.dir/genetic.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tiny_gp.dir/genetic.cpp.s"
	/usr/local/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/phill/Documents/Git/tiny_gp/genetic.cpp -o CMakeFiles/tiny_gp.dir/genetic.cpp.s

CMakeFiles/tiny_gp.dir/main.cpp.o: CMakeFiles/tiny_gp.dir/flags.make
CMakeFiles/tiny_gp.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/phill/Documents/Git/tiny_gp/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/tiny_gp.dir/main.cpp.o"
	/usr/local/bin/g++-9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tiny_gp.dir/main.cpp.o -c /Users/phill/Documents/Git/tiny_gp/main.cpp

CMakeFiles/tiny_gp.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tiny_gp.dir/main.cpp.i"
	/usr/local/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/phill/Documents/Git/tiny_gp/main.cpp > CMakeFiles/tiny_gp.dir/main.cpp.i

CMakeFiles/tiny_gp.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tiny_gp.dir/main.cpp.s"
	/usr/local/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/phill/Documents/Git/tiny_gp/main.cpp -o CMakeFiles/tiny_gp.dir/main.cpp.s

# Object files for target tiny_gp
tiny_gp_OBJECTS = \
"CMakeFiles/tiny_gp.dir/schema.cpp.o" \
"CMakeFiles/tiny_gp.dir/genetic.cpp.o" \
"CMakeFiles/tiny_gp.dir/main.cpp.o"

# External object files for target tiny_gp
tiny_gp_EXTERNAL_OBJECTS =

tiny_gp: CMakeFiles/tiny_gp.dir/schema.cpp.o
tiny_gp: CMakeFiles/tiny_gp.dir/genetic.cpp.o
tiny_gp: CMakeFiles/tiny_gp.dir/main.cpp.o
tiny_gp: CMakeFiles/tiny_gp.dir/build.make
tiny_gp: CMakeFiles/tiny_gp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/phill/Documents/Git/tiny_gp/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable tiny_gp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tiny_gp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tiny_gp.dir/build: tiny_gp

.PHONY : CMakeFiles/tiny_gp.dir/build

CMakeFiles/tiny_gp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tiny_gp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tiny_gp.dir/clean

CMakeFiles/tiny_gp.dir/depend:
	cd /Users/phill/Documents/Git/tiny_gp/Build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/phill/Documents/Git/tiny_gp /Users/phill/Documents/Git/tiny_gp /Users/phill/Documents/Git/tiny_gp/Build /Users/phill/Documents/Git/tiny_gp/Build /Users/phill/Documents/Git/tiny_gp/Build/CMakeFiles/tiny_gp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tiny_gp.dir/depend

