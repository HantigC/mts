#include <memory>
#include <vector>

#include "data/dataset.h"
#include "data/inmemory_ds.h"
#include "keypoint/keypoint.h"
#include "keypoint/sift.h"
#include "match/bf.h"
#include "match/match.h"
#include "render/base.h"
#include "render/model/base.h"
#include "render/model/camera.h"
#include "render/model/scene.h"
#include "scene/scene.h"
#include "sfm/sfm.h"

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
    mts::BFMatcher matcher;
    mts::SfM sfm(std::make_shared<mts::InMemoryDataset>(dataset),
                 std::make_shared<mts::SiftExtractor>(sift),
                 std::make_shared<mts::BFMatcher>(matcher));

    mts::Scene scene = sfm.reconstructTwoView(dataset.imageAt(0), dataset.imageAt(1));
    mts::render::SceneModel sceneModel(scene);
    std::shared_ptr<mts::render::SceneModel> sceneModel_p =
        std::make_shared<mts::render::SceneModel>(sceneModel);
    std::vector<std::shared_ptr<mts::render::BaseModel>> models = {sceneModel_p};
    Eigen::Vector3f origin(0.0f, 0.0f, 0.0f);
    Eigen::Vector3f forward(0.0f, 0.0f, 1.0f);
    origin = origin - 1.0f * forward;
    
    draw(models, origin, forward);

    return 0;
}