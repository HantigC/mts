#ifndef KEYPOINT_DRAW_H
#define KEYPOINT_DRAW_H
#include <opencv2/opencv.hpp>

namespace mts {

void drawPoints(cv::Mat img,
                std::vector<cv::Point2f> points,
                const cv::Scalar &color);
}

#endif // !KEYPOINT_DRAW_H