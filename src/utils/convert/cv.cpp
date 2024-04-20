#include "utils/convert/cv.h"

#include <vector>

Eigen::Vector2f cvToEigen(cv::Point2f point2f) {
    return Eigen::Vector2f(point2f.x, point2f.y);
}

std::vector<Eigen::Vector2f> cvToEigen(std::vector<cv::Point2f> points2d) {
    std::vector<Eigen::Vector2f> points2d_eigen(points2d.size());
    for (auto point2d : points2d) {
        points2d_eigen.push_back(cvToEigen(point2d));
    }
    return points2d_eigen;
}



template <typename Scalar, size_t Rows, size_t Cols>
Eigen::Matrix< Scalar, Rows, Cols> cvToEigen(const cv::Mat &cvMat){
    Eigen::Matrix<Scalar, Rows, Cols> eigenMat;
    cvMat.rows == Rows;
    cvMat.cols == Cols;
}