#ifndef XML_H
#define XML_H

#include <utility>
#include <cstdarg>
#include <sstream>
#include <type_traits>
#include <algorithm>
#include "serialMatrix.hpp"

namespace bkr
{
    std::mt19937 rng(std::random_device{}());
    int decimal_places = 6;
    double max_complexity = QSynth::max_complexity;
    std::string opts[4] = {"", "_inc", "_time", "_maxN"};
    //Functions to get random keys
    std::vector<int> getKeyRange(int from = 0, int to = 128);
    std::vector<double> getKeyWeigths(int n = 128, double mean = 60, double stddev = 6);
    std::vector<int> getRandomKeys(int n, int from = 0, int to = 128, double mean = 60, double stddev = 32);

    //Params to an attribute
    union Params {
        double d_val;
        int i_val;
        bool b_val;
        const char* s_val;
    };
    
    //Overrides of the to_string method
    std::string to_string(int value);
    std::string to_string(const char* value);
    std::string to_string(const std::string& value);
    std::string to_string(const bool value);
    template<typename T>
    std::string to_string(const T& value);
    std::string to_string(const Params& p);

    //First letter to lower case
    std::string fl2lc(std::string str);

    //Repeat a string n times
    std::string repeat(const char* str, int n);
};

#endif