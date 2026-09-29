#ifndef SCORING_HPP
#define SCORING_HPP

#include "bench_result.hpp"
#include "reference_db.hpp"
#include <vector>

ScoreResult calculate_scores(const CategoryResults &seqInt,
                             const CategoryResults &flt,
                             const CategoryResults &mem,
                             const CategoryResults &mt,
                             const std::vector<RefCPU> &db);

#endif // SCORING_HPP
