#ifndef BENCH_RESULT_HPP
#define BENCH_RESULT_HPP

#include <string>
#include <vector>

struct BenchmarkResult {
    std::string name;
    double opsPerSec;    // operations per second
    double durationMs;   // total duration in ms
};

struct CategoryResults {
    std::string categoryName;
    std::vector<BenchmarkResult> tests;
};

struct ScoreResult {
    double integerScore = 0.0;
    double floatScore = 0.0;
    double memoryScore = 0.0;
    double multithreadScore = 0.0;
    double overallScore = 0.0;

    std::string rating;
    std::string closestCPUName;
    double closestCPUScore = 0.0;
    double relativeToClosest = 0.0;
};

#endif // BENCH_RESULT_HPP
