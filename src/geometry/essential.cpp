#include "geometry/essential.h"

#include <opencv2/core/eigen.hpp>

namespace mts {

Eigen::Matrix3f computeEssentialMatrix(Eigen::Matrix3f& st_intrinsectMatrix,
                                       Eigen::Matrix3f& fundamentalMatrix,
                                       Eigen::Matrix3f& nd_intrinsectMatrix) {
    return st_intrinsectMatrix.transpose() * fundamentalMatrix * nd_intrinsectMatrix;
}

cv::Mat computeEssentialMatrix(cv::Mat& st_intrinsectMatrix,
                               cv::Mat& fundamentalMatrix,
                               cv::Mat& nd_intrinsectMatrix) {
    return st_intrinsectMatrix.t() * fundamentalMatrix * nd_intrinsectMatrix;
}
void decomposeEssentialRt(Eigen::Matrix3f& essentialMatrix,
                          Eigen::Matrix3f& stRotationMatrix,
                          Eigen::Matrix3f& ndRotationMatrix,
                          Eigen::Vector3f& translation) {
    cv::Mat E, R1, R2;
    cv::Vec3f t;
    cv::eigen2cv(essentialMatrix, E);
    cv::decomposeEssentialMat(E, R1, R2, t);
    cv::cv2eigen(R1, stRotationMatrix);
    cv::cv2eigen(R2, ndRotationMatrix);
    cv::cv2eigen(t, translation);
}
}  // namespace mts