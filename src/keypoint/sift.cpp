#include "keypoint/sift.h"

#include <cstddef>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/core/eigen.hpp>
#include <vector>

#include "model/keypoint.h"

namespace mts {

void cvKeypointToEigen(std::vector<cv::KeyPoint>& keypoints,
                       Eigen::MatrixX2f& eigenKeypoints) {

    eigenKeypoints = Eigen::MatrixXf(keypoints.size(), 2);
    for (size_t i = 0; i < keypoints.size(); i++) {
        eigenKeypoints(i, 0) = keypoints.at(i).pt.x;
        eigenKeypoints(i, 1) = keypoints.at(i).pt.y;
    }
}

SiftExtractor::SiftExtractor(int nfeatures,
                             int nOctaveLayers,
                             double contrastThreshold,
                             double edgeThreshold,
                             double sigma,
                             bool enable_precise_upscale) {
    detector_ = cv::SiftFeatureDetector::create(nfeatures,
                                                nOctaveLayers,
                                                contrastThreshold,
                                                edgeThreshold,
                                                sigma,
                                                enable_precise_upscale);
}
Keypoints SiftExtractor::computeKeypoints(cv::Mat& image) {
    std::vector<cv::KeyPoint> kps;

    detector_->detect(image, kps, cv::Mat());
    Keypoints eigenKeypoints;
    cvKeypointToEigen(kps, eigenKeypoints);
    return eigenKeypoints;
}
Descriptors SiftExtractor::computeDescriptors(cv::Mat& image) {
    return Eigen::MatrixXf();
}
KeypointDescriptor SiftExtractor::computeKeypointDescriptor(cv::Mat& image) {
    std::vector<cv::KeyPoint> kps;
    cv::Mat descriptors;
    Eigen::MatrixXf eigenDescriptors;

    Keypoints eigenKeypoints;

    detector_->detectAndCompute(image, cv::Mat(), kps, descriptors);
    cvKeypointToEigen(kps, eigenKeypoints);
    cv::cv2eigen(descriptors, eigenDescriptors);
    return KeypointDescriptor(eigenKeypoints, eigenDescriptors);
}
}  // namespace mts