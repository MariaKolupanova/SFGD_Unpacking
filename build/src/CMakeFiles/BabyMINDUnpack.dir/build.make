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
include src/CMakeFiles/BabyMINDUnpack.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/BabyMINDUnpack.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/BabyMINDUnpack.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/BabyMINDUnpack.dir/flags.make

src/CMakeFiles/BabyMINDUnpack.dir/MDargumentHandler.cpp.o: src/CMakeFiles/BabyMINDUnpack.dir/flags.make
src/CMakeFiles/BabyMINDUnpack.dir/MDargumentHandler.cpp.o: /Users/maria/SFGD_Unpacking/src/MDargumentHandler.cpp
src/CMakeFiles/BabyMINDUnpack.dir/MDargumentHandler.cpp.o: src/CMakeFiles/BabyMINDUnpack.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/maria/SFGD_Unpacking/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/BabyMINDUnpack.dir/MDargumentHandler.cpp.o"
	cd /Users/maria/SFGD_Unpacking/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/BabyMINDUnpack.dir/MDargumentHandler.cpp.o -MF CMakeFiles/BabyMINDUnpack.dir/MDargumentHandler.cpp.o.d -o CMakeFiles/BabyMINDUnpack.dir/MDargumentHandler.cpp.o -c /Users/maria/SFGD_Unpacking/src/MDargumentHandler.cpp

src/CMakeFiles/BabyMINDUnpack.dir/MDargumentHandler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BabyMINDUnpack.dir/MDargumentHandler.cpp.i"
	cd /Users/maria/SFGD_Unpacking/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/maria/SFGD_Unpacking/src/MDargumentHandler.cpp > CMakeFiles/BabyMINDUnpack.dir/MDargumentHandler.cpp.i

src/CMakeFiles/BabyMINDUnpack.dir/MDargumentHandler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BabyMINDUnpack.dir/MDargumentHandler.cpp.s"
	cd /Users/maria/SFGD_Unpacking/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/maria/SFGD_Unpacking/src/MDargumentHandler.cpp -o CMakeFiles/BabyMINDUnpack.dir/MDargumentHandler.cpp.s

src/CMakeFiles/BabyMINDUnpack.dir/MDdataFile.cpp.o: src/CMakeFiles/BabyMINDUnpack.dir/flags.make
src/CMakeFiles/BabyMINDUnpack.dir/MDdataFile.cpp.o: /Users/maria/SFGD_Unpacking/src/MDdataFile.cpp
src/CMakeFiles/BabyMINDUnpack.dir/MDdataFile.cpp.o: src/CMakeFiles/BabyMINDUnpack.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/maria/SFGD_Unpacking/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/BabyMINDUnpack.dir/MDdataFile.cpp.o"
	cd /Users/maria/SFGD_Unpacking/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/BabyMINDUnpack.dir/MDdataFile.cpp.o -MF CMakeFiles/BabyMINDUnpack.dir/MDdataFile.cpp.o.d -o CMakeFiles/BabyMINDUnpack.dir/MDdataFile.cpp.o -c /Users/maria/SFGD_Unpacking/src/MDdataFile.cpp

src/CMakeFiles/BabyMINDUnpack.dir/MDdataFile.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BabyMINDUnpack.dir/MDdataFile.cpp.i"
	cd /Users/maria/SFGD_Unpacking/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/maria/SFGD_Unpacking/src/MDdataFile.cpp > CMakeFiles/BabyMINDUnpack.dir/MDdataFile.cpp.i

src/CMakeFiles/BabyMINDUnpack.dir/MDdataFile.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BabyMINDUnpack.dir/MDdataFile.cpp.s"
	cd /Users/maria/SFGD_Unpacking/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/maria/SFGD_Unpacking/src/MDdataFile.cpp -o CMakeFiles/BabyMINDUnpack.dir/MDdataFile.cpp.s

src/CMakeFiles/BabyMINDUnpack.dir/MDdataWordBM.cpp.o: src/CMakeFiles/BabyMINDUnpack.dir/flags.make
src/CMakeFiles/BabyMINDUnpack.dir/MDdataWordBM.cpp.o: /Users/maria/SFGD_Unpacking/src/MDdataWordBM.cpp
src/CMakeFiles/BabyMINDUnpack.dir/MDdataWordBM.cpp.o: src/CMakeFiles/BabyMINDUnpack.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/maria/SFGD_Unpacking/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/BabyMINDUnpack.dir/MDdataWordBM.cpp.o"
	cd /Users/maria/SFGD_Unpacking/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/BabyMINDUnpack.dir/MDdataWordBM.cpp.o -MF CMakeFiles/BabyMINDUnpack.dir/MDdataWordBM.cpp.o.d -o CMakeFiles/BabyMINDUnpack.dir/MDdataWordBM.cpp.o -c /Users/maria/SFGD_Unpacking/src/MDdataWordBM.cpp

