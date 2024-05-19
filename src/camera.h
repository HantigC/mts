#ifndef CAMERA_H
#define CAMERA_H
#include <string.h>

#include <Eigen/Core>
#include <opencv2/opencv.hpp>
#include <vector>

namespace mts {
class Camera {
   public:
    void loadImage(const std::string& imagePath);
    void loadK(const std::string& imagePath);

    Camera(){};
    Camera(const std::string& intrinsecMatrixFilename, cv::Mat image);
    Camera(const std::string& intrinsecMatrixFilename);
    Camera(const std::string& imageFilename, const std::string& intrinsecMatrixFilename);
    Eigen::Matrix3f K;
    Eigen::Vector3f position;
    Eigen::Vector3f direction;
    cv::Mat image;

    std::vector<Eigen::Vector3f> fromImageToCamera(std::vector<Eigen::Vector2f>& pts);
    Eigen::Vector3f fromImageToCamera(Eigen::Vector2f& pts);

    // STATIC

    static Eigen::Matrix4f viewFromRt(const Eigen::Matrix3f& R, const Eigen::Vector3f& t);

    static void fromImageToCamera_(const Eigen::Matrix3f& K, Eigen::Vector3f& pt);
    static void fromImageToCamera_(const Eigen::Matrix3f& K,
                                   std::vector<Eigen::Vector3f>& pts);

    static Eigen::Vector3f fromImageToCamera(const Eigen::Matrix3f& K,
                                             Eigen::Vector2f& pt);
    static std::vector<Eigen::Vector3f> fromImageToCamera(
        const Eigen::Matrix3f& K, std::vector<Eigen::Vector2f>& pts);
};

Eigen::Matrix<float, 3, 3> readIntrinsecMatrix(const std::string& matrixFilename);

}  // namespace mts
#endif /*CAMERA_H*/