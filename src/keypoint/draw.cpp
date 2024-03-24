#include "keypoint/draw.h"

namespace mts {

void drawPoints(cv::Mat img,
                std::vector<cv::Point2f> points,
                const cv::Scalar &color) {
    for (auto &point : points) {
        cv::circle(img, point, 3, color, -1);
    }
}
} // namespace mts