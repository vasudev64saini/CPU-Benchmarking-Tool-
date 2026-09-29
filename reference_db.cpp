#include "reference_db.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<RefCPU> load_reference_db(const std::string &path) {
    std::vector<RefCPU> db;
    std::ifstream ifs(path);
    if (!ifs) {
        std::cerr << "Failed to open reference DB: " << path << "\n";
        return db;
    }

    std::string line;
    // skip header
    std::getline(ifs, line);

    while (std::getline(ifs, line)) {
        std::stringstream ss(line);
        std::string name, scoreStr;
        if (!std::getline(ss, name, ',')) continue;
        if (!std::getline(ss, scoreStr, ',')) continue;
        RefCPU cpu;
        cpu.name = name;
        cpu.baseScore = std::stod(scoreStr);
        db.push_back(cpu);
    }
    return db;
}
