#include "CameraPositionManager.h"
#include <fstream>
#include <sstream>
#include <spdlog/spdlog.h>
#include <stdexcept>

CameraPositionManager::CameraPositionManager(std::string filename)
	: camera_position_filename(filename) {
}

// Подгрузка позиции камер из файла csv
void CameraPositionManager::LoadPositions() {
    camera_positions.clear();
    CameraPosition position;
    std::ifstream file(camera_position_filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed To Open The Camera Position File: " + camera_position_filename);
    }
    int numLine = 0;
    std::string line;
    while (std::getline(file, line))
    {
        numLine++;
        if (line.empty() || line[0] == '#') continue;
        ParseLine(position, line);
        camera_positions.push_back(position);
    }
    file.close();
}

bool CameraPositionManager::GetCameraPosition(const std::string& filename, CameraPosition& camPos) {
    for (const CameraPosition& p : camera_positions) {
        if (p.ImageName == filename) {
            camPos = p;
            return true;
        }
    }
    spdlog::warn("Package {} skipped: Position Not Found", filename);
    return false;
}

void CameraPositionManager::ParseLine(CameraPosition& pos, const std::string& line) {
    std::stringstream ss(line);
    if (!std::getline(ss, pos.ImageName, ','))
        throw std::runtime_error("CameraPositionManager: Missing name in line: " + line);

    auto readDouble = [&](double& out) {
        if (!(ss >> out))
            throw std::runtime_error("CameraPositionManager: Failed to read rotation or location from: " + line);
        ss.ignore(1, ',');
    };

    readDouble(pos.LocX);
    readDouble(pos.LocY);
    readDouble(pos.LocZ);
    readDouble(pos.RotX);
    readDouble(pos.RotY);
    readDouble(pos.RotZ);
}
