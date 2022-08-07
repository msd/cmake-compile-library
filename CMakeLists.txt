cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(MyProj VERSION 0.1.0 LANGUAGES CXX)

set(BUILD_STATIC_LIBS ON CACHE BOOL "create static libraries")
set(BUILD_DYNAMIC_LIBS ON CACHE BOOL "create dynamic libraries")

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT) # only set during the first time
	set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "installation path of libary" FORCE)
endif()

# might need to add "${CMAKE_BINARY_DIR}/" at the front if in nested project
set(LIBHELLO_DYNAMIC_LIBPATH "lib/dynamic")
set(LIBHELLO_SOURCES
	hello.cpp
)

# set output folders instead of setting properties individially
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_INSTALL_PREFIX}/bin") # .dll .so
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_INSTALL_PREFIX}/lib") # .lib .a .dll.a
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_INSTALL_PREFIX}/lib") 

# STATIC LIBARY
if (BUILD_STATIC_LIBS)
	add_library(
		hello_lib_static
		STATIC
		${LIBHELLO_SOURCES}
	)
	set_target_properties(hello_lib_static PROPERTIES
		OUTPUT_NAME hello
		ARCHIVE_OUTPUT_DIRECTORY "${LIBHELLO_STATIC_LIBPATH}"
	)
	if (MINGW)
		message("/!\\ DETECTED MINIMALIST GNU FOR WINDOWS /!\\")
		message("Compiling static library using static libgcc and libstd++")
		target_link_libraries(hello_lib_static -static-libgcc -static-libstdc++)
	endif()
endif()

# SHARED DYNAMIC LIBRARY
if (BUILD_DYNAMIC_LIBS)
	add_library(
		hello_lib_dynamic
		SHARED
		${LIBHELLO_SOURCES}
	)
	set_target_properties(hello_lib_dynamic PROPERTIES
		OUTPUT_NAME hello
		ARCHIVE_OUTPUT_DIRECTORY "${LIBHELLO_DYNAMIC_LIBPATH}" # .dll.a
		RUNTIME_OUTPUT_DIRECTORY "${LIBHELLO_DYNAMIC_LIBPATH}" # .dll .so
	)
	if (MINGW)
		message("/!\\ DETECTED MINIMALIST GNU FOR WINDOWS /!\\")
		message("Compiling dynamic library using static libgcc and libstd++")
		target_link_libraries(hello_lib_dynamic -static-libgcc -static-libstdc++)
	endif()
endif()

# if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU") # minimise binary size
# 	add_compile_options("-Wl,--strip-all -O2 -Wl,-gc-sections -f -ffunction-sections")
# endif()


# target_compile_features(hello_lib_dynamic PUBLIC cxx_std_17) # set language standard
