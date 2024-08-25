#include "match/pair.h"
#include <utility>

#include "util/types.h"

namespace mts {
image_pair_t toPairId(image_t image1, image_t image2, image_t numImages) {
    if (shouldSwapPairs(image1, image2)) {
        return static_cast<image_pair_t>(numImages) * image2 + image1;
    } else {
        return static_cast<image_pair_t>(numImages) * image1 + image2;
    }
}
std::pair<image_t, image_t> fromPairId(image_pair_t pairId, image_t numImages) {
    image_t image2 = pairId % numImages;
    image_t image1 = static_cast<image_t>((pairId - image2) / numImages);
    auto pair = std::make_pair(image1, image2);
    return pair;

}

bool shouldSwapPairs(image_t image1, image_t image2) { return image1 > image2; }

}  // namespace mts