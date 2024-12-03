#include <iostream>

#include "Utilities.h"

using namespace std;

// Tokens
const string mulOpen = "mul(";
constexpr char comma = ',';
constexpr char close = ')';
const string instDo = "do()";
const string instDont = "don't()";

struct Mul {
    size_t start, end;
    int n1, n2;
};

// Using std::regex would be simpler, but where's the fun in that?
Mul parseNextMul(const std::string& memory, size_t start = 0, size_t end = string::npos) {
    // opening token
    Mul mul = { string::npos };
    start = memory.find(mulOpen, start); // real start
    size_t pos = start;
    if (pos >= end) {
        return mul;
    }
    pos += mulOpen.size();

    // parse first number
    size_t len = 0;
    if (!stringToInt(memory, pos, mul.n1, len)) {
        return parseNextMul(memory, pos, end);
    }
    pos += len;

    // parse comma
    if (pos >= end) {
        return mul;
    }
    if (memory[pos++] != comma) {
        return parseNextMul(memory, pos, end);
    }

    // parse second number
    len = 0;
    if (!stringToInt(memory, pos, mul.n2, len)) {
        return parseNextMul(memory, pos, end);
    }
    pos += len;

    // parse closing token
    if (pos >= end) {
        return mul;
    }
    if (memory[pos] != close) {
        return parseNextMul(memory, pos, end);
    }
    pos++;

    mul.start = start;
    mul.end = pos;
    return mul;
}

int sumOfMuls(const std::string& memory, size_t start = 0, size_t end = string::npos) {
    int sum = 0;
    while (start < end) {
        Mul mul = parseNextMul(memory, start, end);
        if (mul.start == string::npos) {
            break;
        }

        sum += mul.n1 * mul.n2;
        start = mul.end;
    }
    
    return sum;
}

void testSumOfMuls() {
    string memory = "xmul(2, 4) % &mul[3, 7]!@ ^ do_not_mul(5, 5) + mul(32, 64]then(mul(11, 8)mul(8, 5))";
    int expected = 161;
    int actual = sumOfMuls(memory, 0, memory.size());
    if (actual != expected) {
        cout << "The sum of" << endl
            << "\"" << memory << "\"" << endl
            << "is " << actual << " (expected: " << expected << ")" << endl;
    }
}

int sumOfEnabledMuls(const std::string& memory, size_t start = 0, size_t end = string::npos) {
    size_t pos = 0;
    int sum = 0;
    bool enabled = true;
    while (pos < memory.size()) {
        if (enabled) {
            const size_t end = min(memory.find(instDont, pos), memory.size());
            sum += sumOfMuls(memory, pos, end);
            pos = end;
            enabled = false;
        }
        else {
            pos = memory.find(instDo, pos);
            enabled = true;
        }
    }
    
    return sum;
}

int main(int argc, char* argv[]) {
//    testSumOfMuls();

    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    string memory;
    readStringFromFile(argv[1], memory);

    cout << "sum of all mul()'s: " << sumOfMuls(memory) << endl
        << "sum of enabled mul()'s: " << sumOfEnabledMuls(memory) << endl;
}