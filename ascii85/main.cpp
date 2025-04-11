#include <iostream>
#include <string>
#include <cstdint>
#include <vector>


const std::string alphabet = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstu";


std::string encode(std::string ascii_chunk) {
    std::string encoded = "";
    uint8_t chunk[4];

    for (int i = 0; i < 4; ++i) {
        chunk[i] = static_cast<uint8_t>(ascii_chunk[i]);
    }

    uint32_t value = (chunk[0] << 24) | (chunk[1] << 16) | (chunk[2] << 8) | chunk[3];

    if (value == 0) {
        encoded = "z";
    }

    while (value > 0) {
        encoded = alphabet[value % 85] + encoded;
        value = value / 85;
    }

    return encoded;
}


std::string decode(std::string ascii85_chunk) {
    std::string decoded = "";
    uint32_t value;

    if (ascii85_chunk == "z") { value = 0; }
    else { value = 52200625*alphabet.find(ascii85_chunk[0]) + 614125*alphabet.find(ascii85_chunk[1]) + 7225*alphabet.find(ascii85_chunk[2]) + 85*alphabet.find(ascii85_chunk[3]) + alphabet.find(ascii85_chunk[4]); }

    uint8_t chunk[4];
    chunk[0] = (value >> 24) & 0xFF;
    chunk[1] = (value >> 16) & 0xFF;
    chunk[2] = (value >> 8) & 0xFF;
    chunk[3] = (value >> 0) & 0xFF;

    for (uint8_t byte : chunk) {
        decoded += static_cast<char>(byte);
    }

    return decoded;
}


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

    std::cout << input.size() << std::endl;
    std::cout << "first symbol:" << input[0] << "\nlast symbol:" << input[input.size() - 1] << static_cast<int>(input[input.size() - 1]) << std::endl;

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
        std::cout << output.size() << std::endl;
        output.resize(output.size() - padding);
        std::cout << output.size() << std::endl;
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
    std::cout << "\nthe code finished executing" << std::endl;
}
