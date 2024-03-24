#include "sfm.h"
#include "camera.h"
#include <opencv2/imgcodecs.hpp>
#include <string>
#include <utility>
#include <vector>

namespace mts {
SfM::SfM() {
    this->imageKPaths = std::vector<std::pair<std::string, std::string>>();
    this->cameras = std::vector<mts::Camera>();
}

SfM::SfM(std::vector<std::pair<std::string, std::string>> &imageKPaths)
    : imageKPaths(imageKPaths) {
    this->cameras = std::vector<mts::Camera>(this->imageKPaths.size());
}

SfM::SfM(std::vector<std::string> &imagePaths,
         std::vector<std::string> &kPaths) {
    this->imageKPaths =
        std::vector<std::pair<std::string, std::string>>(imagePaths.size());
    this->cameras = std::vector<mts::Camera>(this->imageKPaths.size());
    for (int i = 0; i < imagePaths.size(); i++) {
        this->imageKPaths[i] = std::make_pair(imagePaths[i], kPaths[i]);
    }
}

void SfM::loadImages() {
    int i = 0;
    for (auto &imageK : this->imageKPaths) {
        this->cameras[i].image = cv::imread(imageK.first);
        i++;
    }
}
void SfM::loadKs() {

    int i = 0;
    bool areadyLoaded;
    for (auto &imageK : this->imageKPaths) {
        this->cameras[i].intrinsicMatrix =
            mts::readIntrinsecMatrix(imageK.second);
        i++;
    }
}
void SfM::loadData() {
    this->cameras = std::vector<mts::Camera>(this->imageKPaths.size());

    int i = 0;
    for (auto &imageK : this->imageKPaths) {
        this->cameras[i] = mts::Camera(imageK.first, imageK.second);
        i++;
    }
}

} // namespace mts