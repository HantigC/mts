#include "camera.h"
#include "opencvx.h"
#include <Eigen/Core>
#include <algorithm>
#include <atomic>
#include <cstddef>
#include <iostream>
#include <opencv2/calib3d.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/base.hpp>
#include <opencv2/core/cvstd_wrapper.hpp>
#include <opencv2/core/hal/interface.h>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/matx.hpp>
#include <opencv2/core/operations.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <ostream>
#include <pangolin/pangolin.h>
#include <string>
#include <unistd.h>
#include <vector>
#include <opencv2/core/eigen.hpp>
#include "epipolar/epipolar.h"
#include "epipolar/draw.h"
#include "keypoint/draw.h"
#include "sfm.h"



void draw();
int main(int argc, char *argv[]) {
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
    // cv::Mat st_img = cv::imread("./resources/fountain/images/0006.png");
    // cv::Mat nd_img = cv::imread("./resources/fountain/images/0003.png");
    // cv::Ptr<cv::SiftFeatureDetector> detector =
    //     cv::SiftFeatureDetector::create();
    // std::vector<cv::KeyPoint> nd_kps;
    // std::vector<cv::KeyPoint> st_kps;
    // cv::Mat st_descriptors;
    // cv::Mat nd_descriptors;
    // Eigen::Matrix3f st_intrinsectMatrix =
    //     mts::readIntrinsecMatrix("./resources/fountain/K/0006.k");
    // Eigen::Matrix3f nd_intrinsectMatrix =
    //     mts::readIntrinsecMatrix("./resources/fountain/K/0003.k");

    // mts::Camera justACamera = mts::Camera("./resources/fountain/K/0000.k");
    // // std::cout << "intrinsic matrix: " << st_intrinsectMatrix << std::endl;
    // detector->detectAndCompute(st_img, cv::Mat(), st_kps, st_descriptors);
    // detector->detectAndCompute(nd_img, cv::Mat(), nd_kps, nd_descriptors);
    // cv::Mat nd_output;
    // cv::drawKeypoints(nd_img,
    //                   st_kps,
    //                   nd_output,
    //                   cv::Scalar::all(-1),
    //                   cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    // cv::Mat st_output;
    // cv::drawKeypoints(st_img,
    //                   st_kps,
    //                   st_output,
    //                   cv::Scalar::all(-1),
    //                   cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    // std::vector<std::vector<cv::DMatch>> knnMatches;
    // cv::BFMatcher matcher(cv::NORM_L2);
    // matcher.knnMatch(st_descriptors, nd_descriptors, knnMatches, 2);
    // std::sort(knnMatches.begin(), knnMatches.end());
    // std::vector<cv::DMatch> goodMatches;
    // std::vector<cv::Point2f> st_pts;
    // std::vector<cv::Point2f> nd_pts;
    // const float ratio_tresh = 0.5f;
    // for (size_t i = 0; i < knnMatches.size(); i++) {
    //     if (knnMatches[i][0].distance <
    //         ratio_tresh * knnMatches[i][1].distance) {
    //         st_pts.push_back(st_kps[knnMatches[i][0].queryIdx].pt);
    //         nd_pts.push_back(nd_kps[knnMatches[i][0].trainIdx].pt);
    //         goodMatches.push_back(knnMatches[i][0]);
    //     }
    // }

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
    // draw();

    return 0;
}

void draw() {
    pangolin::CreateWindowAndBind("Main", 640, 480);
    glEnable(GL_DEPTH_TEST);

    // Define Projection and initial ModelView matrix
    pangolin::OpenGlRenderState s_cam(
        pangolin::ProjectionMatrix(640, 480, 420, 420, 320, 240, 0.2, 100),
        pangolin::ModelViewLookAt(-2, 2, -2, 0, 0, 0, pangolin::AxisY));

    // Create Interactive View in window
    pangolin::Handler3D handler(s_cam);
    pangolin::View &d_cam = pangolin::CreateDisplay()
                                .SetBounds(0.0, 1.0, 0.0, 1.0, -640.0f / 480.0f)
                                .SetHandler(&handler);

    while (!pangolin::ShouldQuit()) {
        // Clear screen and activate view to render into
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        d_cam.Activate(s_cam);

        // Render OpenGL Cube
        pangolin::glDrawColouredCube();

        // Swap frames and Process Events
        pangolin::FinishFrame();
    }
}
