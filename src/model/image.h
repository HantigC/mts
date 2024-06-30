#ifndef MODEL_IMAGE_H
#define MODEL_IMAGE_H

#include <Eigen/Core>
#include <memory>
#include <opencv2/core/mat.hpp>
#include <opencv2/opencv.hpp>

#include "geometry/rigid3d.h"
#include "model/camera.h"
#include "model/keypoint.h"

namespace mts {
class Image {
   public:
    Image(){};
    Image(const cv::Mat& image, const Eigen::Matrix3f& R, const Eigen::Vector3f& t)
        : image(image) {
        rigid3d = mts::Rigid3D(R, t);
    }
    Image(const cv::Mat& image,
          const Eigen::Matrix3f& R,
          const Eigen::Vector3f& t,
          std::shared_ptr<mts::Camera>& camera)
        : image(image), camera(camera) {
        rigid3d = mts::Rigid3D(R, t);
    }

    Image(const cv::Mat& image, std::shared_ptr<mts::Camera>& camera)
        : rigid3d(), image(image), camera(camera) {}

    Image(const cv::Mat&& image, std::shared_ptr<mts::Camera>&& camera)
        : rigid3d(), image(image), camera(camera) {}

    bool hasKeypoints();
    bool hasDescriptors();

    mts::Rigid3D rigid3d;
    cv::Mat image;
    std::shared_ptr<mts::Camera> camera;
    KeypointDescriptor KeypointDescriptor;
};

}  // namespace mts

#endif  // !MODEL_IMAGE_H