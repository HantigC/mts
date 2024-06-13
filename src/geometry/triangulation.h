#ifndef TRIANGULATION_H
#define TRIANGULATION_H
#include <Eigen/Eigen>
#include <cstddef>
#include <vector>

#include "camera.h"
namespace mts {
Eigen::Vector3f triangulateMidPoint(const Eigen::Vector2f& st_point,
                                    const Eigen::Vector2f& nd_point,
                                    const Eigen::Matrix4f& st_view,
                                    const Eigen::Matrix4f& nd_view);

template <int T>
Eigen::Vector3f triangulateLinearTwoView(const Eigen::Vector<float, T> st_point,
                                         const Eigen::Vector<float, T> nd_point,
                                         const Eigen::Matrix4f& st_view,
                                         const Eigen::Matrix4f& nd_view) {
    Eigen::Matrix4f equation_sys;
    equation_sys.row(0) = st_point(0) * st_view.row(2) - st_view.row(0);
    equation_sys.row(1) = st_point(1) * st_view.row(2) - st_view.row(1);
    equation_sys.row(2) = nd_point(0) * nd_view.row(2) - nd_view.row(0);
    equation_sys.row(3) = nd_point(1) * nd_view.row(2) - nd_view.row(1);

    Eigen::JacobiSVD<Eigen::Matrix4f> svd(equation_sys, Eigen::ComputeFullV);

    Eigen::Vector3f point3d = svd.matrixV().col(3).hnormalized();
    return point3d;
}

template <int T>
Eigen::Vector3f triangulateLinearTwoView(const Eigen::Vector<float, T> st_point,
                                         const Eigen::Vector<float, T> nd_point,
                                         const Eigen::Matrix3f& stR,
                                         const Eigen::Vector3f& stT,
                                         const Eigen::Matrix3f& ndR,
                                         const Eigen::Vector3f& ndT) {
    auto stView = mts::Camera::viewFromRt(stR, stT);
    auto ndView = mts::Camera::viewFromRt(ndR, ndT);
    auto point3d = mts::triangulateLinearTwoView(st_point, nd_point, stView, ndView);
    return point3d;
}

template <int T>
Eigen::Vector3f triangulateLinearTwoView(const Eigen::Vector<float, T> st_point,
                                         const Eigen::Vector<float, T> nd_point,
                                         const Eigen::Matrix4f& view) {
    Eigen::Matrix4f eye = Eigen::Matrix4f::Identity();
    auto point3d = mts::triangulateLinearTwoView<T>(st_point, nd_point, eye, view);
    return point3d;
}

template <int T>
Eigen::Vector3f triangulateLinearTwoView(const Eigen::Vector<float, T> st_point,
                                         const Eigen::Vector<float, T> nd_point,
                                         const Eigen::Matrix3f& R,
                                         const Eigen::Vector3f& t) {
    Eigen::Matrix4f eye = Eigen::Matrix4f::Identity();
    auto view = mts::Camera::viewFromRt(R, t);
    auto point3d = mts::triangulateLinearTwoView<T>(st_point, nd_point, eye, view);
    return point3d;
}

template <int T>
std::vector<Eigen::Vector3f> triangulateLinearTwoView(
    const std::vector<Eigen::Vector<float, T>>& st_points,
    const std::vector<Eigen::Vector<float, T>>& nd_points,
    const Eigen::Matrix4f& st_view,
    const Eigen::Matrix4f& nd_view) {
    std::vector<Eigen::Vector3f> points_3d;
    points_3d.reserve(st_points.size());
    for (int i = 0; i < st_points.size(); i++) {
        points_3d.push_back(triangulateLinearTwoView<T>(
            st_points.at(i), nd_points.at(i), st_view, nd_view));
    }
    return points_3d;
}
template <int T>
std::vector<Eigen::Vector3f> triangulateLinearTwoView(
    const std::vector<Eigen::Vector<float, T>>& st_points,
    const std::vector<Eigen::Vector<float, T>>& nd_points,
    const Eigen::Matrix4f& view) {
    auto eye = Eigen::Matrix4f::Identity();
    auto points3D = mts::triangulateLinearTwoView(st_points, nd_points, eye, view);
    return points3D;
}

template <int T>
std::vector<Eigen::Vector3f> triangulateLinearTwoView(
    const std::vector<Eigen::Vector<float, T>>& st_points,
    const std::vector<Eigen::Vector<float, T>>& nd_points,
    const Eigen::Matrix3f& stR,
    const Eigen::Vector3f& stT,
    const Eigen::Matrix3f& ndR,
    const Eigen::Vector3f& ndT) {
    auto stView = mts::Camera::viewFromRt(stR, stT);
    auto ndView = mts::Camera::viewFromRt(ndR, ndT);
    return mts::triangulateLinearTwoView(st_points, nd_points, stView, ndView);
}

template <int T>
std::vector<Eigen::Vector3f> triangulateLinearTwoView(
    const std::vector<Eigen::Vector<float, T>>& st_points,
    const std::vector<Eigen::Vector<float, T>>& nd_points,
    const Eigen::Matrix3f& R,
    const Eigen::Vector3f& t) {
    auto stView = Eigen::Matrix4f::Identity();
    auto ndView = mts::Camera::viewFromRt(R, t);
    return mts::triangulateLinearTwoView(st_points, nd_points, stView, ndView);
}

Eigen::Vector3f triangulateLinearMultiView(
    const std::vector<Eigen::Vector2f>& camera_points,
    const std::vector<Eigen::Matrix4f>& views);

}  // namespace mts

#endif  // !TRIANGULATION_H