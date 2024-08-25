#ifndef MATCH_PAIR_H
#define MATCH_PAIR_H
#include <utility>
#include "util/types.h"
namespace mts {
    image_pair_t toPairId(image_t image1, image_t image2, image_t numImages);
    std::pair<image_t, image_t> fromPairId(image_pair_t pairId, image_t numImages);
    bool shouldSwapPairs(image_t image1, image_t image2);

}

#endif // !MATCH_PAIR_H