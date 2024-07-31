#include "model/camera.h"

#include <Eigen/LU>

namespace mts {

Eigen::MatrixX3f Camera::fromImageToCamera(const Eigen::Matrix3f& K,
                                           Eigen::MatrixX2f& pts) {
    Eigen::Matrix3f Kinv = K.inverse();
    Eigen::Vector3f ptH;
    Eigen::MatrixX3f cameraPts(pts.rows(), 3);
    for (size_t i = 0; i < pts.rows(); i++) {
        ptH = {pts(i, 0), pts(i, 1), 1.0f};
        cameraPts.row(i) = Kinv * ptH;
    }
    return cameraPts;
}

}  // namespace mts