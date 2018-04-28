#include <iostream>
#include <fstream>
#include <sstream>
#include <omp.h>
#include "ParallelSF.h"

std::string loadFile(char *filename) {
    std::ifstream file(filename);

    std::stringstream stream;

    stream << file.rdbuf();

    return stream.str();
}

int main(int argc, char *argv[]) {
    std::string input(loadFile(argv[1]));

    ParallelSF sf(2);

    double startTime = omp_get_wtime();

    sf.load(input);

    sf.encode();

    double endTime = omp_get_wtime();

    std::cout << (endTime - startTime) << "s\n";

    return 0;
}