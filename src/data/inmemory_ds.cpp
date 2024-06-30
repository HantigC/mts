#include "data/inmemory_ds.h"

#include <fstream>
#include <opencv2/imgcodecs.hpp>

#include "model/image.h"

namespace mts {

InMemoryDataset::InMemoryDataset() {
    this->imageKPaths = std::vector<std::pair<std::string, std::string>>();
    this->cameras = std::vector<mts::Camera>();
}
InMemoryDataset::InMemoryDataset(
    const std::vector<std::pair<std::string, std::string>>& imageKPaths) {
    this->cameras = std::vector<mts::Camera>(this->imageKPaths.size());
}

InMemoryDataset::InMemoryDataset(const std::vector<std::string>& imagePaths,
                                 const std::vector<std::string>& kPaths) {
    imageKPaths = std::vector<std::pair<std::string, std::string>>(imagePaths.size());
    cameras = std::vector<mts::Camera>(this->imageKPaths.size());
    for (int i = 0; i < imagePaths.size(); i++) {
        imageKPaths[i] = std::make_pair(imagePaths[i], kPaths[i]);
    }
}

Eigen::Matrix<float, 3, 3> readIntrinsecMatrix(const std::string& matrixFilename) {
    std::ifstream inStream(matrixFilename);
    float x;
    std::vector<float> data;
    while (inStream >> x) {
        data.push_back(x);
    }
    return Eigen::Matrix<float, 3, 3, Eigen::RowMajor>(data.data());
}

void InMemoryDataset::loadData() {
    cameras = std::vector<mts::Camera>();
    images = std::vector<mts::Image>();
    cameras.reserve(imageKPaths.size());
    images.reserve(imageKPaths.size());

    Eigen::Matrix3f k;
    mts::Camera camera;
    for (auto& imageK : this->imageKPaths) {
        k = readIntrinsecMatrix(imageK.second);
        camera = mts::Camera(k);
        cameras.push_back(camera);
        images.push_back(mts::Image(cv::imread(imageK.first),
                                    std::make_shared<mts::Camera>(cameras.back())));
    }
}

unsigned int InMemoryDataset::numCameras() { return cameras.size(); }
unsigned int InMemoryDataset::numImages() { return images.size(); }

mts::Image InMemoryDataset::imageAt(image_t imageIndex) { return images.at(imageIndex); }

Eigen::Matrix3f InMemoryDataset::rotationFor(image_t imageIndex) { return {}; }

}  // namespace mts