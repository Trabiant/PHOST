#pragma once

#include <chrono>
#include <string>

class ProgressManager {
public:
    explicit ProgressManager(std::size_t numOfIterations);

    void StartIterationTracking();
    void FinishIterationTracking();

    void Reset(std::size_t numOfIterations);

    double GetProgress() const noexcept;

    std::chrono::steady_clock::duration GetElapsedTime() const noexcept;
    std::chrono::steady_clock::duration GetRemainingTime() const noexcept;

    static std::string Format_Duration(std::chrono::steady_clock::duration dur) noexcept;

private:
    std::size_t total_iterations = 0;
    std::size_t completed_iterations = 0;
    std::chrono::steady_clock::duration totalElapsed = std::chrono::steady_clock::duration::zero();
    std::chrono::steady_clock::time_point start_time;
};
