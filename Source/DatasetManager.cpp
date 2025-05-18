#include "DatasetManager.h"
#include "ImageExtensions.h"
#include <algorithm>
#include <execution>
#include <opencv2/opencv.hpp>
#include <spdlog/spdlog.h>
#include <stdexcept>

DatasetManager::DatasetManager(const std::filesystem::path& dir, size_t baseCount, size_t psImageCount)
    : inputDir(dir), baseCount(baseCount), psCount(psImageCount)
{
    if (HasNonLatin(inputDir)) {
        throw std::runtime_error("Input directory path contains non-Latin characters: " + inputDir.string());
    }
    cv::setUseOptimized(true);
    cv::setNumThreads(std::thread::hardware_concurrency());
}

bool DatasetManager::IsValidExt(const std::filesystem::path& p) const {
    auto ext = p.extension().string();
    std::transform(ext.begin(), ext.end(), ext.begin(), [](unsigned char c) { return std::tolower(c); });
    return std::find(ALLOWED_EXT.begin(), ALLOWED_EXT.end(), ext) != ALLOWED_EXT.end();
}

bool DatasetManager::HasNonLatin(const std::filesystem::path& p) const {
    const std::string s = p.string();
    for (unsigned char c : s) {
        if (c > 127) {
            return true;
        }
    }
    return false;
}

std::vector<std::vector<ImageData>> DatasetManager::ManageDataset(){
    if (!std::filesystem::exists(inputDir) || !std::filesystem::is_directory(inputDir))
        throw std::runtime_error("Input Directory Not Found: " + inputDir.string());

    std::vector<std::filesystem::path> paths;
    for (auto& entry : std::filesystem::directory_iterator(inputDir)) {
        if (entry.is_regular_file() && IsValidExt(entry.path()))
            paths.push_back(entry.path());
    }
    std::sort(paths.begin(), paths.end());

    std::vector<ImageData> entries(paths.size());
    std::transform(
        std::execution::par,
        paths.begin(), paths.end(),
        entries.begin(),
        [&](const std::filesystem::path& p) {
            cv::Mat img = cv::imread(p.string(), cv::IMREAD_COLOR);
        if (img.empty()) {
            spdlog::error("Cannot Load Image (empty): {}", p.string());
            throw std::runtime_error("Image Load Failed: " + p.string());
        }
        return ImageData{ p.filename().string(), std::move(img) };
        }
    );
    size_t step = baseCount + psCount;
    std::vector<std::vector<ImageData>> packages;
    packages.reserve((entries.size() + step - 1) / step);
    for (size_t i = 0; i + step <= entries.size(); i += step)
        packages.emplace_back(entries.begin() + i, entries.begin() + i + step);

    return packages;
}
