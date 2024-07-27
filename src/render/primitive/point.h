#ifndef RENDER_PRIMITIVE_POINT_H
#define RENDER_PRIMITIVE_POINT_H

#include <Eigen/Core>
namespace mts {
namespace render {
void drawPoints(std::vector<Eigen::Vector3f>& points,
                 std::vector<Eigen::Vector3f>& colors);

void drawPoints(std::vector<Eigen::Vector3f>& points, Eigen::Vector3f& color);

}  // namespace render
}  // namespace mts
#endif  // !RENDER_PRIMITIVE_POINT_H