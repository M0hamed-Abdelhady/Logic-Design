//
// Created by Mohamed Abdelhady on 10/23/2023.
//

#include "binaryInt.h"

namespace NumberSystem {
    bool binaryInt::comparator::operator()(const std::set<int> &a, const std::set<int> &b) const {
        if (a.size() == b.size()) {
            auto ai = a.begin(), bi = b.begin();
            while (*ai == *bi) ++ai, ++bi;
            return binaryInt(*ai).popcount() < binaryInt(*ai).popcount();
        } else return a.size() > b.size();
    }

    binaryInt::binaryInt() {}

//    binaryInt::binaryInt(binaryInt &other) {
//        this->binary = other.binary,
//        this->decimal = other.decimal,
//        this->ones = other.ones;
//    }

    binaryInt::binaryInt(long long int Decimal, bool completeBytes) {
        decimal = Decimal;
        binary = decimalToBinary(Decimal, completeBytes);
        ones = popcount(binary);
    }

    binaryInt::binaryInt(long long int Decimal, int bits) {
        decimal = Decimal;
        binary = decimalToBinary(Decimal, bits);
        ones = popcount(binary);

    }

    binaryInt::binaryInt(std::string bin, bool completeBytes) {
        int n;
        ones = popcount(bin);
        decimal = binaryToDecimal(bin);
        if (completeBytes) {
            int currentSize = bin.size();
            double bs2 = log2(currentSize);
            if (!Assistant::isInteger(std::to_string(bs2)))
                binary = std::string(pow(2, ceil(bs2)) - currentSize, '0') + bin;
        } else binary = bin;
    }

    void binaryInt::operator=(binaryInt &other) {
        this->binary = other.binary,
        this->decimal = other.decimal,
        this->ones = other.ones;
    }

    std::string binaryInt::operator&(binaryInt &other) {
        Assistant::equalizer(this->binary, other.binary);
        std::string res(this->binary.size(), '0');
        for (int i = 0; i < this->binary.size(); ++i)
            if (this->binary[i] == '1' && other.binary[i] == '1')res[i] = '1';
        return res;
    }

    std::string binaryInt::operator|(binaryInt &other) {
        Assistant::equalizer(this->binary, other.binary);
        std::string res(this->binary.size(), '0');
        for (int i = 0; i < this->binary.size(); ++i)
            if (this->binary[i] == '1' || other.binary[i] == '1')res[i] = '1';
        return res;
    }

    const std::string &binaryInt::getNumber() const {
        return binary;
    }

    void binaryInt::setValue(long long Decimal, bool completeBytes) {
        decimal = Decimal;
        binary = decimalToBinary(Decimal);
        ones = popcount(binary);
    }

    void binaryInt::setValue(long long Decimal, int bits) {
        decimal = Decimal;
        binary = decimalToBinary(Decimal, bits);
        ones = popcount(binary);
    }

    void binaryInt::setValue(const std::string &bin) {
        ones = 0;
        binary = bin;
        decimal = binaryToDecimal(bin);
        for (const auto &c: bin) if (c == '1')++ones;
    }

    long long int binaryInt::getDecimal() const {
        return decimal;
    }

    int binaryInt::popcount() const { return this->ones; }

    int binaryInt::popcount(const std::string &bin) {
        int one = 0;
        for (const auto &c: bin) if (c == '1')++one;
        return one;
    }

    std::string binaryInt::decimalToBinary(long long int Decimal, bool completeBytes) {
        int n = determineBits(Decimal, completeBytes);
        std::string Number(n, '0');
        while (Decimal) {
            --n;
            Number[n] = (Decimal & 1) + 48;
            Decimal >>= 1;
        }
        return Number;
    }

    std::string binaryInt::decimalToBinary(long long int Decimal, int bits) {
        int n = std::max(bits, determineBits(Decimal));
        std::string Number(n, '0');
        while (Decimal) {
            --n;
            Number[n] = (Decimal & 1) + 48;
            Decimal >>= 1;
        }
        return Number;
    }

    long long binaryInt::binaryToDecimal(const std::string &bin) {
        int x = 0, value = 1;
        for (auto i = bin.rbegin(); i != bin.rend(); ++i) {
            if (*i == '1')x += value;
            value <<= 1;
        }
        return x;
    }

    int binaryInt::determineBits(long long int Decimal, bool completeBytes) {
        int n = ceil(log2(Decimal + 1));
        if (completeBytes && n % 8 != 0) n = n + 8 - (n % 8);
        return n;
    }


} // NumberSystem