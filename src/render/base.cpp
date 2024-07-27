#include "render/base.h"

#include <pangolin/gl/opengl_render_state.h>
#include <pangolin/pangolin.h>
namespace mts {
namespace render {

void draw(const std::vector<std::shared_ptr<mts::render::BaseModel>>& models,
          Eigen::Vector3f& position,
          Eigen::Vector3f& gaze) {
    pangolin::CreateWindowAndBind("Main", 640, 480);
    glEnable(GL_DEPTH_TEST);

    // Define Projection and initial ModelView matrix
    pangolin::OpenGlRenderState s_cam(
        pangolin::ProjectionMatrix(640, 480, 420, 420, 320, 240, 0.2, 100),
        pangolin::ModelViewLookAt(position.x(),
                                  position.y(),
                                  position.z(),
                                  gaze.x(),
                                  gaze.y(),
                                  gaze.z(),
                                  pangolin::AxisNegY));

    // Create Interactive View in window
    pangolin::Handler3D handler(s_cam);
    pangolin::View& d_cam = pangolin::CreateDisplay()
                                .SetBounds(0.0, 1.0, 0.0, 1.0, -640.0f / 480.0f)
                                .SetHandler(&handler);

    while (!pangolin::ShouldQuit()) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        d_cam.Activate(s_cam);
        for (auto& model : models) {
            model->draw();
        }

        // Render OpenGL Cube
        // pangolin::glDrawColouredCube();

        // Swap frames and Process Events
        pangolin::FinishFrame();
    }
}

}  // namespace render
}  // namespace mts