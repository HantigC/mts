#include "render/primitive/point.h"

#include <pangolin/pangolin.h>

namespace mts {
namespace render {

void drawPoints(std::vector<Eigen::Vector3f>& points, Eigen::Vector3f& color) {
    glBegin(GL_POINTS);

    for (Eigen::Vector3f point3d : points) {
        glColor3f(color.x(), color.y(), color.z());
        glVertex3f(point3d.x(), point3d.y(), point3d.z());
    }
    glEnd();
}

void drawPoints(std::vector<Eigen::Vector3f>& points,
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
}  // namespace render
}  // namespace mts