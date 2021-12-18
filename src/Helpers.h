//
// Created by Peter Ivony on 17.12.21.
//

#ifndef ADVENTOFCODE_HELPERS_H
#define ADVENTOFCODE_HELPERS_H

#include "Structures.h"

#include <fstream>
#include <array>

class Helpers{
public:
    //Standard, can be used in any function
    static std::vector<std::string> read_from_file(std::ifstream& file);
    static std::vector<double> divide_string(std::string str);
    static std::string string_diff(std::string str1, std::string str2);
    static bool find_in_string(std::string str, char ch);
    static bool same_different_order(std::string container, std::string str2);

    // Made for specific problems
    static uint64_t sum_of_basin(std::array<std::array<int,100>,100>& map, std::vector<std::pair<int,int>>& visited, size_t i, size_t j);
    static uint64_t sum_of_flashes(std::array<std::array<Structures::Octopus,10>,10>& map);
    static uint64_t day13solver(std::vector<Structures::Point>& points, std::vector<std::string>& folds);
    static uint64_t parse_packet(const std::string& bin, int& cnt, std::vector<uint64_t>& version_nums);
    static bool reduce_snailnum(std::string& str);
    static bool explode(std::string &str);
    static bool split(std::string &str);
    static uint64_t get_magnitude(const std::string &str);
};



#endif //ADVENTOFCODE_HELPERS_H
