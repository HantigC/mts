#ifndef EPIPOLAR_DRAW_H
#define EPIPOLAR_DRAW_H
#include <opencv2/opencv.hpp>

namespace mts {
void drawEpilines(cv::Mat img,
                  std::vector<cv::Vec3f> lines,
                  const cv::Scalar &color);
}

#endif // !EPIPOLAR_DRAW_H