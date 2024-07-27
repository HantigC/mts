#include "render/model/scene.h"

#include "render/model/rigid3d.h"
#include "render/primitive/point.h"

namespace mts {
namespace render {

void SceneModel::draw() {
    Eigen::Vector3f red(1.0f, 0.0f, 0.0f);
    mts::render::drawPoints(scene.points3D, red);
    for (auto pose : scene.poses) {
        Rigid3DModel::drawRigid3DAxes(pose);
    }
}

}  // namespace render

}  // namespace mts