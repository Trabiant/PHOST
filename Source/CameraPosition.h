#pragma once
#include <string>
struct CameraPosition
{
	std::string ImageName{};
	double LocX = 0.0;
	double LocY = 0.0;
	double LocZ = 0.0;
	double RotX = 0.0;
	double RotY = 0.0;
	double RotZ = 0.0;
};