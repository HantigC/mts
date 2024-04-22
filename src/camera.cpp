#include "camera.h"

#include <fstream>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>

namespace mts {

Eigen::Matrix<float, 3, 3> readIntrinsecMatrix(const std::string& matrixFilename) {
    std::ifstream inStream(matrixFilename);
    float x;
    std::vector<float> data;
    while (inStream >> x) {
        data.push_back(x);
    }
    return Eigen::Matrix<float, 3, 3, Eigen::RowMajor>(data.data());
}

Camera::Camera(const std::string& intrinsecMatrixFilename, cv::Mat image) {
    this->intrinsicMatrix = readIntrinsecMatrix(intrinsecMatrixFilename);
    this->image = image;
}

Camera::Camera(const std::string& intrinsecMatrixFilename) {
    this->intrinsicMatrix = readIntrinsecMatrix(intrinsecMatrixFilename);
}

Camera::Camera(const std::string& imageFilename,
               const std::string& intrinsecMatrixFilename) {
    this->intrinsicMatrix = readIntrinsecMatrix(intrinsecMatrixFilename);
    this->image = cv::imread(imageFilename);
}

void Camera::loadImage(const std::string& imagePath) {
    this->image = cv::imread(imagePath);
}
void Camera::loadK(const std::string& kPath) {
    this->intrinsicMatrix = readIntrinsecMatrix(kPath);
}

Eigen::Matrix4f Camera::viewFromRt(const Eigen::Matrix3f& R, const Eigen::Vector3f& t) {
    Eigen::Matrix4f view;
    view.block<3, 3>(0, 0) = R;
    view.block<3, 1>(0, 3) = t;
    view(3,3) = 1.0f;
    return view;
}
}  // namespace mts
