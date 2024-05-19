#include "camera.h"

#include <fstream>
#include <iostream>
#include <ostream>
#include <vector>
#include <Eigen/LU>

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
    this->K = readIntrinsecMatrix(intrinsecMatrixFilename);
    this->image = image;
}

Camera::Camera(const std::string& intrinsecMatrixFilename) {
    this->K = readIntrinsecMatrix(intrinsecMatrixFilename);
}

Camera::Camera(const std::string& imageFilename,
               const std::string& intrinsecMatrixFilename) {
    this->K = readIntrinsecMatrix(intrinsecMatrixFilename);
    this->image = cv::imread(imageFilename);
}

void Camera::loadImage(const std::string& imagePath) {
    this->image = cv::imread(imagePath);
}
void Camera::loadK(const std::string& kPath) { this->K = readIntrinsecMatrix(kPath); }

// STATIC
Eigen::Matrix4f Camera::viewFromRt(const Eigen::Matrix3f& R, const Eigen::Vector3f& t) {
    Eigen::Matrix4f view;
    view.block<3, 3>(0, 0) = R;
    view.block<3, 1>(0, 3) = t;
    view.block<1, 4>(3, 0) << 0.0f, 0.0f, 0.0f, 1.0f;
    std::cout << "rotation" << std::endl << R << std::endl;
    std::cout << "t" << std::endl << t << std::endl;
    std::cout << "view" << std::endl << view << std::endl;
    return view;
}

std::vector<Eigen::Vector3f> Camera::fromImageToCamera(
    std::vector<Eigen::Vector2f>& pts) {
    return Camera::fromImageToCamera(K, pts);
}
Eigen::Vector3f Camera::fromImageToCamera(Eigen::Vector2f& pt) {
    return Camera::fromImageToCamera(K, pt);
}

void fromImageToCamera_(const Eigen::Matrix3f& K, Eigen::Vector3f& pt) {}
void fromImageToCamera_(const Eigen::Matrix3f& K, std::vector<Eigen::Vector3f>& pts) {}

Eigen::Vector3f Camera::fromImageToCamera(const Eigen::Matrix3f& K, Eigen::Vector2f& pt) {
    Eigen::Vector3f cameraPts = {pt.x(), pt.y(), 1.0f};
    cameraPts = K.inverse() * cameraPts;
    return cameraPts;
}

std::vector<Eigen::Vector3f> Camera::fromImageToCamera(const Eigen::Matrix3f& K,
                                               std::vector<Eigen::Vector2f>& pts) {
    std::vector<Eigen::Vector3f> cameraPts;
    cameraPts.reserve(pts.size());
    Eigen::Matrix3f Kinv = K.inverse();
    Eigen::Vector3f ptH;

    for (auto& pt : pts) {
        ptH = {pt.x(), pt.y(), 1.0f};
        cameraPts.push_back(Kinv * ptH);
    }
    return cameraPts;
}
}  // namespace mts
