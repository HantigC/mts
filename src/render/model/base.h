#ifndef RENDER_MODEL_BASE_H
#define RENDER_MODEL_BASE_H

namespace mts {
namespace render {

class BaseModel {
   public:
    BaseModel();
    virtual ~BaseModel() = default;
    virtual void draw() = 0;
};

}  // namespace render

}  // namespace mts

#endif  // RENDER_MODEL_BASE_H