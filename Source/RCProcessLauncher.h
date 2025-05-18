#pragma once
#include "TextureGenerator.h"
#include <filesystem>
#include <string>

class RCProcessLauncher {
public:
    RCProcessLauncher(const std::filesystem::path& appPath, TextureGenerator& texGenerator,
        const std::filesystem::path& projectRoot, std::string Name);
    void ExecuteCommand(const std::string& command);
    void SetRCProjectPath(const std::string& projectPath);
    std::string BuildTextureCommand() const;
    std::string BuildModelCommand(int quality) const;


private:
    std::filesystem::path rcApp;
    std::filesystem::path workDirRC;
    std::filesystem::path currentPath;
    std::string projectName;
    std::string textureFolder;
    std::string objPath;
    std::string rcprojPath;
    std::string textureConfig;
    std::string modelConfig;
    std::string regConfig;

    TextureGenerator& texGen;
};
