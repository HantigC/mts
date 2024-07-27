#include "render/model/rigid3d.h"

#include <pangolin/pangolin.h>

namespace mts {
namespace render {
void Rigid3DModel::draw() { Rigid3DModel::drawRigid3DAxes(rigid3d); }
void Rigid3DModel::drawRigid3DAxes(mts::Rigid3D& rigid3d) {
    drawRigid3DAxes(rigid3d.invT(), rigid3d.R.row(0), rigid3d.R.row(1), rigid3d.R.row(2));
}
void Rigid3DModel::drawRigid3DAxes(const Eigen::Vector3f& position,
                                   const Eigen::Vector3f& xaxis,
                                   const Eigen::Vector3f& yaxis,
                                   const Eigen::Vector3f& zaxis,
                                   const Eigen::Vector3f& xrgb,
                                   const Eigen::Vector3f& yrgb,
                                   const Eigen::Vector3f& zrgb,
                                   float scale) {
    glBegin(GL_LINES);
    // Draw x axis
    glColor3f(xrgb.x(), xrgb.y(), xrgb.z());
    glVertex3f(position.x(), position.y(), position.z());
    glVertex3f(
        position.x() + xaxis.x(), position.y() + xaxis.y(), position.z() + xaxis.z());

    // Draw y axis
    glColor3f(yrgb.x(), yrgb.y(), yrgb.z());
    glVertex3f(position.x(), position.y(), position.z());
    glVertex3f(
        position.x() + yaxis.x(), position.y() + yaxis.y(), position.z() + yaxis.z());

    // Draw z axis
    glColor3f(zrgb.x(), zrgb.y(), zrgb.z());
    glVertex3f(position.x(), position.y(), position.z());
    glVertex3f(
        position.x() + zaxis.x(), position.y() + zaxis.y(), position.z() + zaxis.z());
    glEnd();
}

void Rigid3DModel::drawRigid3DAxes(const Eigen::Vector3f& position,
                                   const Eigen::Vector3f& xaxis,
                                   const Eigen::Vector3f& yaxis,
                                   const Eigen::Vector3f& zaxis,
                                   float scale) {
    Eigen::Vector3f xrgb(1.0, 0.0f, 0.0f);
    Eigen::Vector3f yrgb(0.0, 1.0, 0.0f);
    Eigen::Vector3f zrgb(0.0, 0.0f, 1.0f);
    Rigid3DModel::drawRigid3DAxes(position, xaxis, yaxis, zaxis, xrgb, yrgb, zrgb, scale);
}
}  // namespace render

}  // namespace mts