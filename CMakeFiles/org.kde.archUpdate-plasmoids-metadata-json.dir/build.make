# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

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
CMAKE_SOURCE_DIR = /home/cis422/UpdateArchFinal/UpdateArch

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cis422/UpdateArchFinal/UpdateArch

# Utility rule file for org.kde.archUpdate-plasmoids-metadata-json.

# Include the progress variables for this target.
include CMakeFiles/org.kde.archUpdate-plasmoids-metadata-json.dir/progress.make

CMakeFiles/org.kde.archUpdate-plasmoids-metadata-json: org.kde.archUpdate-plasmoids-metadata.json


org.kde.archUpdate-plasmoids-metadata.json:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/cis422/UpdateArchFinal/UpdateArch/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating org.kde.archUpdate-plasmoids-metadata.json"
	/usr/bin/desktoptojson -i /home/cis422/UpdateArchFinal/UpdateArch/package/metadata.desktop -o /home/cis422/UpdateArchFinal/UpdateArch/org.kde.archUpdate-plasmoids-metadata.json

org.kde.archUpdate-plasmoids-metadata-json: CMakeFiles/org.kde.archUpdate-plasmoids-metadata-json
org.kde.archUpdate-plasmoids-metadata-json: org.kde.archUpdate-plasmoids-metadata.json
org.kde.archUpdate-plasmoids-metadata-json: CMakeFiles/org.kde.archUpdate-plasmoids-metadata-json.dir/build.make

.PHONY : org.kde.archUpdate-plasmoids-metadata-json

# Rule to build all files generated by this target.
CMakeFiles/org.kde.archUpdate-plasmoids-metadata-json.dir/build: org.kde.archUpdate-plasmoids-metadata-json

.PHONY : CMakeFiles/org.kde.archUpdate-plasmoids-metadata-json.dir/build

CMakeFiles/org.kde.archUpdate-plasmoids-metadata-json.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/org.kde.archUpdate-plasmoids-metadata-json.dir/cmake_clean.cmake
.PHONY : CMakeFiles/org.kde.archUpdate-plasmoids-metadata-json.dir/clean

CMakeFiles/org.kde.archUpdate-plasmoids-metadata-json.dir/depend:
	cd /home/cis422/UpdateArchFinal/UpdateArch && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cis422/UpdateArchFinal/UpdateArch /home/cis422/UpdateArchFinal/UpdateArch /home/cis422/UpdateArchFinal/UpdateArch /home/cis422/UpdateArchFinal/UpdateArch /home/cis422/UpdateArchFinal/UpdateArch/CMakeFiles/org.kde.archUpdate-plasmoids-metadata-json.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/org.kde.archUpdate-plasmoids-metadata-json.dir/depend

