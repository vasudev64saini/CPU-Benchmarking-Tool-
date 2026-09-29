#ifndef REFERENCE_DB_HPP
#define REFERENCE_DB_HPP

#include <string>
#include <vector>

struct RefCPU {
    std::string name;
    double baseScore;
};

std::vector<RefCPU> load_reference_db(const std::string &path);

#endif // REFERENCE_DB_HPP
