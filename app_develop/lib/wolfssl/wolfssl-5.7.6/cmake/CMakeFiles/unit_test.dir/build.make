# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_SOURCE_DIR = /home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/cmake

# Include any dependencies generated for this target.
include CMakeFiles/unit_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/unit_test.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/unit_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/unit_test.dir/flags.make

CMakeFiles/unit_test.dir/tests/api.c.o: CMakeFiles/unit_test.dir/flags.make
CMakeFiles/unit_test.dir/tests/api.c.o: /home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/tests/api.c
CMakeFiles/unit_test.dir/tests/api.c.o: CMakeFiles/unit_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/unit_test.dir/tests/api.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/unit_test.dir/tests/api.c.o -MF CMakeFiles/unit_test.dir/tests/api.c.o.d -o CMakeFiles/unit_test.dir/tests/api.c.o -c /home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/tests/api.c

CMakeFiles/unit_test.dir/tests/api.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/unit_test.dir/tests/api.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/tests/api.c > CMakeFiles/unit_test.dir/tests/api.c.i

CMakeFiles/unit_test.dir/tests/api.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/unit_test.dir/tests/api.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/tests/api.c -o CMakeFiles/unit_test.dir/tests/api.c.s

CMakeFiles/unit_test.dir/tests/hash.c.o: CMakeFiles/unit_test.dir/flags.make
CMakeFiles/unit_test.dir/tests/hash.c.o: /home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/tests/hash.c
CMakeFiles/unit_test.dir/tests/hash.c.o: CMakeFiles/unit_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/unit_test.dir/tests/hash.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/unit_test.dir/tests/hash.c.o -MF CMakeFiles/unit_test.dir/tests/hash.c.o.d -o CMakeFiles/unit_test.dir/tests/hash.c.o -c /home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/tests/hash.c

CMakeFiles/unit_test.dir/tests/hash.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/unit_test.dir/tests/hash.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/tests/hash.c > CMakeFiles/unit_test.dir/tests/hash.c.i

CMakeFiles/unit_test.dir/tests/hash.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/unit_test.dir/tests/hash.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/tests/hash.c -o CMakeFiles/unit_test.dir/tests/hash.c.s

CMakeFiles/unit_test.dir/tests/srp.c.o: CMakeFiles/unit_test.dir/flags.make
CMakeFiles/unit_test.dir/tests/srp.c.o: /home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/tests/srp.c
CMakeFiles/unit_test.dir/tests/srp.c.o: CMakeFiles/unit_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/unit_test.dir/tests/srp.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/unit_test.dir/tests/srp.c.o -MF CMakeFiles/unit_test.dir/tests/srp.c.o.d -o CMakeFiles/unit_test.dir/tests/srp.c.o -c /home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/tests/srp.c

CMakeFiles/unit_test.dir/tests/srp.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/unit_test.dir/tests/srp.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/tests/srp.c > CMakeFiles/unit_test.dir/tests/srp.c.i

CMakeFiles/unit_test.dir/tests/srp.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/unit_test.dir/tests/srp.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/tests/srp.c -o CMakeFiles/unit_test.dir/tests/srp.c.s

CMakeFiles/unit_test.dir/tests/suites.c.o: CMakeFiles/unit_test.dir/flags.make
CMakeFiles/unit_test.dir/tests/suites.c.o: /home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/tests/suites.c
CMakeFiles/unit_test.dir/tests/suites.c.o: CMakeFiles/unit_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/unit_test.dir/tests/suites.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/unit_test.dir/tests/suites.c.o -MF CMakeFiles/unit_test.dir/tests/suites.c.o.d -o CMakeFiles/unit_test.dir/tests/suites.c.o -c /home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/tests/suites.c

CMakeFiles/unit_test.dir/tests/suites.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/unit_test.dir/tests/suites.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/tests/suites.c > CMakeFiles/unit_test.dir/tests/suites.c.i

CMakeFiles/unit_test.dir/tests/suites.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/unit_test.dir/tests/suites.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/tests/suites.c -o CMakeFiles/unit_test.dir/tests/suites.c.s

CMakeFiles/unit_test.dir/tests/w64wrapper.c.o: CMakeFiles/unit_test.dir/flags.make
CMakeFiles/unit_test.dir/tests/w64wrapper.c.o: /home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/tests/w64wrapper.c
CMakeFiles/unit_test.dir/tests/w64wrapper.c.o: CMakeFiles/unit_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/unit_test.dir/tests/w64wrapper.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/unit_test.dir/tests/w64wrapper.c.o -MF CMakeFiles/unit_test.dir/tests/w64wrapper.c.o.d -o CMakeFiles/unit_test.dir/tests/w64wrapper.c.o -c /home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/tests/w64wrapper.c

CMakeFiles/unit_test.dir/tests/w64wrapper.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/unit_test.dir/tests/w64wrapper.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/tests/w64wrapper.c > CMakeFiles/unit_test.dir/tests/w64wrapper.c.i

CMakeFiles/unit_test.dir/tests/w64wrapper.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/unit_test.dir/tests/w64wrapper.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/tests/w64wrapper.c -o CMakeFiles/unit_test.dir/tests/w64wrapper.c.s

CMakeFiles/unit_test.dir/tests/unit.c.o: CMakeFiles/unit_test.dir/flags.make
CMakeFiles/unit_test.dir/tests/unit.c.o: /home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/tests/unit.c
CMakeFiles/unit_test.dir/tests/unit.c.o: CMakeFiles/unit_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/unit_test.dir/tests/unit.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/unit_test.dir/tests/unit.c.o -MF CMakeFiles/unit_test.dir/tests/unit.c.o.d -o CMakeFiles/unit_test.dir/tests/unit.c.o -c /home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/tests/unit.c

