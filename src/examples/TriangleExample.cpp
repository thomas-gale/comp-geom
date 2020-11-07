#include <Magnum/GL/Buffer.h>
#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/Math/Color.h>
#include <Magnum/Platform/Sdl2Application.h>
#include <Magnum/Shaders/VertexColor.h>

namespace M = Magnum;

class TriangleExample : public M::Platform::Application {
  public:
    explicit TriangleExample(const Arguments& arguments);

  private:
    void drawEvent() override;

    M::GL::Mesh _mesh;
    M::Shaders::VertexColor2D _shader;
};

// C'tor for TriangleExample
TriangleExample::TriangleExample(const Arguments& arguments)
    : M::Platform::Application{
          arguments, Configuration{}.setTitle("Magnum Triangle Example")} {

    using namespace M::Math::Literals;

    struct TriangleVertex {
        M::Vector2 position;
        M::Color3 color;
    };
    const TriangleVertex data[]{
        {{-0.5f, -0.5f}, 0xff0000_rgbf}, /* Left vertex, red color */
        {{0.5f, -0.5f}, 0x00ff00_rgbf},  /* Right vertex, green color */
        {{0.0f, 0.5f}, 0x0000ff_rgbf}    /* Top vertex, blue color */
    };

    M::GL::Buffer buffer;
    buffer.setData(data);

    _mesh.setCount(3).addVertexBuffer(std::move(buffer), 0,
                                      M::Shaders::VertexColor2D::Position{},
                                      M::Shaders::VertexColor2D::Color3{});
};

// Override for drawEvent in TriangleExample
void TriangleExample::drawEvent() {
    M::GL::defaultFramebuffer.clear(M::GL::FramebufferClear::Color);

    _shader.draw(_mesh);

    swapBuffers();
}

// Main entry point.
MAGNUM_APPLICATION_MAIN(TriangleExample)
