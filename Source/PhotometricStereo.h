#pragma once

#include "ImageData.h"
#include <vector>
#include <opencv2/opencv.hpp>
#include <cuda_runtime.h>

class PhotometricStereo {
public:
    PhotometricStereo();
    void load(std::vector<ImageData>&& images, const cv::Mat& mask,
        size_t imagesBeforeDataset);
    cv::Mat GetNormalMap() const;

private:
    std::vector<cv::Mat> images_;
    cv::Mat mask_;
    cv::Mat lightDirs_;
    cv::Mat normalMap_;

    void DetectSphere(cv::Point2f& center, float& radius) const;
    cv::Mat EstimateLightDirs() const;
    void ComputeNormal_CPU();
    void ComputeNormal_GPU();
};