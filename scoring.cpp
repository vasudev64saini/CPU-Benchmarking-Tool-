#include "scoring.hpp"
#include <algorithm>
#include <cmath>

static double average_ops(const CategoryResults &cat) {
    if (cat.tests.empty()) return 0.0;
    double sum = 0.0;
    for (const auto &r : cat.tests) sum += r.opsPerSec;
    return sum / cat.tests.size();
}

// simple baselines for normalization (tuned for your machine later)
static const double BASE_INT_OPS   = 1e9;
static const double BASE_FLOAT_OPS = 5e8;
static const double BASE_MEM_OPS   = 5e8;
static const double BASE_MT_OPS    = 2e9;

ScoreResult calculate_scores(const CategoryResults &seqInt,
                             const CategoryResults &flt,
                             const CategoryResults &mem,
                             const CategoryResults &mt,
                             const std::vector<RefCPU> &db) {
    ScoreResult s;

    double intAvg   = average_ops(seqInt);
    double floatAvg = average_ops(flt);
    double memAvg   = average_ops(mem);
    double mtAvg    = average_ops(mt);

    s.integerScore     = (intAvg   / BASE_INT_OPS)   * 1000.0;
    s.floatScore       = (floatAvg / BASE_FLOAT_OPS) * 1000.0;
    s.memoryScore      = (memAvg   / BASE_MEM_OPS)   * 1000.0;
    s.multithreadScore = (mtAvg    / BASE_MT_OPS)    * 1000.0;

    // weights: 30% int, 20% float, 20% mem, 30% mt
    s.overallScore =
        0.3 * s.integerScore +
        0.2 * s.floatScore +
        0.2 * s.memoryScore +
        0.3 * s.multithreadScore;

    // Determine rating
    if (s.overallScore >= 2200) s.rating = "Enthusiast / High-End";
    else if (s.overallScore >= 1600) s.rating = "Upper Mid-Range";
    else if (s.overallScore >= 1100) s.rating = "Mid-Range";
    else if (s.overallScore >= 800) s.rating = "Entry-Level";
    else s.rating = "Low-End";

    // Find closest reference CPU
    if (!db.empty()) {
        const RefCPU *best = &db[0];
        double bestDiff = std::abs(s.overallScore - db[0].baseScore);
        for (const auto &cpu : db) {
            double diff = std::abs(s.overallScore - cpu.baseScore);
            if (diff < bestDiff) {
                bestDiff = diff;
                best = &cpu;
            }
        }
        s.closestCPUName = best->name;
        s.closestCPUScore = best->baseScore;
        if (best->baseScore > 0.0)
            s.relativeToClosest = s.overallScore / best->baseScore;
    }

    return s;
}
