//
// Created by Peter Ivony on 17.12.21.
//
#include <sstream>
#include "Helpers.h"

// Standard
std::vector<std::string> Helpers::read_from_file(std::ifstream& file){

    std::vector<std::string> to_return;

    if (file.is_open()){
        std::string temp;
        while (file.good()){
            temp = "";
            file >> temp;
            to_return.push_back(temp);
        }
    }
    file.close();

    return to_return;
}
std::vector<double> Helpers::divide_string(std::string str){
    std::vector<double> ret;
    size_t last=0;

    for (size_t i{0}; i < str.size(); ++i){
        if (str.at(i) == ','){
            ret.push_back(std::stoi(str.substr(last,i)));
            last = i+1;
        }
    }

    ret.push_back(std::stoi(str.substr(last,str.npos)));
    return ret;
}
std::string Helpers::string_diff(std::string str1, std::string str2){
    std::string k = str2;
    for (const char& ch : k){
        auto it= std::find(std::begin(str1),std::end(str1),ch);
        if (it != str1.end())
            str1.erase(it);
    }
    std::string ret = str1;
    return ret;
}
bool Helpers::find_in_string(std::string str, char ch){
    for (auto i{str.begin()}; i != str.end(); ++i){
        if (*i == ch)
            return true;
    }
    return false;
}
bool Helpers::same_different_order(std::string container, std::string str2){
    if (container.size() != str2.size())
        return false;
    bool asd[3] = {std::all_of(str2.begin(),str2.end(),[&container](const char& ch){return Helpers::find_in_string(container, ch);}),
                   Helpers::string_diff(container,str2).empty(),
                   Helpers::string_diff(str2,container).empty()
    };
    return asd[0] && asd[1] && asd[2];
}

