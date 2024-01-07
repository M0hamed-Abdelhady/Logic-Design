//
// Created by Mohamed Abdelhady on 10/23/2023.
//

#ifndef INC_E91D1EAD42FF4AF09009FFCE47BD6E48
#define INC_E91D1EAD42FF4AF09009FFCE47BD6E48

#include "../Assistant.h"
#include <iostream>
#include <algorithm>
#include <cmath>

namespace NumberSystem {

    class binaryInt {
        std::string binary; //two's complement
        long long int decimal;
        int ones;
        bool sign, completeBytes;

    public:

        explicit binaryInt();

        explicit binaryInt(long long int Decimal, bool completeBytes = false);

        explicit binaryInt(std::string bin, char Sign = '+', bool completeBytes = false);

        binaryInt(const binaryInt &other);

        void setValue(long long Decimal);

        void setValue(const std::string &bin);

        const std::string &getBinary() const;

        long long int getDecimal() const;

        int popcount() const;

        static int popcount(const std::string &bin);

        static std::string decimalToBinary(long long int Decimal, int bits);

        static long long int binaryToDecimal(const std::string &bin);

        static std::string TwosComplementPlus1(std::string bin);

        static int determineBits(long long int Decimal, bool completeBytes);

        static int determineBits(const std::string &bin, bool completeBytes);

        static bool isInteger(const std::string &s);

        bool isBinary(const std::string &s);

        static void equalizer(std::string &a, std::string &b);


/// @operators


        binaryInt &operator=(const binaryInt &other);

        binaryInt operator++();

        const binaryInt operator++(int);

        binaryInt operator--();

        const binaryInt operator--(int);

        binaryInt operator+() const;

        binaryInt operator-() const;

        binaryInt operator!() const;

        binaryInt operator~() const;

        binaryInt operator&(const binaryInt &other) const;

        binaryInt operator|(const binaryInt &other) const;

        binaryInt operator^(const binaryInt &other) const;

        binaryInt operator>>(const binaryInt &other) const;

        binaryInt operator<<(const binaryInt &other) const;

        binaryInt operator%(const binaryInt &other) const;

        binaryInt operator*(const binaryInt &other) const;

        binaryInt operator/(const binaryInt &other) const;

        binaryInt operator+(const binaryInt &other) const;

        binaryInt operator-(const binaryInt &other) const;

        binaryInt operator&(long long int x) const;

        binaryInt operator|(long long int x) const;

        binaryInt operator^(long long int x) const;

        binaryInt operator>>(long long int x) const;

        binaryInt operator<<(long long int x) const;

        binaryInt operator*(long long int x) const;

        binaryInt operator%(long long int x) const;

        binaryInt operator/(long long int x) const;

        binaryInt operator+(long long int x) const;

        binaryInt operator-(long long int x) const;

        binaryInt operator&=(const binaryInt &other);

        binaryInt operator|=(const binaryInt &other);

        binaryInt operator^=(const binaryInt &other);

        binaryInt operator>>=(const binaryInt &other);

        binaryInt operator<<=(const binaryInt &other);

        binaryInt operator%=(const binaryInt &other);

        binaryInt operator*=(const binaryInt &other);

        binaryInt operator/=(const binaryInt &other);

        binaryInt operator+=(const binaryInt &other);

        binaryInt operator-=(const binaryInt &other);

        binaryInt operator&=(long long int x);

        binaryInt operator|=(long long int x);

        binaryInt operator^=(long long int x);

        binaryInt operator>>=(long long int x);

        binaryInt operator<<=(long long int x);

        binaryInt operator%=(long long int x);

        binaryInt operator*=(long long int x);

        binaryInt operator/=(long long int x);

        binaryInt operator+=(long long int x);

        binaryInt operator-=(long long int x);

        bool operator==(const binaryInt &other) const;

        bool operator!=(const binaryInt &other) const;

        bool operator>=(const binaryInt &other) const;

        bool operator<=(const binaryInt &other) const;

        bool operator>(const binaryInt &other) const;

        bool operator<(const binaryInt &other) const;

        bool operator==(long long int x) const;

        bool operator!=(long long int x) const;

        bool operator>=(long long int x) const;

        bool operator<=(long long int x) const;

        bool operator>(long long int x) const;

        bool operator<(long long int x) const;

        friend std::ostream &operator<<(std::ostream &out, const binaryInt &number);
    };

} // NumberSystem

#endif //INC_E91D1EAD42FF4AF09009FFCE47BD6E48
