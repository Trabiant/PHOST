#pragma once
#include "ImageData.h"
#include "CameraPositionManager.h"
#include <filesystem>
#include <vector>
#include <string>

class TextureGenerator {
public:
	explicit TextureGenerator(const std::filesystem::path& root,
        const cv::Mat& mask_, size_t baseCount, CameraPositionManager& CamPosMng);
	void PrepareBaseColor(const std::vector<ImageData>& package);
	void ProcessTextures(std::vector<ImageData>& package, bool useDirectX_NormalMap);
	const std::filesystem::path& getTextureFolder() const { return textureFolder; }
private:
	std::filesystem::path textureFolder;
	void ComputeRoughness(const cv::Mat& imgCross, const cv::Mat& imgNonCross, cv::Mat& result);
	void CameraSpaceToObjectSpace(const ImageData& NormalData, cv::Mat& result);
	void ConvertFilenameExtCase(std::string& filename, bool toUpper);
	void ConvertNormalToDirectX(cv::Mat& img);
    cv::Mat mask, invMask;
	size_t imagesBeforePSDataset;
	std::string commonImageFilename;
	CameraPositionManager& CamPosManager;
};
