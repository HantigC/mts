#include <Eigen/Dense>
#include "render/model/camera.h"

#include "visualization/camera.h"
#include <iostream>

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
    this->position = viewmInv.block<3, 1>(0, 0);
}

void CameraModel::draw() {
    // std::cout << this->position;
    drawCameraAxes(this->position, this->xaxis, this->yaxis, this->zaxis);
}

}  // namespace mts