# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.24.1/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.24.1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/maria/SFGD_Unpacking

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/maria/SFGD_Unpacking/build

# Include any dependencies generated for this target.
include examples/CMakeFiles/TimeFromTrigger.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include examples/CMakeFiles/TimeFromTrigger.dir/compiler_depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/TimeFromTrigger.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/TimeFromTrigger.dir/flags.make

examples/CMakeFiles/TimeFromTrigger.dir/Time_From_Trigger.cpp.o: examples/CMakeFiles/TimeFromTrigger.dir/flags.make
examples/CMakeFiles/TimeFromTrigger.dir/Time_From_Trigger.cpp.o: /Users/maria/SFGD_Unpacking/examples/Time_From_Trigger.cpp
examples/CMakeFiles/TimeFromTrigger.dir/Time_From_Trigger.cpp.o: examples/CMakeFiles/TimeFromTrigger.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/maria/SFGD_Unpacking/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/CMakeFiles/TimeFromTrigger.dir/Time_From_Trigger.cpp.o"
	cd /Users/maria/SFGD_Unpacking/build/examples && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT examples/CMakeFiles/TimeFromTrigger.dir/Time_From_Trigger.cpp.o -MF CMakeFiles/TimeFromTrigger.dir/Time_From_Trigger.cpp.o.d -o CMakeFiles/TimeFromTrigger.dir/Time_From_Trigger.cpp.o -c /Users/maria/SFGD_Unpacking/examples/Time_From_Trigger.cpp

examples/CMakeFiles/TimeFromTrigger.dir/Time_From_Trigger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TimeFromTrigger.dir/Time_From_Trigger.cpp.i"
	cd /Users/maria/SFGD_Unpacking/build/examples && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/maria/SFGD_Unpacking/examples/Time_From_Trigger.cpp > CMakeFiles/TimeFromTrigger.dir/Time_From_Trigger.cpp.i

examples/CMakeFiles/TimeFromTrigger.dir/Time_From_Trigger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TimeFromTrigger.dir/Time_From_Trigger.cpp.s"
	cd /Users/maria/SFGD_Unpacking/build/examples && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/maria/SFGD_Unpacking/examples/Time_From_Trigger.cpp -o CMakeFiles/TimeFromTrigger.dir/Time_From_Trigger.cpp.s

# Object files for target TimeFromTrigger
TimeFromTrigger_OBJECTS = \
"CMakeFiles/TimeFromTrigger.dir/Time_From_Trigger.cpp.o"

# External object files for target TimeFromTrigger
TimeFromTrigger_EXTERNAL_OBJECTS =

/Users/maria/SFGD_Unpacking/bin/TimeFromTrigger: examples/CMakeFiles/TimeFromTrigger.dir/Time_From_Trigger.cpp.o
/Users/maria/SFGD_Unpacking/bin/TimeFromTrigger: examples/CMakeFiles/TimeFromTrigger.dir/build.make
/Users/maria/SFGD_Unpacking/bin/TimeFromTrigger: /Users/maria/SFGD_Unpacking/lib/libBabyMINDUnpack.dylib
/Users/maria/SFGD_Unpacking/bin/TimeFromTrigger: examples/CMakeFiles/TimeFromTrigger.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/maria/SFGD_Unpacking/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /Users/maria/SFGD_Unpacking/bin/TimeFromTrigger"
	cd /Users/maria/SFGD_Unpacking/build/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TimeFromTrigger.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/TimeFromTrigger.dir/build: /Users/maria/SFGD_Unpacking/bin/TimeFromTrigger
.PHONY : examples/CMakeFiles/TimeFromTrigger.dir/build

examples/CMakeFiles/TimeFromTrigger.dir/clean:
	cd /Users/maria/SFGD_Unpacking/build/examples && $(CMAKE_COMMAND) -P CMakeFiles/TimeFromTrigger.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/TimeFromTrigger.dir/clean

examples/CMakeFiles/TimeFromTrigger.dir/depend:
	cd /Users/maria/SFGD_Unpacking/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/maria/SFGD_Unpacking /Users/maria/SFGD_Unpacking/examples /Users/maria/SFGD_Unpacking/build /Users/maria/SFGD_Unpacking/build/examples /Users/maria/SFGD_Unpacking/build/examples/CMakeFiles/TimeFromTrigger.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/TimeFromTrigger.dir/depend

