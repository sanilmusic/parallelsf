#ifndef PARALLELSF_NODE_H
#define PARALLELSF_NODE_H

#include <string>

class Node {
private:
    char ch;
    long long frequency;
    std::string code;
public:
    Node(char c, long long f) {
        ch = c;
        frequency = f;
    }

    char getCh() const {
        return ch;
    }

    long long getFrequency() const {
        return frequency;
    }

    const std::string &getCode() const {
        return code;
    }

    void appendCharToCode(char ch) {
        code += ch;
    }
};


#endif
