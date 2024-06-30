#ifndef GEOMETRY_FUNDAMENTAL_H
#define GEOMETRY_FUNDAMENTAL_H
#include <Eigen/Core>

namespace mts {

Eigen::Matrix3f computeFundamentalMatrix(Eigen::MatrixX2f& points1,
                                         Eigen::MatrixX2f& points2);

Eigen::Matrix3f computeFundamentalMatrix(std::vector<Eigen::Vector2f>& points1,
                                         std::vector<Eigen::Vector2f>& points2);

}  // namespace mts

#endif  // !GEOMETRY_FUNDAMENTAL_H