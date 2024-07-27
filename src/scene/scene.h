#ifndef SCENE_SCENE_H
#define SCENE_SCENE_H
#include <vector>

#include "geometry/rigid3d.h"
#include "model/image.h"
namespace mts {
class Scene {
   public:
    Scene(std::vector<mts::Image>& images, std::vector<Eigen::Vector3f>& points3D)
        : images(images), points3D(points3D) {}

    Scene(std::vector<mts::Image>& images,
          std::vector<Eigen::Vector3f>& points3D,
          std::vector<mts::Rigid3D>& poses)
        : images(images), points3D(points3D), poses(poses) {}

    std::vector<mts::Image> images;
    std::vector<mts::Rigid3D> poses;
    std::vector<Eigen::Vector3f> points3D;
};

}  // namespace mts

#endif  // !SCENE_SCENE_H