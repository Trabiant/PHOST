#include "ProgressManager.h"
#include <iomanip>
#include <sstream>

ProgressManager::ProgressManager(std::size_t numOfIterations)
    : total_iterations(numOfIterations) {}

void ProgressManager::StartIterationTracking() {
    start_time = std::chrono::steady_clock::now();
}

void ProgressManager::FinishIterationTracking() {
    auto now = std::chrono::steady_clock::now();
    totalElapsed += (now - start_time);
    ++completed_iterations;
}

void ProgressManager::Reset(std::size_t numOfIterations) {
    total_iterations = numOfIterations;
    completed_iterations = 0;
    totalElapsed = std::chrono::steady_clock::duration::zero();
}

double ProgressManager::GetProgress() const noexcept {
    return total_iterations > 0
        ? static_cast<double>(completed_iterations) / total_iterations
        : 1.0;
}

std::chrono::steady_clock::duration ProgressManager::GetElapsedTime() const noexcept {
    return totalElapsed;
}

std::chrono::steady_clock::duration ProgressManager::GetRemainingTime() const noexcept {
    if (completed_iterations == 0 || completed_iterations >= total_iterations)
        return std::chrono::steady_clock::duration::zero();

    auto avg = totalElapsed / completed_iterations;
    auto left = total_iterations - completed_iterations;
    return avg * left;
}

std::string ProgressManager::Format_Duration(std::chrono::steady_clock::duration dur) noexcept {
    auto secs_total = std::chrono::duration_cast<std::chrono::seconds>(dur).count();
    int hours = static_cast<int>(secs_total / 3600);
    int minutes = static_cast<int>((secs_total % 3600) / 60);
    int seconds = static_cast<int>(secs_total % 60);

    std::ostringstream oss;
    oss << std::setfill('0');
    if (hours > 0) {
        // H:MM:SS
        oss << hours << ':'
            << std::setw(2) << minutes << ':'
            << std::setw(2) << seconds;
    }
    else if (minutes > 0) {
        // M:SS
        oss << minutes << ':'
            << std::setw(2) << seconds;
    }
    else {
        // Ss
        oss << seconds << 's';
    }
    return oss.str();
}
