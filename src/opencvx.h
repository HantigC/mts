#ifndef OPENCVX_H
#define OPENCVX_H
#include <opencv2/core/mat.hpp>
#include <string>
#include <Eigen/Core>


namespace mts {
namespace cvx {
cv::Mat readIntrinsecMatrix(const std::string &matrixFilename);
Eigen::MatrixXd convertToEigen(cv::Mat &mat);

}

} // namespace mts

#endif /*OPENCVX_H*/