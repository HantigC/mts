#ifndef MODEL_CAMERA_H
#define MODEL_CAMERA_H

#include <Eigen/Core>

namespace mts {

class Camera {
   public:
    Camera(){};
    Camera(float focalLength, float cx, float cy)
        : focalLength(focalLength), cx(cx), cy(cy) {
        K << focalLength, 0.0f, cx, 0.0f, focalLength, cy, 0.0f, 0.0f, 1.0f;
    };

    Camera(Eigen::Matrix3f& K) : K(K) {
        cx = K(0, 2);
        cy = K(0, 2);
        focalLength = K(0, 0);
    };

    static std::vector<Eigen::Vector3f> fromImageToCamera(
        const Eigen::Matrix3f& K, std::vector<Eigen::Vector2f>& pts);

    static Eigen::MatrixX3f fromImageToCamera(
        const Eigen::Matrix3f& K, Eigen::MatrixX2f& pts);

    Eigen::Matrix3f K;
    float focalLength;
    float cx;
    float cy;
};
}  // namespace mts

#endif  // !MODEL_CAMERA_H