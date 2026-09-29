CPU Benchmarking Tool

Overview

CPU Benchmarking Tool is a C++ based system performance analysis application that evaluates processor efficiency through a set of synthetic workloads. The tool measures execution performance across integer arithmetic, floating-point computation, memory operations, and multi-threaded processing, then generates a consolidated performance score and compares the result against a reference CPU database.

Key Features

Performance Benchmarking

Sequential integer workload benchmarking
Floating-point computation benchmarking
Memory access and throughput evaluation
Multi-threaded performance analysis
CPU Scoring System

Generates individual benchmark scores
Calculates an overall CPU performance score
Categorizes processor performance levels
Produces detailed benchmark reports
Reference CPU Comparison

Loads CPU reference data from a CSV database
Matches benchmark results against known processors
Identifies the closest-performing CPU
File Handling

Reads CPU reference data from CSV files
Stores benchmark results in structured CSV format
Generates human-readable summary reports
Maintains persistent benchmark records for future comparison
Modular Design

Separate modules for benchmarking, scoring, reporting, timing, and database management
Header/source file separation for maintainability
Reusable and extensible architecture
Technologies Used

C++
STL
Multithreading (std::thread)
High Resolution Timing (std::chrono)
File Handling (fstream)
CSV Data Processing
Object-Oriented Programming
Benchmark Categories

1. Integer Benchmark

Measures processor efficiency for arithmetic operations involving integers.

2. Floating Point Benchmark

Evaluates floating-point computational performance commonly used in scientific and engineering workloads.

3. Memory Benchmark

Analyzes memory access behavior and throughput through large-scale memory operations.

4. Multi-thread Benchmark

Measures CPU scalability and utilization across multiple execution threads.

Output Generated

The application generates:

sequential.csv
float.csv
memory.csv
multithread.csv
results.csv
summary.txt
These files provide both raw benchmark measurements and consolidated performance reports.

Reference CPU Database

The project supports a configurable CPU reference database through:

CPU,Score
Intel Core i5-10400F,1850
AMD Ryzen 5 5600X,2400
Intel Core i7-12700K,3400
Benchmark results are compared against this dataset to estimate the closest-performing processor.

Project Structure

CPU Benchmarking Tool
│
├── include/
│   ├── bench_result.hpp
│   ├── float_bench.hpp
│   ├── memory_bench.hpp
│   ├── multithread_bench.hpp
│   ├── output.hpp
│   ├── reference_db.hpp
│   ├── scoring.hpp
│   ├── sequential_bench.hpp
│   └── timer.hpp
│
├── src/
│   ├── main.cpp
│   ├── float_bench.cpp
│   ├── memory_bench.cpp
│   ├── multithread_bench.cpp
│   ├── output.cpp
│   ├── reference_db.cpp
│   ├── scoring.cpp
│   ├── sequential_bench.cpp
│   └── timer.cpp
│
├── data/
│   └── reference_cpus.csv
│
└── output/
    ├── benchmark reports
    └── generated CSV files
Compilation

Windows (MinGW)

g++ -std=c++17 src/*.cpp -Iinclude -O2 -pthread -o cpu_bench.exe
Linux

g++ -std=c++17 src/*.cpp -Iinclude -O2 -pthread -o cpu_bench
Running the Application

Windows

cpu_bench.exe
Linux

./cpu_bench


