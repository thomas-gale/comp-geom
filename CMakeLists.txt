cmake_minimum_required(VERSION 3.4)
project(CompGeom)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/modules/" ${CMAKE_MODULE_PATH})

# Configure all build options for Corrade, Magnum and Magnum-Plugins.

# For easy release on Linux machine, set to static:
# Remember that the host machine will still need libSDS2-2.0.so.0
# So run something like `sudo apt install libsdl2-2.0`
#set(BUILD_STATIC ON CACHE BOOL "" FORCE)
#set(BUILD_PLUGINS_STATIC ON CACHE BOOL "" FORCE)

# Loading OBJ files
set(WITH_ANYIMAGEIMPORTER ON CACHE BOOL "" FORCE)
set(WITH_ANYSCENEIMPORTER ON CACHE BOOL "" FORCE)
set(WITH_OBJIMPORTER ON CACHE BOOL "" FORCE)

# If you want to load (textured) glTF as well
set(WITH_STBIMAGEIMPORTER ON CACHE BOOL "" FORCE)
set(WITH_TINYGLTFIMPORTER ON CACHE BOOL "" FORCE)

# Enable Magnum Sdl2Application
set(WITH_SDL2APPLICATION ON CACHE BOOL "" FORCE)

# Add Corrade as a subproject
add_subdirectory(lib/corrade EXCLUDE_FROM_ALL)

# Add Magnum as a subproject
add_subdirectory(lib/magnum EXCLUDE_FROM_ALL)

# Add src
add_subdirectory(src)
