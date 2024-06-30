#ifndef MODEL_KEYPOINT_H
#define MODEL_KEYPOINT_H

#include <Eigen/Core>

namespace mts {
typedef Eigen::Matrix<float, Eigen::Dynamic, 2> Keypoints;
typedef Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic> Descriptors;

class KeypointDescriptor {
   public:
    KeypointDescriptor() {}
    KeypointDescriptor(Keypoints& keypoints, Descriptors& descriptors)
        : descriptors(descriptors), keypoints(keypoints) {}

    KeypointDescriptor(Keypoints& keypoints) : keypoints(keypoints) {}

    Keypoints keypoints;
    Descriptors descriptors;
};
}  // namespace mts

#endif  // !MODEL_KEYPOINT_H