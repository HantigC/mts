#ifndef SFM_H
#define SFM_H

#include "camera.h"
#include <opencv2/core.hpp>
#include <string>
#include <utility>
#include <vector>
#include <map>

namespace mts {
class SfM {
  public:
    SfM();
    SfM(const std::vector<std::pair<std::string, std::string>> &imageKPaths);
    SfM(const std::vector<std::string> &imagePaths, const std::vector<std::string> &kPaths);
    void loadImages();
    void loadKs();
    void loadData();
    std::vector<std::pair<std::string, std::string>> imageKPaths_;
    std::vector<mts::Camera> cameras_;
    
};
} // namespace mts

#endif // SFM_H