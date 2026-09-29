#include "multithread_bench.hpp"
#include "timer.hpp"
#include <thread>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

static void cpu_worker(long long iterations, volatile long long &sink) {
    long long x = 0;
    for (long long i = 0; i < iterations; ++i) {
        x += i;
    }
    sink = x;
}

static BenchmarkResult run_thread_test(int numThreads, long long iterationsPerThread) {
    volatile long long sink = 0;
    std::vector<std::thread> threads;

    Timer t;
    t.start();
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(cpu_worker, iterationsPerThread, std::ref(sink));
    }
    for (auto &th : threads) {
        th.join();
    }
    double ms = t.elapsedMs();
    double seconds = ms / 1000.0;

    long long totalOps = iterationsPerThread * numThreads;
    double opsPerSec = totalOps / seconds;

    BenchmarkResult r;
    r.name = std::to_string(numThreads) + " threads";
    r.opsPerSec = opsPerSec;
    r.durationMs = ms;
    return r;
}

CategoryResults run_multithread_benchmarks() {
    CategoryResults cat;
    cat.categoryName = "Multi-threaded Scaling";

    unsigned int hw = std::thread::hardware_concurrency();
    if (hw == 0) hw = 4;

    // test with 1, 2, 4, 8 threads (capped by hw)
    std::vector<int> threadCounts = {1, 2, 4, 8};
    long long iterationsPerThread = 20'000'000;

    for (int tc : threadCounts) {
        if (tc <= static_cast<int>(hw)) {
            cat.tests.push_back(run_thread_test(tc, iterationsPerThread));
        }
    }

    std::ofstream ofs("output/multithread.csv");
    if (ofs) {
        ofs << "threads,ops_per_sec,duration_ms\n";
        for (const auto &r : cat.tests) {
            ofs << r.name << "," << r.opsPerSec << "," << r.durationMs << "\n";
        }
    } else {
        std::cerr << "Failed to open output/multithread.csv\n";
    }

    return cat;
}
