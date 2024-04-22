#include <opencv2/core/hal/interface.h>
#include <pangolin/gl/opengl_render_state.h>
#include <pangolin/pangolin.h>
#include <unistd.h>

#include <Eigen/Core>
#include <algorithm>
#include <atomic>
#include <cstddef>
#include <iostream>
#include <memory>
#include <opencv2/calib3d.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/base.hpp>
#include <opencv2/core/cvstd_wrapper.hpp>
#include <opencv2/core/eigen.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/matx.hpp>
#include <opencv2/core/operations.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <ostream>
#include <string>
#include <vector>

#include "camera.h"
#include "epipolar/draw.h"
#include "geometry/epipolar.h"
#include "geometry/triangulation.h"
#include "keypoint/draw.h"
#include "opencvx.h"
#include "render/model/base.h"
#include "render/model/camera.h"
#include "sfm.h"
#include "visualization/camera.h"

void draw(const std::vector<std::shared_ptr<mts::BaseModel>>& models);
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
    mts::Camera cam6 = sfm.cameras_.at(6);
    mts::Camera cam3 = sfm.cameras_.at(3);

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

    mts::triangulateLinearTwoView(p1, p2, view1, view2);
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
    cv::Mat mask;
    auto F = cv::findFundamentalMat(st_pts, nd_pts, mask);
    Eigen::Matrix3f eF;

    cv::cv2eigen(F, eF);
    auto eE = mts::computeEssentialMatrix(cam6.intrinsicMatrix, eF, cam3.intrinsicMatrix);
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
    Eigen::Matrix4f view1_e = mts::Camera::viewFromRt(R1_e, t_e);
    Eigen::Matrix4f view2_e = mts::Camera::viewFromRt(R2_e, t_e);
    Eigen::Matrix4f view3_e = mts::Camera::viewFromRt(R1_e, -t_e);
    Eigen::Matrix4f view4_e = mts::Camera::viewFromRt(R2_e, -t_e);

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
    models.push_back(camModel2_p);
    models.push_back(camModel3_p);
    models.push_back(camModel4_p);

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
    draw(models);

    return 0;
}

void draw(const std::vector<std::shared_ptr<mts::BaseModel>>& models) {
    pangolin::CreateWindowAndBind("Main", 640, 480);
    glEnable(GL_DEPTH_TEST);

    // Define Projection and initial ModelView matrix
    pangolin::OpenGlRenderState s_cam(
        pangolin::ProjectionMatrix(640, 480, 420, 420, 320, 240, 0.2, 100),
        pangolin::ModelViewLookAt(-2, 2, -2, 0, 0, 0, pangolin::AxisZ));

    // Create Interactive View in window
    pangolin::Handler3D handler(s_cam);
    pangolin::View& d_cam = pangolin::CreateDisplay()
                                .SetBounds(0.0, 1.0, 0.0, 1.0, -640.0f / 480.0f)
                                .SetHandler(&handler);

    while (!pangolin::ShouldQuit()) {
        // Clear screen and activate view to render into
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        d_cam.Activate(s_cam);
        for (auto& model : models) {
            model->draw();
        }

        // Render OpenGL Cube
        // pangolin::glDrawColouredCube();

        // Swap frames and Process Events
        pangolin::FinishFrame();
    }
}
