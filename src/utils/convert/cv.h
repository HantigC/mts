#ifndef UTILS_CONVERT_CV_H
#define UTILS_CONVERT_CV_H
#include <Eigen/Core>
#include <cstddef>
#include <opencv2/opencv.hpp>
#include <vector>
namespace mts {

Eigen::Vector2f cvToEigen(cv::Point2f);
Eigen::Vector3f cvToEigen(cv::Vec3b);
std::vector<Eigen::Vector2f> cvToEigen(std::vector<cv::Point2f> &pts);
std::vector<Eigen::Vector3f> cvToEigen(std::vector<cv::Vec3b> &pts);
}  // namespace mts

#endif  // !UTILS_CONVERT_CV_H