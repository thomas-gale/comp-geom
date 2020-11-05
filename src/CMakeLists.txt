find_package(Corrade REQUIRED)
find_package(Magnum REQUIRED GL Sdl2Application)

set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

add_executable(comp_geom
CompGeom.cpp
#TriangleExample.cpp
#PrimitivesExample.cpp
)

target_link_libraries(comp_geom PRIVATE
    Corrade::Main
    Magnum::Application
    Magnum::GL
    Magnum::Magnum
    Magnum::MeshTools
    Magnum::Primitives
    Magnum::Shaders)
