#include "main.h"
#include <iostream>
#include <vector>



int main(int argc, char* argv[]) {
    // encoding/decoding mode
    bool encoding_mode = true;

    for (int i = 0; i < argc; ++i) {
        if (std::string(argv[i]) == "-d") {
            encoding_mode = false;
        }
    }

    // reading the input
    std::vector<char> output;
    std::vector<char> input;
    char byte;
    while(std::cin.get(byte)) {
        input.push_back(byte);
    }

    // encoding process
    if (encoding_mode) {
        size_t padding = (4 - (input.size() % 4)) % 4;
        input.resize(input.size() + padding, '\0');

        for (int i = 0; i < input.size(); i+=4) {
            std::string chunk(input.begin() + i, input.begin() + i + 4);
            for (char character : encode(chunk)) {
                output.push_back(character);
            }
        }
        output.resize(output.size() - padding);
    }

    // decoding process
    else {
        if (static_cast<int>(input[input.size() - 1]) == 10) {
            input.erase(input.begin() + input.size() - 1);
        }

        size_t padding = (5 - (input.size() % 5)) % 5;
        input.resize(input.size() + padding, 'u');

        int i = 0;
        while (i < input.size()) {
            if (input[i] == 'z') {
                for (char character : decode("z")) {
                    output.push_back(character);
                }
                i += 1;
            }
            else {
                std::string chunk(input.begin() + i, input.begin() + i + 5);
                for (char character : decode(chunk))  {
                    output.push_back(character);
                }
                i += 5;
            }
        }
        output.resize(output.size() - padding);
    }

    for (char c : output) {
        std::cout << c;
    }
    std::cout << "\n";
}
