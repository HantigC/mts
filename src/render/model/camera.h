#ifndef RENDER_MODEL_CAMERA_H
#define RENDER_MODEL_CAMERA_H

#include <Eigen/Core>

#include "render/model/base.h"

namespace mts {
class CameraModel : public BaseModel {
   public:
    CameraModel();
    CameraModel(Eigen::Vector3f& position,
                Eigen::Vector3f& xaxis,
                Eigen::Vector3f& yaxis,
                Eigen::Vector3f& zaxis);
    CameraModel(Eigen::Matrix4f& view);
    void draw() override;

    Eigen::Vector3f position;
    Eigen::Vector3f xaxis;
    Eigen::Vector3f yaxis;
    Eigen::Vector3f zaxis;
};
}  // namespace mts

#endif  // !RENDER_MODEL_CAMERA_H