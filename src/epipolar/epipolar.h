#ifndef EPIPOLAR_H
#define EPIPOLAR_H
#include <Eigen/Core>
#include <opencv2/opencv.hpp>

Eigen::Matrix3f computeEssentialMatrix(Eigen::Matrix3f &st_intrinsectMatrix,
                                       Eigen::Matrix3f &fundamentalMatrix,
                                       Eigen::Matrix3f &nd_intrinsectMatrix);

cv::Mat computeEssentialMatrix(cv::Mat &st_intrinsectMatrix,
                               cv::Mat &fundamentalMatrix,
                               cv::Mat &nd_intrinsectMatrix);

#endif // !EPIPOLAR_H