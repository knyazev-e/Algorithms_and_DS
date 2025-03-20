#include <vector>
#include <iostream>
#include <string>

const std::string alphabet = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstu";

std::string encode(uint8_t (&chunk)[4]) {
    std::string encoded = "";
    uint32_t value = (chunk[0] << 24) | (chunk[1] << 16) | (chunk[2] << 8) | chunk[3];

    if (value == 0) {
        encoded = "z";
    }

    while (vlaue > 0) {
        encoded = alphabet[value % 85] + encoded;
        value = value / 85;
    }

    return encoded;
}

uint8_t chunk[4] decode(std::string ascii_code) {

}

int main(int argc, char* argv[]) {
    // encoding/decoding mode
    bool encoding_mode = true;

    for (int i = 0; i < argc; ++i) {
        if (argv[i] == "-d") {
            encoding_mode = false;
        }
    }

    // reading the input
    std::string input;
    char byte;

    while(std::cin.get(byte)) {
        input.push_back(byte);
    }

    // calling main functions
    std::string output = "";

    if (encoding_mode) {
        // call the encoding func
        size_t padding = (4 - (input.length() % 4)) % 4;
        input.append(padding, "\0");

        for (int i = 0; i < input.length(); i+=4) {
            uint8_t chunk[4];
            for (int j = 0; j < 4; ++j) {
                chunk[j] = static_cast<uint8_t>(input[i + j]);
            }
            output += encode(&chunk[4]);
        }
        output.erase(output.length() - padding, padding);
    }

    else {
        //call the decoding func

    }
}
