#ifndef RENDER_MODEL_SCENE_H
#define RENDER_MODEL_SCENE_H

#include "render/model/base.h"
#include "scene/scene.h"
namespace mts {
namespace render {

class SceneModel : public BaseModel {
   public:
    SceneModel(mts::Scene& scene) : scene(scene) {}
    void draw() override;
    mts::Scene scene;
};

}  // namespace render
}  // namespace mts

#endif  // !RENDER_MODEL_SCENE_H