// Specific
uint64_t Helpers::sum_of_basin(std::array<std::array<int,100>,100>& map, std::vector<std::pair<int,int>>& visited, size_t i, size_t j) {

    if (map[i][j] == 9 ||
        std::find(visited.begin(), visited.end(), std::pair(static_cast<int>(i), static_cast<int>(j))) != visited.end())
        return 0;
    visited.emplace_back(i, j);
    uint64_t sum = 1;
    if (i + 1 < 100)
        sum += sum_of_basin(map, visited, i + 1, j);
    if (i > 0)
        sum += sum_of_basin(map, visited, i - 1, j);
    if (j > 0)
        sum += sum_of_basin(map, visited, i, j - 1);
    if (j + 1 < 100)
        sum += sum_of_basin(map, visited, i, j + 1);

    return sum;
}
uint64_t Helpers::sum_of_flashes(std::array<std::array<Structures::Octopus,10>,10>& map){

    bool flash = true;
    uint64_t flashes = 0;

    Structures::Octopus oct = 3;

    // Inc by 1
    for (size_t i{0}; i < 10; ++i)
        for (size_t j{0}; j < 10; ++j)
            map[i][j].energy++;

    while (flash){
        // Flashing
        size_t cnt2 = 0;
        for (size_t i{0}; i < 10; ++i){
            size_t cnt1 = 0;
            for (size_t j{0}; j < 10; ++j){
                if (map[i][j].energy > 9 && !map[i][j].flashed){
                    map[i][j].flashed = true;
                    if (i > 0)
                        map[i-1][j].energy++;
                    if (j > 0)
                        map[i][j-1].energy++;
                    if (i < 9)
                        map[i+1][j].energy++;
                    if (j < 9)
                        map[i][j+1].energy++;
                    if (i > 0 && j > 0)
                        map[i-1][j-1].energy++;
                    if (i > 0 && j < 9)
                        map[i-1][j+1].energy++;
                    if (i < 9 && j > 0)
                        map[i+1][j-1].energy++;
                    if (i < 9  && j < 9)
                        map[i+1][j+1].energy++;
                } else
                    cnt1++;
            }
            if (cnt1 == 10)
                cnt2++;
        }
        if (cnt2 == 10){
            flash = false;
            for (size_t i{0}; i < 10; ++i)
                for (size_t j{0}; j < 10; ++j)
                    if (map[i][j].flashed){
                        map[i][j].energy = 0;
                        map[i][j].flashed = false;
                        flashes++;
                    }
        }
    }
    return flashes;
}
uint64_t Helpers::day13solver(std::vector<Structures::Point>& points, std::vector<std::string>& folds){
    size_t lastx=1, lasty=1;
    for (const auto& f : folds) {
        size_t num = std::stoi(f.substr(2, std::string::npos));
        if (f.at(0) == 'x') {
            lastx = num;
            std::vector<Structures::Point> to_transform;
            for (const Structures::Point &p: points)
                if (p.x > num)
                    to_transform.push_back(p);
            points.erase(std::remove_if(points.begin(), points.end(), [&num](Structures::Point p) { return p.x >= num; }),
                         points.end());
            for (const Structures::Point &p: to_transform) {
                bool exists = false;
                Structures::Point to_add = Structures::Point(num - (p.x - num), p.y);
                for (const Structures::Point &p1: points)
                    if (p1 == to_add) {
                        exists = true;
                        break;
                    }
                if (!exists)
                    points.push_back(to_add);
            }

        } else if (f.at(0) == 'y') {
            lasty = num;
            std::vector<Structures::Point> to_transform;
            for (const Structures::Point &p: points)
                if (p.y > num)
                    to_transform.push_back(p);
            points.erase(std::remove_if(points.begin(), points.end(), [&num](Structures::Point p) { return p.y >= num; }),
                         points.end());
            for (const Structures::Point &p: to_transform) {
                bool exists = false;
                Structures::Point to_add = Structures::Point(p.x, num - (p.y - num));
                for (const Structures::Point &p1: points)
                    if (p1 == to_add) {
                        exists = true;
                        break;
                    }
                if (!exists)
                    points.push_back(to_add);
            }
        }
        if (lasty != 1 && lastx != 1){ // This just makes the output file

            std::ofstream outfile;
            outfile.open("../outputs/day13.txt");

            char img[lastx][lasty];
            for (size_t i{0}; i < lastx; ++i)
                for (size_t j{0}; j < lasty; ++j)
                    img[i][j] = '.';

            for (const auto &p: points)
                img[p.x][p.y] = '#';

            for (size_t j{0}; j < lasty; ++j) {
                for (size_t i{0}; i < lastx; ++i)
                    outfile << img[i][j];
                outfile << std::endl;
            }
            outfile.close();
        }
    }

    return points.size();
}
uint64_t Helpers::parse_packet(const std::string& bin, int& cnt, std::vector<uint64_t>& version_nums){

    version_nums.push_back(std::bitset<3>(bin.substr(cnt,cnt+3)).to_ulong());
    cnt+=3;
    int packet_type = std::bitset<3>(bin.substr(cnt,cnt+3)).to_ulong();
    cnt+=3;

    if (packet_type == 4){
        std::string num;
        while (true){
            num += bin.substr(cnt+1,4);
            if (bin[cnt] == '0'){
                cnt += 5;
                break;
            }
            cnt += 5;
        }
        uint64_t res = 0;
        for (size_t i{0}; i < num.size(); ++i)
            if (num[i] == '1')
                res += pow(2,num.size()-1-i);

        return res;
    }

    cnt++;
    std::vector<uint64_t> ret;
    if (bin[cnt-1] == '1'){

        size_t loops = std::bitset<11>(bin.substr(cnt,cnt+11)).to_ulong();
        cnt += 11;

        for (size_t i{0}; i < loops; ++i)
            ret.push_back(parse_packet(bin, cnt, version_nums));

    } else {

        uint64_t length = std::bitset<15>(bin.substr(cnt,cnt+15)).to_ulong();
        cnt += 15;

        size_t asd = cnt;
        while (int(cnt)-int(asd) < length)
            ret.push_back(parse_packet(bin, cnt, version_nums));

    }

    uint64_t to_ret = 0;

    switch (packet_type){
        case 0:
            std::for_each(ret.begin(), ret.end(), [&to_ret](auto n){to_ret += n;});
            break;
        case 1:
            to_ret = 1;
            std::for_each(ret.begin(), ret.end(), [&to_ret](auto n){to_ret *= n;});
            break;
        case 2:
            to_ret = *std::min_element(ret.begin(), ret.end());
            break;
        case 3:
            to_ret = *std::max_element(ret.begin(), ret.end());
            break;
        case 5:
            to_ret = (ret.at(0) > ret.at(1));
            break;
        case 6:
            to_ret = (ret.at(0) < ret.at(1));
            break;
        case 7:
            to_ret = (ret.at(0) == ret.at(1));
            break;
    }

    return to_ret;

}
bool Helpers::reduce_snailnum(std::string &str) {
    std::stack<char> st;
    for (int i{0}; i < str.size(); ++i){

        if (str[i] == '[')
            st.push('[');
        else if (str[i] == ']')
            st.pop();

        // Explosion
        if (st.size() == 5){

            size_t pos_begin = i, pos_comma;
            while (str[i] != ']'){
                if (str[i] == ',')
                    pos_comma = i;
                i++;
            }
            size_t pos_end = i;

            // Save the 2 numbers
            int pair[2] = {std::stoi(str.substr(pos_begin+1,pos_comma)), std::stoi(str.substr(pos_comma+1,pos_end))};

            //Check if comma is before or after pair
            if (str[pos_end+1] == ','){

                // Replace the number after with the added value (if exists)
                i = pos_end;
                while (str[i] == '[' || str[i] == ',' || str[i] == ']')
                    ++i;

                if (i < str.size()-1){
                    int a = i;
                    while (str[i] != '[' && str[i] != ',' && str[i] != ']')
                        i++;
                    str.replace(a,i-a, std::to_string( std::stoi(str.substr(a,i)) + pair[1]));
                }

                // Replace the bracket expression with 0
                i = pos_begin;
                str.replace(pos_begin,pos_end-pos_begin+2,"0,");

                // Replace the number before with the added value (if exists)
                i = pos_begin-1;
                while (str[i] == '[' || str[i] == ',' || str[i] == ']'){
                    --i;
                    if (i < 0)
                        break;
                }
                if (i > 0){
                    int a = i;
                    while (str[i] != '[' && str[i] != ',' && str[i] != ']')
                        --i;
                    str.replace(i+1,a-i, std::to_string( std::stoi(str.substr(i+1,a-i)) + pair[0]));
                }

                return true;

            } else if (str[pos_begin-1] == ','){
                // Replace the number after with the added value (if exists)
                while (str[i] == '[' || str[i] == ',' || str[i] == ']')
                    ++i;
                if (i < str.size()-1){
                    int a = i;
                    while (str[i] != '[' && str[i] != ',' && str[i] != ']')
                        i++;
                    str.replace(a,i-a, std::to_string( std::stoi(str.substr(a,i)) + pair[1]));
                }

                // Replace the bracket expression with 0
                i = pos_begin;
                str.replace(pos_begin,pos_end-pos_begin+1,"0");

                // Replace the number before with the added value (if exists)
                i = pos_begin-1;
                while (str[i] == '[' || str[i] == ',' || str[i] == ']'){
                    --i;
                    if (i < 0)
                        break;
                }
                if (i > 0){
                    int a = i;
                    while (str[i] != '[' && str[i] != ',' && str[i] != ']')
                        --i;
                    str.replace(i+1,a-i, std::to_string( std::stoi(str.substr(i+1,a-i)) + pair[0]));
                }

                return true;
            }

        }

        // Split
        if (str[i] != '[' && str[i] != ']' && str[i] != ',' && str[i+1] != '[' && str[i+1] != ']' && str[i+1] != ','){
            int nm = (static_cast<int>(str[i]) - 48)*10 + static_cast<int>(str[i+1]) - 48;
            str.replace(i,2, "[" + std::to_string(nm/2) + "," + std::to_string(static_cast<int>(std::ceil(static_cast<float>(nm)/2))) +"]");
            return true;
        }

    }

    return false;

}
bool Helpers::explode(std::string &str) {

    std::stack<char> st;
    int i = 0, count_brackets = 0;
    bool explod = false;
    for (; i < str.size(); ++i) {
        if (str[i] == '[')
            count_brackets++;
        else if (str[i] == ']' && count_brackets != 0)
            count_brackets--;
        if (count_brackets >= 5 && str[i+1] != '['){
            explod = true;
            break;
        }
    }

    if (explod){

        size_t pos_begin = i, pos_comma;
        while (str[i] != ']') {
            if (str[i] == ',')
                pos_comma = i;
            i++;
        }
        size_t pos_end = i;

        // Save the 2 numbers
        int pair[2] = {std::stoi(str.substr(pos_begin + 1, pos_comma)),
                       std::stoi(str.substr(pos_comma + 1, pos_end))};

        //Check if comma is before or after pair
        if (str[pos_end + 1] == ',') {

            // Replace the number after with the added value (if exists)
            i = pos_end;
            while (str[i] == '[' || str[i] == ',' || str[i] == ']')
                ++i;

            if (i < str.size() - 1) {
                int a = i;
                while (str[i] != '[' && str[i] != ',' && str[i] != ']')
                    i++;
                str.replace(a, i - a, std::to_string(std::stoi(str.substr(a, i)) + pair[1]));
            }

            // Replace the bracket expression with 0
            i = pos_begin;
            str.replace(pos_begin, pos_end - pos_begin + 2, "0,");

            // Replace the number before with the added value (if exists)
            i = pos_begin - 1;
            while (str[i] == '[' || str[i] == ',' || str[i] == ']') {
                --i;
                if (i < 0)
                    break;
            }
            if (i > 0) {
                int a = i;
                while (str[i] != '[' && str[i] != ',' && str[i] != ']')
                    --i;
                str.replace(i + 1, a - i, std::to_string(std::stoi(str.substr(i + 1, a - i)) + pair[0]));
            }
            return true;

        } else if (str[pos_begin - 1] == ',') {
            // Replace the number after with the added value (if exists)
            while (str[i] == '[' || str[i] == ',' || str[i] == ']')
                ++i;
            if (i < str.size() - 1) {
                int a = i;
                while (str[i] != '[' && str[i] != ',' && str[i] != ']')
                    i++;
                str.replace(a, i - a, std::to_string(std::stoi(str.substr(a, i)) + pair[1]));
            }

            // Replace the bracket expression with 0
            i = pos_begin;
            str.replace(pos_begin, pos_end - pos_begin + 1, "0");

            // Replace the number before with the added value (if exists)
            i = pos_begin - 1;
            while (str[i] == '[' || str[i] == ',' || str[i] == ']') {
                --i;
                if (i < 0)
                    break;
            }
            if (i > 0) {
                int a = i;
                while (str[i] != '[' && str[i] != ',' && str[i] != ']')
                    --i;
                str.replace(i + 1, a - i, std::to_string(std::stoi(str.substr(i + 1, a - i)) + pair[0]));
            }
            return true;
        }

    }
    return false;
}
bool Helpers::split(std::string &str) {

    std::stack<char> st;
    for (int i{0}; i < str.size(); ++i) {

        if (str[i] == '[')
            st.push('[');
        else if (str[i] == ']')
            st.pop();

        if (str[i] != '[' && str[i] != ']' && str[i] != ',' && str[i+1] != '[' && str[i+1] != ']' && str[i+1] != ','){
            int nm = (static_cast<int>(str[i]) - 48)*10 + static_cast<int>(str[i+1]) - 48;
            str.replace(i,2, "[" + std::to_string(nm/2) + "," + std::to_string(static_cast<int>(std::ceil(static_cast<float>(nm)/2))) +"]");
            return true;
        }
    }


    return false;
}
uint64_t Helpers::get_magnitude(const std::string& str){

    if (str.size() == 1){
        return static_cast<int>(str[0]) - 48;
    }

    std::stack<char> st;
    size_t comma_loc, ada=0;
    for (size_t i{0}; i < str.size(); ++i){
        if (str[i] == '[')
            st.push('[');
        else if (str[i] == ']')
            st.pop();
        if (st.size() == 1){
            if (ada == 1)
                comma_loc = i+1;
            ++ada;
        }

    }

    return 3*Helpers::get_magnitude(str.substr(1,comma_loc-1)) + 2*Helpers::get_magnitude(str.substr(comma_loc+1,str.size()-comma_loc-2));

}
