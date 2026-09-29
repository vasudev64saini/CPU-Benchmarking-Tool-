#include "sequential_bench.hpp"
#include "timer.hpp"
#include <fstream>
#include <iostream>

static BenchmarkResult run_int_add_test(long long iterations) {
    volatile int x = 0;
    Timer t;
    t.start();
    for (long long i = 0; i < iterations; ++i) {
        x += 1;
    }
    double ms = t.elapsedMs();
    double opsPerSec = iterations / (ms / 1000.0);
    return {"Integer Add", opsPerSec, ms};
}

static BenchmarkResult run_int_mul_test(long long iterations) {
    volatile int x = 1;
    Timer t;
    t.start();
    for (long long i = 0; i < iterations; ++i) {
        x *= 2;
        if (x > 1e6) x = 1; // prevent overflow
    }
    double ms = t.elapsedMs();
    double opsPerSec = iterations / (ms / 1000.0);
    return {"Integer Multiply", opsPerSec, ms};
}

static BenchmarkResult run_int_div_test(long long iterations) {
    volatile int x = 1e6;
    Timer t;
    t.start();
    for (long long i = 1; i <= iterations; ++i) {
        x /= 2;
        if (x == 0) x = 1e6;
    }
    double ms = t.elapsedMs();
    double opsPerSec = iterations / (ms / 1000.0);
    return {"Integer Divide", opsPerSec, ms};
}

CategoryResults run_sequential_benchmarks() {
    long long iterations = 50'000'000; // adjust if too slow

    CategoryResults cat;
    cat.categoryName = "Sequential Integer Arithmetic";

    BenchmarkResult addRes = run_int_add_test(iterations);
    BenchmarkResult mulRes = run_int_mul_test(iterations);
    BenchmarkResult divRes = run_int_div_test(iterations);

    cat.tests.push_back(addRes);
    cat.tests.push_back(mulRes);
    cat.tests.push_back(divRes);

    // File handling: write to output/sequential.csv
    std::ofstream ofs("output/sequential.csv");
    if (ofs) {
        ofs << "name,ops_per_sec,duration_ms\n";
        for (const auto &r : cat.tests) {
            ofs << r.name << "," << r.opsPerSec << "," << r.durationMs << "\n";
        }
    } else {
        std::cerr << "Failed to open output/sequential.csv\n";
    }

    return cat;
}