src/CMakeFiles/BabyMINDUnpack.dir/MDdataWordBM.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BabyMINDUnpack.dir/MDdataWordBM.cpp.i"
	cd /Users/maria/SFGD_Unpacking/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/maria/SFGD_Unpacking/src/MDdataWordBM.cpp > CMakeFiles/BabyMINDUnpack.dir/MDdataWordBM.cpp.i

src/CMakeFiles/BabyMINDUnpack.dir/MDdataWordBM.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BabyMINDUnpack.dir/MDdataWordBM.cpp.s"
	cd /Users/maria/SFGD_Unpacking/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/maria/SFGD_Unpacking/src/MDdataWordBM.cpp -o CMakeFiles/BabyMINDUnpack.dir/MDdataWordBM.cpp.s

src/CMakeFiles/BabyMINDUnpack.dir/MDexception.cpp.o: src/CMakeFiles/BabyMINDUnpack.dir/flags.make
src/CMakeFiles/BabyMINDUnpack.dir/MDexception.cpp.o: /Users/maria/SFGD_Unpacking/src/MDexception.cpp
src/CMakeFiles/BabyMINDUnpack.dir/MDexception.cpp.o: src/CMakeFiles/BabyMINDUnpack.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/maria/SFGD_Unpacking/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/CMakeFiles/BabyMINDUnpack.dir/MDexception.cpp.o"
	cd /Users/maria/SFGD_Unpacking/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/BabyMINDUnpack.dir/MDexception.cpp.o -MF CMakeFiles/BabyMINDUnpack.dir/MDexception.cpp.o.d -o CMakeFiles/BabyMINDUnpack.dir/MDexception.cpp.o -c /Users/maria/SFGD_Unpacking/src/MDexception.cpp

src/CMakeFiles/BabyMINDUnpack.dir/MDexception.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BabyMINDUnpack.dir/MDexception.cpp.i"
	cd /Users/maria/SFGD_Unpacking/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/maria/SFGD_Unpacking/src/MDexception.cpp > CMakeFiles/BabyMINDUnpack.dir/MDexception.cpp.i

src/CMakeFiles/BabyMINDUnpack.dir/MDexception.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BabyMINDUnpack.dir/MDexception.cpp.s"
	cd /Users/maria/SFGD_Unpacking/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/maria/SFGD_Unpacking/src/MDexception.cpp -o CMakeFiles/BabyMINDUnpack.dir/MDexception.cpp.s

src/CMakeFiles/BabyMINDUnpack.dir/MDfragmentBM.cpp.o: src/CMakeFiles/BabyMINDUnpack.dir/flags.make
src/CMakeFiles/BabyMINDUnpack.dir/MDfragmentBM.cpp.o: /Users/maria/SFGD_Unpacking/src/MDfragmentBM.cpp
src/CMakeFiles/BabyMINDUnpack.dir/MDfragmentBM.cpp.o: src/CMakeFiles/BabyMINDUnpack.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/maria/SFGD_Unpacking/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/CMakeFiles/BabyMINDUnpack.dir/MDfragmentBM.cpp.o"
	cd /Users/maria/SFGD_Unpacking/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/BabyMINDUnpack.dir/MDfragmentBM.cpp.o -MF CMakeFiles/BabyMINDUnpack.dir/MDfragmentBM.cpp.o.d -o CMakeFiles/BabyMINDUnpack.dir/MDfragmentBM.cpp.o -c /Users/maria/SFGD_Unpacking/src/MDfragmentBM.cpp

src/CMakeFiles/BabyMINDUnpack.dir/MDfragmentBM.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BabyMINDUnpack.dir/MDfragmentBM.cpp.i"
	cd /Users/maria/SFGD_Unpacking/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/maria/SFGD_Unpacking/src/MDfragmentBM.cpp > CMakeFiles/BabyMINDUnpack.dir/MDfragmentBM.cpp.i

src/CMakeFiles/BabyMINDUnpack.dir/MDfragmentBM.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BabyMINDUnpack.dir/MDfragmentBM.cpp.s"
	cd /Users/maria/SFGD_Unpacking/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/maria/SFGD_Unpacking/src/MDfragmentBM.cpp -o CMakeFiles/BabyMINDUnpack.dir/MDfragmentBM.cpp.s

