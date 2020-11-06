#include <Magnum/GL/Buffer.h>
#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/GL/Renderer.h>
#include <Magnum/Math/Color.h>
#include <Magnum/Math/Matrix4.h>
#include <Magnum/MeshTools/Compile.h>
#include <Magnum/MeshTools/CompressIndices.h>
#include <Magnum/MeshTools/Interleave.h>
#include <Magnum/Platform/Sdl2Application.h>
#include <Magnum/Primitives/Axis.h>
#include <Magnum/Primitives/Cube.h>
#include <Magnum/Primitives/Square.h>
#include <Magnum/Shaders/Phong.h>
#include <Magnum/Trade/MeshData.h>

using namespace Magnum;
using namespace Math::Literals;

class CompGeom : public Platform::Application {
  public:
    explicit CompGeom(const Arguments& arguments);

  private:
    void drawEvent() override;

    GL::Mesh axis_{NoCreate};
    GL::Mesh point_{NoCreate};
    Shaders::Phong shader_;

    Matrix4 projection_;
};

CompGeom::CompGeom(const Arguments& arguments)
    : Platform::Application{arguments, Configuration{}.setTitle("Comp Geom")} {
    GL::Renderer::enable(GL::Renderer::Feature::DepthTest);
    GL::Renderer::enable(GL::Renderer::Feature::FaceCulling);

    // Initialise the meshes.
    axis_ = MeshTools::compile(Primitives::axis3D());
    point_ = MeshTools::compile(Primitives::squareSolid());

    // Configure fixed info for shader.
    projection_ =
        Matrix4::perspectiveProjection(
            35.0_degf, Vector2{windowSize()}.aspectRatio(), 0.01f, 100.0f) *
        Matrix4::translation(Vector3::zAxis(-20.0f));

    shader_.setLightPositions({{7.0f, 5.0f, 2.5f, 0.0f}})
        .setProjectionMatrix(projection_);
}

void CompGeom::drawEvent() {
    GL::defaultFramebuffer.clear(GL::FramebufferClear::Color |
                                 GL::FramebufferClear::Depth);
    // Render Axis and Points
    shader_.setAmbientColor(Color3(1, 1, 1));
    shader_.setTransformationMatrix(Matrix4::translation(Vector3(-4, -4, 0)))
        .draw(axis_);
    for (int i = -4; i <= 4; i += 2) {
        for (int j = -4; j <= 4; j += 2) {
            shader_.setTransformationMatrix(
                Matrix4::translation(Vector3(i, j, 0)));
            shader_.setAmbientColor(
                Color3(float(i + 4) / float(10), float(j + 4) / float(10), 0));
            shader_.draw(point_);
        }
    }

    swapBuffers();
}

MAGNUM_APPLICATION_MAIN(CompGeom)
