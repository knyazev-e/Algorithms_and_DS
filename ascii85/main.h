#include <string>
#include <cstdint>


#ifndef MAIN_H
#define MAIN_H


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

#endif
