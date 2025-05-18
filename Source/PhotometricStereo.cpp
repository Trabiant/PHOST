#include "PhotometricStereo.h"
#include "ImageData.h"
#include <stdexcept>
#include <cmath>
#include <spdlog/spdlog.h>


PhotometricStereo::PhotometricStereo() = default;

void PhotometricStereo::load(std::vector<ImageData>&& images,
    const cv::Mat& mask, size_t imagesBeforeDataset) {
    if (images.empty())
        throw std::runtime_error("No input images provided");
    if (mask.empty() || mask.type() != CV_8U)
        throw std::runtime_error("Mask must be non-empty CV_8U");

    images_.clear();
    for (std::size_t i = imagesBeforeDataset; i < images.size(); i++) {
        const auto& im = images[i];
        cv::Mat f;
        cv::cvtColor(im.image, f, cv::COLOR_BGR2GRAY);
        f.convertTo(f, CV_32F, 1.0 / 255.0);
        images_.push_back(f);
        images[i].image.release();
    }
    mask_ = mask;
    images.clear();
    images.shrink_to_fit();
    lightDirs_ = EstimateLightDirs();
    int deviceCount = 0;
    cudaError_t err = cudaGetDeviceCount(&deviceCount);
    if (err != cudaSuccess || deviceCount == 0)
        ComputeNormal_CPU();
    else
        ComputeNormal_GPU();

}

cv::Mat PhotometricStereo::GetNormalMap() const {
    return normalMap_;
}

void PhotometricStereo::DetectSphere(cv::Point2f& center, float& radius) const
{
    cv::Mat thr;
    cv::threshold(mask_, thr, 127, 255, cv::THRESH_BINARY);
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(thr, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    if (contours.empty()) {
        spdlog::error("Mask Has No Contours");
        throw std::runtime_error("Mask contains no contours for sphere detection");
    }

    auto maxCnt = *std::max_element(
        contours.begin(), contours.end(),
        [](auto& a, auto& b) { return cv::contourArea(a) < cv::contourArea(b); }
    );
    cv::minEnclosingCircle(maxCnt, center, radius);
}

cv::Mat PhotometricStereo::EstimateLightDirs() const {
    cv::Point2f c;
    float r;
    // Автоматическое определение сферы калибровки по маске
    DetectSphere(c, r);

    std::vector<cv::Vec3f> normals;
    std::vector<cv::Point>  coords;
    // Для каждого пикселя маски оцениваем нормаль сферы
    for (int y = 0; y < mask_.rows; ++y) {
        for (int x = 0; x < mask_.cols; ++x) {
            if (mask_.at<uchar>(y, x) > 127) {
                float nx = (x - c.x) / r;
                float ny = (y - c.y) / r;
                float nz2 = 1.0f - nx * nx - ny * ny;
                if (nz2 >= 0.0f) {
                    normals.emplace_back(nx, ny, std::sqrt(nz2));
                    coords.emplace_back(x, y);
                }
            }
        }
    }
    // Решение уравнения освещенности I = N·L через разложение по сингулярным значениям для оценки L
    int P = (int)normals.size();
    int M = (int)images_.size();
    cv::Mat N(P, 3, CV_32F);
    for (int i = 0; i < P; ++i) {
        N.at<float>(i, 0) = normals[i][0];
        N.at<float>(i, 1) = normals[i][1];
        N.at<float>(i, 2) = normals[i][2];
    }

    cv::Mat L(M, 3, CV_32F);
    for (int i = 0; i < M; ++i) {
        cv::Mat I(P, 1, CV_32F);
        for (int j = 0; j < P; ++j) {
            const auto& pt = coords[j];
            I.at<float>(j) = images_[i].at<float>(pt.y, pt.x);
        }
        cv::Mat b;
        // Получаем вектор освещения
        cv::solve(N, I, b, cv::DECOMP_SVD);
        double nrm = cv::norm(b);
        if (nrm > 1e-6f) b /= nrm;
        for (int k = 0; k < 3; ++k)
            L.at<float>(i, k) = b.at<float>(k);
    }
    return L;
}

void PhotometricStereo::ComputeNormal_CPU() {
    int M = static_cast<int>(images_.size());
    int h = images_[0].rows;
    int w = images_[0].cols;
    // Предварительно вычисляем псевдообратную матрицу направлений света: L
    cv::Mat l_pinv;
    cv::invert(lightDirs_, l_pinv, cv::DECOMP_SVD);
    std::vector<float> Lpinv_arr(3 * M);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < M; ++j) {
            Lpinv_arr[i * M + j] = l_pinv.at<float>(i, j);
        }
    }
    std::vector<const float*> img_ptrs(M);
    for (int i = 0; i < M; ++i) {
        img_ptrs[i] = images_[i].ptr<float>(0);
    }
    const uchar* mask_ptr = mask_.ptr<uchar>(0);
    normalMap_.create(h, w, CV_8UC3);
    uchar* out_ptr = normalMap_.ptr<uchar>(0);
    std::vector<float> I_data(M);

    for (int y = 0; y < h; ++y) {
        int base = y * w;
        for (int x = 0; x < w; ++x) {
            int idx = base + x;
            // Пропускаем пиксели вне маски
            if (mask_ptr[idx] > 127)
                continue;
            // Собираем вектор интенсивностей I для данного пикселя
            for (int i = 0; i < M; ++i) {
                I_data[i] = img_ptrs[i][idx];
            }
            // Решаем уравнение g = L*I --> g = (ρ*n), затем нормализуем
            float g0 = 0, g1 = 0, g2 = 0;
            for (int i = 0; i < M; ++i) {
                float v = I_data[i];
                g0 += Lpinv_arr[0 * M + i] * v;
                g1 += Lpinv_arr[1 * M + i] * v;
                g2 += Lpinv_arr[2 * M + i] * v;
            }
            float nrm = std::sqrt(g0 * g0 + g1 * g1 + g2 * g2);
            float nx = 0, ny = 0, nz = 0;
            // Нормируем вектор, чтобы получить единичную нормаль
            if (nrm > 1e-6f) {
                nx = g0 / nrm;
                ny = g1 / nrm;
                nz = g2 / nrm;
            }
            else
            {
                nz = 1;
            }
            int o = idx * 3;
            out_ptr[o + 0] = cv::saturate_cast<uchar>((nz + 1.0f) * 0.5f * 255.0f);
            out_ptr[o + 1] = cv::saturate_cast<uchar>((ny + 1.0f) * 0.5f * 255.0f);
            out_ptr[o + 2] = cv::saturate_cast<uchar>((nx + 1.0f) * 0.5f * 255.0f);
        }
    }
}
