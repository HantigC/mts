#include "epipolar/epipolar.h"

Eigen::Matrix3f computeEssentialMatrix(Eigen::Matrix3f &st_intrinsectMatrix,
                                       Eigen::Matrix3f &fundamentalMatrix,
                                       Eigen::Matrix3f &nd_intrinsectMatrix) {
    return st_intrinsectMatrix.transpose() * fundamentalMatrix *
           nd_intrinsectMatrix;
}

cv::Mat computeEssentialMatrix(cv::Mat &st_intrinsectMatrix,
                               cv::Mat &fundamentalMatrix,
                               cv::Mat &nd_intrinsectMatrix) {
    return st_intrinsectMatrix.t() * fundamentalMatrix * nd_intrinsectMatrix;
}