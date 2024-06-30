#ifndef KEYPOINT_KEYPOINT_H
#define KEYPOINT_KEYPOINT_H
#include <opencv2/opencv.hpp>

#include "model/keypoint.h"

namespace mts {
class KeypointExtractor {
   public:
    virtual ~KeypointExtractor() = default;
    virtual Keypoints computeKeypoints(cv::Mat& image) = 0;
    virtual Descriptors computeDescriptors(cv::Mat& image) = 0;
    virtual KeypointDescriptor computeKeypointDescriptor(cv::Mat& image) = 0;
};
}  // namespace mts

#endif  // !KEYPOINT_KEYPOINT_H