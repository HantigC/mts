#include "geometry/fundamental.h"

#include <opencv2/core/eigen.hpp>
#include <opencv2/opencv.hpp>

namespace mts {

Eigen::Matrix3f computeFundamentalMatrix(Eigen::MatrixX2f& stPoints,
                                         Eigen::MatrixX2f& ndPoints) {
    cv::Mat stPoints_cv;
    cv::Mat ndPoints_cv;

    cv::eigen2cv(stPoints, stPoints_cv);
    cv::eigen2cv(ndPoints, ndPoints_cv);

    auto F_cv = cv::findFundamentalMat(stPoints_cv, ndPoints_cv);
    Eigen::Matrix3f F;
    cv::cv2eigen(F_cv, F);

    return F;
}

}  // namespace mts