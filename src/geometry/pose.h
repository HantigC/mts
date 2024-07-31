#ifndef GEOMETRY_POSE_H
#define GEOMETRY_POSE_H
#include <Eigen/Eigen>
#include <vector>

#include "geometry/essential.h"
#include "geometry/rigid3d.h"
#include "geometry/triangulation.h"

namespace mts {

float computeDepth(const Eigen::Matrix3f& R,
                   const Eigen::Vector3f& t,
                   const Eigen::Vector3f& point3D);
float computeDepth(const Eigen::Matrix4f& view, const Eigen::Vector3f& point3D);

template <unsigned int T>
bool checkCheirality(const Eigen::Matrix4f& stView,
                     const Eigen::Matrix4f& ndView,
                     const Eigen::Vector<float, T>& stPoint,
                     const Eigen::Vector<float, T>& ndPoint,
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
bool checkCheirality(const Eigen::Matrix3f& R,
                     const Eigen::Vector3f& t,
                     const Eigen::Matrix<float, Eigen::Dynamic, T>& stPoints,
                     const Eigen::Matrix<float, Eigen::Dynamic, T>& ndPoints,
                     std::vector<Eigen::Vector3f>& points3D) {
    Eigen::Vector3f point3D;
    Eigen::Matrix4f eye = Eigen::Matrix4f::Identity();
    auto view = mts::Rigid3D::viewFromRt(R, t);
    float stDepth, ndDepth;
    for (size_t rowIdx = 0; rowIdx < stPoints.rows(); ++rowIdx) {
        point3D = mts::triangulateLinearTwoView<T>(
            stPoints.row(rowIdx), ndPoints.row(rowIdx), eye, view);
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

template <unsigned int T>
bool checkCheirality(const Eigen::Matrix4f& stView,
                     const Eigen::Matrix4f& ndView,
                     const Eigen::Matrix<float, Eigen::Dynamic, T>& stPoints,
                     const Eigen::Matrix<float, Eigen::Dynamic, T>& ndPoints,
                     std::vector<Eigen::Vector3f>& points3D) {
    Eigen::Vector3f point3D;
    float stDepth, ndDepth;
    for (size_t rowIdx = 0; rowIdx < stPoints.rows(); ++rowIdx) {
        point3D = mts::triangulateLinearTwoView<T>(
            stPoints.row(rowIdx), ndPoints.row(rowIdx), stView, ndView);
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
bool checkCheirality(const Eigen::Matrix4f& stView,
                     const Eigen::Matrix4f& ndView,
                     const std::vector<Eigen::Vector<float, T>>& stPoints,
                     const std::vector<Eigen::Vector<float, T>>& ndPoints,
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
void poseFromEssential(Eigen::Matrix3f& essentialMatrix,
                       Eigen::Matrix<float, Eigen::Dynamic, T>& stPoints,
                       Eigen::Matrix<float, Eigen::Dynamic, T>& ndPoints,
                       Eigen::Matrix3f* R,
                       Eigen::Vector3f* t,
                       std::vector<Eigen::Vector3f>* points3D) {
    Eigen::Matrix3f R1;
    Eigen::Matrix3f R2;

    mts::decomposeEssentialRt(essentialMatrix, R1, R2, *t);
    const std::array<Eigen::Matrix3f, 4> R_cmbs{{R1, R2, R1, R2}};
    const std::array<Eigen::Vector3f, 4> t_cmbs{{*t, *t, -*t, -*t}};
    points3D->clear();
    for (size_t i = 0; i < R_cmbs.size(); i++) {
        std::vector<Eigen::Vector3f> points3D_cmb;
        mts::checkCheirality<T>(
            R_cmbs.at(i), t_cmbs.at(i), stPoints, ndPoints, points3D_cmb);
        if (points3D_cmb.size() > points3D->size()) {
            *R = R_cmbs.at(i);
            *t = t_cmbs.at(i);
            *points3D = points3D_cmb;
        }
    }
}

template <unsigned int T>
void poseFromEssential(Eigen::Matrix3f& essentialMatrix,
                       std::vector<Eigen::Vector<float, T>>& stPoints,
                       std::vector<Eigen::Vector<float, T>>& ndPoints,
                       Eigen::Matrix3f* R,
                       Eigen::Vector3f* t,
                       std::vector<Eigen::Vector3f>* points3D) {
    Eigen::Matrix3f R1;
    Eigen::Matrix3f R2;

    mts::decomposeEssentialRt(essentialMatrix, R1, R2, *t);
    const std::array<Eigen::Matrix3d, 4> R_cmbs{{R1, R2, R1, R2}};
    const std::array<Eigen::Vector3d, 4> t_cmbs{{*t, *t, -*t, -*t}};
    points3D->clear();
    for (size_t i = 0; i < R_cmbs.size(); i++) {
        std::vector<Eigen::Vector3f> points3D_cmb;
        mts::checkCheirality<T>(
            R_cmbs.at(i), t_cmbs.at(i), stPoints, ndPoints, points3D_cmb);
        if (points3D_cmb.size() > points3D->size()) {
            *R = R_cmbs.at(i);
            *t = t_cmbs.at(i);
            *points3D = points3D_cmb;
        }
    }
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