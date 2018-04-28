#include "ParallelSF.h"
#include <algorithm>
#include <thread>

std::map<char, long long> ParallelSF::countFrequencies(const std::string &input) {
    std::map<char, long long> freqs;

#pragma omp parallel for schedule(static) num_threads(4)
    for (long long i = 0; i < input.length(); i++) {
#pragma omp atomic
        freqs[input[i]]++;
    }

    return freqs;
}

long long ParallelSF::findOptimalBreakpoint(long long start, long long end) {
    long long total(0);

    for (long long i(start); i < end; i++) {
        total += nodes[i]->getFrequency();
    }

    long long current(nodes[0]->getFrequency()), breakpoint(start + 1);

    while (true) {
        long long diff1(std::abs(total - 2 * current)), diff2(std::abs(total - 2 * (current + nodes[breakpoint]->getFrequency())));

        if (diff1 <= diff2) {
            break;
        }

        current += nodes[breakpoint++]->getFrequency();
    }

    return breakpoint;
}

void ParallelSF::workSequential(long long start, long long breakpoint, long long end) {
    if (breakpoint - start > 1) {
        work(start, breakpoint);
    }

    if (end - breakpoint > 1) {
        work(breakpoint, end);
    }
}

void ParallelSF::workParallel(long long start, long long breakpoint, long long end) {
    std::thread t1, t2;

    if (breakpoint - start > 1) {
        t1 = std::thread(&ParallelSF::work, this, start, breakpoint);
    }

    if (end - breakpoint > 1) {
        t2 = std::thread(&ParallelSF::work, this, breakpoint, end);
    }

    if (t1.joinable()) {
        t1.join();
    }

    if (t2.joinable()) {
        t2.join();
    }
}

void ParallelSF::work(long long start, long long end) {
    auto breakpoint = findOptimalBreakpoint(start, end);

    for (long long i(start); i < breakpoint; i++) {
        nodes[i]->appendCharToCode('0');
    }

    for (long long i(breakpoint); i < end; i++) {
        nodes[i]->appendCharToCode('1');
    }

    if (depth-- > 0) {
        workParallel(start, breakpoint, end);
    } else {
        workSequential(start, breakpoint, end);
    }
}

ParallelSF::ParallelSF(long long d) {
    depth = d;
}

void ParallelSF::load(const std::string &input) {
    auto freqs = countFrequencies(input);

    nodes.resize(freqs.size());

    long long i(0);

    for (const auto &el : freqs) {
        nodes[i++] = std::make_shared<Node>(el.first, el.second);
    }

    std::sort(nodes.begin(), nodes.end(), [](const std::shared_ptr<Node> &node1, const std::shared_ptr<Node> &node2) -> bool {
        return node1->getFrequency() > node2->getFrequency();
    });
}

void ParallelSF::encode() {
    work(0, nodes.size());
}

std::map<char, std::string> ParallelSF::getCodes() const {
    std::map<char, std::string> codes;

    for (auto node : nodes) {
        codes[node->getCh()] = node->getCode();
    }

    return codes;
}
