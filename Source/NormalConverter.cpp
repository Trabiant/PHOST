#define _USE_MATH_DEFINES
#include "NormalConverter.h"
#include <Eigen/Dense>
#include <cmath>
#include <opencv2/opencv.hpp>

// Получаем матрицу поворота взависимости от положения камеры
Mat3x3 NormalConverter::makeRotationPOD(const CameraPosition& pos) {
    double yaw = pos.RotX * M_PI / 180.0;
    double pitch = pos.RotY * M_PI / 180.0;
    double roll = pos.RotZ * M_PI / 180.0;


    Eigen::AngleAxisd yA(yaw, Eigen::Vector3d::UnitZ());
    Eigen::AngleAxisd pA(pitch, Eigen::Vector3d::UnitY());
    Eigen::AngleAxisd rA(roll, Eigen::Vector3d::UnitX());

    Eigen::Matrix3d Rcam2obj = (yA * pA * rA).toRotationMatrix();

    Mat3x3 pod;
    pod.m[0] = Rcam2obj(0, 0); pod.m[1] = Rcam2obj(0, 1); pod.m[2] = Rcam2obj(0, 2);
    pod.m[3] = Rcam2obj(1, 0); pod.m[4] = Rcam2obj(1, 1); pod.m[5] = Rcam2obj(1, 2);
    pod.m[6] = Rcam2obj(2, 0); pod.m[7] = Rcam2obj(2, 1); pod.m[8] = Rcam2obj(2, 2);

    return pod;
}

NormalConverter::NormalConverter(const CameraPosition& pos)
    : position_(pos)
    , rotPOD_(makeRotationPOD(pos))
{}

void NormalConverter::convertCPU(const cv::Mat& src, cv::Mat& dst) const {
    dst = src.clone();
    for (int y = 0; y < src.rows; ++y) {
        const cv::Vec3b* sp = src.ptr<cv::Vec3b>(y);
        cv::Vec3b* dp = dst.ptr<cv::Vec3b>(y);
        for (int x = 0; x < src.cols; ++x) {
            // Для каждого пикселя — преобразование нормали
            dp[x] = transformNormalCPU(sp[x], rotPOD_);
        }
    }
}

// Преобразования нормали через ее умножение на матрицу поворота камеры
cv::Vec3b NormalConverter::transformNormalCPU(
    const cv::Vec3b& in, const Mat3x3& R)
{
    double nx = in[2] / 127.5 - 1.0;
    double ny = in[1] / 127.5 - 1.0;
    double nz = in[0] / 127.5 - 1.0;

    double ox = R.m[0] * nx + R.m[1] * ny + R.m[2] * nz;
    double oy = R.m[3] * nx + R.m[4] * ny + R.m[5] * nz;
    double oz = R.m[6] * nx + R.m[7] * ny + R.m[8] * nz;

    double len = std::sqrt(ox * ox + oy * oy + oz * oz);
    if (len > 1e-6) { ox /= len; oy /= len; oz /= len; }
    else { ox = 0; oy = 0; oz = 1; }

    cv::Vec3b out;
    out[0] = cv::saturate_cast<uchar>((oz * 0.5 + 0.5) * 255.0);
    out[1] = cv::saturate_cast<uchar>((oy * 0.5 + 0.5) * 255.0);
    out[2] = cv::saturate_cast<uchar>((ox * 0.5 + 0.5) * 255.0);
    return out;
}
