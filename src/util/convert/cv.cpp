#include "util/convert/cv.h"

#include <opencv2/opencv.hpp>
#include <vector>

namespace mts {

Eigen::Vector2f cvToEigen(cv::Point2f point2f) {
    return Eigen::Vector2f(point2f.x, point2f.y);
}

Eigen::Vector3f cvToEigen(cv::Vec3b vec) {
    return {static_cast<float>(vec.val[0]),
            static_cast<float>(vec.val[1]),
            static_cast<float>(vec.val[2])};
}

std::vector<Eigen::Vector3f> cvToEigen(std::vector<cv::Vec3b> &pts) {
    std::vector<Eigen::Vector3f> pts_eigen;
    pts_eigen.reserve(pts.size());
    for (auto pt : pts) {
        pts_eigen.push_back(cvToEigen(pt));
    }
    return pts_eigen;
}

std::vector<Eigen::Vector2f> cvToEigen(std::vector<cv::Point2f> &points2d) {
    std::vector<Eigen::Vector2f> points2d_eigen;
    points2d_eigen.reserve(points2d.size());
    for (auto point2d : points2d) {
        points2d_eigen.push_back(cvToEigen(point2d));
    }
    return points2d_eigen;
}

}  // namespace mts