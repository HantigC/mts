#include "geometry/rigid3d.h"
namespace mts {

Eigen::Matrix4f Rigid3D::viewFromRt(const Eigen::Matrix3f& R, const Eigen::Vector3f& t) {
    Eigen::Matrix4f view;
    view.block<3, 3>(0, 0) = R;
    view.block<3, 1>(0, 3) = t;
    view.block<1, 4>(3, 0) << 0.0f, 0.0f, 0.0f, 1.0f;
    return view;
}

}