#ifndef DATA_INMEMORY_DS_H
#define DATA_INMEMORY_DS_H

#include <unordered_map>
#include <vector>
#include "data/dataset.h"
#include "model/camera.h"
#include "model/image.h"
#include "model/keypoint.h"
#include "sfm/pair.h"
#include "util/types.h"

namespace mts {
class InMemoryDataset : public Dataset {
   public:
    InMemoryDataset();
    InMemoryDataset(const std::vector<std::pair<std::string, std::string>>& imageKPaths);
    InMemoryDataset(const std::vector<std::string>& imagePaths,
                    const std::vector<std::string>& kPaths);
    mts::Image imageAt(image_t imageIndex) override;
    Eigen::Matrix3f rotationFor(image_t imageIndex) override;
    void loadData() override;
    unsigned int numCameras () override;
    unsigned int numImages () override;

    std::vector<std::pair<std::string, std::string>> imageKPaths;
    std::vector<KeypointDescriptor> keypointDescriptors;
    std::vector<KeypointDescriptor> matches;
    std::vector<mts::Camera> cameras;
    std::vector<mts::Image> images;
    std::unordered_map<image_pair_t, TwoViewPair> twoViewPairs;
};

}  // namespace mts

#endif  // !DATA_MEMORY_DATA_H