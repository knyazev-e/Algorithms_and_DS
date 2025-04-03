#include <iostream>
#include <string>


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
    std::string output = "";
    std::string input;
    char byte;
    while(std::cin.get(byte)) {
        input.push_back(byte);
    }

    // decoding/encoding process
    if (encoding_mode) {
        size_t padding = (4 - (input.length() % 4)) % 4;
        input.append(padding, '\0');

        for (int i = 0; i < input.length(); i+=4) {
            output += encode(input.substr(i, 4));
        }
        padding = padding * 5/4;
        output.erase(output.length() - padding, padding);
    }

    else {
        size_t padding = (5 - (input.length() % 5)) % 5;
        input.append(padding, 'u');

        int i = 0;
        while (i < input.length()) {
            if (input[i] == 'z') {
                output += decode("z");
                i += 1;
            }
            else {
                output += decode(input.substr(i, 5));
                i += 5;
            }
        }
        output.erase(output.length() - padding, padding);
    }

    std::cout << output << std::endl;
    std::cout << "the code finished executing" << std::endl;
}
