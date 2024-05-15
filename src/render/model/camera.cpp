#include "render/model/camera.h"
#include <pangolin/gl/glfont.h>

#include <Eigen/Dense>
#include <iostream>

#include "visualization/camera.h"

namespace mts {

CameraModel::CameraModel() {
    this->position = Eigen::Vector3f(0.0f, 0.0f, 0.0f);
    this->xaxis = Eigen::Vector3f(1.0f, 0.0f, 0.0f);
    this->yaxis = Eigen::Vector3f(0.0f, 1.0f, 0.0f);
    this->zaxis = Eigen::Vector3f(0.0f, 0.0f, 1.0f);
}

CameraModel::CameraModel(Eigen::Vector3f& position,
                         Eigen::Vector3f& xaxis,
                         Eigen::Vector3f& yaxis,
                         Eigen::Vector3f& zaxis)
    : position(position), xaxis(xaxis), yaxis(yaxis), zaxis(zaxis) {}

CameraModel::CameraModel(Eigen::Matrix4f& view) {
    Eigen::Vector3f xaxis = view.block<1, 3>(0, 0);
    Eigen::Vector3f yaxis = view.block<1, 3>(1, 0);
    Eigen::Vector3f zaxis = view.block<1, 3>(2, 0);
    this->xaxis = xaxis;
    this->yaxis = yaxis;
    this->zaxis = zaxis;
    Eigen::Matrix4f viewmInv = view.inverse();
    this->position = viewmInv.block<3, 1>(0, 3);
}

void CameraModel::draw() {
    // std::cout << this->position;
    drawCameraAxes(this->position, this->xaxis, this->yaxis, this->zaxis);
}

std::ostream& operator<<(std::ostream& os, const CameraModel& camera) {
    os << "CameraModel("
       << "\nPosition(" << camera.position.x() << ", " << camera.position.y() << ", "
       << camera.position.z() << ")"
       << "\nxaxis(" << camera.xaxis.x() << ", " << camera.xaxis.y() << ", "
       << camera.xaxis.z() << ")"
       << "\nyaxis(" << camera.yaxis.x() << ", " << camera.yaxis.y() << ", "
       << camera.yaxis.z() << ")"
       << "\nzaxis(" << camera.zaxis.x() << ", " << camera.zaxis.y() << ", "
       << camera.zaxis.z() << ")"
       << ")";
    return os;
}

}  // namespace mts