#include "triangulation.h"

#include <vector>

Eigen::Vector3f mts::triangulateMidPoint(const Eigen::Vector2f& st_point,
                                         const Eigen::Vector2f& nd_point,
                                         const Eigen::Matrix4f& st_view,
                                         const Eigen::Matrix4f& nd_view) {
    Eigen::Vector3f midpoint;
    return midpoint;
}

Eigen::Vector3f mts::triangulateLinearTwoView(const Eigen::Vector2f& st_point,
                                              const Eigen::Vector2f& nd_point,
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

std::vector<Eigen::Vector3f> mts::triangulateLinearTwoView(
    const std::vector<Eigen::Vector2f>& st_points,
    const std::vector<Eigen::Vector2f>& nd_points,
    const Eigen::Matrix4f& st_view,
    const Eigen::Matrix4f& nd_view) {
    std::vector<Eigen::Vector3f> points_3d(st_points.size());
    for (int i = 0; i < st_points.size(); i++) {
        points_3d.push_back(mts::triangulateLinearTwoView(
            st_points.at(i), nd_points.at(i), st_view, nd_view));
    }
    return points_3d;
}