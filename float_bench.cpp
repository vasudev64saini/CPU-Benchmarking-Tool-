#include "float_bench.hpp"
#include "timer.hpp"
#include <fstream>
#include <iostream>
#include <cmath>

static BenchmarkResult run_float_add_test(long long iterations) {
    volatile double x = 0.0;
    Timer t;
    t.start();
    for (long long i = 0; i < iterations; ++i) {
        x += 0.1;
    }
    double ms = t.elapsedMs();
    double opsPerSec = iterations / (ms / 1000.0);
    return {"Float Add", opsPerSec, ms};
}

static BenchmarkResult run_float_mul_test(long long iterations) {
    volatile double x = 1.001;
    Timer t;
    t.start();
    for (long long i = 0; i < iterations; ++i) {
        x *= 1.000001;
        if (x > 1e6) x = 1.001;
    }
    double ms = t.elapsedMs();
    double opsPerSec = iterations / (ms / 1000.0);
    return {"Float Multiply", opsPerSec, ms};
}

static BenchmarkResult run_float_div_test(long long iterations) {
    volatile double x = 1e6;
    Timer t;
    t.start();
    for (long long i = 0; i < iterations; ++i) {
        x /= 1.000001;
        if (x < 1.0) x = 1e6;
    }
    double ms = t.elapsedMs();
    double opsPerSec = iterations / (ms / 1000.0);
    return {"Float Divide", opsPerSec, ms};
}

CategoryResults run_float_benchmarks() {
    long long iterations = 30'000'000; // slightly lower, floats are slower

    CategoryResults cat;
    cat.categoryName = "Floating Point Arithmetic";

    cat.tests.push_back(run_float_add_test(iterations));
    cat.tests.push_back(run_float_mul_test(iterations));
    cat.tests.push_back(run_float_div_test(iterations));

    std::ofstream ofs("output/float.csv");
    if (ofs) {
        ofs << "name,ops_per_sec,duration_ms\n";
        for (const auto &r : cat.tests) {
            ofs << r.name << "," << r.opsPerSec << "," << r.durationMs << "\n";
        }
    } else {
        std::cerr << "Failed to open output/float.csv\n";
    }

    return cat;
}
