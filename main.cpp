#include <iostream>
#include <filesystem>

#include "sequential_bench.hpp"
#include "float_bench.hpp"
#include "memory_bench.hpp"
#include "multithread_bench.hpp"
#include "reference_db.hpp"
#include "scoring.hpp"
#include "output.hpp"

int main() {
    // ensure output directory exists
    std::filesystem::create_directory("output");

    print_header();

    std::cout << "Running benchmarks...\n\n";

    auto seqInt = run_sequential_benchmarks();
    auto flt    = run_float_benchmarks();
    auto mem    = run_memory_benchmarks();
    auto mt     = run_multithread_benchmarks();

    auto refDB  = load_reference_db("data/reference_cpus.csv");

    auto score  = calculate_scores(seqInt, flt, mem, mt, refDB);

    std::cout << "\n================ Detailed Results ================\n\n";
    print_category(seqInt);
    print_category(flt);
    print_memory_hierarchy(mem);
    print_multithread_scaling(mt);
    print_score_summary(score);

    export_combined_results(seqInt, flt, mem, mt, score);

    std::cout << "Reports generated in ./output/\n";
    std::cout << " - sequential.csv\n";
    std::cout << " - float.csv\n";
    std::cout << " - memory.csv\n";
    std::cout << " - multithread.csv\n";
    std::cout << " - results.csv\n";
    std::cout << " - summary.txt\n";

    return 0;
}
