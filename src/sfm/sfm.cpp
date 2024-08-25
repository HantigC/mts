#include "sfm/sfm.h"

#include <opencv2/core.hpp>
#include <vector>

#include "geometry/essential.h"
#include "geometry/fundamental.h"
#include "geometry/pose.h"
#include "geometry/rigid3d.h"
#include "keypoint/keypoint.h"
#include "match/match.h"
#include "model/camera.h"
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

    Eigen::Array<unsigned int, Eigen::Dynamic, 1> stMathces = matches.col(0).array();
    Eigen::Array<unsigned int, Eigen::Dynamic, 1> ndMathces = matches.col(1).array();

    Eigen::MatrixX2f stKeypoints = stKeypointDescriptor.keypoints(stMathces, Eigen::all);
    Eigen::MatrixX2f ndKeypoints = ndKeypointDescriptor.keypoints(ndMathces, Eigen::all);
    Eigen::VectorXi mask;

    auto F = mts::computeFundamentalMatrix(stKeypoints, ndKeypoints, mask);

    auto E = mts::computeEssentialMatrix(stImage.camera->K, F, ndImage.camera->K);
    Eigen::Matrix3f R;
    Eigen::Vector3f t;
    std::vector<Eigen::Vector3f> points3D;

    auto stCameraKeypoints =
        mts::Camera::fromImageToCamera(stImage.camera->K, stKeypoints);
    auto ndCameraKeypoints =
        mts::Camera::fromImageToCamera(ndImage.camera->K, ndKeypoints);

    mts::poseFromEssential<3>(E, stCameraKeypoints, ndCameraKeypoints, &R, &t, &points3D);
    std::vector<mts::Image> images{stImage, ndImage};
    std::vector<mts::Rigid3D> poses{mts::Rigid3D(), mts::Rigid3D(R, t)};

    mts::Scene scene(images, points3D, poses);
    return scene;
}

    mts::Scene SfM::reconstructMultipleView(std::vector<mts::Image> &images){
        // findInitialPairs
        // findNextImage
        // compute rigid
        //
        // global refinment

    }

}  // namespace mts