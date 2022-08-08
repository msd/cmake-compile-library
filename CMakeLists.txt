cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
project(MyProj VERSION 0.1.0 LANGUAGES CXX)

cmake_policy(SET CMP0054 NEW) # cmake --help-policy CMP0054

set(BUILD_STATIC_LIBS ON CACHE BOOL "create static libraries")
set(BUILD_DYNAMIC_LIBS ON CACHE BOOL "create dynamic libraries")
set(BUILD_EXAMPELS OFF CACHE BOOL "compile example programs")

# if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT) # only set during the first time
# 	set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "installation path of libary" FORCE)
# endif()

# might need to add "${CMAKE_BINARY_DIR}/" at the front if in nested project
set(LIBHELLO_STATIC_LIBPATH "lib/static")
set(LIBHELLO_DYNAMIC_LIBPATH "lib/dynamic")
set(LIBHELLO_SOURCES
	hello.cpp
)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	set(LIBHELLO_USING_MSVC)
	message(STATUS "Microsft compiler, hence __declspec will be added")
	add_compile_definitions(MSVC_COMPILER 1)
endif()

if (MINGW)
	message(STATUS "Using static libgcc and libstdc++ (MINGW detected)")
	link_libraries(-static-libgcc -static-libstdc++)
endif()

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
		ARCHIVE_OUTPUT_DIRECTORY "${LIBHELLO_DYNAMIC_LIBPATH}" # .dll.a (mignw)
		RUNTIME_OUTPUT_DIRECTORY "${LIBHELLO_DYNAMIC_LIBPATH}" # .dll (win) .so (linux)
 		LIBRARY_OUTPUT_DIRECTORY "${LIBHELLO_DYNAMIC_LIBPATH}" # .dylib (mac)
	)
endif()

# if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU") # minimise binary size
# 	add_compile_options("-Wl,--strip-all -O2 -Wl,-gc-sections -f -ffunction-sections")
# endif()


# target_compile_features(hello_lib_dynamic PUBLIC cxx_std_17) # set language standard

if (BUILD_EXAMPLES)
	add_executable(main main.cpp)
	target_link_libraries(main hello_lib_static)
endif()
