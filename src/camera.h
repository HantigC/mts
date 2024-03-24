#ifndef CAMERA_H
#define CAMERA_H
#include <Eigen/Core>
#include <opencv2/opencv.hpp>
#include <string.h>

namespace mts {
class Camera {
  public:
    void loadImage(const std::string &imagePath);
    void loadK(const std::string &imagePath);

    Camera(){};
    Camera(const std::string &intrinsecMatrixFilename, cv::Mat image);
    Camera(const std::string &intrinsecMatrixFilename);
    Camera(const std::string &imageFilename,
           const std::string &intrinsecMatrixFilename);
    Eigen::Matrix<float, 3, 3> intrinsicMatrix;
    Eigen::Vector<float, 3> position;
    Eigen::Vector<float, 3> direction;
    cv::Mat image;
};

Eigen::Matrix<float, 3, 3>
readIntrinsecMatrix(const std::string &matrixFilename);

} // namespace mts
#endif /*CAMERA_H*/