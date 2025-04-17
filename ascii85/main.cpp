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
        size_t chunk_count = input.size() / 4;
        size_t remaining = input.size() % 4;

        for (int i = 0; i < chunk_count*4; i+=4) {
            std::string chunk(input.begin() + i, input.begin() + i + 4);
            for (char c : encode(chunk)) {
                output.push_back(c);
            }
        }

        if (remaining > 0) {
            std::string chunk(input.end() - remaining, input.end());
            for (char c : encode(chunk)) {
                output.push_back(c);
            }
        }
    }

    // decoding process
    else {
        if (static_cast<int>(input[input.size() - 1]) == 10) {
            input.erase(input.begin() + input.size() - 1);
        }

        size_t chunk_count = input.size() / 5;
        size_t remaining = input.size() % 5;

        int i = 0;
        while (i < input.size()) {
            if (input[i] == 'z') {
                for (char c : decode("z")) {
                    output.push_back(c);
                }
                i += 1;
            }
            else {
                size_t chunk_len = std::min(static_cast<size_t>(5), input.size() - i);
                std::string chunk(input.begin() + i, input.begin() + i + chunk_len);
                for (char c : decode(chunk))  {
                    output.push_back(c);
                }
                i += chunk_len;
            }
        }
    }

    for (char c : output) {
        std::cout << c;
    }

    return 0;
}
