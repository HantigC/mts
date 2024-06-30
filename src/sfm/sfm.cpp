#include "sfm/sfm.h"
#include <opencv2/core.hpp>

#include "geometry/essential.h"
#include "geometry/fundamental.h"
#include "keypoint/keypoint.h"
#include "match/match.h"

namespace mts {
void SfM::reconstruct(mts::Image stImage, mts::Image ndImage) {
    auto stKeypointDescriptor =
        keypointExtractor->computeKeypointDescriptor(stImage.image);
    auto ndKeypointDescriptor =
        keypointExtractor->computeKeypointDescriptor(ndImage.image);

    Matches matches;
    matcher->match(
        stKeypointDescriptor.descriptors, ndKeypointDescriptor.descriptors, matches);

    Eigen::MatrixX2f stKeypoints =
        stKeypointDescriptor.keypoints(matches(Eigen::all, 0), Eigen::all);
    Eigen::MatrixX2f ndKeypoints =
        ndKeypointDescriptor.keypoints(matches(Eigen::all, 1), Eigen::all);

    auto F = mts::computeFundamentalMatrix(stKeypoints, ndKeypoints);

    auto E = mts::computeEssentialMatrix(stImage.camera->K, F, ndImage.camera->K);
    Eigen::Matrix3f R1, R2;
    Eigen::Vector3f t;
    mts::decomposeEssentialRt(E, R1, R2, t);
}
}  // namespace mts