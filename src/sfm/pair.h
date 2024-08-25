#ifndef SFM_PAIR_H
#define SFM_PAIR_H
#include "geometry/rigid3d.h"
#include "match/match.h"
#include "util/types.h"
namespace mts {
class TwoViewPair {
   public:
    TwoViewPair(image_t image1, image_t image2, Matches& matches)
        : matches(matches), image1(image1), image2(image2) {}

    TwoViewPair(image_t image1, image_t image2) : image1(image1), image2(image2) {}
    TwoViewPair(image_t image1,
                image_t image2,
                Matches& matches,
                Eigen::Matrix3f& fundamentalMatrix)
        : matches(matches),
          image1(image1),
          image2(image2),
          fundamentalMatrix(fundamentalMatrix) {}

    TwoViewPair(image_t image1,
                image_t image2,
                Matches& matches,
                Eigen::Matrix3f& fundamentalMatrix,
                Eigen::Matrix3f& essentialMatrix)
        : matches(matches),
          image1(image1),
          image2(image2),
          fundamentalMatrix(fundamentalMatrix),
          essentialMatrix(essentialMatrix) {}

    TwoViewPair(image_t image1,
                image_t image2,
                Matches& matches,
                Eigen::Matrix3f& fundamentalMatrix,
                Eigen::Matrix3f& essentialMatrix,
                mts::Rigid3D& relativePose)
        : matches(matches),
          image1(image1),
          image2(image2),
          fundamentalMatrix(fundamentalMatrix),
          essentialMatrix(essentialMatrix),
          relativePose(relativePose) {}

    image_t image1;
    image_t image2;
    Matches matches;
    Eigen::Matrix3f essentialMatrix;
    Eigen::Matrix3f fundamentalMatrix;
    mts::Rigid3D relativePose;
};

}  // namespace mts

#endif  // !SFM_PAIR_H