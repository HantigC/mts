#include "render/model/pcl.h"

#include <pangolin/pangolin.h>

namespace mts {
Pcl::Pcl(const std::vector<Eigen::Vector3f>& points)
    : points(points), colors({Eigen::Vector3f(1.0f, 0.0f, 0.0f)}){};

Pcl::Pcl(const std::vector<Eigen::Vector3f>& points,
         const std::vector<Eigen::Vector3f>& colors)
    : points(points), colors(colors){};

void Pcl::draw() {
    if (colors.size() == 1) {
        Pcl::draw_points(points, colors.at(0));
    } else {
        Pcl::draw_points(points, colors);
    }
}

void Pcl::draw_points(std::vector<Eigen::Vector3f>& points, Eigen::Vector3f& color) {
    glBegin(GL_POINTS);

    for (Eigen::Vector3f point3d : points) {
        glColor3f(color.x(), color.y(), color.z());
        glVertex3f(point3d.x(), point3d.y(), point3d.z());
    }
    glEnd();
}

void Pcl::draw_points(std::vector<Eigen::Vector3f>& points,
                      std::vector<Eigen::Vector3f>& colors) {
    glBegin(GL_POINTS);
    Eigen::Vector3f color, point3d;

    for (size_t i = 0; i < points.size(); i++) {
        color = colors[i];
        point3d = points[i];
        glColor3f(color.x(), color.y(), color.z());
        glVertex3f(point3d.x(), point3d.y(), point3d.z());
    }
    glEnd();
}
}  // namespace mts