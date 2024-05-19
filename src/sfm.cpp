#include "sfm.h"

#include <opencv2/imgcodecs.hpp>
#include <string>
#include <utility>
#include <vector>

#include "camera.h"

namespace mts {
SfM::SfM() {
    this->imageKPaths_ = std::vector<std::pair<std::string, std::string>>();
    this->cameras_ = std::vector<mts::Camera>();
}

SfM::SfM(const std::vector<std::pair<std::string, std::string>>& imageKPaths)
    : imageKPaths_(imageKPaths) {
    this->cameras_ = std::vector<mts::Camera>(this->imageKPaths_.size());
}

SfM::SfM(const std::vector<std::string>& imagePaths,
         const std::vector<std::string>& kPaths) {
    this->imageKPaths_ =
        std::vector<std::pair<std::string, std::string>>(imagePaths.size());
    this->cameras_ = std::vector<mts::Camera>(this->imageKPaths_.size());
    for (int i = 0; i < imagePaths.size(); i++) {
        this->imageKPaths_[i] = std::make_pair(imagePaths[i], kPaths[i]);
    }
}

void SfM::loadImages() {
    int i = 0;
    for (auto& imageK : this->imageKPaths_) {
        this->cameras_[i].image = cv::imread(imageK.first);
        i++;
    }
}
void SfM::loadKs() {
    int i = 0;
    bool areadyLoaded;
    for (auto& imageK : this->imageKPaths_) {
        this->cameras_[i].K = mts::readIntrinsecMatrix(imageK.second);
        i++;
    }
}
void SfM::loadData() {
    this->cameras_ = std::vector<mts::Camera>(this->imageKPaths_.size());

    int i = 0;
    for (auto& imageK : this->imageKPaths_) {
        this->cameras_[i] = mts::Camera(imageK.first, imageK.second);
        i++;
    }
}

}  // namespace mts