#ifndef UTILS_CONVERT_CV_H
#define UTILS_CONVERT_CV_H
#include <Eigen/Core>
#include <cstddef>
#include <opencv2/core/mat.hpp>
#include <opencv2/opencv.hpp>
#include <vector>

Eigen::Vector2f cvToEigen(cv::Point2f);
std::vector<Eigen::Vector2f> cvToEigen(std::vector<cv::Point2f>);

template <typename Scalar, size_t Rows, size_t Cols>
Eigen::Matrix<Scalar, Rows, Cols> cvToEigen(const cv::Mat& mat);

#endif  // !UTILS_CONVERT_CV_H