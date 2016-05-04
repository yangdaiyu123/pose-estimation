#ifndef UniformDownsampling_H
#define UniformDownsampling_H

#include <pcl/filters/uniform_sampling.h>

#include "../types.h"
#include "../parameter.h"
#include "../pointcloud.h"
#include "../downsampling.hpp"

namespace PoseEstimation
{
    template<typename PointT>
    class UniformDownsampler : public Downsampler<PointT>
    {
    public:
        virtual void downsample(PC<PointT> &pc, PC<PointT> &downsampled) const
        {
            pcl::UniformSampling<PointT> uniform_sampling;
            uniform_sampling.setRadiusSearch(sampleSize.value<float>() * pc.resolution());
            uniform_sampling.setInputCloud(pc.cloud());
            uniform_sampling.filter(*(downsampled.cloud()));
            downsampled.update();
        }

        static ParameterCategory argumentCategory;

        static Parameter sampleSize;
    };

    template<typename PointT>
    ParameterCategory UniformDownsampler<PointT>::argumentCategory(
                "uniformdown", "Uniform downsampling");

    template<typename PointT>
    Parameter UniformDownsampler<PointT>::sampleSize = Parameter(
                "uniformdown",
                "size",
                10.0f,
                "Sample size");
}

#endif // UniformDownsampling_H
