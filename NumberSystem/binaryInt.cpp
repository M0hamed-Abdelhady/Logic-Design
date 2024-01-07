//
// Created by Mohamed Abdelhady on 10/23/2023.
//

#include "binaryInt.h"

namespace NumberSystem {
    binaryInt::binaryInt() {}

    binaryInt::binaryInt(long long int Decimal, bool completeBytes) : completeBytes(completeBytes) {
        sign = Decimal >= 0;
        decimal = Decimal;
        binary = decimalToBinary(Decimal, determineBits(Decimal, completeBytes));
        ones = popcount(binary);
    }

    binaryInt::binaryInt(std::string bin, char Sign, bool completeBytes) : completeBytes(completeBytes) {
        if (bin.empty()) throw std::invalid_argument("Invalid Argument: empty string");
        if (!isBinary(bin)) throw std::invalid_argument("Invalid Argument: non-binary string");

        Sign = (char) tolower(Sign);
        if (Sign != '2' && Sign != 't' && Sign != '-')Sign = '+';
        else if (Sign == 't')Sign = '2';

        char s = Sign == '2' ? bin[0] : (Sign == '+' ? '0' : (bin = TwosComplementPlus1(bin), '1'));
        int addonBits = determineBits(bin, completeBytes) - (int) bin.size();
        if (Sign != '2')addonBits = std::max(determineBits(bin, completeBytes) - (int) bin.size(), 1);

        sign = s - '0';
        binary = std::string(addonBits, s) + bin;
        ones = popcount(binary);
        decimal = binaryToDecimal(binary);
    }

    binaryInt::binaryInt(const binaryInt &other) {
        this->sign = other.sign;
        this->completeBytes = other.completeBytes;
        this->binary = other.binary;
        this->decimal = other.decimal;
        this->ones = other.ones;
    }

    void binaryInt::setValue(long long Decimal) {
        sign = Decimal >= 0;
        decimal = Decimal;
        binary = decimalToBinary(Decimal, determineBits(Decimal, completeBytes));
        ones = popcount(binary);
    }

    void binaryInt::setValue(const std::string &bin) {
        int addonBits = determineBits(bin, this->completeBytes) - (int) bin.size();
        this->sign = bin.front() == '0';
        this->binary = std::string(addonBits, bin.front()) + bin;
        this->ones = popcount(this->binary);
        this->decimal = binaryToDecimal(this->binary);
    }

