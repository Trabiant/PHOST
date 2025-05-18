#pragma once
#include <filesystem>
#include <string>

struct Config {
    std::string projectName = "NewProject";
    std::filesystem::path datasetPath, rcPath, rcProjectPath;
    size_t baseCount = 2;
    size_t psImageCount = 8;
    int quality = 1;
    bool isModelProcessed = false;
    bool launchRC = true;
    bool useDirectX_NormalMap = false;
};
