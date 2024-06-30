#ifndef GEOMETRY_POSE_H
#define GEOMETRY_POSE_H
#include <Eigen/Eigen>
#include <vector>

#include "geometry/rigid3d.h"
#include "geometry/triangulation.h"

namespace mts {

float computeDepth(Eigen::Matrix3f& R, Eigen::Vector3f& t, Eigen::Vector3f& point3D);
float computeDepth(Eigen::Matrix4f& view, Eigen::Vector3f& point3D);

template <unsigned int T>
bool checkCheirality(Eigen::Matrix4f& stView,
                     Eigen::Matrix4f& ndView,
                     Eigen::Vector<float, T>& stPoint,
                     Eigen::Vector<float, T>& ndPoint,
                     Eigen::Vector3f& point3D) {
    Eigen::Vector3f point3D_;
    float stDepth, ndDepth;
    point3D_ = mts::triangulateLinearTwoView<T>(stPoint, ndPoint, stView, ndView);
    stDepth = computeDepth(stView, point3D_);
    if (stDepth < 0.0f) {
        return false;
    }
    ndDepth = computeDepth(ndView, point3D_);
    if (ndDepth < 0.0f) {
        return false;
    }
    point3D.x() = point3D_.x();
    point3D.y() = point3D_.y();
    point3D.z() = point3D_.z();
    return true;
}

template <unsigned int T>
bool checkCheirality(Eigen::Matrix4f& stView,
                     Eigen::Matrix4f& ndView,
                     std::vector<Eigen::Vector<float, T>>& stPoints,
                     std::vector<Eigen::Vector<float, T>>& ndPoints,
                     std::vector<Eigen::Vector3f>& points3D) {
    Eigen::Vector3f point3D;
    float stDepth, ndDepth;
    for (size_t i = 0; i < stPoints.size(); ++i) {
        point3D = mts::triangulateLinearTwoView<T>(
            stPoints.at(i), ndPoints.at(i), stView, ndView);
        stDepth = computeDepth(stView, point3D);
        if (stDepth < 0.0f) {
            continue;
        }
        ndDepth = computeDepth(ndView, point3D);
        if (ndDepth < 0.0f) {
            continue;
        }
        points3D.push_back(point3D);
    }
    return !points3D.empty();
}

template <unsigned int T>
bool checkCheirality(Eigen::Matrix3f& R,
                     Eigen::Vector3f& t,
                     std::vector<Eigen::Vector<float, T>>& stPoints,
                     std::vector<Eigen::Vector<float, T>>& ndPoints,
                     std::vector<Eigen::Vector3f>& points3D) {
    Eigen::Vector3f point3D;
    Eigen::Matrix4f eye = Eigen::Matrix4f::Identity();
    auto view = mts::Rigid3D::viewFromRt(R, t);
    float stDepth, ndDepth;
    for (size_t i = 0; i < stPoints.size(); ++i) {
        point3D =
            mts::triangulateLinearTwoView<T>(stPoints.at(i), ndPoints.at(i), eye, view);
        stDepth = computeDepth(eye, point3D);
        if (stDepth < 0.0f) {
            continue;
        }
        ndDepth = computeDepth(view, point3D);
        if (ndDepth < 0.0f) {
            continue;
        }
        points3D.push_back(point3D);
    }
    return !points3D.empty();
}
}  // namespace mts

#endif  // !GEOMETRY_POSE_H