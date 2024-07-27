#ifndef SFM_SFM_H
#define SFM_SFM_H
#include <memory>

#include "data/dataset.h"
#include "keypoint/keypoint.h"
#include "match/match.h"
#include "model/image.h"
#include "scene/scene.h"
namespace mts {
class SfM {
   public:
    SfM(std::shared_ptr<mts::KeypointExtractor>& keypointExtractor,
        std::shared_ptr<mts::Dataset>& dataset)
        : dataset(dataset), keypointExtractor(keypointExtractor) {}

    SfM(std::shared_ptr<mts::Dataset>& dataset) : dataset(dataset) {}

    SfM(std::shared_ptr<mts::Dataset>& dataset,
        std::shared_ptr<mts::KeypointExtractor>& keypointExtractor,
        std::shared_ptr<mts::Matcher>& matcher)
        : dataset(dataset), keypointExtractor(keypointExtractor), matcher(matcher) {}

    SfM(std::shared_ptr<mts::Dataset>&& dataset,
        std::shared_ptr<mts::KeypointExtractor>&& keypointExtractor,
        std::shared_ptr<mts::Matcher>&& matcher)
        : dataset(dataset), keypointExtractor(keypointExtractor), matcher(matcher) {}

    mts::Scene reconstructTwoView(mts::Image stImage, mts::Image ndImage);

    std::shared_ptr<mts::Dataset> dataset;
    std::shared_ptr<mts::KeypointExtractor> keypointExtractor = nullptr;
    std::shared_ptr<mts::Matcher> matcher = nullptr;
};
}  // namespace mts

#endif  // !SFM_SFM_H