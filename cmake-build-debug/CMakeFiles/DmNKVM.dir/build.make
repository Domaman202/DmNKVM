# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.19

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


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

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Games\CLion 2021.1.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Games\CLion 2021.1.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Games\DmNKVM

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Games\DmNKVM\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles\DmNKVM.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\DmNKVM.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\DmNKVM.dir\flags.make

CMakeFiles\DmNKVM.dir\main.cpp.obj: CMakeFiles\DmNKVM.dir\flags.make
CMakeFiles\DmNKVM.dir\main.cpp.obj: ..\main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Games\DmNKVM\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/DmNKVM.dir/main.cpp.obj"
	C:\PROGRA~2\MICROS~2\2019\ENTERP~1\VC\Tools\MSVC\1429~1.300\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\DmNKVM.dir\main.cpp.obj /FdCMakeFiles\DmNKVM.dir\ /FS -c C:\Games\DmNKVM\main.cpp
<<

CMakeFiles\DmNKVM.dir\main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DmNKVM.dir/main.cpp.i"
	C:\PROGRA~2\MICROS~2\2019\ENTERP~1\VC\Tools\MSVC\1429~1.300\bin\Hostx86\x86\cl.exe > CMakeFiles\DmNKVM.dir\main.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Games\DmNKVM\main.cpp
<<

CMakeFiles\DmNKVM.dir\main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DmNKVM.dir/main.cpp.s"
	C:\PROGRA~2\MICROS~2\2019\ENTERP~1\VC\Tools\MSVC\1429~1.300\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\DmNKVM.dir\main.cpp.s /c C:\Games\DmNKVM\main.cpp
<<

# Object files for target DmNKVM
DmNKVM_OBJECTS = \
"CMakeFiles\DmNKVM.dir\main.cpp.obj"

# External object files for target DmNKVM
DmNKVM_EXTERNAL_OBJECTS =

DmNKVM.exe: CMakeFiles\DmNKVM.dir\main.cpp.obj
DmNKVM.exe: CMakeFiles\DmNKVM.dir\build.make
DmNKVM.exe: CMakeFiles\DmNKVM.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Games\DmNKVM\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable DmNKVM.exe"
	"C:\Games\CLion 2021.1.3\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\DmNKVM.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100190~1.0\x86\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100190~1.0\x86\mt.exe --manifests -- C:\PROGRA~2\MICROS~2\2019\ENTERP~1\VC\Tools\MSVC\1429~1.300\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\DmNKVM.dir\objects1.rsp @<<
 /out:DmNKVM.exe /implib:DmNKVM.lib /pdb:C:\Games\DmNKVM\cmake-build-debug\DmNKVM.pdb /version:0.0 /machine:X86 /debug /INCREMENTAL /subsystem:console  kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\DmNKVM.dir\build: DmNKVM.exe

.PHONY : CMakeFiles\DmNKVM.dir\build

CMakeFiles\DmNKVM.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\DmNKVM.dir\cmake_clean.cmake
.PHONY : CMakeFiles\DmNKVM.dir\clean

CMakeFiles\DmNKVM.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Games\DmNKVM C:\Games\DmNKVM C:\Games\DmNKVM\cmake-build-debug C:\Games\DmNKVM\cmake-build-debug C:\Games\DmNKVM\cmake-build-debug\CMakeFiles\DmNKVM.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\DmNKVM.dir\depend

