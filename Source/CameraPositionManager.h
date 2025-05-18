#pragma once
#include "CameraPosition.h"
#include <string>
#include <vector>
class CameraPositionManager
{
public:
	void LoadPositions();
	explicit CameraPositionManager(std::string filename);
	bool GetCameraPosition(const std::string& filename, CameraPosition& camPos);
	bool GetCameraPosition(const std::string& filename) {
		CameraPosition dummy;
		return GetCameraPosition(filename, dummy);
	}
private:
	void ParseLine(CameraPosition& pos, const std::string& line);
	std::string camera_position_filename;
	std::vector<CameraPosition> camera_positions;
};