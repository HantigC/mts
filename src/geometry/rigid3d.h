#ifndef GEOMETRY_RIGID_H
#define GEOMETRY_RIGID_H
#include <Eigen/Core>

namespace mts {

class Rigid3D {
   public:
    Rigid3D(): R(Eigen::Matrix3f::Identity()), t() {
        view = Rigid3D::viewFromRt(R, t);
    }
    Rigid3D(const Eigen::Matrix3f& R, const Eigen::Vector3f& t) : R(R), t(t) {
        view = Rigid3D::viewFromRt(R, t);
    }

    Eigen::Matrix3f R;
    Eigen::Vector3f t;
    Eigen::Matrix4f view;
    static Eigen::Matrix4f viewFromRt(const Eigen::Matrix3f &R, const Eigen::Vector3f &t);
};

}  // namespace mts

#endif  // !GEOMETRY_RIGID_H