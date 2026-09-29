#include "output.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>

static void print_bar(double value, double maxValue, int width = 25) {
    if (maxValue <= 0) maxValue = 1.0;
    int filled = static_cast<int>((value / maxValue) * width);
    if (filled > width) filled = width;
    for (int i = 0; i < filled; ++i) std::cout << '#';
    for (int i = filled; i < width; ++i) std::cout << ' ';
}

void print_header() {
    std::cout << "========================================\n";
    std::cout << " CPU BENCHMARKING TOOL - SUMMARY REPORT\n";
    std::cout << "========================================\n\n";
}

void print_category(const CategoryResults &cat) {
    std::cout << "---------- " << cat.categoryName << " ----------\n";
    std::cout << std::left << std::setw(25) << "Test"
              << std::right << std::setw(15) << "Ops/sec"
              << std::setw(15) << "Time (ms)" << "\n";
    std::cout << "-------------------------------------------------------\n";
    double maxOps = 0.0;
    for (const auto &r : cat.tests) {
        maxOps = std::max(maxOps, r.opsPerSec);
    }
    for (const auto &r : cat.tests) {
        std::cout << std::left << std::setw(25) << r.name
                  << std::right << std::setw(15) << std::fixed << std::setprecision(2) << r.opsPerSec
                  << std::setw(15) << std::fixed << std::setprecision(2) << r.durationMs
                  << "\n";

        // ASCII bar
        std::cout << "   [";
        print_bar(r.opsPerSec, maxOps);
        std::cout << "]\n";
    }
    std::cout << "\n";
}

void print_multithread_scaling(const CategoryResults &mt) {
    std::cout << "---------- Multi-thread Scaling ----------\n";
    if (mt.tests.empty()) {
        std::cout << "No data.\n\n";
        return;
    }
    double baseOps = mt.tests.front().opsPerSec;
    std::cout << std::left << std::setw(10) << "Threads"
              << std::setw(15) << "Ops/sec"
              << std::setw(10) << "Speedup" << "\n";
    std::cout << "---------------------------------------\n";

    double maxSpeedup = 0.0;
    for (const auto &r : mt.tests) {
        double speedup = r.opsPerSec / baseOps;
        maxSpeedup = std::max(maxSpeedup, speedup);
    }

    for (const auto &r : mt.tests) {
        int threads = std::stoi(r.name);
        double speedup = r.opsPerSec / baseOps;
        std::cout << std::left << std::setw(10) << threads
                  << std::setw(15) << std::fixed << std::setprecision(2) << r.opsPerSec
                  << std::setw(10) << std::fixed << std::setprecision(2) << speedup << "\n";

        std::cout << "   [";
        print_bar(speedup, maxSpeedup);
        std::cout << "] " << std::fixed << std::setprecision(2) << speedup << "x\n";
    }
    std::cout << "\n";
}

void print_memory_hierarchy(const CategoryResults &mem) {
    std::cout << "---------- Memory Hierarchy ----------\n";
    std::cout << std::left << std::setw(30) << "Test"
              << std::setw(15) << "Ops/sec" << "\n";
    std::cout << "-------------------------------------------\n";

    double maxOps = 0.0;
    for (const auto &r : mem.tests) maxOps = std::max(maxOps, r.opsPerSec);

    for (const auto &r : mem.tests) {
        std::cout << std::left << std::setw(30) << r.name
                  << std::setw(15) << std::fixed << std::setprecision(2) << r.opsPerSec << "\n";
        std::cout << "   [";
        print_bar(r.opsPerSec, maxOps);
        std::cout << "]\n";
    }
    std::cout << "\n";
}

void print_score_summary(const ScoreResult &s) {
    std::cout << "---------- Score Summary ----------\n";
    std::cout << std::left << std::setw(20) << "Category"
              << std::setw(10) << "Score" << "\n";
    std::cout << "---------------------------------\n";
    std::cout << std::left << std::setw(20) << "Integer"
              << std::setw(10) << std::fixed << std::setprecision(2) << s.integerScore << "\n";
    std::cout << std::left << std::setw(20) << "Float"
              << std::setw(10) << s.floatScore << "\n";
    std::cout << std::left << std::setw(20) << "Memory"
              << std::setw(10) << s.memoryScore << "\n";
    std::cout << std::left << std::setw(20) << "Multi-thread"
              << std::setw(10) << s.multithreadScore << "\n";
    std::cout << "---------------------------------\n";
    std::cout << std::left << std::setw(20) << "Overall"
              << std::setw(10) << s.overallScore << "\n";
    std::cout << "Rating: " << s.rating << "\n";
    if (!s.closestCPUName.empty()) {
        std::cout << "Closest reference CPU: " << s.closestCPUName
                  << " (score " << s.closestCPUScore << ")\n";
        std::cout << "Relative performance: " << std::fixed << std::setprecision(2)
                  << s.relativeToClosest << "x\n";
    }
    std::cout << "\n";
}

void export_combined_results(const CategoryResults &seqInt,
                             const CategoryResults &flt,
                             const CategoryResults &mem,
                             const CategoryResults &mt,
                             const ScoreResult &score) {
    // CSV with all raw benchmarks
    std::ofstream csv("output/results.csv");
    if (csv) {
        csv << "category,test_name,ops_per_sec,duration_ms\n";
        auto dumpCat = [&](const CategoryResults &c) {
            for (const auto &r : c.tests) {
                csv << c.categoryName << "," << r.name << ","
                    << r.opsPerSec << "," << r.durationMs << "\n";
            }
        };
        dumpCat(seqInt);
        dumpCat(flt);
        dumpCat(mem);
        dumpCat(mt);
    }

    // Human-readable summary
    std::ofstream txt("output/summary.txt");
    if (txt) {
        txt << "CPU Benchmark Summary\n";
        txt << "=====================\n\n";
        txt << "Integer Score:      " << score.integerScore << "\n";
        txt << "Float Score:        " << score.floatScore << "\n";
        txt << "Memory Score:       " << score.memoryScore << "\n";
        txt << "Multi-thread Score: " << score.multithreadScore << "\n";
        txt << "Overall Score:      " << score.overallScore << "\n";
        txt << "Rating:             " << score.rating << "\n";
        if (!score.closestCPUName.empty()) {
            txt << "Closest Reference CPU: " << score.closestCPUName
                << " (score " << score.closestCPUScore << ")\n";
            txt << "Relative Performance:  " << score.relativeToClosest << "x\n";
        }
    }
}