CMakeFiles/unit_test.dir/tests/unit.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/unit_test.dir/tests/unit.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/tests/unit.c > CMakeFiles/unit_test.dir/tests/unit.c.i

CMakeFiles/unit_test.dir/tests/unit.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/unit_test.dir/tests/unit.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/tests/unit.c -o CMakeFiles/unit_test.dir/tests/unit.c.s

CMakeFiles/unit_test.dir/tests/quic.c.o: CMakeFiles/unit_test.dir/flags.make
CMakeFiles/unit_test.dir/tests/quic.c.o: /home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/tests/quic.c
CMakeFiles/unit_test.dir/tests/quic.c.o: CMakeFiles/unit_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/unit_test.dir/tests/quic.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/unit_test.dir/tests/quic.c.o -MF CMakeFiles/unit_test.dir/tests/quic.c.o.d -o CMakeFiles/unit_test.dir/tests/quic.c.o -c /home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/tests/quic.c

CMakeFiles/unit_test.dir/tests/quic.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/unit_test.dir/tests/quic.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/tests/quic.c > CMakeFiles/unit_test.dir/tests/quic.c.i

CMakeFiles/unit_test.dir/tests/quic.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/unit_test.dir/tests/quic.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/tests/quic.c -o CMakeFiles/unit_test.dir/tests/quic.c.s

CMakeFiles/unit_test.dir/examples/server/server.c.o: CMakeFiles/unit_test.dir/flags.make
CMakeFiles/unit_test.dir/examples/server/server.c.o: /home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/examples/server/server.c
CMakeFiles/unit_test.dir/examples/server/server.c.o: CMakeFiles/unit_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/unit_test.dir/examples/server/server.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/unit_test.dir/examples/server/server.c.o -MF CMakeFiles/unit_test.dir/examples/server/server.c.o.d -o CMakeFiles/unit_test.dir/examples/server/server.c.o -c /home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/examples/server/server.c

CMakeFiles/unit_test.dir/examples/server/server.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/unit_test.dir/examples/server/server.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/examples/server/server.c > CMakeFiles/unit_test.dir/examples/server/server.c.i

CMakeFiles/unit_test.dir/examples/server/server.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/unit_test.dir/examples/server/server.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/examples/server/server.c -o CMakeFiles/unit_test.dir/examples/server/server.c.s

CMakeFiles/unit_test.dir/examples/client/client.c.o: CMakeFiles/unit_test.dir/flags.make
CMakeFiles/unit_test.dir/examples/client/client.c.o: /home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/examples/client/client.c
CMakeFiles/unit_test.dir/examples/client/client.c.o: CMakeFiles/unit_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/unit_test.dir/examples/client/client.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/unit_test.dir/examples/client/client.c.o -MF CMakeFiles/unit_test.dir/examples/client/client.c.o.d -o CMakeFiles/unit_test.dir/examples/client/client.c.o -c /home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/examples/client/client.c

CMakeFiles/unit_test.dir/examples/client/client.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/unit_test.dir/examples/client/client.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/examples/client/client.c > CMakeFiles/unit_test.dir/examples/client/client.c.i

CMakeFiles/unit_test.dir/examples/client/client.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/unit_test.dir/examples/client/client.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/examples/client/client.c -o CMakeFiles/unit_test.dir/examples/client/client.c.s

# Object files for target unit_test
unit_test_OBJECTS = \
"CMakeFiles/unit_test.dir/tests/api.c.o" \
"CMakeFiles/unit_test.dir/tests/hash.c.o" \
"CMakeFiles/unit_test.dir/tests/srp.c.o" \
"CMakeFiles/unit_test.dir/tests/suites.c.o" \
"CMakeFiles/unit_test.dir/tests/w64wrapper.c.o" \
"CMakeFiles/unit_test.dir/tests/unit.c.o" \
"CMakeFiles/unit_test.dir/tests/quic.c.o" \
"CMakeFiles/unit_test.dir/examples/server/server.c.o" \
"CMakeFiles/unit_test.dir/examples/client/client.c.o"

# External object files for target unit_test
unit_test_EXTERNAL_OBJECTS =

tests/unit.test: CMakeFiles/unit_test.dir/tests/api.c.o
tests/unit.test: CMakeFiles/unit_test.dir/tests/hash.c.o
tests/unit.test: CMakeFiles/unit_test.dir/tests/srp.c.o
tests/unit.test: CMakeFiles/unit_test.dir/tests/suites.c.o
tests/unit.test: CMakeFiles/unit_test.dir/tests/w64wrapper.c.o
tests/unit.test: CMakeFiles/unit_test.dir/tests/unit.c.o
tests/unit.test: CMakeFiles/unit_test.dir/tests/quic.c.o
tests/unit.test: CMakeFiles/unit_test.dir/examples/server/server.c.o
tests/unit.test: CMakeFiles/unit_test.dir/examples/client/client.c.o
tests/unit.test: CMakeFiles/unit_test.dir/build.make
tests/unit.test: libwolfssl.so.43.0.0
tests/unit.test: CMakeFiles/unit_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking C executable tests/unit.test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/unit_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/unit_test.dir/build: tests/unit.test
.PHONY : CMakeFiles/unit_test.dir/build

CMakeFiles/unit_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/unit_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/unit_test.dir/clean

CMakeFiles/unit_test.dir/depend:
	cd /home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/cmake && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6 /home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6 /home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/cmake /home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/cmake /home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/cmake/CMakeFiles/unit_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/unit_test.dir/depend

