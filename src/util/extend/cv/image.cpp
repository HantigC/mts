#include "util/extend/cv/image.h"

#include <opencv2/opencv.hpp>
#include <vector>

namespace mts {

std::vector<cv::Vec3b> getRGBAt(cv::Mat& img, std::vector<Eigen::Vector2f>& pts) {
    int x, y;
    std::vector<cv::Vec3b> rgbs;
    rgbs.reserve(pts.size());
    for (auto& pt : pts) {
        x = static_cast<int>(pt.x());
        y = static_cast<int>(pt.y());
        rgbs.push_back(img.at<cv::Vec3b>(y, x));
    }
    return rgbs;
}
} // namespace mts