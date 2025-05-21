#define _USE_MATH_DEFINES
#include "TextureGenerator.h"
#include "PhotometricStereo.h"
#include "NormalConverter.h"
#include <cuda_runtime.h>
#include <spdlog/spdlog.h>
#include <Eigen/Dense>
#include <omp.h>

TextureGenerator::TextureGenerator(const std::filesystem::path& root,
    const cv::Mat& mask_, size_t baseCount, CameraPositionManager& CamPosMng)
    : textureFolder(root / "ProjectFiles" / "LocalTextures"),
    imagesBeforePSDataset(baseCount), CamPosManager(CamPosMng),
    mask(mask_)
{
    std::filesystem::create_directories(textureFolder);

    if (mask.empty()) {
        throw std::runtime_error("Failed To Load Mask Image");
    }

    cv::bitwise_not(mask, invMask);
    cv::cvtColor(invMask, invMask, cv::COLOR_GRAY2BGR);
}

void TextureGenerator::PrepareBaseColor(const std::vector<ImageData>& package) {
    auto& baseColor = package[0];
    cv::bitwise_and(baseColor.image, invMask, baseColor.image);
    cv::imwrite((textureFolder / baseColor.filename).string(), baseColor.image);
}

void TextureGenerator::ProcessTextures(std::vector<ImageData>& package,
    bool useDirectX_NormalMap) {
    if (package.size() < imagesBeforePSDataset + 3) {
        throw std::runtime_error("Not enough images in package for Photometric Stereo");
    }
    commonImageFilename = package[0].filename;
    spdlog::info("================ {} ================", commonImageFilename);

    // Roughness Map
    cv::Mat roughness;
    ComputeRoughness(package[0].image, package[1].image, roughness);
    cv::imwrite((textureFolder / commonImageFilename).string() +
        ".texture01@Roughness.png", roughness);
    spdlog::info("Processed Roughness Map", commonImageFilename);

    // Normal Map
    PhotometricStereo ps;
    ps.load(std::move(package), mask, imagesBeforePSDataset);
    cv::Mat normal_cam = ps.GetNormalMap();
    ImageData normalData;
    normalData.filename = commonImageFilename;
    normalData.image = normal_cam;
    cv::Mat normal_obj = normal_cam;
    CameraSpaceToObjectSpace(normalData, normal_obj);
    if (useDirectX_NormalMap) {
        spdlog::info("Convert To DirectX");
        ConvertNormalToDirectX(normal_obj);
    }
    cv::imwrite((textureFolder / commonImageFilename).string() +
        ".texture02@Normal.png", normal_obj);
    spdlog::info("Processed Normal Map", commonImageFilename);

    // Displacement Map
}

void TextureGenerator::ComputeRoughness(const cv::Mat& imgCross, const cv::Mat& imgNonCross, cv::Mat& result) {
    if (imgCross.size() != imgNonCross.size()) {
        throw std::invalid_argument("Input Images Have Different Sizes");
    }
    // Получение разницы между поляризованным снимком и неполяризованным
    cv::subtract(imgNonCross, imgCross, result);
    cv::cvtColor(result, result, cv::COLOR_BGR2GRAY);
    cv::bitwise_not(result, result);
    float gamma = 2.5;
    float contrast = 0.734181;
    cv::Mat lut(1, 256, CV_8UC1);
    for (int i = 0; i < 256; i++) {
        lut.at<unsigned char>(i) = cv::saturate_cast<unsigned char>(std::pow(i / 255.0, gamma) * 255.0);
    }
    // Коррекция Roughness Map для получения правильного результата
    cv::LUT(result, lut, result);
    result.convertTo(result, -1, contrast, 0);
}

void TextureGenerator::ConvertFilenameExtCase(std::string& filename, bool toUpper) {
    std::size_t target_i = 0, i = filename.length();
    while (i > 0) {
        if (filename[i] == '.') {
            target_i = i;
            break;
        }
        i--;
    }
    for (std::size_t i = target_i + 1; i < filename.length(); i++) {
        int char_i = static_cast<int>(filename[i]);
        char upper = toUpper ? static_cast<char>(char_i - 32) : static_cast<char>(char_i + 32);
        filename[i] = upper;
    }
}


void TextureGenerator::CameraSpaceToObjectSpace(const ImageData& NormalData, cv::Mat& result) {
    CameraPosition position;
    CamPosManager.GetCameraPosition(NormalData.filename, position);
    NormalConverter converter(position);
    int deviceCount = 0;
    cudaError_t err = cudaGetDeviceCount(&deviceCount);
    if (err != cudaSuccess || deviceCount == 0)
        converter.convertCPU(NormalData.image, result);
    else
        converter.convertGPU(NormalData.image, result);
}

// Инвертирование Y нормали для формата DirectX
void TextureGenerator::ConvertNormalToDirectX(cv::Mat& img) {
    std::vector<cv::Mat> ch;
    split(img, ch);
    cv::bitwise_not(ch[1], ch[1]);
    merge(ch, img);
}
