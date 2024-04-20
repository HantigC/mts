#ifndef TRIANGULATION_H
#define TRIANGULATION_H
#include <Eigen/Eigen>
#include <vector>
namespace mts {
Eigen::Vector3f triangulateMidPoint(const Eigen::Vector2f &st_point,
                                    const Eigen::Vector2f &nd_point,
                                    const Eigen::Matrix4f &st_view,
                                    const Eigen::Matrix4f &nd_view);

Eigen::Vector3f triangulateLinearTwoView(const Eigen::Vector2f &st_point,
                                         const Eigen::Vector2f &nd_point,
                                         const Eigen::Matrix4f &st_view,
                                         const Eigen::Matrix4f &nd_view);

std::vector<Eigen::Vector3f>
triangulateLinearTwoView(const std::vector<Eigen::Vector2f> &st_points,
                         const std::vector<Eigen::Vector2f> &nd_points,
                         const Eigen::Matrix4f &st_view,
                         const Eigen::Matrix4f &nd_view);

Eigen::MatrixX3f triangulateLinearTwoView(const Eigen::MatrixX2f &st_points,
                                          const Eigen::MatrixX2f &nd_points,
                                          const Eigen::Matrix4f &st_view,
                                          const Eigen::Matrix4f &nd_view);

Eigen::MatrixX3f triangulateLinearTwoView(const Eigen::MatrixX3f &st_points,
                                          const Eigen::MatrixX3f &nd_points,
                                          const Eigen::Matrix4f &st_view,
                                          const Eigen::Matrix4f &nd_view);

Eigen::MatrixX3f triangulateLinearTwoView(const Eigen::MatrixX4f &st_points,
                                          const Eigen::MatrixX4f &nd_points,
                                          const Eigen::Matrix4f &st_view,
                                          const Eigen::Matrix4f &nd_view);

Eigen::Vector3f
triangulateLinearMultiView(const std::vector<Eigen::Vector2f> &camera_points,
                           const std::vector<Eigen::Matrix4f> &views);

} // namespace mts

#endif // !TRIANGULATION_H