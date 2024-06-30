#ifndef KEYPOINT_SIFT_H
#define KEYPOINT_SIFT_H
#include "keypoint/keypoint.h"
namespace mts {
class SiftExtractor : public KeypointExtractor {
   public:
    SiftExtractor(int nfeatures = 0,
                  int nOctaveLayers = 3,
                  double contrastThreshold = 0.040000000000000001,
                  double edgeThreshold = 10,
                  double sigma = 1.6000000000000001,
                  bool enable_precise_upscale = false);
    Keypoints computeKeypoints(cv::Mat& image) override;
    Descriptors computeDescriptors(cv::Mat& image) override;
    KeypointDescriptor computeKeypointDescriptor(cv::Mat& image) override;
    int nfeatures = 0;
    int nOctaveLayers = 3;
    double contrastThreshold = 0.040000000000000001;
    double edgeThreshold = 10;
    double sigma = 1.6000000000000001;
    bool enable_precise_upscale = false;

   private:
    cv::Ptr<cv::SiftFeatureDetector> detector_;
};
}  // namespace mts

#endif  // !KEYPOINT_SIFT_H