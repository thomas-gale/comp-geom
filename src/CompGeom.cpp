#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/Platform/Sdl2Application.h>

using namespace Magnum;

class CompGeom: public Platform::Application {
    public:
        explicit CompGeom(const Arguments& arguments);

    private:
        void drawEvent() override;
};

CompGeom::CompGeom(const Arguments& arguments):
    Platform::Application{arguments}
{
    // TODO: Add your initialization code here
}

void CompGeom::drawEvent() {
    GL::defaultFramebuffer.clear(GL::FramebufferClear::Color);

    // TODO: Add your drawing code here

    swapBuffers();
}

MAGNUM_APPLICATION_MAIN(CompGeom)
