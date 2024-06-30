#include "data/inmemory_ds.h"
#include "keypoint/sift.h"


int main(int argc, const char** argv) {

    std::vector<std::string> imagePaths = {
        "./resources/fountain/images/0000.png",
        "./resources/fountain/images/0001.png",
        "./resources/fountain/images/0002.png",
        "./resources/fountain/images/0003.png",
        "./resources/fountain/images/0004.png",
        "./resources/fountain/images/0005.png",
        "./resources/fountain/images/0006.png",
        "./resources/fountain/images/0007.png",
        "./resources/fountain/images/0008.png",
        "./resources/fountain/images/0009.png",

    };

    std::vector<std::string> kPaths = {
        "./resources/fountain/K/0000.K",
        "./resources/fountain/K/0001.K",
        "./resources/fountain/K/0002.K",
        "./resources/fountain/K/0003.K",
        "./resources/fountain/K/0004.K",
        "./resources/fountain/K/0005.K",
        "./resources/fountain/K/0006.K",
        "./resources/fountain/K/0007.K",
        "./resources/fountain/K/0008.K",
        "./resources/fountain/K/0009.K",

    };
    auto dataset = mts::InMemoryDataset(imagePaths, kPaths);
    dataset.loadData();
    mts::SiftExtractor sift;
    auto keypoints = sift.computeKeypointDescriptor(dataset.images.back().image);
    std::cout << "hmm";
    std::cout << keypoints.descriptors;

    
    return 0;
}