# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/amefodev/work/SuperFGD/SFGD_Unpacking

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/amefodev/work/SuperFGD/SFGD_Unpacking/cmake-build-debug

# Include any dependencies generated for this target.
include examples/CMakeFiles/pid_vs_tof.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/pid_vs_tof.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/pid_vs_tof.dir/flags.make

examples/CMakeFiles/pid_vs_tof.dir/out_vs_pid.cpp.o: examples/CMakeFiles/pid_vs_tof.dir/flags.make
examples/CMakeFiles/pid_vs_tof.dir/out_vs_pid.cpp.o: ../examples/out_vs_pid.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/amefodev/work/SuperFGD/SFGD_Unpacking/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/CMakeFiles/pid_vs_tof.dir/out_vs_pid.cpp.o"
	cd /Users/amefodev/work/SuperFGD/SFGD_Unpacking/cmake-build-debug/examples && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pid_vs_tof.dir/out_vs_pid.cpp.o -c /Users/amefodev/work/SuperFGD/SFGD_Unpacking/examples/out_vs_pid.cpp

examples/CMakeFiles/pid_vs_tof.dir/out_vs_pid.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pid_vs_tof.dir/out_vs_pid.cpp.i"
	cd /Users/amefodev/work/SuperFGD/SFGD_Unpacking/cmake-build-debug/examples && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/amefodev/work/SuperFGD/SFGD_Unpacking/examples/out_vs_pid.cpp > CMakeFiles/pid_vs_tof.dir/out_vs_pid.cpp.i

examples/CMakeFiles/pid_vs_tof.dir/out_vs_pid.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pid_vs_tof.dir/out_vs_pid.cpp.s"
	cd /Users/amefodev/work/SuperFGD/SFGD_Unpacking/cmake-build-debug/examples && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/amefodev/work/SuperFGD/SFGD_Unpacking/examples/out_vs_pid.cpp -o CMakeFiles/pid_vs_tof.dir/out_vs_pid.cpp.s

# Object files for target pid_vs_tof
pid_vs_tof_OBJECTS = \
"CMakeFiles/pid_vs_tof.dir/out_vs_pid.cpp.o"

# External object files for target pid_vs_tof
pid_vs_tof_EXTERNAL_OBJECTS =

../bin/pid_vs_tof: examples/CMakeFiles/pid_vs_tof.dir/out_vs_pid.cpp.o
../bin/pid_vs_tof: examples/CMakeFiles/pid_vs_tof.dir/build.make
../bin/pid_vs_tof: examples/CMakeFiles/pid_vs_tof.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/amefodev/work/SuperFGD/SFGD_Unpacking/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/pid_vs_tof"
	cd /Users/amefodev/work/SuperFGD/SFGD_Unpacking/cmake-build-debug/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pid_vs_tof.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/pid_vs_tof.dir/build: ../bin/pid_vs_tof

.PHONY : examples/CMakeFiles/pid_vs_tof.dir/build

examples/CMakeFiles/pid_vs_tof.dir/clean:
	cd /Users/amefodev/work/SuperFGD/SFGD_Unpacking/cmake-build-debug/examples && $(CMAKE_COMMAND) -P CMakeFiles/pid_vs_tof.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/pid_vs_tof.dir/clean

examples/CMakeFiles/pid_vs_tof.dir/depend:
	cd /Users/amefodev/work/SuperFGD/SFGD_Unpacking/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/amefodev/work/SuperFGD/SFGD_Unpacking /Users/amefodev/work/SuperFGD/SFGD_Unpacking/examples /Users/amefodev/work/SuperFGD/SFGD_Unpacking/cmake-build-debug /Users/amefodev/work/SuperFGD/SFGD_Unpacking/cmake-build-debug/examples /Users/amefodev/work/SuperFGD/SFGD_Unpacking/cmake-build-debug/examples/CMakeFiles/pid_vs_tof.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/pid_vs_tof.dir/depend
