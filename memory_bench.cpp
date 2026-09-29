#include "memory_bench.hpp"
#include "timer.hpp"
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdlib>

static BenchmarkResult run_memory_test(std::size_t elements, int stride) {
    std::vector<int> arr(elements, 1);
    volatile int sum = 0;
    Timer t;
    t.start();

    // run enough passes to get measurable time
    for (int pass = 0; pass < 50; ++pass) {
        for (std::size_t i = 0; i < elements; i += stride) {
            sum += arr[i];
        }
    }

    double ms = t.elapsedMs();
    // approximate "ops" = number of accesses
    long long accesses = (elements / stride) * 50LL;
    double opsPerSec = accesses / (ms / 1000.0);

    BenchmarkResult r;
    r.name = "Size=" + std::to_string(elements * sizeof(int) / 1024) + "KB stride=" + std::to_string(stride);
    r.opsPerSec = opsPerSec;
    r.durationMs = ms;
    return r;
}

CategoryResults run_memory_benchmarks() {
    CategoryResults cat;
    cat.categoryName = "Memory Hierarchy (Cache / RAM)";

    // These are rough working set sizes, not exact L1/L2, but good for a COA project demo
    cat.tests.push_back(run_memory_test(8 * 1024, 1));       // ~32KB
    cat.tests.push_back(run_memory_test(64 * 1024, 4));      // ~256KB
    cat.tests.push_back(run_memory_test(512 * 1024, 16));    // ~2MB
    cat.tests.push_back(run_memory_test(8 * 1024 * 1024, 64)); // large, DRAM-like

    std::ofstream ofs("output/memory.csv");
    if (ofs) {
        ofs << "test_name,ops_per_sec,duration_ms\n";
        for (const auto &r : cat.tests) {
            ofs << r.name << "," << r.opsPerSec << "," << r.durationMs << "\n";
        }
    } else {
        std::cerr << "Failed to open output/memory.csv\n";
    }

    return cat;
}
