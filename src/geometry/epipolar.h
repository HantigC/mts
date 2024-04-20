#ifndef EPIPOLAR_H
#define EPIPOLAR_H
#include <Eigen/Core>
#include <opencv2/opencv.hpp>
#include <vector>

namespace mts {

Eigen::Matrix3f computeEssentialMatrix(Eigen::Matrix3f& st_intrinsectMatrix,
                                       Eigen::Matrix3f& fundamentalMatrix,
                                       Eigen::Matrix3f& nd_intrinsectMatrix);

cv::Mat computeEssentialMatrix(cv::Mat& st_intrinsectMatrix,
                               cv::Mat& fundamentalMatrix,
                               cv::Mat& nd_intrinsectMatrix);

void extractRtFromEssentialMatrix(Eigen::Matrix3f& essentialMatrix,
                                  Eigen::Matrix3f& rotationMatrix1,
                                  Eigen::Matrix3f& rotationMatrix2,
                                  Eigen::Vector3f& translation);

Eigen::Matrix3f computeFundamentalMatrix(Eigen::MatrixX2f& points1,
                                         Eigen::MatrixX2f& points2);

Eigen::Matrix3f computeFundamentalMatrix(std::vector<Eigen::Vector2f>& points1,
                                         std::vector<Eigen::Vector2f>& points2);

}  // namespace mts
#endif  // !EPIPOLAR_H