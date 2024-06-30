#ifndef MATCH_BF_H
#define MATCH_BF_H
#include <opencv2/features2d.hpp>

#include "match/match.h"

namespace mts {
class BFMatcher : public Matcher {
   public:
    BFMatcher(float ratio_tresh = 0.5) : ratio_tresh(ratio_tresh) {
        matcher_ = cv::BFMatcher(cv::NORM_L2);
    }

    void match(Descriptors& stDescriptors,
               Descriptors& ndDescriptors,
               Matches& matches) override;
    float ratio_tresh;

   private:
    cv::BFMatcher matcher_;
};
}  // namespace mts

#endif  // !MATCH_BF_H