# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = "/Users/denny/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/173.4548.31/CLion.app/Contents/bin/cmake/bin/cmake"

# The command to remove a file.
RM = "/Users/denny/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/173.4548.31/CLion.app/Contents/bin/cmake/bin/cmake" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/denny/projects/clang/sockets

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/denny/projects/clang/sockets/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/sockets.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/sockets.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sockets.dir/flags.make

CMakeFiles/sockets.dir/main.c.o: CMakeFiles/sockets.dir/flags.make
CMakeFiles/sockets.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/denny/projects/clang/sockets/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/sockets.dir/main.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/sockets.dir/main.c.o   -c /Users/denny/projects/clang/sockets/main.c

CMakeFiles/sockets.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sockets.dir/main.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/denny/projects/clang/sockets/main.c > CMakeFiles/sockets.dir/main.c.i

CMakeFiles/sockets.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sockets.dir/main.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/denny/projects/clang/sockets/main.c -o CMakeFiles/sockets.dir/main.c.s

CMakeFiles/sockets.dir/main.c.o.requires:

.PHONY : CMakeFiles/sockets.dir/main.c.o.requires

CMakeFiles/sockets.dir/main.c.o.provides: CMakeFiles/sockets.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/sockets.dir/build.make CMakeFiles/sockets.dir/main.c.o.provides.build
.PHONY : CMakeFiles/sockets.dir/main.c.o.provides

CMakeFiles/sockets.dir/main.c.o.provides.build: CMakeFiles/sockets.dir/main.c.o


# Object files for target sockets
sockets_OBJECTS = \
"CMakeFiles/sockets.dir/main.c.o"

# External object files for target sockets
sockets_EXTERNAL_OBJECTS =

sockets: CMakeFiles/sockets.dir/main.c.o
sockets: CMakeFiles/sockets.dir/build.make
sockets: CMakeFiles/sockets.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/denny/projects/clang/sockets/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable sockets"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sockets.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sockets.dir/build: sockets

.PHONY : CMakeFiles/sockets.dir/build

CMakeFiles/sockets.dir/requires: CMakeFiles/sockets.dir/main.c.o.requires

.PHONY : CMakeFiles/sockets.dir/requires

CMakeFiles/sockets.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sockets.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sockets.dir/clean

CMakeFiles/sockets.dir/depend:
	cd /Users/denny/projects/clang/sockets/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/denny/projects/clang/sockets /Users/denny/projects/clang/sockets /Users/denny/projects/clang/sockets/cmake-build-debug /Users/denny/projects/clang/sockets/cmake-build-debug /Users/denny/projects/clang/sockets/cmake-build-debug/CMakeFiles/sockets.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sockets.dir/depend

