#ifndef PARALLELSF_PARALLELSF_H
#define PARALLELSF_PARALLELSF_H

#include <string>
#include <map>
#include <vector>
#include <memory>
#include "Node.h"

class ParallelSF {
private:
    long long depth;
    std::vector<std::shared_ptr<Node>> nodes;

    std::map<char, long long> countFrequencies(const std::string &input);
    long long findOptimalBreakpoint(long long start, long long end);
    void workSequential(long long start, long long breakpoint, long long end);
    void workParallel(long long start, long long breakpoint, long long end);
    void work(long long start, long long end);
public:
    ParallelSF(long long d = 1);
    void load(const std::string &input);
    void encode();
    std::map<char, std::string> getCodes() const;
};


#endif
