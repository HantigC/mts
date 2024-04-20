#ifndef VISUALIZATION_CAMERA_H
#define VISUALIZATION_CAMERA_H
#include <Eigen/Core>

namespace mts {
void drawCameraAxes(const Eigen::Vector3f& position,
                    const Eigen::Vector3f& xaxis,
                    const Eigen::Vector3f& yaxis,
                    const Eigen::Vector3f& zaxis,
                    const Eigen::Vector3f& xrgb,
                    const Eigen::Vector3f& yrgb,
                    const Eigen::Vector3f& zrgb,
                    float scale = 0.1);


void drawCameraAxes(const Eigen::Vector3f& position,
                    const Eigen::Vector3f& xaxis,
                    const Eigen::Vector3f& yaxis,
                    const Eigen::Vector3f& zaxis,
                    float scale = 0.1);



}  // namespace mts

#endif  // !VISUALIZATION_CAMERA_H