find_package(Corrade REQUIRED)
find_package(Magnum REQUIRED 
    GL
    MeshTools
    ObjImporter
    Sdl2Application
    Shaders
    SceneGraph
    Trade
)
find_package(MagnumIntegration REQUIRED
    Bullet
)
find_package(MagnumPlugins REQUIRED 
    TinyGltfImporter
)
find_package(Bullet REQUIRED)

set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

add_executable(comp_geom
#CompGeom.cpp
#examples/TriangleExample.cpp
#examples/PrimitivesExample.cpp
#examples/ViewerExample.cpp
examples/BulletExample.cpp
)

target_link_libraries(comp_geom PRIVATE 
    Corrade::Main
    Magnum::Application
    Magnum::GL
    Magnum::Magnum
    Magnum::MeshTools
    #Magnum::ObjImporter
    Magnum::Primitives
    Magnum::SceneGraph
    Magnum::Shaders
    Magnum::Trade
    MagnumIntegration::Bullet
    Bullet::Dynamics
    #MagnumPlugins::TinyGltfImporter
)
