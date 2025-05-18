#pragma once

#include<filesystem>
#include "ImageData.h"
#include <vector>

class DatasetManager {
public:
	DatasetManager(const std::filesystem::path& dir, size_t baseCount, size_t psImageCount);
    std::vector<std::vector<ImageData>> ManageDataset();

private:
	bool IsValidExt(const std::filesystem::path& p) const;
    bool HasNonLatin(const std::filesystem::path& p) const;
    std::filesystem::path inputDir;
	size_t baseCount = 2; //Pair of Cross Polarized & Not Cross Polarized Images
	size_t psCount;
};

