#ifndef MATCH_MATCH_H
#define MATCH_MATCH_H
#include <Eigen/Core>

#include "model/keypoint.h"

namespace mts {
typedef Eigen::Matrix<unsigned int, Eigen::Dynamic, 2> Matches;
class Matcher {
   public:
    virtual void match(Descriptors& stDescriptors,
                       Descriptors& ndDescriptors,
                       Matches& matches) = 0;
};
}  // namespace mts

#endif  // !MATCH_MATCH_H