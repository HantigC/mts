#include "geometry/rigid3d.h"
#include <Eigen/Dense>
namespace mts {

Eigen::Matrix4f Rigid3D::viewFromRt(const Eigen::Matrix3f& R, const Eigen::Vector3f& t) {
    Eigen::Matrix4f view;
    view.block<3, 3>(0, 0) = R;
    view.block<3, 1>(0, 3) = t;
    view.block<1, 4>(3, 0) << 0.0f, 0.0f, 0.0f, 1.0f;
    return view;
}

Eigen::Vector3f Rigid3D::invT() {
    Eigen::Matrix4f invView = view.inverse();
    Eigen::Vector3f invT = invView.block<3, 1>(0, 3);
    return invT;
}

}  // namespace mts