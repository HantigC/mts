#include "opencvx.h"
#include <fstream>
#include <iostream>
#include <opencv2/core/eigen.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/opencv.hpp>
#include <ostream>
#include <vector>

namespace mts {
namespace cvx {
cv::Mat readIntrinsecMatrix(const std::string &matrixFilename) {
    std::ifstream inStream(matrixFilename);
    float *xs = new float[9];
    for (int i = 0; i < 9; i++) {
        inStream >> xs[i];
    }

    cv::Mat intrisecMatrix = cv::Mat(3, 3, CV_32F, xs);
    return intrisecMatrix;
}

Eigen::MatrixXd convertToEigen(cv::Mat &mat) {
    Eigen::MatrixXd m;
    cv::cv2eigen(mat, m);
    return m;
}
} // namespace cvx

} // namespace mts