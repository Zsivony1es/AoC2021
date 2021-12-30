//
// Created by Peter Ivony on 17.12.21.
//

#ifndef ADVENTOFCODE_HELPERS_H
#define ADVENTOFCODE_HELPERS_H

#include "Structures.h"

#include <fstream>
#include <array>
#include <unordered_map>

class Helpers{
public:
    //Standard, can be used in any function
    static std::vector<std::string> read_from_file(std::ifstream& file);
    static std::string string_diff(std::string str1, std::string str2);
    static bool find_in_string(std::string str, char ch); // true if the given character can be found in the string
    static bool same_different_order(std::string container, std::string str2); // The two strings have the same characters and the same amount of them

    // Made for specific problems
    static std::vector<double> divide_string(std::string str);
    static uint64_t sum_of_basin(std::array<std::array<int,100>,100>& map, std::vector<std::pair<int,int>>& visited, size_t i, size_t j);
    static uint64_t sum_of_flashes(std::array<std::array<Structures::Octopus,10>,10>& map);
    static uint64_t day13solver(std::vector<Structures::Point>& points, std::vector<std::string>& folds);
    static uint64_t parse_packet(const std::string& bin, int& cnt, std::vector<uint64_t>& version_nums);
    static bool explode(std::string &str);
    static bool split(std::string &str);
    static uint64_t get_magnitude(const std::string &str);
    static std::vector<std::string> enhance_image(const std::string &img_alg, std::vector<std::string> vec, bool even);
    static uint64_t wins_in_universe(std::pair<size_t,size_t> scores, std::pair<size_t,size_t> pos, uint64_t universe_num, bool turn); // turn = true -> player 1 throws, turn = false -> player 2 throws
    static uint64_t search_for_monad(std::array<int, 14> l, std::array<int, 14> k, std::array<int, 14> m, const std::function <uint64_t (uint64_t, uint64_t)>& f);
};



#endif //ADVENTOFCODE_HELPERS_H
