#pragma once

#include <opencv2/opencv.hpp>
#include "CameraPosition.h"

struct Mat3x3 { double m[9]; };

class NormalConverter {
public:
    explicit NormalConverter(const CameraPosition& pos);
    void convertCPU(const cv::Mat& src, cv::Mat& dst) const;
    void convertGPU(const cv::Mat& src, cv::Mat& dst) const;

private:
    CameraPosition position_;
    Mat3x3 rotPOD_;

    static cv::Vec3b transformNormalCPU(const cv::Vec3b& in, const Mat3x3& R);
    static Mat3x3 makeRotationPOD(const CameraPosition& pos);
};