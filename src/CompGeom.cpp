#include <algorithm>
#include <random>
#include <vector>

#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/GL/Renderer.h>
#include <Magnum/Math/Color.h>
#include <Magnum/Math/Matrix4.h>
#include <Magnum/MeshTools/Compile.h>
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
    // Computation geometry components
    const int gridHeight_ = 10;
    std::vector<Vector2> points_;
    std::vector<Vector2> generateRandomGridPoints2D(int number);
    std::vector<Vector2>
    compute2DConvexHullJarvisMarch(const std::vector<Vector2>& points);

    // Rendering components
    GL::Mesh axis_{NoCreate};
    GL::Mesh point_{NoCreate};
    GL::Mesh line_{NoCreate};
    Shaders::Phong shader_;
    Matrix4 projection_;

    void drawEvent() override;
    void renderPoints(const std::vector<Vector2>& points);
    void render2DGridOfPoints(int step = 1);
    void renderPolyLine(const std::vector<Vector2>& polyLine);
};

// Setup and perform a single render pass in the main c'tor.
CompGeom::CompGeom(const Arguments& arguments)
    : Platform::Application{arguments, Configuration{}.setTitle("Comp Geom")} {
    GL::Renderer::enable(GL::Renderer::Feature::DepthTest);
    GL::Renderer::enable(GL::Renderer::Feature::FaceCulling);

    // Comp Geom steps.
    std::vector<Vector2> points = generateRandomGridPoints2D(20);
    std::vector<Vector2> hull = compute2DConvexHullJarvisMarch(points);

    // Render Steps
    GL::defaultFramebuffer.clear(GL::FramebufferClear::Color |
                                 GL::FramebufferClear::Depth);

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

    // Render axis.
    shader_.setAmbientColor(Color3(1, 1, 1));
    shader_
        .setTransformationMatrix(Matrix4::translation(
            Vector3(-(gridHeight_ / 2), -(gridHeight_ / 2), 0)))
        .draw(axis_);

    // Render random points
    renderPoints(points);

    /// Render hull
    renderPolyLine(hull);

    // Render test lines.
    /*
    shader_.setAmbientColor(Color3(1, 0, 0));

    shader_
        .setTransformationMatrix(Matrix4::translation(Vector3(-2, 2, 1)) *
                                 Matrix4::scaling(Vector3(4, 4, 4)))
        .draw(line_);
    shader_
        .setTransformationMatrix(Matrix4::rotationZ(90.0_degf) *
                                 Matrix4::translation(Vector3(-2, -2, 1)) *
                                 Matrix4::scaling(Vector3(4, 4, 4)))
        .draw(line_);
    shader_
        .setTransformationMatrix(Matrix4::translation(Vector3(-2, -2, 1)) *
                                 Matrix4::scaling(Vector3(4, 4, 4)))
        .draw(line_);
    shader_
        .setTransformationMatrix(Matrix4::rotationZ(90.0_degf) *
                                 Matrix4::translation(Vector3(-2, 2, 1)) *
                                 Matrix4::scaling(Vector3(4, 4, 4)))
        .draw(line_);*/

    swapBuffers();
}

void CompGeom::drawEvent() {
    // No need for any redrawing right now.
}

std::vector<Vector2> CompGeom::generateRandomGridPoints2D(int number) {
    std::random_device rd;  // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_real_distribution<> distr(
        0.0f, float(gridHeight_)); // define the range

    std::vector<Vector2> points;
    for (int i = 0; i < number; ++i) {
        points.push_back(Vector2(distr(gen), distr(gen)));
    }
    return points;
}

std::vector<Vector2>
CompGeom::compute2DConvexHullJarvisMarch(const std::vector<Vector2>& points) {
    // Simple case anything less than triangle.
    if (points.size() <= 3)
        return points;

    // Find leftmost point in points.
    std::vector<Vector2> sorted(points);
    std::sort(sorted.begin(), sorted.end(),
              [](const Vector2& lhs, const Vector2& rhs) {
                  return lhs.x() < rhs.x();
              });

    // Initial point on hull is the leftmost point.
    Vector2 pointOnHull = sorted.front();

    // Starting with empty hull, loop till wrap around to first hull point.
    std::vector<Vector2> hull;
    while (hull.size() == 0 || pointOnHull != hull.front()) {
        // Add point on hull to collection
        hull.push_back(pointOnHull);
        // Temp endpoint
        Vector2 endpoint = hull.front();
        // Nest loop over all points
        for (size_t i = 0; i < sorted.size(); ++i) {
            Vector2 bestSeg = endpoint - hull.back();
            Vector2 currSeg = sorted[i] - hull.back();
            if (endpoint == pointOnHull ||
                Math::cross(bestSeg, currSeg) > 0.0f) {
                // Found greater left turn updated endpoint.
                endpoint = sorted[i];
            }
        }
        pointOnHull = endpoint;
    }

    // Append front point again to close segment
    hull.push_back(hull.front());

    return hull;
}

void CompGeom::renderPoints(const std::vector<Vector2>& points) {
    for (const auto& point : points) {
        shader_.setTransformationMatrix(
            Matrix4::translation(Vector3(point.x() - float(gridHeight_) / 2.0f,
                                         point.y() - float(gridHeight_) / 2.0f,
                                         0.0f)) *
            Matrix4::scaling(Vector3(0.05f, 0.05f, 0.05f)));
        shader_.setAmbientColor(Color3(1.0f, 1.0f, 1.0f));
        shader_.draw(point_);
    }
}

void CompGeom::render2DGridOfPoints(int step) {
    // Render grid points.
    for (int i = -(gridHeight_ / 2); i <= gridHeight_ / 2; i += step) {
        for (int j = -(gridHeight_ / 2); j <= (gridHeight_ / 2); j += step) {
            shader_.setTransformationMatrix(
                Matrix4::translation(Vector3(i, j, 0)) *
                Matrix4::scaling(Vector3(0.2, 0.2, 0)));
            shader_.setAmbientColor(
                Color3(float(i + gridHeight_ / 2) / float(gridHeight_),
                       float(j + gridHeight_ / 2) / float(gridHeight_), 0));
            shader_.draw(point_);
        }
    }
}

void CompGeom::renderPolyLine(const std::vector<Vector2>& polyLine) {
    if (polyLine.size() < 2)
        return;

    // Red color for polyline
    shader_.setAmbientColor(Color3(1, 0, 0));
    float offset = float(gridHeight_) / 2.0f;
    for (int i = 1; i < polyLine.size(); ++i) {
        Vector3 start =
            Vector3(polyLine[i - 1], 0.0f) - Vector3(offset, offset, 0.0f);
        Vector3 end =
            Vector3(polyLine[i], 0.0f) - Vector3(offset, offset, 0.0f);

        shader_
            .setTransformationMatrix(
                Matrix4::lookAt(start, end, Vector3::zAxis()) *
                Matrix4::rotationY(90.0_degf) *
                Matrix4::scaling(Vector3((end - start).length())))
            .draw(line_);
    }
}

MAGNUM_APPLICATION_MAIN(CompGeom)
