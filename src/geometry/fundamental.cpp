#include "geometry/fundamental.h"

#include <opencv2/calib3d.hpp>
#include <opencv2/core/eigen.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/opencv.hpp>

namespace mts {

Eigen::Matrix3f computeFundamentalMatrix(Eigen::MatrixX2f& stPoints,
                                         Eigen::MatrixX2f& ndPoints,
                                         Eigen::VectorXi& mask) {
    cv::Mat stPoints_cv;
    cv::Mat ndPoints_cv;

    cv::eigen2cv(stPoints, stPoints_cv);
    cv::eigen2cv(ndPoints, ndPoints_cv);
    cv::Mat mask_cv;

    auto F_cv = cv::findFundamentalMat(
        stPoints_cv, ndPoints_cv, cv::FM_RANSAC, 3.0f, 0.99, mask_cv);

    cv::cv2eigen(mask_cv, mask);

    Eigen::Matrix3f F;
    cv::cv2eigen(F_cv, F);

    return F;
}

}  // namespace mts