src/CMakeFiles/BabyMINDUnpack.dir/MDpartEventBM.cpp.o: src/CMakeFiles/BabyMINDUnpack.dir/flags.make
src/CMakeFiles/BabyMINDUnpack.dir/MDpartEventBM.cpp.o: /Users/maria/SFGD_Unpacking/src/MDpartEventBM.cpp
src/CMakeFiles/BabyMINDUnpack.dir/MDpartEventBM.cpp.o: src/CMakeFiles/BabyMINDUnpack.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/maria/SFGD_Unpacking/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/CMakeFiles/BabyMINDUnpack.dir/MDpartEventBM.cpp.o"
	cd /Users/maria/SFGD_Unpacking/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/BabyMINDUnpack.dir/MDpartEventBM.cpp.o -MF CMakeFiles/BabyMINDUnpack.dir/MDpartEventBM.cpp.o.d -o CMakeFiles/BabyMINDUnpack.dir/MDpartEventBM.cpp.o -c /Users/maria/SFGD_Unpacking/src/MDpartEventBM.cpp

src/CMakeFiles/BabyMINDUnpack.dir/MDpartEventBM.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BabyMINDUnpack.dir/MDpartEventBM.cpp.i"
	cd /Users/maria/SFGD_Unpacking/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/maria/SFGD_Unpacking/src/MDpartEventBM.cpp > CMakeFiles/BabyMINDUnpack.dir/MDpartEventBM.cpp.i

src/CMakeFiles/BabyMINDUnpack.dir/MDpartEventBM.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BabyMINDUnpack.dir/MDpartEventBM.cpp.s"
	cd /Users/maria/SFGD_Unpacking/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/maria/SFGD_Unpacking/src/MDpartEventBM.cpp -o CMakeFiles/BabyMINDUnpack.dir/MDpartEventBM.cpp.s

# Object files for target BabyMINDUnpack
BabyMINDUnpack_OBJECTS = \
"CMakeFiles/BabyMINDUnpack.dir/MDargumentHandler.cpp.o" \
"CMakeFiles/BabyMINDUnpack.dir/MDdataFile.cpp.o" \
"CMakeFiles/BabyMINDUnpack.dir/MDdataWordBM.cpp.o" \
"CMakeFiles/BabyMINDUnpack.dir/MDexception.cpp.o" \
"CMakeFiles/BabyMINDUnpack.dir/MDfragmentBM.cpp.o" \
"CMakeFiles/BabyMINDUnpack.dir/MDpartEventBM.cpp.o"

# External object files for target BabyMINDUnpack
BabyMINDUnpack_EXTERNAL_OBJECTS =

/Users/maria/SFGD_Unpacking/lib/libBabyMINDUnpack.dylib: src/CMakeFiles/BabyMINDUnpack.dir/MDargumentHandler.cpp.o
/Users/maria/SFGD_Unpacking/lib/libBabyMINDUnpack.dylib: src/CMakeFiles/BabyMINDUnpack.dir/MDdataFile.cpp.o
/Users/maria/SFGD_Unpacking/lib/libBabyMINDUnpack.dylib: src/CMakeFiles/BabyMINDUnpack.dir/MDdataWordBM.cpp.o
/Users/maria/SFGD_Unpacking/lib/libBabyMINDUnpack.dylib: src/CMakeFiles/BabyMINDUnpack.dir/MDexception.cpp.o
/Users/maria/SFGD_Unpacking/lib/libBabyMINDUnpack.dylib: src/CMakeFiles/BabyMINDUnpack.dir/MDfragmentBM.cpp.o
/Users/maria/SFGD_Unpacking/lib/libBabyMINDUnpack.dylib: src/CMakeFiles/BabyMINDUnpack.dir/MDpartEventBM.cpp.o
/Users/maria/SFGD_Unpacking/lib/libBabyMINDUnpack.dylib: src/CMakeFiles/BabyMINDUnpack.dir/build.make
/Users/maria/SFGD_Unpacking/lib/libBabyMINDUnpack.dylib: src/CMakeFiles/BabyMINDUnpack.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/maria/SFGD_Unpacking/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX shared library /Users/maria/SFGD_Unpacking/lib/libBabyMINDUnpack.dylib"
	cd /Users/maria/SFGD_Unpacking/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/BabyMINDUnpack.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/BabyMINDUnpack.dir/build: /Users/maria/SFGD_Unpacking/lib/libBabyMINDUnpack.dylib
.PHONY : src/CMakeFiles/BabyMINDUnpack.dir/build

src/CMakeFiles/BabyMINDUnpack.dir/clean:
	cd /Users/maria/SFGD_Unpacking/build/src && $(CMAKE_COMMAND) -P CMakeFiles/BabyMINDUnpack.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/BabyMINDUnpack.dir/clean

src/CMakeFiles/BabyMINDUnpack.dir/depend:
	cd /Users/maria/SFGD_Unpacking/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/maria/SFGD_Unpacking /Users/maria/SFGD_Unpacking/src /Users/maria/SFGD_Unpacking/build /Users/maria/SFGD_Unpacking/build/src /Users/maria/SFGD_Unpacking/build/src/CMakeFiles/BabyMINDUnpack.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/BabyMINDUnpack.dir/depend
