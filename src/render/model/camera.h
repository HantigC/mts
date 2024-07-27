#ifndef RENDER_MODEL_CAMERA_H
#define RENDER_MODEL_CAMERA_H

#include <Eigen/Core>

#include "render/model/base.h"

namespace mts {
namespace render {

class CameraModel : public BaseModel {
   public:
    CameraModel();
    CameraModel(Eigen::Vector3f& position,
                Eigen::Vector3f& xaxis,
                Eigen::Vector3f& yaxis,
                Eigen::Vector3f& zaxis,
                Eigen::Matrix3f& K,
                size_t width,
                size_t height);
    CameraModel(Eigen::Matrix4f& view);
    void draw() override;

    Eigen::Matrix3f K;
    Eigen::Vector3f position;
    Eigen::Vector3f xaxis;
    Eigen::Vector3f yaxis;
    Eigen::Vector3f zaxis;

    size_t width;
    size_t height;

    friend std::ostream& operator<<(std::ostream& os, const CameraModel& camera);
};

}  // namespace render
}  // namespace mts

#endif  // !RENDER_MODEL_CAMERA_H