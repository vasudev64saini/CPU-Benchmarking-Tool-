#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include "bench_result.hpp"
#include "reference_db.hpp"
#include <vector>

void print_header();
void print_category(const CategoryResults &cat);
void print_multithread_scaling(const CategoryResults &mt);
void print_memory_hierarchy(const CategoryResults &mem);
void print_score_summary(const ScoreResult &score);
void export_combined_results(const CategoryResults &seqInt,
                             const CategoryResults &flt,
                             const CategoryResults &mem,
                             const CategoryResults &mt,
                             const ScoreResult &score);

#endif // OUTPUT_HPP
