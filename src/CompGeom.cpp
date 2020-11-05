#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/Platform/Sdl2Application.h>

#include <Corrade/Utility/DebugStl.h>
#include <Magnum/GL/Context.h>
#include <Magnum/GL/Renderer.h>
#include <Magnum/GL/Version.h>
#include <Magnum/Math/Color.h>

using namespace Magnum;

class CompGeom : public Platform::Application {
public:
  explicit CompGeom(const Arguments &arguments);

private:
  void drawEvent() override;
};

CompGeom::CompGeom(const Arguments &arguments)
    : Platform::Application{arguments} {
  // TODO: Add your initialization code here

  using namespace Math::Literals;

  GL::Renderer::setClearColor(0xa5c9ea_rgbf);

  Debug{} << "Hello! This application is running on"
          << GL::Context::current().version() << "using"
          << GL::Context::current().rendererString();
}

void CompGeom::drawEvent() {
  GL::defaultFramebuffer.clear(GL::FramebufferClear::Color);

  // TODO: Add your drawing code here

  swapBuffers();
}

MAGNUM_APPLICATION_MAIN(CompGeom)
