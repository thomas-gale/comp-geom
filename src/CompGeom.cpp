//#include <Magnum/GL/Buffer.h>
#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/GL/Renderer.h>
#include <Magnum/Math/Color.h>
#include <Magnum/Math/Matrix4.h>
#include <Magnum/MeshTools/Compile.h>
//#include <Magnum/MeshTools/CompressIndices.h>
//#include <Magnum/MeshTools/Interleave.h>
#include <Magnum/Platform/Sdl2Application.h>
#include <Magnum/Primitives/Axis.h>
#include <Magnum/Primitives/Cube.h>
#include <Magnum/Primitives/Line.h>
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

    const int gridHeight_ = 10;

    GL::Mesh axis_{NoCreate};
    GL::Mesh point_{NoCreate};
    GL::Mesh line_{NoCreate};

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
    line_ = MeshTools::compile(Primitives::line3D());

    // Configure fixed info for shader.
    projection_ = Matrix4::orthographicProjection(
        Vector2{Vector2{windowSize()}.aspectRatio() * gridHeight_ + 1,
                float(gridHeight_ + 1)},
        -100.0f, 100.0f);

    // Turn on 3D perspective projection.
    /*Matrix4::perspectiveProjection(
        35.0_degf, Vector2{windowSize()}.aspectRatio(), 0.01f, 100.0f) *
    Matrix4::translation(Vector3::zAxis(-20.0f));*/

    shader_.setLightPositions({{7.0f, 5.0f, 2.5f, 0.0f}})
        .setProjectionMatrix(projection_);
}

void CompGeom::drawEvent() {
    GL::defaultFramebuffer.clear(GL::FramebufferClear::Color |
                                 GL::FramebufferClear::Depth);

    // Render axis.
    shader_.setAmbientColor(Color3(1, 1, 1));
    shader_
        .setTransformationMatrix(Matrix4::translation(
            Vector3(-(gridHeight_ / 2), -(gridHeight_ / 2), 0)))
        .draw(axis_);

    // Render points.
    for (int i = -(gridHeight_ / 2); i <= gridHeight_ / 2; ++i) {
        for (int j = -(gridHeight_ / 2); j <= (gridHeight_ / 2); ++j) {
            shader_.setTransformationMatrix(
                Matrix4::translation(Vector3(i, j, 0)) *
                Matrix4::scaling(Vector3(0.2, 0.2, 0)));
            shader_.setAmbientColor(
                Color3(float(i + gridHeight_ / 2) / float(gridHeight_),
                       float(j + gridHeight_ / 2) / float(gridHeight_), 0));
            shader_.draw(point_);
        }
    }

    // Render test lines.
    shader_.setAmbientColor(Color3(1, 0, 0));

    shader_
        .setTransformationMatrix(Matrix4::translation(Vector3(-2, 2, 1)) *
                                 Matrix4::scaling(Vector3(4, 4, 4)))
        .draw(line_);
    shader_
        .setTransformationMatrix(Matrix4::rotationZ(90.0_degf) * Matrix4::translation(Vector3(-2, -2, 1)) *
                                 Matrix4::scaling(Vector3(4, 4, 4)))
        .draw(line_);
    shader_
        .setTransformationMatrix(Matrix4::translation(Vector3(-2, -2, 1)) *
                                 Matrix4::scaling(Vector3(4, 4, 4)))
        .draw(line_);
    shader_
        .setTransformationMatrix(Matrix4::rotationZ(90.0_degf) * Matrix4::translation(Vector3(-2, 2, 1)) *
                                 Matrix4::scaling(Vector3(4, 4, 4)))
        .draw(line_);

    swapBuffers();
}

MAGNUM_APPLICATION_MAIN(CompGeom)
