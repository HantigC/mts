#include "sfm/sfm.h"

#include <opencv2/core.hpp>
#include <vector>

#include "geometry/essential.h"
#include "geometry/fundamental.h"
#include "geometry/pose.h"
#include "geometry/rigid3d.h"
#include "keypoint/keypoint.h"
#include "match/match.h"
#include "model/image.h"
#include "scene/scene.h"

namespace mts {
mts::Scene SfM::reconstructTwoView(mts::Image stImage, mts::Image ndImage) {
    auto stKeypointDescriptor =
        keypointExtractor->computeKeypointDescriptor(stImage.image);
    auto ndKeypointDescriptor =
        keypointExtractor->computeKeypointDescriptor(ndImage.image);

    Matches matches;
    matcher->match(
        stKeypointDescriptor.descriptors, ndKeypointDescriptor.descriptors, matches);

    matches(0);
    Eigen::Array<unsigned int, Eigen::Dynamic, 1> stMathces = matches.col(0).array();
    Eigen::Array<unsigned int, Eigen::Dynamic, 1> ndMathces = matches.col(1).array();
    stMathces(0);
    ndMathces(0);

    Eigen::MatrixX2f stKeypoints = stKeypointDescriptor.keypoints(stMathces, Eigen::all);
    Eigen::MatrixX2f ndKeypoints = ndKeypointDescriptor.keypoints(ndMathces, Eigen::all);
    Eigen::VectorXi mask;

    auto F = mts::computeFundamentalMatrix(stKeypoints, ndKeypoints, mask);
    mask(0);

    auto E = mts::computeEssentialMatrix(stImage.camera->K, F, ndImage.camera->K);
    Eigen::Matrix3f R;
    Eigen::Vector3f t;
    std::vector<Eigen::Vector3f> points3D;

    mts::poseFromEssential<2>(E, stKeypoints, ndKeypoints, &R, &t, &points3D);
    std::vector<mts::Image> images{stImage, ndImage};
    std::vector<mts::Rigid3D> poses{mts::Rigid3D(), mts::Rigid3D(R, t)};

    mts::Scene scene(images, points3D, poses);
    return scene;
}
}  // namespace mts