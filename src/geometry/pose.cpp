#include "geometry/pose.h"

#include <cstddef>

#include "geometry/triangulation.h"

namespace mts {
float computeDepth(Eigen::Matrix3f& R, Eigen::Vector3f& t, Eigen::Vector3f& point3D) {
    float depth = R.row(2).dot(point3D) + t.z();
    return depth;
}

float computeDepth(Eigen::Matrix4f& view, Eigen::Vector3f& point3D) {
    float depth = view.row(2).dot(point3D.homogeneous());
    return depth;
}


}  // namespace mts