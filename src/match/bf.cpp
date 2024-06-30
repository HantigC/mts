#include "match/bf.h"

#include <cstddef>
#include <opencv2/core/eigen.hpp>

#include "match/match.h"
namespace mts {
void BFMatcher::match(Descriptors& stDescriptors,
                      Descriptors& ndDescriptors,
                      Matches& matches) {
    std::vector<std::vector<cv::DMatch>> knnMatches;

    cv::Mat stDescriptors_cv;
    cv::Mat ndDescriptors_cv;
    cv::eigen2cv(stDescriptors, stDescriptors_cv);
    cv::eigen2cv(ndDescriptors, ndDescriptors_cv);

    matcher_.knnMatch(stDescriptors_cv, ndDescriptors_cv, knnMatches, 2);

    std::vector<cv::DMatch> goodMatches;
    for (size_t i = 0; i < knnMatches.size(); i++) {
        if (knnMatches[i][0].distance < ratio_tresh * knnMatches[i][1].distance) {
            goodMatches.push_back(knnMatches[i][0]);
        }
    }
    matches = Matches(goodMatches.size(), 2);
    for (size_t i = 0; i < goodMatches.size(); i++) {
        matches(0, 0) = goodMatches.at(i).queryIdx;
        matches(0, 1) = goodMatches.at(i).trainIdx;
    }
}
}  // namespace mts