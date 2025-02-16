cmake_minimum_required(VERSION 3.13)
project(CompGeom)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/modules/" ${CMAKE_MODULE_PATH})

# Configure all build options for Corrade, Magnum and Magnum-Plugins.

# For easy release on Linux machine, set to static:
# Remember that the host machine will still need libSDS2-2.0.so.0
# So run something like `sudo apt install libsdl2-2.0`
#set(BUILD_STATIC ON CACHE BOOL "" FORCE)
#set(BUILD_PLUGINS_STATIC ON CACHE BOOL "" FORCE)

# -- File Loading --

# Loading OBJ files
set(WITH_ANYIMAGEIMPORTER ON CACHE BOOL "" FORCE)
set(WITH_ANYSCENEIMPORTER ON CACHE BOOL "" FORCE)
set(WITH_OBJIMPORTER ON CACHE BOOL "" FORCE)

# If you want to load (textured) glTF as well
set(WITH_STBIMAGEIMPORTER ON CACHE BOOL "" FORCE)
set(WITH_TINYGLTFIMPORTER ON CACHE BOOL "" FORCE)

# -- Bullet --

# Disable Bullet tests and demos
set(BUILD_UNIT_TESTS OFF CACHE BOOL "" FORCE)
set(BUILD_BULLET2_DEMOS OFF CACHE BOOL "" FORCE)
set(BUILD_CPU_DEMOS OFF CACHE BOOL "" FORCE)
set(BUILD_OPENGL3_DEMOS OFF CACHE BOOL "" FORCE)
# While not needed for Magnum, you might actually want some of those
set(BUILD_ENET OFF CACHE BOOL "" FORCE)
set(BUILD_CLSOCKET OFF CACHE BOOL "" FORCE)
set(BUILD_EXTRAS OFF CACHE BOOL "" FORCE)
set(BUILD_BULLET3 OFF CACHE BOOL "" FORCE)
# This is needed in case BUILD_EXTRAS is enabled, as you'd get a CMake syntax
# error otherwise
set(PKGCONFIG_INSTALL_PREFIX "lib${LIB_SUFFIX}/pkgconfig/")
# Actuallly enable bullet!
#set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)
set(WITH_BULLET ON CACHE BOOL "" FORCE)

# -- General --

# Enable Magnum Sdl2Application
set(WITH_SDL2APPLICATION ON CACHE BOOL "" FORCE)

# -- Add all subprojects --

add_subdirectory(lib/corrade EXCLUDE_FROM_ALL)
add_subdirectory(lib/magnum EXCLUDE_FROM_ALL)
add_subdirectory(lib/magnum-plugins EXCLUDE_FROM_ALL)
add_subdirectory(lib/bullet3 EXCLUDE_FROM_ALL)
add_subdirectory(lib/magnum-integration EXCLUDE_FROM_ALL)

add_subdirectory(src)
