#include <string>
#include <cstdint>
#include <iostream>


#ifndef MAIN_H
#define MAIN_H


const std::string alphabet = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstu";

std::string encode(std::string ascii_chunk) {
    size_t chunk_len = ascii_chunk.size();
    uint8_t chunk[4] = {0, 0, 0, 0};

    for (int i = 0; i < chunk_len; ++i) {
        chunk[i] = static_cast<uint8_t>(ascii_chunk[i]);
    }

    uint32_t value = (chunk[0] << 24) | (chunk[1] << 16) | (chunk[2] << 8) | chunk[3];

    if (value == 0 && chunk_len == 4) {
        return "z";
    }

    std::string encoded(5, alphabet[0]);
    for (int i = 4; i >= 0; --i) {
        encoded[i] = alphabet[value % 85];
        value /= 85;
    }

    return encoded.substr(0, chunk_len + 1);
}


std::string decode(std::string ascii85_chunk) {
    size_t chunk_len = ascii85_chunk.size();
    std::string decoded = "";
    uint32_t value;

    if (ascii85_chunk == "z") {
            value = 0;
    }
    else {
        for (char c : ascii85_chunk) {
            if (alphabet.find(c) == std::string::npos) {
                std::cout << "the message passed to decoder contains non-ascii85 symbols" << std::endl;
                exit(1);
            }
        }
        for (size_t i = 0; i < (5 - chunk_len); ++i) {
            ascii85_chunk += 'u';
        }
        value = 52200625*alphabet.find(ascii85_chunk[0]) + 614125*alphabet.find(ascii85_chunk[1]) + 7225*alphabet.find(ascii85_chunk[2]) + 85*alphabet.find(ascii85_chunk[3]) + alphabet.find(ascii85_chunk[4]);
    }

    uint8_t chunk[4];
    chunk[0] = (value >> 24) & 0xFF;
    chunk[1] = (value >> 16) & 0xFF;
    chunk[2] = (value >> 8) & 0xFF;
    chunk[3] = (value >> 0) & 0xFF;

    for (uint8_t byte : chunk) {
        decoded += static_cast<char>(byte);
    }

    return decoded.substr(0, chunk_len - 1);
}

#endif
