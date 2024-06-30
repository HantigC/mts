#ifndef UTILS_EXTEND_CV_IMAGE_H
#define UTILS_EXTEND_CV_IMAGE_H

#include <opencv2/opencv.hpp>
#include <vector>
#include <Eigen/Core>

namespace mts {

std::vector<cv::Vec3b> getRGBAt(cv::Mat &img, std::vector<Eigen::Vector2f> &pts);
std::vector<cv::Vec3b> getRGBAt(cv::Mat &img, std::vector<cv::Vec2f> &pts);

} // namespace mts
#endif // !UTILS_EXTEND_CV_IMAGE_H