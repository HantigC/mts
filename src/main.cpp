#include <pangolin/gl/opengl_render_state.h>
#include <pangolin/pangolin.h>
#include <unistd.h>

#include <Eigen/Core>
#include <algorithm>
#include <atomic>
#include <cstddef>
#include <iostream>
#include <memory>
#include <opencv2/core/base.hpp>
#include <opencv2/core/eigen.hpp>
#include <opencv2/opencv.hpp>
#include <ostream>
#include <string>
#include <vector>

#include "epipolar/draw.h"
#include "geometry/epipolar.h"
#include "geometry/pose.h"
#include "geometry/triangulation.h"
#include "keypoint/draw.h"
#include "opencvx.h"
#include "render/model/base.h"
#include "render/model/camera.h"
#include "render/model/pcl.h"
#include "sfm/sfm.h"
#include "util/convert/cv.h"
#include "util/extend/cv/image.h"
#include "visualization/camera.h"

void draw(const std::vector<std::shared_ptr<mts::BaseModel>>& models,
          Eigen::Vector3f& position,
          Eigen::Vector3f& gaze);

int main(int argc, char* argv[]) {
    std::vector<std::string> imagePaths = {
        "./resources/fountain/images/0000.png",
        "./resources/fountain/images/0001.png",
        "./resources/fountain/images/0002.png",
        "./resources/fountain/images/0003.png",
        "./resources/fountain/images/0004.png",
        "./resources/fountain/images/0005.png",
        "./resources/fountain/images/0006.png",
        "./resources/fountain/images/0007.png",
        "./resources/fountain/images/0008.png",
        "./resources/fountain/images/0009.png",

    };

    std::vector<std::string> kPaths = {
        "./resources/fountain/K/0000.K",
        "./resources/fountain/K/0001.K",
        "./resources/fountain/K/0002.K",
        "./resources/fountain/K/0003.K",
        "./resources/fountain/K/0004.K",
        "./resources/fountain/K/0005.K",
        "./resources/fountain/K/0006.K",
        "./resources/fountain/K/0007.K",
        "./resources/fountain/K/0008.K",
        "./resources/fountain/K/0009.K",

    };
    mts::SfM sfm = {imagePaths, kPaths};
    sfm.loadData();
    std::cout << "fin" << std::endl;
    mts::Camera cam6 = sfm.cameras_.at(4);
    mts::Camera cam3 = sfm.cameras_.at(5);

    // cv::Mat st_img = cv::imread("./resources/fountain/images/0006.png");
    // cv::Mat nd_img = cv::imread("./resources/fountain/images/0003.png");
    cv::Ptr<cv::SiftFeatureDetector> detector = cv::SiftFeatureDetector::create();
    std::vector<cv::KeyPoint> nd_kps;
    std::vector<cv::KeyPoint> st_kps;
    cv::Mat st_descriptors;
    cv::Mat nd_descriptors;
    Eigen::Matrix3f st_intrinsectMatrix =
        mts::readIntrinsecMatrix("./resources/fountain/K/0006.k");
    Eigen::Matrix3f nd_intrinsectMatrix =
        mts::readIntrinsecMatrix("./resources/fountain/K/0003.k");

    // mts::Camera justACamera = mts::Camera("./resources/fountain/K/0000.k");
    // // std::cout << "intrinsic matrix: " << st_intrinsectMatrix << std::endl;
    detector->detectAndCompute(cam6.image, cv::Mat(), st_kps, st_descriptors);
    detector->detectAndCompute(cam3.image, cv::Mat(), nd_kps, nd_descriptors);
    cv::Mat nd_output;
    cv::drawKeypoints(cam3.image,
                      nd_kps,
                      nd_output,
                      cv::Scalar::all(-1),
                      cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    cv::Mat st_output;
    cv::drawKeypoints(cam6.image,
                      st_kps,
                      st_output,
                      cv::Scalar::all(-1),
                      cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

    Eigen::Vector2f p1(0.1, 0.2);
    Eigen::Vector2f p2(0.2, 0.2);
    Eigen::Matrix4f view1 = Eigen::Matrix4f::Identity();
    Eigen::Matrix4f view2 = Eigen::Matrix4f::Identity();

    std::vector<std::vector<cv::DMatch>> knnMatches;
    cv::BFMatcher matcher(cv::NORM_L2);
    matcher.knnMatch(st_descriptors, nd_descriptors, knnMatches, 2);
    std::sort(knnMatches.begin(), knnMatches.end());
    std::vector<cv::DMatch> goodMatches;
    std::vector<cv::Point2f> st_pts;
    std::vector<cv::Point2f> nd_pts;
    const float ratio_tresh = 0.5f;
    for (size_t i = 0; i < knnMatches.size(); i++) {
        if (knnMatches[i][0].distance < ratio_tresh * knnMatches[i][1].distance) {
            st_pts.push_back(st_kps[knnMatches[i][0].queryIdx].pt);
            nd_pts.push_back(nd_kps[knnMatches[i][0].trainIdx].pt);
            goodMatches.push_back(knnMatches[i][0]);
        }
    }
    std::vector<Eigen::Vector2f> st_pts_E = mts::cvToEigen(st_pts);
    std::vector<Eigen::Vector2f> nd_pts_E = mts::cvToEigen(nd_pts);

    auto stCameraPts = cam6.fromImageToCamera(st_pts_E);
    auto ndCameraPts = cam6.fromImageToCamera(nd_pts_E);

    auto st_rgbs = mts::getRGBAt(cam6.image, st_pts_E);
    auto nd_rgbs = mts::getRGBAt(cam6.image, st_pts_E);

    auto st_rgbs_e = mts::cvToEigen(st_rgbs);
    auto nd_rgbs_e = mts::cvToEigen(nd_rgbs);
    cv::Mat mask;
    auto F = cv::findFundamentalMat(st_pts, nd_pts, mask);
    Eigen::Matrix3f eF;

    cv::cv2eigen(F, eF);
    auto eE = mts::computeEssentialMatrix(cam6.K, eF, cam3.K);
    cv::Mat E;
    cv::eigen2cv(eE, E);
    std::cout << "Fundamental matrix" << std::endl << F << std::endl;
    std::cout << "Fundamental matrix Eigen" << std::endl << eF << std::endl;

    std::cout << "Essentianl matrix" << std::endl << E << std::endl;
    std::cout << "Essentianl matrix Eigen" << std::endl << eE << std::endl;
    cv::Mat R1, R2;
    Eigen::Matrix3f R1_e, R2_e;
    cv::Vec3f t;
    Eigen::Vector3f t_e;
    cv::decomposeEssentialMat(E, R1, R2, t);
    cv::cv2eigen(R1, R1_e);
    cv::cv2eigen(R2, R2_e);
    cv::cv2eigen(t, t_e);
    Eigen::Vector3f negT_e = -t_e;
    Eigen::Matrix4f view1_e = mts::Camera::viewFromRt(R1_e, t_e);
    Eigen::Matrix4f view2_e = mts::Camera::viewFromRt(R2_e, t_e);
    Eigen::Matrix4f view3_e = mts::Camera::viewFromRt(R1_e, -t_e);
    Eigen::Matrix4f view4_e = mts::Camera::viewFromRt(R2_e, -t_e);
    std::vector<Eigen::Vector3f> points3D;
    points3D.reserve(stCameraPts.size());
    mts::checkCheirality<3>(R1_e, t_e, stCameraPts, ndCameraPts, points3D);
    std::cout << "amouth R1, t: "  << points3D.size() << std::endl;
    mts::checkCheirality<3>(R2_e, t_e, stCameraPts, ndCameraPts, points3D);
    std::cout << "amouth R2, t: "  << points3D.size() << std::endl;
    mts::checkCheirality<3>(R1_e, negT_e, stCameraPts, ndCameraPts, points3D);
    std::cout << "amouth R1, -t: "  << points3D.size() << std::endl;
    mts::checkCheirality<3>(R2_e, negT_e, stCameraPts, ndCameraPts, points3D);
    std::cout << "amouth R1, -t: "  << points3D.size() << std::endl;
    std::vector<Eigen::Vector3f> points_3d_1 = mts::triangulateLinearTwoView<3>(
        stCameraPts, ndCameraPts, Eigen::Matrix4f::Identity(), view1_e);
    std::vector<Eigen::Vector3f> points_3d_2 = mts::triangulateLinearTwoView<3>(
        stCameraPts, ndCameraPts, Eigen::Matrix4f::Identity(), view2_e);
    std::vector<Eigen::Vector3f> points_3d_3 = mts::triangulateLinearTwoView<3>(
        stCameraPts, ndCameraPts, Eigen::Matrix4f::Identity(), view3_e);
    std::vector<Eigen::Vector3f> points_3d_4 = mts::triangulateLinearTwoView<3>(
        stCameraPts, ndCameraPts, Eigen::Matrix4f::Identity(), view4_e);

    mts::Pcl point_cloud1(points_3d_1, st_rgbs_e);
    mts::Pcl point_cloud2(points_3d_2, st_rgbs_e);
    mts::Pcl point_cloud3(points_3d_3, st_rgbs_e);
    mts::Pcl point_cloud4(points_3d_4, st_rgbs_e);
    std::shared_ptr<mts::BaseModel> point_cloud1_p =
        std::make_shared<mts::Pcl>(point_cloud1);

    std::shared_ptr<mts::BaseModel> point_cloud2_p =
        std::make_shared<mts::Pcl>(point_cloud2);

    std::shared_ptr<mts::BaseModel> point_cloud3_p =
        std::make_shared<mts::Pcl>(point_cloud3);

    std::shared_ptr<mts::BaseModel> point_cloud4_p =
        std::make_shared<mts::Pcl>(point_cloud4);

    mts::CameraModel camOrigin;
    auto camModel1 = mts::CameraModel(view1_e);
    auto camModel2 = mts::CameraModel(view2_e);
    auto camModel3 = mts::CameraModel(view3_e);
    auto camModel4 = mts::CameraModel(view4_e);
    std::shared_ptr<mts::BaseModel> camOrigin_p =
        std::make_shared<mts::CameraModel>(camOrigin);
    std::shared_ptr<mts::BaseModel> camModel1_p =
        std::make_shared<mts::CameraModel>(camModel1);
    std::shared_ptr<mts::BaseModel> camModel2_p =
        std::make_shared<mts::CameraModel>(camModel2);
    std::shared_ptr<mts::BaseModel> camModel3_p =
        std::make_shared<mts::CameraModel>(camModel3);
    std::shared_ptr<mts::BaseModel> camModel4_p =
        std::make_shared<mts::CameraModel>(camModel4);
    std::vector<std::shared_ptr<mts::BaseModel>> models;

    models.push_back(camOrigin_p);

    models.push_back(camModel1_p);
    models.push_back(point_cloud1_p);

    // models.push_back(camModel2_p);
    // models.push_back(point_cloud2_p);

    // models.push_back(camModel3_p);
    // models.push_back(point_cloud3_p);

    // models.push_back(camModel4_p);
    // models.push_back(point_cloud4_p);

    std::cout << camOrigin << std::endl;
    std::cout << "view no 1: " << view1_e << std::endl << std::endl;
    std::cout << "view no 2: " << view2_e << std::endl << std::endl;
    std::cout << "view no 3: " << view3_e << std::endl << std::endl;
    std::cout << "view no 4: " << view4_e << std::endl << std::endl;
    std::cout << camOrigin << std::endl;
    std::cout << "cam no 1: " << camModel1 << std::endl << std::endl;
    std::cout << "cam no 2: " << camModel2 << std::endl << std::endl;
    std::cout << "cam no 3: " << camModel3 << std::endl << std::endl;
    std::cout << "cam no 4: " << camModel4 << std::endl << std::endl;

    // cv::Mat mask;
    // auto F = cv::findFundamentalMat(st_pts, nd_pts, mask = mask);
    // Eigen::Matrix3f FEigen;
    // cv::cv2eigen(F, FEigen);
    // std::cout << "Fundamental matrix" << std::endl << F << std::endl;
    // std::cout << "Fundamental matrix" << std::endl << FEigen << std::endl;
    // auto E =
    //      computeEssentialMatrix(st_intrinsectMatrix, FEigen, nd_intrinsectMatrix);

    // std::cout << "Essential matrix" << std::endl << E << std::endl;

    // std::vector<cv::Point2f> filteredStPts;
    // std::vector<cv::Point2f> filteredNdPts;
    // for (size_t i = 0; i < mask.rows; i++) {
    //     if (mask.at<uchar>(i)) {
    //         filteredStPts.push_back(st_pts[i]);
    //         filteredNdPts.push_back(nd_pts[i]);
    //     }
    // }
    // auto K6 = mts::cvx::readIntrinsecMatrix("./resources/fountain/K/0006.k");
    // std::cout << "intrinsec matrix cv" << std::endl;
    // std::cout << cv::format(K6, cv::Formatter::FMT_NUMPY) << std::endl;
    // std::cout << std::endl;

    // // std::cout << "fundamental matrix is" << std::endl << F;
    // std::vector<cv::Vec3f> nd_lines;
    // std::vector<cv::Vec3f> st_lines;

    // cv::computeCorrespondEpilines(filteredStPts, 1, F, nd_lines);
    // cv::computeCorrespondEpilines(filteredNdPts, 2, F, st_lines);
    // cv::Mat imgMatches;
    // cv::drawMatches(st_img, st_kps, nd_img, nd_kps, goodMatches, imgMatches);
    // cv::Scalar c(0, 255, 0);
    // mts::drawEpilines(nd_img, nd_lines, c);
    // mts::drawPoints(nd_img, filteredNdPts, c);
    // mts::drawPoints(st_img, filteredStPts, c);
    // mts::drawEpilines(st_img, st_lines, c);

    // cv::imshow("st_kps", st_output);
    // cv::imshow("nd_kps", nd_output);
    // cv::imshow("Matches", imgMatches);
    // cv::imshow("img0", st_img);
    // cv::imshow("img1", nd_img);
    // cv::waitKey();
    Eigen::Vector3f origin(0.0f, 0.0f, 0.0f);
    Eigen::Vector3f forward(0.0f, 0.0f, 1.0f);
    origin = origin - 1.0f * forward;
    draw(models, origin, forward);

    return 0;
}


