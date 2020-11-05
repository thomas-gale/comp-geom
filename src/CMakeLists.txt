find_package(Magnum REQUIRED GL Sdl2Application)
#include_directories(lib)

#find_package(SDL2 REQUIRED)
#include_directories(${SDL2_INCLUDE_DIRS})

set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

add_executable(comp_geom
CompGeom.cpp)

target_link_libraries(comp_geom PRIVATE
    #Magnum

    Magnum::Application
    Magnum::GL
    Magnum::Magnum

    #${SDL2_LIBRARIES}
    )
