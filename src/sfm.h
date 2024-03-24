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
    SfM(std::vector<std::pair<std::string, std::string>> &imageKPaths);
    SfM(std::vector<std::string> &imagePaths, std::vector<std::string> &kPaths);
    void loadImages();
    void loadKs();
    void loadData();
    std::vector<std::pair<std::string, std::string>> imageKPaths;
    std::vector<mts::Camera> cameras;
    
};
} // namespace mts

#endif // SFM_H