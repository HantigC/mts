#ifndef RENDER_MODEL_RIGID3D
#define RENDER_MODEL_RIGID3D
#include "geometry/rigid3d.h"
#include "render/model/base.h"
namespace mts {
namespace render {
class Rigid3DModel : public BaseModel {
   public:
    Rigid3DModel(mts::Rigid3D& rigid3d) : rigid3d(rigid3d) {}
    void draw() override;
    static void drawRigid3DAxes(mts::Rigid3D& rigid3d);
    static void drawRigid3DAxes(const Eigen::Vector3f& position,
                                const Eigen::Vector3f& xaxis,
                                const Eigen::Vector3f& yaxis,
                                const Eigen::Vector3f& zaxis,
                                float scale = 1.0f);
    static void drawRigid3DAxes(const Eigen::Vector3f& position,
                                const Eigen::Vector3f& xaxis,
                                const Eigen::Vector3f& yaxis,
                                const Eigen::Vector3f& zaxis,
                                const Eigen::Vector3f& xrgb,
                                const Eigen::Vector3f& yrgb,
                                const Eigen::Vector3f& zrgb,
                                float scale = 1.0f);

    mts::Rigid3D rigid3d;
};

}  // namespace render

}  // namespace mts

#endif  // !RENDER_MODEL_RIGID3D