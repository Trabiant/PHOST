#include "RCProcessLauncher.h"
#include <windows.h>
#include <spdlog/spdlog.h>

RCProcessLauncher::RCProcessLauncher(const std::filesystem::path& appPath, TextureGenerator& texGenerator,
    const std::filesystem::path& projectRoot, std::string Name)
    : rcApp(appPath), texGen(texGenerator), projectName(std::move(Name))
{
    workDirRC = projectRoot / "ProjectFiles" / "RC";
    std::filesystem::create_directories(workDirRC);

    textureFolder = texGen.getTextureFolder().string();
    objPath = (projectRoot / (projectName + ".obj")).string();
    rcprojPath = workDirRC.string() + "\\" + projectName + ".rcproj";
    currentPath = std::filesystem::current_path();
    textureConfig = (currentPath / "Config" / "TextureExport.xml").string();
    modelConfig = (currentPath / "Config" / "ModelExport.xml").string();
    regConfig = (currentPath / "Config" / "RegistrationExport.xml").string();
}

// Постройка комманды для обращения к движку фотограмметрии
std::string RCProcessLauncher::BuildTextureCommand() const {
    std::ostringstream cmd;
    cmd << rcApp.string()
        << " -headless"
        << " -load \"" << rcprojPath << "\""
        << " -addFolder \"" << textureFolder << "\""
        << " -set ImageLayerForTexturing=all"
        << " -calculateTexture"
        << " -exportSelectedModel \"" << objPath << "\""
        << " \"" << textureConfig << "\""
        << " -save \"" << rcprojPath << "\""
        << " -quit";
    return cmd.str();
}

std::string RCProcessLauncher::BuildModelCommand(int quality) const {
    static const std::vector<std::string> qualityOptions = {
        "-calculatePreviewModel",
        "-calculateNormalModel",
        "-calculateHighModel"
    };

    const auto qualOpt = (quality >= 0 && quality < static_cast<int>(qualityOptions.size()))
        ? qualityOptions[quality]
        : qualityOptions[1];

    std::ostringstream cmd;
    cmd << rcApp.string()
        << " -headless"
        << " -addFolder \"" << textureFolder << "\""
        << " -align"
        << " -save \"" << rcprojPath << "\""
        << " -selectMaximalComponent"
        << " -setReconstructionRegionAuto"
        << " -scaleReconstructionRegion 5.0 5.0 5.0 center factor"
        << " " << qualOpt
        << " -calculateTexture"
        << " -save \"" << rcprojPath << "\""
        << " -exportSelectedModel \"" << objPath << "\""
        << " \"" << modelConfig << "\""
        << " -exportRegistration \"" << (workDirRC / (projectName + ".csv")).string() << "\""
        << " \"" << regConfig << "\""
        << " -quit";
    return cmd.str();
}

void RCProcessLauncher::SetRCProjectPath(const std::string& projectPath) {
    auto trim_quotes = [](const std::string& input) -> std::string {
        if (!input.empty() && input.front() == '"' && input.back() == '"' && input.length() >= 2) {
            return input.substr(1, input.length() - 2);
        }
        return input;
    };

    rcprojPath = trim_quotes(projectPath);
}

// Обращение к движку фотограмметрии
void RCProcessLauncher::ExecuteCommand(const std::string& command) {
    std::string cmdLine = command;
    spdlog::info(command);
    STARTUPINFOA si = { 0 };
    PROCESS_INFORMATION pi = { 0 };
    si.cb = sizeof(si);

    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_SHOWNORMAL;

    BOOL success = CreateProcessA(
    nullptr, &cmdLine[0], nullptr, nullptr, TRUE,
    0, nullptr, nullptr, &si, &pi);

    if (!success) {
        DWORD err = GetLastError();
        spdlog::error("CreateProcess failed with error {}", err);
        return;
    }

    if (WaitForSingleObject(pi.hProcess, INFINITE) == WAIT_OBJECT_0)
        DWORD exitCode = 0;

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}
