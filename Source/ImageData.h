#pragma once
#include <string>
#include <opencv2/opencv.hpp>

struct ImageData {
    std::string filename;
    cv::Mat image;
};
