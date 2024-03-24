#include "epipolar/draw.h"
namespace mts {

void drawEpilines(cv::Mat img,
                  std::vector<cv::Vec3f> lines,
                  const cv::Scalar &color) {
    cv::Point2d pt1, pt2;
    float st_x = 0.0f, nd_x = static_cast<float>(img.cols - 1);
    pt1.x = st_x;
    pt2.x = nd_x;
    for (auto &line : lines) {
        pt1.y = -line[2] / line[1];
        pt2.y = -(line[2] + line[0] * nd_x) / line[1];

        cv::line(img, pt1, pt2, color);
    }
}
} // namespace mts