    const std::string &binaryInt::getBinary() const {
        return binary;
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

    std::string binaryInt::decimalToBinary(long long int Decimal, int bits) {
        std::string Number(bits, '0');
        bool negative = Decimal < 0;
        Decimal = std::abs(Decimal);
        while (Decimal) {
            --bits;
            Number[bits] = (Decimal & 1) + 48;
            Decimal >>= 1;
        }
        return negative ? TwosComplementPlus1(Number) : Number;
    }

    long long int binaryInt::binaryToDecimal(const std::string &bin) {
        std::string number;
        int n = 1;

        if (bin.front() == '1')number = TwosComplementPlus1(bin), n = -n;
        else number = bin;

        long long x = 0, value = 1;
        for (auto i = number.end() - 1; i != number.begin(); --i) {
            if (*i == '1')x += value;
            value <<= 1;
        }
        return n * x;
    }

    std::string binaryInt::TwosComplementPlus1(std::string bin) {
        int index = bin.find_last_of('1') - 1;
        for (; ~index; --index)
            bin[index] = (char) (97 - (int) bin[index]);
        return bin;
    }

    int binaryInt::determineBits(long long int Decimal, bool completeBytes) {
        int n = ceil(log2(std::abs(Decimal) + 1)) + 1;
        if (completeBytes && n % 8) n += 8 - (n % 8);
        return n;
    }

    int binaryInt::determineBits(const std::string &bin, bool completeBytes) {
        int n = bin.size();
        if (completeBytes && n % 8) n += 8 - (n % 8);
        return n;
    }

    bool binaryInt::isInteger(const std::string &s) {
        std::istringstream iss(s);
        int value;
        iss >> value;
        return !iss.fail() && iss.eof();
    }

    bool binaryInt::isBinary(const std::string &s) {
        return std::all_of(s.begin(), s.end(), [&](const char &i) { return i == '0' || i == '1'; });
    }

    void binaryInt::equalizer(std::string &a, std::string &b) {
        if (a.size() < b.size()) a = std::string(b.size() - a.size(), '0') + a;
        else if (a.size() > b.size()) b = std::string(a.size() - b.size(), '0') + b;
    }


/// @operators


    binaryInt &binaryInt::operator=(const binaryInt &other) {
        if (this != &other) {
            this->binary = other.binary,
            this->decimal = other.decimal,
            this->ones = other.ones;
        }
        return *this;
    }

    binaryInt binaryInt::operator++() {
        this->setValue(++this->decimal);
        return *this;
    }

    const binaryInt binaryInt::operator++(int) {
        const binaryInt temp(*this);
        this->setValue(++this->decimal);
        return temp;
    }

    binaryInt binaryInt::operator--() {
        this->setValue(--this->decimal);
        return *this;
    }

    const binaryInt binaryInt::operator--(int) {
        const binaryInt temp(*this);
        this->setValue(--this->decimal);
        return temp;
    }

    binaryInt binaryInt::operator+() const {
        return *this;
    }

    binaryInt binaryInt::operator-() const {
        return binaryInt(-this->decimal, completeBytes);
    }

    binaryInt binaryInt::operator!() const {
        return binaryInt(!this->decimal, completeBytes);
    }

    binaryInt binaryInt::operator~() const {
        return binaryInt(~this->decimal, completeBytes);
    }

    binaryInt binaryInt::operator&(const binaryInt &other) const {
        return binaryInt(this->decimal & other.decimal, this->completeBytes);
    }

    binaryInt binaryInt::operator|(const binaryInt &other) const {
        return binaryInt(this->decimal | other.decimal, this->completeBytes);
    }

    binaryInt binaryInt::operator^(const binaryInt &other) const {
        return binaryInt(this->decimal ^ other.decimal, this->completeBytes);
    }

    binaryInt binaryInt::operator>>(const binaryInt &other) const {
        return binaryInt(this->decimal >> other.decimal, this->completeBytes);
    }

    binaryInt binaryInt::operator<<(const binaryInt &other) const {
        return binaryInt(this->decimal << other.decimal, this->completeBytes);
    }

    binaryInt binaryInt::operator%(const binaryInt &other) const {
        return binaryInt(this->decimal % other.decimal, this->completeBytes);
    }

    binaryInt binaryInt::operator*(const binaryInt &other) const {
        return binaryInt(this->decimal * other.decimal, this->completeBytes);
    }

    binaryInt binaryInt::operator/(const binaryInt &other) const {
        return binaryInt(this->decimal / other.decimal, this->completeBytes);
    }

    binaryInt binaryInt::operator+(const binaryInt &other) const {
        return binaryInt(this->decimal + other.decimal, this->completeBytes);
    }

    binaryInt binaryInt::operator-(const binaryInt &other) const {
        return binaryInt(this->decimal - other.decimal, this->completeBytes);
    }

    binaryInt binaryInt::operator&(long long int x) const {
        return binaryInt(this->decimal & x, this->completeBytes);
    }

    binaryInt binaryInt::operator|(long long int x) const {
        return binaryInt(this->decimal | x, this->completeBytes);
    }

    binaryInt binaryInt::operator^(long long int x) const {
        return binaryInt(this->decimal ^ x, this->completeBytes);
    }

    binaryInt binaryInt::operator>>(long long int x) const {
        return binaryInt(this->decimal >> x, this->completeBytes);
    }

    binaryInt binaryInt::operator<<(long long int x) const {
        return binaryInt(this->decimal << x, this->completeBytes);
    }

    binaryInt binaryInt::operator%(long long int x) const {
        return binaryInt(this->decimal % x, this->completeBytes);
    }

    binaryInt binaryInt::operator*(long long int x) const {
        return binaryInt(this->decimal * x, this->completeBytes);
    }

    binaryInt binaryInt::operator/(long long int x) const {
        return binaryInt(this->decimal / x, this->completeBytes);
    }

    binaryInt binaryInt::operator+(long long int x) const {
        return binaryInt(this->decimal + x, this->completeBytes);
    }

    binaryInt binaryInt::operator-(long long int x) const {
        return binaryInt(this->decimal - x, this->completeBytes);
    }

    binaryInt binaryInt::operator&=(const binaryInt &other) {
        this->setValue(this->decimal & other.decimal);
        return *this;
    }

    binaryInt binaryInt::operator|=(const binaryInt &other) {
        this->setValue(this->decimal | other.decimal);
        return *this;
    }

    binaryInt binaryInt::operator^=(const binaryInt &other) {
        this->setValue(this->decimal ^ other.decimal);
        return *this;
    }

    binaryInt binaryInt::operator>>=(const binaryInt &other) {
        this->setValue(this->decimal >> other.decimal);
        return *this;
    }

    binaryInt binaryInt::operator<<=(const binaryInt &other) {
        this->setValue(this->decimal << other.decimal);
        return *this;
    }

    binaryInt binaryInt::operator%=(const binaryInt &other) {
        this->setValue(this->decimal % other.decimal);
        return *this;
    }

    binaryInt binaryInt::operator*=(const binaryInt &other) {
        this->setValue(this->decimal * other.decimal);
        return *this;
    }

    binaryInt binaryInt::operator/=(const binaryInt &other) {
        this->setValue(this->decimal / other.decimal);
        return *this;
    }

    binaryInt binaryInt::operator+=(const binaryInt &other) {
        this->setValue(this->decimal + other.decimal);
        return *this;
    }

    binaryInt binaryInt::operator-=(const binaryInt &other) {
        this->setValue(this->decimal - other.decimal);
        return *this;
    }

    binaryInt binaryInt::operator&=(long long int x) {
        this->setValue(this->decimal & x);
        return *this;
    }

    binaryInt binaryInt::operator|=(long long int x) {
        this->setValue(this->decimal | x);
        return *this;
    }

    binaryInt binaryInt::operator^=(long long int x) {
        this->setValue(this->decimal ^ x);
        return *this;
    }

    binaryInt binaryInt::operator>>=(long long int x) {
        this->setValue(this->decimal >> x);
        return *this;
    }

    binaryInt binaryInt::operator<<=(long long int x) {
        this->setValue(this->decimal << x);
        return *this;
    }

    binaryInt binaryInt::operator%=(long long int x) {
        this->setValue(this->decimal % x);
        return *this;
    }

    binaryInt binaryInt::operator*=(long long int x) {
        this->setValue(this->decimal * x);
        return *this;
    }

    binaryInt binaryInt::operator/=(long long int x) {
        this->setValue(this->decimal / x);
        return *this;
    }

    binaryInt binaryInt::operator+=(long long int x) {
        this->setValue(this->decimal + x);
        return *this;
    }

    binaryInt binaryInt::operator-=(long long int x) {
        this->setValue(this->decimal - x);
        return *this;
    }

    bool binaryInt::operator==(const binaryInt &other) const {
        return this->decimal == other.decimal;
    }

    bool binaryInt::operator!=(const binaryInt &other) const {
        return this->decimal != other.decimal;
    }

    bool binaryInt::operator>=(const binaryInt &other) const {
        return this->decimal >= other.decimal;
    }

    bool binaryInt::operator<=(const binaryInt &other) const {
        return this->decimal <= other.decimal;
    }

    bool binaryInt::operator>(const binaryInt &other) const {
        return this->decimal > other.decimal;
    }

    bool binaryInt::operator<(const binaryInt &other) const {
        return this->decimal < other.decimal;
    }

    bool binaryInt::operator==(long long int x) const {
        return this->decimal == x;
    }

    bool binaryInt::operator!=(long long int x) const {
        return this->decimal != x;
    }

    bool binaryInt::operator>=(long long int x) const {
        return this->decimal >= x;
    }

    bool binaryInt::operator<=(long long int x) const {
        return this->decimal <= x;
    }

    bool binaryInt::operator>(long long int x) const {
        return this->decimal > x;
    }

    bool binaryInt::operator<(long long int x) const {
        return this->decimal < x;
    }

    std::ostream &operator<<(std::ostream &out, const binaryInt &number) {
        out << number.decimal << ' ' << number.binary;
        return out;
    }

} // NumberSystem