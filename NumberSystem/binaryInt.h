//
// Created by Mohamed Abdelhady on 10/23/2023.
//

#ifndef INC_E91D1EAD42FF4AF09009FFCE47BD6E48
#define INC_E91D1EAD42FF4AF09009FFCE47BD6E48

#include "../Assistant.h"

namespace NumberSystem {

    class binaryInt {
        std::string binary;
        long long int decimal;
        int ones;
    public:
        class comparator {
        public:
            bool operator()(const std::set<int> &a, const std::set<int> &b) const;
        };

        explicit binaryInt();

//        explicit binaryInt(binaryInt &other);

        explicit binaryInt(long long int Decimal, bool completeBytes = false);

        explicit binaryInt(std::string bin, bool completeBytes = false);

        explicit binaryInt(long long int Decimal, int bits);

        void operator=(binaryInt &other);

        std::string operator&(binaryInt &other);

        std::string operator|(binaryInt &other);

        const std::string &getNumber() const;

        void setValue(const std::string &bin);

        void setValue(long long Decimal, bool completeBytes = false);

        void setValue(long long Decimal, int bits);

        long long int getDecimal() const;

        int popcount() const;

        static int popcount(const std::string &bin);

        static std::string decimalToBinary(long long int Decimal, bool completeBytes = false);

        std::string decimalToBinary(long long int Decimal, int bits);

        static long long int binaryToDecimal(const std::string &bin);

        static int determineBits(long long int Decimal, bool completeBytes = false);

        friend Assistant;
    };

} // NumberSystem

#endif //INC_E91D1EAD42FF4AF09009FFCE47BD6E48
