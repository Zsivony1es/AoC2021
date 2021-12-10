#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <stdexcept>
#include <chrono>
#include <array>
#include <map>

#define NC "\e[0m"
#define RED "\e[0;31m"

std::vector<std::string> read_from_file(std::ifstream& file){

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
std::vector<double> divide_string(std::string str){
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
std::string string_diff(std::string str1, std::string str2){
    std::string k = str2;
    for (const char& ch : k){
        auto it= std::find(std::begin(str1),std::end(str1),ch);
        if (it != str1.end())
            str1.erase(it);
    }
    std::string ret = str1;
    return ret;
}
bool find_in_string(std::string str, char ch){
    for (auto i{str.begin()}; i != str.end(); ++i){
        if (*i == ch)
            return true;
    }
    return false;
}
bool same_different_order(std::string container, std::string str2){
    if (container.size() != str2.size())
        return false;
    bool asd[3] = {std::all_of(str2.begin(),str2.end(),[&container](const char& ch){return find_in_string(container, ch);}),
                       string_diff(container,str2).empty(),
                       string_diff(str2,container).empty()
                  };
    return asd[0] && asd[1] && asd[2];
}
uint64_t sum_of_basin(std::array<std::array<int,100>,100>& map, std::vector<std::pair<int,int>>& visited, size_t i, size_t j) {

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
// For day 4
struct TableElement{
    bool called;
    int val;
};
const size_t TABLE_SIZE = 5;
class BingoTable{
public:
    TableElement table[TABLE_SIZE][TABLE_SIZE];
    BingoTable(std::vector<int> contents){
        if (contents.size() != pow(TABLE_SIZE,2))
            throw std::runtime_error("Invalid vector size!");
        for (size_t i{0}; i < TABLE_SIZE; ++i){
            for (size_t j{0}; j < TABLE_SIZE; ++j){
                table[i][j].val = contents.at(i*TABLE_SIZE + j);
                table[i][j].called = false;
            }
        }
    }
    //Sets called member of TableElement true if number was called
    void numberCalled(int num){
        for (size_t i{0}; i < TABLE_SIZE; ++i) {
            for (size_t j{0}; j < TABLE_SIZE; ++j) {
                if (table[i][j].val == num)
                    table[i][j].called = true;
            }
        }
    }
    // Returns true if table has bingo, false otherwise
    bool checkBingo(){
        for (size_t i{0}; i < TABLE_SIZE; ++i) {
            int cnt1 = 0, cnt2 = 0;
            for (size_t j{0}; j < TABLE_SIZE; ++j) {
                if (table[i][j].called)
                    cnt1++;
                if (table[j][i].called)
                    cnt2++;
            }
            if (cnt1 == TABLE_SIZE)
                return true;
            if (cnt2 == TABLE_SIZE)
                return true;
        }
        return false;
    }
    int sum_of_not_called(){
        int sum{0};
        for (size_t i{0}; i < TABLE_SIZE; ++i) {
            for (size_t j{0}; j < TABLE_SIZE; ++j) {
                if (!table[i][j].called)
                    sum += table[i][j].val;
            }
        }
        return sum;
    }
    std::string to_string(){
        std::string to_ret="";
        for (size_t i{0}; i < TABLE_SIZE; ++i) {
            for (size_t j{0}; j < TABLE_SIZE; ++j) {
                if (table[i][j].called)
                    to_ret += RED;
                else
                    to_ret += NC;
                to_ret += std::to_string(table[i][j].val) + " ";
            }
            to_ret.erase(to_ret.end()-1);
            to_ret += '\n';
        }
        to_ret.erase(to_ret.end()-1);
        to_ret += NC;
        return to_ret;
    }

    bool operator==(BingoTable ro){
        if (this->to_string() == ro.to_string())
            return true;
        return false;
    }
};

// For day 5
class Point{
public:
    int x = 0, y = 0;
    Point() = default;
    Point(int x,int y){
        this->x = x;
        this->y = y;
    }
    Point(const Point& p){
        this->x = p.x;
        this->y = p.y;
    }
    std::string to_string() const{
        return reinterpret_cast<const char *>('(' + x + ',' + y + ')');
    }
};
class Line{
public:
    Point begin, end;
    Line(const Point& begin, const Point& end){
        this->begin = Point(begin.x, begin.y);
        this->end = Point(end.x, end.y);
    }
    Line(int x1, int y1, int x2, int y2){
        this->begin = Point(x1,y1);
        this->end = Point(x2, y2);
    }
    std::vector<Point> getAllPoints() const {
        std::vector<Point> ret;
        if (begin.x == end.x) // x coordinates are same - vertical
            if (begin.y <= end.y)
                for (int i{begin.y}; i <= end.y; ++i)
                    ret.emplace_back(begin.x, i);
            else
                for (int i{end.y}; i <= begin.y; ++i)
                    ret.emplace_back(begin.x, i);
        else if (begin.y == end.y) // y coordinates are same - horizontal
            if (begin.x <= end.x)
                for (int i{begin.x}; i <= end.x; ++i)
                    ret.emplace_back(i, begin.y);
            else
                for (int i{end.x}; i <= begin.x; ++i)
                    ret.emplace_back(i, begin.y);
        else if (end.x - begin.x == end.y - begin.y) // 45° diagonal increasing
            if (begin.x <= end.x)
                for (int i{0}; i <= (end.x-begin.x); ++i)
                    ret.emplace_back(begin.x+i,begin.y+i);
            else
                for (int i{0}; i <= (begin.x-end.x); ++i)
                    ret.emplace_back(begin.x-i,begin.y-i);
        else if (end.x - begin.x == - (end.y - begin.y) ) // 45° diagonal decreasing
            if (begin.x <= end.x)
                for (int i{0}; i <= (end.x-begin.x); ++i)
                    ret.emplace_back(begin.x+i,begin.y-i);
            else
                for (int i{0}; i <= (begin.x-end.x); ++i)
                    ret.emplace_back(begin.x-i,begin.y+i);

        return ret;
    }
    friend std::ostream& operator<<(std::ostream& os, const Line& l);
};
std::ostream& operator<<(std::ostream& os, const Point& p){
    return os << '(' << p.x << ',' << p.y << ')';
}
std::ostream& operator<<(std::ostream& os, const Line& l){
    return os << l.begin << " -> " << l.end;
}

uint64_t d1t1(){
    std::ifstream file;
    file.open("/Users/peterivony/Documents/VSCode Projects/AdventOfCode/inputs/day1.txt");
    std::vector<std::string> set = read_from_file(file);
    bool first = true;
    int cntr = 0;
    int prev_num;
    for (const auto& el : set){

        if (first)
            first = false;
        else
        if (prev_num < std::stoi(el))
            cntr++;
        prev_num = std::stoi(el);
    }
    return cntr;
}
uint64_t d1t2(){
    std::ifstream file;
    file.open("/Users/peterivony/Documents/VSCode Projects/AdventOfCode/inputs/day1.txt");
    std::vector<std::string> set = read_from_file(file);
    bool first[3] = {true,true,true};
    int cntr = 0;
    int prev_nums[3] = {0,0,0};
    for (const auto& el : set){

        if (first[0])
            first[0] = false;
        else if (first[1])
            first[1] = false;
        else if (first[2])
            first[2] = false;
        else
        if ( (prev_nums[0]+prev_nums[1]+prev_nums[2]) < (prev_nums[1]+prev_nums[2]+std::stoi(el)) )
            cntr++;

        prev_nums[0] = prev_nums[1];
        prev_nums[1] = prev_nums[2];
        prev_nums[2] = std::stoi(el);
    }
    return cntr;
}

uint64_t d2t1(){
    std::ifstream file;
    file.open("/Users/peterivony/Documents/VSCode Projects/AdventOfCode/inputs/day2.txt");
    std::vector<std::string> set = read_from_file(file);

    int hor = 0;
    int depth = 0;

    for (size_t i=0; i < set.size(); i+=2){
        if (set.at(i) == "forward")
            hor += std::stoi(set.at(i+1));
        else if (set.at(i) == "up")
            depth -= std::stoi(set.at(i+1));
        else
            depth += std::stoi(set.at(i+1));
    }
    return hor*depth;
}
uint64_t d2t2(){
    std::ifstream file;
    file.open("/Users/peterivony/Documents/VSCode Projects/AdventOfCode/inputs/day2.txt");
    std::vector<std::string> set = read_from_file(file);

    int hor = 0;
    int depth = 0;
    int aim = 0;

    for (size_t i=0; i < set.size(); i+=2){
        if (set.at(i) == "forward"){
            hor += std::stoi(set.at(i+1));
            depth += aim * std::stoi(set.at(i+1));
        } else if (set.at(i) == "up")
            aim -= std::stoi(set.at(i+1));
        else
            aim += std::stoi(set.at(i+1));
    }

    return hor*depth;
}

uint64_t d3t1(){
    std::ifstream file;
    file.open("/Users/peterivony/Documents/VSCode Projects/AdventOfCode/inputs/day3.txt");
    std::vector<std::string> set = read_from_file(file);

    const size_t AMOUNT_OF_BITS = 12;

    int null_counter[AMOUNT_OF_BITS];

    for (size_t i = 0; i < AMOUNT_OF_BITS; ++i)
        null_counter[i] = 0;

    for (const std::string& str : set){
        for (size_t i = 0; i < str.length(); i++){
            if (str.at(i) == '0')
                null_counter[i]++;
        }
    }

    int gamma_arr[AMOUNT_OF_BITS];
    for (size_t i = 0; i < AMOUNT_OF_BITS; ++i){
        if (null_counter[i] >= set.size()/2)
            gamma_arr[i] = 0;
        else
            gamma_arr[i] = 1;

    }

    int gamma = 0; int epsilon = 0;
    for (size_t i = 0; i < AMOUNT_OF_BITS; ++i) {
        if (gamma_arr[i] == 1)
            gamma += pow(2,AMOUNT_OF_BITS-1-i);
        else
            epsilon += pow(2,AMOUNT_OF_BITS-1-i);
    }

    return gamma*epsilon;
}
uint64_t d3t2(){
    std::ifstream file;
    file.open("/Users/peterivony/Documents/VSCode Projects/AdventOfCode/inputs/day3.txt");
    std::vector<std::string> oxygen = read_from_file(file);
    std::vector<std::string> co2 = oxygen;

    const size_t AMOUNT_OF_BITS = 12;
    int null_counter;
    bool mcb;

    for (size_t i = 0; i < AMOUNT_OF_BITS; i++){

        // Reset 0 counter
        null_counter = 0;
        // Count up the number of 0's in oxygen at the i-th position
        for (const std::string& str : oxygen){
            if (str.at(i) == '0')
                null_counter++;
        }

        // Save in mcb which one was the most common bit
        mcb = null_counter <= oxygen.size() / 2;

        // Removes elements from vector if mcb doesn't match their i-th bit
        oxygen.erase(std::remove_if(oxygen.begin(),
                                    oxygen.end(),
                                    [&i, &mcb](std::string str){ if (mcb) return str.at(i) == '0'; else return str.at(i) == '1'; }
                     ),
                     oxygen.end()
        );

        if (oxygen.size() == 1)
            break;
    }

    for (size_t i = 0; i < AMOUNT_OF_BITS; i++){

        // Reset 0 counter
        null_counter = 0;
        // Count up the number of 0's in co2 at the i-th position
        for (const std::string& str : co2){
            if (str.at(i) == '0')
                null_counter++;
        }

        // Save in mcb which one was the least common bit
        mcb = null_counter > co2.size()/2;

        // Removes elements from vector if mcb doesn't match their i-th bit
        co2.erase(std::remove_if(co2.begin(),
                                 co2.end(),
                                 [&i, &mcb](std::string str){ if (mcb) return str.at(i) == '0'; else return str.at(i) == '1'; }
                  ),
                  co2.end()
        );

        if (co2.size() == 1)
            break;
    }

    int ox = 0; int co = 0;
    for (size_t i = 0; i < AMOUNT_OF_BITS; ++i) {
        if (oxygen.at(0).at(i) == '1')
            ox += pow(2,AMOUNT_OF_BITS-1-i);
        if (co2.at(0).at(i) == '1')
            co += pow(2,AMOUNT_OF_BITS-1-i);
    }

    return ox*co;
}

uint64_t d4t1(){

    std::ifstream file;
    file.open("/Users/peterivony/Documents/VSCode Projects/AdventOfCode/inputs/day4.txt");
    std::vector<std::string> input = read_from_file(file);

    std::string called_nums_str = input.at(0);
    input.erase(input.begin());

    std::vector<BingoTable> tables_vec;
    while (!input.empty()){
        std::vector<std::string> strings{input.begin(),input.begin()+25};
        std::vector<int> vals;
        std::transform(input.begin(),
                       input.begin()+25,
                       std::back_inserter(vals),
                       [](const std::string& s){return std::stoi(s);}
        );
        BingoTable tab(vals);
        tables_vec.push_back(tab);
        input.erase(input.begin(), input.begin()+25);
    }

    std::vector<int> called_nums;
    const char DELIMITER = ',';
    size_t k = 0;
    for (size_t i{0}; i < called_nums_str.size(); ++i){
        if (called_nums_str.at(i) == DELIMITER || i == called_nums_str.size()-1) {
            called_nums.push_back(std::stoi(called_nums_str.substr(k, i)));
            k = i+1;
        }
    }

    BingoTable* bingoTable = nullptr;
    int bingo_called;
    for (const int& call : called_nums){
        for (auto& tab : tables_vec){
            tab.numberCalled(call);
            if (tab.checkBingo())
                bingoTable = &tab;
        }
        if (bingoTable != nullptr){
            bingo_called = call;
            break;
        }
    }

   return bingo_called*bingoTable->sum_of_not_called();

}
uint64_t d4t2() {

    std::ifstream file;
    file.open("/Users/peterivony/Documents/VSCode Projects/AdventOfCode/inputs/day4.txt");
    std::vector<std::string> input = read_from_file(file);

    std::string called_nums_str = input.at(0);
    input.erase(input.begin());

    std::vector<BingoTable> tables_vec;
    while (!input.empty()) {
        std::vector<std::string> strings{input.begin(), input.begin() + 25};
        std::vector<int> vals;
        std::transform(input.begin(),
                       input.begin() + 25,
                       std::back_inserter(vals),
                       [](const std::string &s) { return std::stoi(s); }
        );
        BingoTable tab(vals);
        tables_vec.push_back(tab);
        input.erase(input.begin(), input.begin() + 25);
    }

    std::vector<int> called_nums;
    const char DELIMITER = ',';
    size_t k = 0;
    for (size_t i{0}; i < called_nums_str.size(); ++i) {
        if (called_nums_str.at(i) == DELIMITER || i == called_nums_str.size() - 1) {
            called_nums.push_back(std::stoi(called_nums_str.substr(k, i)));
            k = i + 1;
        }
    }

    int bingo_called;
    BingoTable* bingoTable = nullptr;
    for (const int& call : called_nums){
        for (auto& tab : tables_vec)
            tab.numberCalled(call);
        tables_vec.erase(std::remove_if(tables_vec.begin(),
                                        tables_vec.end(),
                                        [](BingoTable tab){return tab.checkBingo();}
                         ),
                         tables_vec.end()
        );
        if (tables_vec.size() == 1) {
            bingoTable = &tables_vec.at(0);
        }
        if (tables_vec.size() == 0){
            bingo_called = call;
            break;
        }
    }

    return bingo_called*bingoTable->sum_of_not_called();

}

uint64_t d5t1(){

    std::ifstream file;
    file.open("/Users/peterivony/Documents/VSCode Projects/AdventOfCode/inputs/day5.txt");
    std::vector<std::string> input = read_from_file(file);

    size_t i{1};
    while (i < input.size()){
        input.erase(input.begin()+i);
        i += 2;
    }
    i = 0;
    while (i < input.size()){
        input[i] = input[i] + ',' + input[i+1];
        input.erase(input.begin()+i+1);
        ++i;
    }

    //Filtering where x1 = x2 or y1 = y2
    input.erase(std::remove_if(input.begin(),
                                        input.end(),
                                        [](std::string s){std::vector<int> v; size_t last=0;
                                                                        for (size_t i{0}; i < s.size(); ++i){
                                                                            if (s.at(i) == ','){
                                                                                v.push_back(std::stoi(s.substr(last,i)));
                                                                                last = i+1;
                                                                            }
                                                                        }
                                                                        v.push_back(std::stoi(s.substr(last,std::string::npos)));
                                                                        return (v.at(0) != v.at(2) && v.at(1) != v.at(3));
                                                    }
                                        ),
                input.end());

    std::vector<Line> lines;
    for (const std::string& s : input){
        size_t last=0;
        std::vector<int> v;
        for (size_t i{0}; i < s.size(); ++i){
            if (s.at(i) == ','){
                v.push_back(std::stoi(s.substr(last,i)));
                last = i+1;
            }
        }
        v.push_back(std::stoi(s.substr(last,std::string::npos)));
        lines.emplace_back(v.at(0),v.at(1),v.at(2),v.at(3));
    }

    short map[1000][1000];

    for (size_t i{0}; i < 1000; ++i)
        for (size_t j{0}; j < 1000; ++j)
            map[i][j] = 0;

    for (const auto& line : lines){
        for (const auto& point : line.getAllPoints()){
            map[point.x][point.y]++;
        }
    }

    int counter = 0;
    for (size_t i{0}; i < 1000; ++i)
        for (size_t j{0}; j < 1000; ++j)
            if (map[i][j] >= 2)
                counter++;

    return counter;

}
uint64_t d5t2(){
    std::ifstream file;
    file.open("/Users/peterivony/Documents/VSCode Projects/AdventOfCode/inputs/day5.txt");
    std::vector<std::string> input = read_from_file(file);

    size_t i{1};
    while (i < input.size()){
        input.erase(input.begin()+i);
        i += 2;
    }
    i = 0;
    while (i < input.size()){
        input[i] = input[i] + ',' + input[i+1];
        input.erase(input.begin()+i+1);
        ++i;
    }

    /*
    for (const auto& el : input)
        std::cout << el << std::endl;
    */

    //Filtering where x1 = x2 or y1 = y2 or 45° diagonal
    input.erase(std::remove_if(input.begin(),
                               input.end(),
                               [](std::string s){std::vector<int> v; size_t last=0;
                                   for (size_t i{0}; i < s.size(); ++i){
                                       if (s.at(i) == ','){
                                           v.push_back(std::stoi(s.substr(last,i)));
                                           last = i+1;
                                       }
                                   }
                                   v.push_back(std::stoi(s.substr(last,std::string::npos)));
                                   return !(v.at(0) == v.at(2) || v.at(1) == v.at(3) ||
                                            (v.at(2) - v.at(0) == v.at(3) - v.at(1)) ||
                                            (v.at(2) - v.at(0) == - (v.at(3) - v.at(1)) )
                                            );
                               }
                ),
                input.end());

    std::vector<Line> lines;
    for (const std::string& s : input){
        size_t last=0;
        std::vector<int> v;
        for (size_t i{0}; i < s.size(); ++i){
            if (s.at(i) == ','){
                v.push_back(std::stoi(s.substr(last,i)));
                last = i+1;
            }
        }
        v.push_back(std::stoi(s.substr(last,std::string::npos)));
        lines.emplace_back(v.at(0),v.at(1),v.at(2),v.at(3));
    }

    short map[1000][1000];

    for (size_t i{0}; i < 1000; ++i)
        for (size_t j{0}; j < 1000; ++j)
            map[i][j] = 0;

    for (const auto& line : lines){
        for (const auto& point : line.getAllPoints()){
            map[point.x][point.y]++;
        }
    }

    int counter = 0;
    for (size_t i{0}; i < 1000; ++i)
        for (size_t j{0}; j < 1000; ++j)
            if (map[i][j] >= 2)
                counter++;

    return counter;
}

uint64_t d6(size_t days){

   std::ifstream file;
   file.open("/Users/peterivony/Documents/VSCode Projects/AdventOfCode/inputs/day6.txt");
   std::vector<std::string> vec = read_from_file(file);

   uint64_t fish[9];
   for (size_t i{0}; i<9;++i)
       fish[i] = 0;

   size_t last=0;
   for (size_t i{0}; i < vec.at(0).size(); ++i){
       if (vec.at(0).at(i) == ','){
          fish[std::stoi(vec.at(0).substr(last,i))]++;
          last = i+1;
       }
   }
   fish[std::stoi(vec.at(0).substr(last,vec.at(0).npos))]++;

   for (size_t i{0}; i < days; ++i){

       uint64_t k = fish[0];
       for (size_t j{1}; j < 9; j++)
           fish[j-1] = fish[j];
       fish[8] = k;
       fish[6] += k;

   }

   uint64_t res = 0;
   for (size_t i{0}; i < 9; ++i)
       res += fish[i];

   return res;

}

uint64_t d7t1(){
    std::ifstream file;
    file.open("/Users/peterivony/Documents/VSCode Projects/AdventOfCode/inputs/day7.txt");
    std::vector<std::string> vec = read_from_file(file);

    std::vector<double> positions = divide_string(vec.at(0));

    int min = 1000000000;
    size_t min_pos;
    for (size_t i{0}; i < 2000; ++i){
        int num = 0;
        for (const auto& el : positions){
            num += abs(static_cast<int>(el-i));
        }
        if (num < min){
            min = num;
            min_pos = i;
        }
    }

    return min;

}
uint64_t d7t2(){
    std::ifstream file;
    file.open("/Users/peterivony/Documents/VSCode Projects/AdventOfCode/inputs/day7.txt");
    std::vector<std::string> vec = read_from_file(file);
    std::vector<double> positions = divide_string(vec.at(0));

    int min = 1000000000;
    size_t min_pos;
    for (size_t i{0}; i < 2000; ++i){
        int num = 0;
        for (const auto& el : positions){
            int n = abs(static_cast<int>(el-i))+1;
            num += n*(n-1)/2;
        }
        if (num < min){
            min = num;
            min_pos = i;
        }
    }

    return min;
}

uint64_t d8t1(){

    std::ifstream file;
    file.open("/Users/peterivony/Documents/VSCode Projects/AdventOfCode/inputs/day8.txt");
    std::vector<std::string> vec = read_from_file(file);

    size_t cnt = 0;
    uint64_t res{0};
    for (size_t i{11}; i < vec.size(); ++i){
        if (vec.at(i).size() == 2 || vec.at(i).size() == 4 || vec.at(i).size() == 7 || vec.at(i).size() == 3)
            res++;
        if (cnt == 3){
            cnt = 0;
            i += 11;
        } else
            cnt++;
        if (i >= vec.size())
            break;
    }

    return res;
}
uint64_t d8t2(){

    std::ifstream file;
    file.open("/Users/peterivony/Documents/VSCode Projects/AdventOfCode/inputs/day8.txt");
    std::vector<std::string> vec = read_from_file(file);
    uint64_t res = 0;

    for (size_t i{0}; i < 200; ++i) { // Loop rows
        std::array<std::string,10> numbers;
        std::vector<std::string> inputs, display;

        for (size_t j{0}; j < 10; ++j) // Loop row elements - current element = i*15+j
            inputs.push_back(vec.at(i*15+j));
        for (size_t j{11}; j < 15; ++j)
            display.push_back(vec.at(i*15+j));

        // Find out which numbers are which
        for (const auto& el : inputs){
            switch (el.size()) {
                case 2:
                    numbers[1] = el;
                    break;
                case 3:
                    numbers[7] = el;
                    break;
                case 4:
                    numbers[4] = el;
                    break;
                case 7:
                    numbers[8] = el;
            }
        }
        for (const auto& el : inputs){
            switch (el.size()){
                case 6:
                    if (string_diff(el,numbers[1]).size() + 1 == el.size())
                        numbers[6] = el;
                    else if (string_diff(el,numbers[4]).size() + 4 == el.size())
                        numbers[9] = el;
                    else
                        numbers[0] = el;
                    break;
                case 5:
                    if (string_diff(el,numbers[1]).size() + 2 == el.size())
                        numbers[3] = el;
                    else if (string_diff(el, numbers[4]).size() + 2 == el.size())
                        numbers[2] = el;
                    else
                        numbers[5] = el;
                    break;
            }
        }

        std::string temp;
        for (const auto &str : display){
            for (size_t j{0}; j < 10; j++){
                if (same_different_order(str,numbers[j])) {
                    temp += std::to_string(j);
                    break;
                }
            }
        }
        res += std::stoi(temp);
    }

    return res;
}

uint64_t d9t1(){
    std::ifstream file;
    file.open("/Users/peterivony/Documents/VSCode Projects/AdventOfCode/inputs/day9.txt");
    std::vector<std::string> vec = read_from_file(file);

    int map[100][100];
    for (size_t i{0}; i < vec.size(); ++i)
        for (size_t j{0}; j < vec.at(i).size(); ++j)
            map[i][j] = static_cast<int>(vec.at(i).at(j)) - 48;

    uint64_t sum = 0;
    for (size_t i{0}; i < 100; ++i){
        for (size_t j{0}; j < 100; ++j) {
            if (i == 0) {   //  First row
                if (j == 0) {   //Top left
                    if (map[i + 1][j] > map[i][j] && map[i][j + 1] > map[i][j])
                        sum += map[i][j] + 1;
                } else if (j == 99) {  //Top right
                    if (map[i + 1][j] > map[i][j] && map[i][j - 1] > map[i][j])
                        sum += map[i][j] + 1;
                } else {
                    if (map[i + 1][j] > map[i][j] && map[i][j + 1] > map[i][j] && map[i][j - 1] > map[i][j])
                        sum += map[i][j] + 1;
                }
            } else if (i == 99) { // Last row
                if (j == 0) { // Bottom left
                    if (map[i][j + 1] > map[i][j] && map[i - 1][j] > map[i][j])
                        sum += map[i][j] + 1;
                } else if (j == 99) { // Bottom right
                    if (map[i - 1][j] > map[i][j] && map[i][j - 1] > map[i][j])
                        sum += map[i][j] + 1;
                } else {
                    if (map[i][j - 1] > map[i][j] && map[i][j + 1] > map[i][j] && map[i - 1][j] > map[i][j])
                        sum += map[i][j] + 1;
                }
            } else if (j == 0) { // First column
                if (map[i-1][j] > map[i][j] && map[i+1][j] > map[i][j] && map[i][j+1] > map[i][j])
                    sum += map[i][j] + 1;
            } else if (j == 99) { // Last column
                if (map[i-1][j] > map[i][j] && map[i+1][j] > map[i][j] && map[i][j-1] > map[i][j])
                    sum += map[i][j] + 1;
            } else {
                if (map[i-1][j] > map[i][j] && map[i+1][j] > map[i][j] && map[i][j-1] > map[i][j] && map[i][j+1] > map[i][j])
                    sum += map[i][j] + 1;
            }
        }
    }
    return sum;
}
uint64_t d9t2(){
    std::ifstream file;
    file.open("/Users/peterivony/Documents/VSCode Projects/AdventOfCode/inputs/day9.txt");
    std::vector<std::string> vec = read_from_file(file);

    std::array<std::array<int,100>,100> map{};
    for (size_t i{0}; i < vec.size(); ++i)
        for (size_t j{0}; j < vec.at(i).size(); ++j)
            map[i][j] = static_cast<int>(vec.at(i).at(j)) - 48;

    // Find lowest points
    std::vector<std::pair<size_t,size_t>> lowest_points;
    for (size_t i{0}; i < 100; ++i) {
        for (size_t j{0}; j < 100; ++j) {
            if (i == 0) {   //  First row
                if (j == 0) {   //Top left
                    if (map[i + 1][j] > map[i][j] && map[i][j + 1] > map[i][j])
                        lowest_points.emplace_back(i, j);
                } else if (j == 99) {  //Top right
                    if (map[i + 1][j] > map[i][j] && map[i][j - 1] > map[i][j])
                        lowest_points.emplace_back(i, j);
                } else {
                    if (map[i + 1][j] > map[i][j] && map[i][j + 1] > map[i][j] && map[i][j - 1] > map[i][j])
                        lowest_points.emplace_back(i, j);
                }
            } else if (i == 99) { // Last row
                if (j == 0) { // Bottom left
                    if (map[i][j + 1] > map[i][j] && map[i - 1][j] > map[i][j])
                        lowest_points.emplace_back(i, j);
                } else if (j == 99) { // Bottom right
                    if (map[i - 1][j] > map[i][j] && map[i][j - 1] > map[i][j])
                        lowest_points.emplace_back(i, j);
                } else {
                    if (map[i][j - 1] > map[i][j] && map[i][j + 1] > map[i][j] && map[i - 1][j] > map[i][j])
                        lowest_points.emplace_back(i, j);
                }
            } else if (j == 0) { // First column
                if (map[i - 1][j] > map[i][j] && map[i + 1][j] > map[i][j] && map[i][j + 1] > map[i][j])
                    lowest_points.emplace_back(i, j);
            } else if (j == 99) { // Last column
                if (map[i - 1][j] > map[i][j] && map[i + 1][j] > map[i][j] && map[i][j - 1] > map[i][j])
                    lowest_points.emplace_back(i, j);
            } else {
                if (map[i - 1][j] > map[i][j] && map[i + 1][j] > map[i][j] && map[i][j - 1] > map[i][j] &&
                    map[i][j + 1] > map[i][j])
                    lowest_points.emplace_back(i, j);
            }
        }
    }

    // Go through all lowest points and find the 3 biggest basins
    uint64_t largest_basins[3]{0,0,0};
    size_t cnt = 0;
    for (const auto& ref : lowest_points){
        std::vector<std::pair<int,int>> vis;
        uint64_t num = sum_of_basin(map,vis,ref.first,ref.second);
        if (num >= largest_basins[0]){
            largest_basins[2] = largest_basins[1];
            largest_basins[1] = largest_basins[0];
            largest_basins[0] = num;
        } else if (num >= largest_basins[1]){
            largest_basins[2] = largest_basins[1];
            largest_basins[1] = num;
        } else if (num >= largest_basins[2]){
            largest_basins[2] = num;
        }
    }

    return largest_basins[0] * largest_basins[1] * largest_basins[2];
}

uint64_t d10t1(){
    std::ifstream file;
    file.open("/Users/peterivony/Documents/VSCode Projects/AdventOfCode/inputs/day10.txt");
    std::vector<std::string> vec = read_from_file(file);

    std::stack<char> st;
    uint64_t res = 0;
    for (const auto& str: vec){
        for (const char& ch : str){
            bool break_cond = false;
            if (st.empty() && !((ch == '}') || (ch == ')') || (ch==']') || (ch=='>'))){
                st.push(ch);
            } else {
                switch (ch){
                    case ')':
                        if (st.empty() || st.top() != '('){
                            res+=3;
                            break_cond = true;
                        } else
                            st.pop();
                        break;
                    case ']':
                        if (st.empty() || st.top() != '['){
                            res+=57;
                            break_cond = true;
                        } else
                            st.pop();
                        break;
                    case '}':
                        if (st.empty() || st.top() != '{'){
                            res+=1197;
                            break_cond = true;
                        } else
                            st.pop();
                        break;
                    case '>':
                        if (st.empty() || st.top() != '<'){
                            res+=25137;
                            break_cond = true;
                        } else
                            st.pop();
                        break;
                    default:
                        st.push(ch);
                        break;
                }
            }
            if (break_cond)
                break;
        }
    }
    return res;
}
uint64_t d10t2(){
    std::ifstream file;
    file.open("/Users/peterivony/Documents/VSCode Projects/AdventOfCode/inputs/day10.txt");
    std::vector<std::string> vec = read_from_file(file);

    std::map<char,int> valpairs{{'(',1}, {'[',2},{'{', 3},{'<',4}};

    erase_if(vec,[](std::string& str){
        std::stack<char> st;
        for (const char& ch : str){
            if (st.empty() && !((ch == '}') || (ch == ')') || (ch==']') || (ch=='>'))){
                st.push(ch);
            } else {
                switch (ch){
                    case ')':
                        if (st.empty() || st.top() != '('){
                            return true;
                        } else
                            st.pop();
                        break;
                    case ']':
                        if (st.empty() || st.top() != '['){
                            return true;
                        } else
                            st.pop();
                        break;
                    case '}':
                        if (st.empty() || st.top() != '{'){
                            return true;
                        } else
                            st.pop();
                        break;
                    case '>':
                        if (st.empty() || st.top() != '<'){
                            return true;
                        } else
                            st.pop();
                        break;
                    default:
                        st.push(ch);
                        break;
                }
            }
        }
        return false;
    }); // Clears corrupted lines

    /*for (const auto& a : vec){
        std::cout << a << std::endl;
    }*/

    std::vector<uint64_t> total_scores;

    for (const std::string& str : vec){
        uint64_t res = 0;
        std::deque<char> dq;
        for (const char& ch : str){
            if (ch == ')' || ch == ']' || ch == '}' || ch == '>')
                dq.pop_back();
            else
                dq.push_back(ch);
        }

        std::reverse(dq.begin(), dq.end());

        for (const char& ch : dq){
            res *= 5;
            res += valpairs.at(ch);
        }
        total_scores.push_back(res);
    }

    std::sort(total_scores.begin(),total_scores.end());

    return total_scores.at((total_scores.size()-1)/2);
}

int main() {

    uint64_t res;
    std::chrono::time_point<std::chrono::system_clock> start,end;
    std::chrono::duration<double> elapsed_seconds;

    /*
    // Day 1
    {
        std::cout << "================== Day 1 ==================" << std::endl;
        std::cout << "Task 1:" << std::endl;
        start = std::chrono::system_clock::now();
        res = d1t1();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << res << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
        std::cout << "Task 2:" << std::endl;
        start = std::chrono::system_clock::now();
        res = d1t2();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << res << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
    }
    // Day 2
    {
        std::cout << "================== Day 2 ==================" << std::endl;
        std::cout << "Task 1:" << std::endl;
        start = std::chrono::system_clock::now();
        res = d2t1();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << res << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
        std::cout << "Task 2:" << std::endl;
        start = std::chrono::system_clock::now();
        res = d2t2();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << res << "\t Time elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
    }
    // Day 3
    {
        std::cout << "================== Day 3 ==================" << std::endl;
        std::cout << "Task 1:" << std::endl;
        start = std::chrono::system_clock::now();
        res = d3t1();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << res << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
        std::cout << "Task 2:" << std::endl;
        start = std::chrono::system_clock::now();
        res = d3t2();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << res << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
    }
    // Day 4
    {
        std::cout << "================== Day 4 ==================" << std::endl;
        std::cout << "Task 1:" << std::endl;
        start = std::chrono::system_clock::now();
        res = d4t1();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << res << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
        std::cout << "Task 2:" << std::endl;
        start = std::chrono::system_clock::now();
        res = d4t2();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << res << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
    }
    // Day 5
    {
        std::cout << "================== Day 5 ==================" << std::endl;
        std::cout << "Task 1:" << std::endl;
        start = std::chrono::system_clock::now();
        res = d5t1();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << res << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
        std::cout << "Task 2:" << std::endl;
        start = std::chrono::system_clock::now();
        res = d5t2();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << res << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
    }
    // Day 6
    {
        std::cout << "================== Day 6 ==================" << std::endl;
        std::cout << "Task 1:" << std::endl;
        start = std::chrono::system_clock::now();
        res = d6(80);
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << res << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
        std::cout << "Task 2:" << std::endl;
        start = std::chrono::system_clock::now();
        res = d6(256);
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << res << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
    }
    // Day 7
    {
        std::cout << "================== Day 7 ==================" << std::endl;
        std::cout << "Task 1:" << std::endl;
        start = std::chrono::system_clock::now();
        res = d7t1();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << res << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
        std::cout << "Task 2:" << std::endl;
        start = std::chrono::system_clock::now();
        res = d7t2();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << res << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
    }
    // Day 8
    {
        std::cout << "================== Day 8 ==================" << std::endl;
        std::cout << "Task 1:" << std::endl;
        start = std::chrono::system_clock::now();
        res = d8t1();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << res << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
        std::cout << "Task 2:" << std::endl;
        start = std::chrono::system_clock::now();
        res = d8t2();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << res << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
    }

    // Day 9
    {
        std::cout << "================== Day 9 ==================" << std::endl;
        std::cout << "Task 1:" << std::endl;
        start = std::chrono::system_clock::now();
        res = d9t1();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << res << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
        std::cout << "Task 2:" << std::endl;
        start = std::chrono::system_clock::now();
        res = d9t2();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << res << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
    }
    */
    // Day 10
    {
        std::cout << "================== Day 10 ==================" << std::endl;
        std::cout << "Task 1:" << std::endl;
        start = std::chrono::system_clock::now();
        res = d10t1();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << res << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
        std::cout << "Task 2:" << std::endl;
        start = std::chrono::system_clock::now();
        res = d10t2();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << res << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
    }
    return 0;
}