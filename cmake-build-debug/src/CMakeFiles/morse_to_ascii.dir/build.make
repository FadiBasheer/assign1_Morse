# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /home/fadi/Downloads/CLion-2021.2.1/clion-2021.2.1/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/fadi/Downloads/CLion-2021.2.1/clion-2021.2.1/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/fadi/work/assignments/assign1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/fadi/work/assignments/assign1/cmake-build-debug

# Include any dependencies generated for this target.
include src/CMakeFiles/morse_to_ascii.dir/depend.make
# Include the progress variables for this target.
include src/CMakeFiles/morse_to_ascii.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/morse_to_ascii.dir/flags.make

src/CMakeFiles/morse_to_ascii.dir/common.c.o: src/CMakeFiles/morse_to_ascii.dir/flags.make
src/CMakeFiles/morse_to_ascii.dir/common.c.o: ../src/common.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fadi/work/assignments/assign1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/CMakeFiles/morse_to_ascii.dir/common.c.o"
	cd /home/fadi/work/assignments/assign1/cmake-build-debug/src && $(CMAKE_COMMAND) -E __run_co_compile --tidy="clang-tidy;-checks=*,-llvmlibc-restrict-system-libc-headers,-cppcoreguidelines-init-variables,-clang-analyzer-security.insecureAPI.strcpy,-concurrency-mt-unsafe,-android-cloexec-accept,-android-cloexec-dup,-google-readability-todo,-cppcoreguidelines-avoid-magic-numbers,-readability-magic-numbers,-cert-dcl03-c,-hicpp-static-assert,-misc-static-assert,-altera-struct-pack-align,-clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling;--quiet;--extra-arg-before=--driver-mode=gcc" --source=/home/fadi/work/assignments/assign1/src/common.c -- /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/morse_to_ascii.dir/common.c.o -c /home/fadi/work/assignments/assign1/src/common.c

src/CMakeFiles/morse_to_ascii.dir/common.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/morse_to_ascii.dir/common.c.i"
	cd /home/fadi/work/assignments/assign1/cmake-build-debug/src && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/fadi/work/assignments/assign1/src/common.c > CMakeFiles/morse_to_ascii.dir/common.c.i

src/CMakeFiles/morse_to_ascii.dir/common.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/morse_to_ascii.dir/common.c.s"
	cd /home/fadi/work/assignments/assign1/cmake-build-debug/src && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/fadi/work/assignments/assign1/src/common.c -o CMakeFiles/morse_to_ascii.dir/common.c.s

src/CMakeFiles/morse_to_ascii.dir/main_to_ascii.c.o: src/CMakeFiles/morse_to_ascii.dir/flags.make
src/CMakeFiles/morse_to_ascii.dir/main_to_ascii.c.o: ../src/main_to_ascii.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fadi/work/assignments/assign1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object src/CMakeFiles/morse_to_ascii.dir/main_to_ascii.c.o"
	cd /home/fadi/work/assignments/assign1/cmake-build-debug/src && $(CMAKE_COMMAND) -E __run_co_compile --tidy="clang-tidy;-checks=*,-llvmlibc-restrict-system-libc-headers,-cppcoreguidelines-init-variables,-clang-analyzer-security.insecureAPI.strcpy,-concurrency-mt-unsafe,-android-cloexec-accept,-android-cloexec-dup,-google-readability-todo,-cppcoreguidelines-avoid-magic-numbers,-readability-magic-numbers,-cert-dcl03-c,-hicpp-static-assert,-misc-static-assert,-altera-struct-pack-align,-clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling;--quiet;--extra-arg-before=--driver-mode=gcc" --source=/home/fadi/work/assignments/assign1/src/main_to_ascii.c -- /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/morse_to_ascii.dir/main_to_ascii.c.o -c /home/fadi/work/assignments/assign1/src/main_to_ascii.c

src/CMakeFiles/morse_to_ascii.dir/main_to_ascii.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/morse_to_ascii.dir/main_to_ascii.c.i"
	cd /home/fadi/work/assignments/assign1/cmake-build-debug/src && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/fadi/work/assignments/assign1/src/main_to_ascii.c > CMakeFiles/morse_to_ascii.dir/main_to_ascii.c.i

src/CMakeFiles/morse_to_ascii.dir/main_to_ascii.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/morse_to_ascii.dir/main_to_ascii.c.s"
	cd /home/fadi/work/assignments/assign1/cmake-build-debug/src && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/fadi/work/assignments/assign1/src/main_to_ascii.c -o CMakeFiles/morse_to_ascii.dir/main_to_ascii.c.s

# Object files for target morse_to_ascii
morse_to_ascii_OBJECTS = \
"CMakeFiles/morse_to_ascii.dir/common.c.o" \
"CMakeFiles/morse_to_ascii.dir/main_to_ascii.c.o"

# External object files for target morse_to_ascii
morse_to_ascii_EXTERNAL_OBJECTS =

src/morse_to_ascii: src/CMakeFiles/morse_to_ascii.dir/common.c.o
src/morse_to_ascii: src/CMakeFiles/morse_to_ascii.dir/main_to_ascii.c.o
src/morse_to_ascii: src/CMakeFiles/morse_to_ascii.dir/build.make
src/morse_to_ascii: /usr/lib/x86_64-linux-gnu/libm.so
src/morse_to_ascii: /usr/local/lib/libdc_error.so
src/morse_to_ascii: /usr/local/lib/libdc_posix.so
src/morse_to_ascii: src/CMakeFiles/morse_to_ascii.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/fadi/work/assignments/assign1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable morse_to_ascii"
	cd /home/fadi/work/assignments/assign1/cmake-build-debug/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/morse_to_ascii.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/morse_to_ascii.dir/build: src/morse_to_ascii
.PHONY : src/CMakeFiles/morse_to_ascii.dir/build

src/CMakeFiles/morse_to_ascii.dir/clean:
	cd /home/fadi/work/assignments/assign1/cmake-build-debug/src && $(CMAKE_COMMAND) -P CMakeFiles/morse_to_ascii.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/morse_to_ascii.dir/clean

src/CMakeFiles/morse_to_ascii.dir/depend:
	cd /home/fadi/work/assignments/assign1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/fadi/work/assignments/assign1 /home/fadi/work/assignments/assign1/src /home/fadi/work/assignments/assign1/cmake-build-debug /home/fadi/work/assignments/assign1/cmake-build-debug/src /home/fadi/work/assignments/assign1/cmake-build-debug/src/CMakeFiles/morse_to_ascii.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/morse_to_ascii.dir/depend

