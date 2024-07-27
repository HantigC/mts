#ifndef RENDER_BASE_H
#define RENDER_BASE_H
#include <memory>
#include <Eigen/Core>
#include "render/model/base.h"

namespace mts {
namespace render {

 void draw(const std::vector<std::shared_ptr<mts::render::BaseModel>>& models,
          Eigen::Vector3f& position,
          Eigen::Vector3f& gaze);   
}

}  // namespace mts

#endif  // !RENDER_BASE_H