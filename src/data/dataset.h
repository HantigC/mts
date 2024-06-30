#ifndef DATA_DATASET_H
#define DATA_DATASET_H
#include <Eigen/Core>
#include <opencv2/opencv.hpp>

#include "util/types.h"
#include "model/image.h"

namespace mts {

class Dataset {
   public:
    virtual ~Dataset() = default;
    virtual mts::Image imageAt(image_t imageIndex) = 0;
    virtual Eigen::Matrix3f rotationFor(image_t imageIndex) = 0;
    virtual void loadData() = 0;
    virtual unsigned int numImages() = 0;
    virtual unsigned int numCameras() = 0;
};

}  // namespace mts

#endif  // DATA_DATASET_H