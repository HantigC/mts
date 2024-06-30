#ifndef GEOMETRY_ESSENTIAL_H
#define GEOMETRY_ESSENTIAL_H

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

void decomposeEssentialRt(Eigen::Matrix3f& essentialMatrix,
                          Eigen::Matrix3f& rotationMatrix1,
                          Eigen::Matrix3f& rotationMatrix2,
                          Eigen::Vector3f& translation);

}  // namespace mts
#endif  // !GEOMETRY_ESSENTIAL_H