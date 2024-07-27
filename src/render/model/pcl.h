#ifndef RENDER_MODEL_PCL_H
#define RENDER_MODEL_PCL_H
#include <Eigen/Core>
#include <memory>
#include <vector>

#include "render/model/base.h"

namespace mts {
namespace render {

class Pcl : public BaseModel {
   public:
    Pcl();
    Pcl(const std::vector<Eigen::Vector3f>& points);
    Pcl(const std::vector<Eigen::Vector3f>& points,
        const std::vector<Eigen::Vector3f>& colors);
    void draw() override;
    std::vector<Eigen::Vector3f> points;
    std::vector<Eigen::Vector3f> colors;
    static void draw_points(std::vector<Eigen::Vector3f>& points, Eigen::Vector3f& color);
    static void draw_points(std::vector<Eigen::Vector3f>& points,
                            std::vector<Eigen::Vector3f>& colors);
};

}  // namespace render

}  // namespace mts

#endif  // !RENDER_MODEL_PCL_H