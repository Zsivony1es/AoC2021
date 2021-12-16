#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <stdexcept>
#include <chrono>
#include <array>
#include <map>
#include <bitset>
#include <sstream>

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

struct Octopus{
    bool flashed = false;
    size_t energy;
    Octopus(size_t e){
        this->energy = e;
    }
    Octopus()=default;
};
uint64_t sum_of_flashes(std::array<std::array<Octopus,10>,10>& map){

    bool flash = true;
    uint64_t flashes = 0;

    Octopus oct = 3;

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

template<typename T>
struct LinkedList{
    T val;
    LinkedList<T>* next;
};

struct Node{
    std::string val;
    std::vector<Node*> conns;
    size_t visited = 0;
    bool isLarge;

    Node(std::string val){ this->val = val; isLarge = val.at(0) >= 'A' && val.at(0) <= 'Z'; }

    static uint64_t count_routes1(Node& node){
        uint64_t cnt = 0;
        node.visited++;
        for (auto& child : node.conns){
            if (child->val == "end")
                cnt++;
            else if (child->visited == 0 || child->isLarge)
                cnt += count_routes1(*child);
        }
        node.visited--;
        return cnt;
    }
    static uint64_t count_routes2(Node& node, const std::string& twice_name){
        uint64_t cnt = 0;
        node.visited++;
        for (auto& child : node.conns){
            if (child->val == "end")
                cnt++;
            else if (child->visited < 1 || child->isLarge || (child->visited < 2 && child->val == twice_name) )
                cnt += count_routes2(*child, twice_name);
        }
        node.visited--;
        return cnt;
    }

};

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
    bool operator==(const Point& p) const{return this->x == p.x && this->y == p.y;}
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

uint64_t day13solver(std::vector<Point>& points, std::vector<std::string>& folds){
    size_t lastx=1, lasty=1;
    for (const auto& f : folds) {
        size_t num = std::stoi(f.substr(2, std::string::npos));
        if (f.at(0) == 'x') {
            lastx = num;
            std::vector<Point> to_transform;
            for (const Point &p: points)
                if (p.x > num)
                    to_transform.push_back(p);
            points.erase(std::remove_if(points.begin(), points.end(), [&num](Point p) { return p.x >= num; }),
                         points.end());
            for (const Point &p: to_transform) {
                bool exists = false;
                Point to_add = Point(num - (p.x - num), p.y);
                for (const Point &p1: points)
                    if (p1 == to_add) {
                        exists = true;
                        break;
                    }
                if (!exists)
                    points.push_back(to_add);
            }

        } else if (f.at(0) == 'y') {
            lasty = num;
            std::vector<Point> to_transform;
            for (const Point &p: points)
                if (p.y > num)
                    to_transform.push_back(p);
            points.erase(std::remove_if(points.begin(), points.end(), [&num](Point p) { return p.y >= num; }),
                         points.end());
            for (const Point &p: to_transform) {
                bool exists = false;
                Point to_add = Point(p.x, num - (p.y - num));
                for (const Point &p1: points)
                    if (p1 == to_add) {
                        exists = true;
                        break;
                    }
                if (!exists)
                    points.push_back(to_add);
            }
        }
        if (lasty != 1 && lastx != 1){
            std::ofstream outfile;
            outfile.open("/Users/peterivony/Documents/VSCode Projects/AdventOfCode/outputs/day13.txt");

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

uint64_t parse_packet(const std::string& bin, int& cnt, std::vector<uint64_t>& version_nums){

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

uint64_t d11t1(){
    std::ifstream file;
    file.open("/Users/peterivony/Documents/VSCode Projects/AdventOfCode/inputs/day11.txt");
    std::vector<std::string> vec = read_from_file(file);

    std::array<std::array<Octopus,10>,10> map;
    for (size_t i{0}; i < vec.size(); ++i)
        for (size_t j{0}; j < vec.at(i).size(); ++j)
            map[i][j] = Octopus(static_cast<int>(vec.at(i).at(j)) - 48);

    uint64_t res = 0;
    for (size_t i{0}; i < 100; ++i)
        res += sum_of_flashes(map);

    return res;
}
uint64_t d11t2(){
    std::ifstream file;
    file.open("/Users/peterivony/Documents/VSCode Projects/AdventOfCode/inputs/day11.txt");
    std::vector<std::string> vec = read_from_file(file);

    std::array<std::array<Octopus,10>,10> map;
    for (size_t i{0}; i < vec.size(); ++i)
        for (size_t j{0}; j < vec.at(i).size(); ++j)
            map[i][j] = Octopus(static_cast<int>(vec.at(i).at(j)) - 48);

    uint64_t cnt = 1;
    while (sum_of_flashes(map) != 100)
        cnt++;

    return cnt;
}

uint64_t d12t1(){
    std::ifstream file;
    file.open("/Users/peterivony/Documents/VSCode Projects/AdventOfCode/inputs/day12.txt");
    std::vector<std::string> vec = read_from_file(file);

    std::map<std::string,Node> nodes;

    // Setting our map
    for (const auto& str : vec){
        size_t index;
        for (size_t i{0}; i < str.size(); ++i)
            if (str[i] == '-'){
                index = i;
                break;
            }
        std::string st1 = str.substr(0,index),
                    st2 = str.substr(index+1,std::string::npos);

        if (!nodes.contains(st1))
            nodes.insert(std::pair<std::string,Node>(st1,Node(st1)));
        if (!nodes.contains(st2))
            nodes.insert(std::pair<std::string,Node>(st2,Node(st2)));

        nodes.at(st1).conns.push_back(&nodes.at(st2));
        nodes.at(st2).conns.push_back(&nodes.at(st1));
    }

    return Node::count_routes1(nodes.at("start"));

}
uint64_t d12t2(){

    std::ifstream file;
    file.open("/Users/peterivony/Documents/VSCode Projects/AdventOfCode/inputs/day12.txt");
    std::vector<std::string> vec = read_from_file(file);

    std::map<std::string,Node> nodes;

    // Setting our map
    for (const auto& str : vec){
        size_t index;
        for (size_t i{0}; i < str.size(); ++i)
            if (str[i] == '-'){
                index = i;
                break;
            }
        std::string st1 = str.substr(0,index),
                st2 = str.substr(index+1,std::string::npos);

        if (!nodes.contains(st1))
            nodes.insert(std::pair<std::string,Node>(st1,Node(st1)));
        if (!nodes.contains(st2))
            nodes.insert(std::pair<std::string,Node>(st2,Node(st2)));

        nodes.at(st1).conns.push_back(&nodes.at(st2));
        nodes.at(st2).conns.push_back(&nodes.at(st1));
    }


    uint64_t to_sub = Node::count_routes1(nodes.at("start"));
    uint64_t res = to_sub;
    for (auto& el : nodes){
        if (el.first != "start" && el.first != "end" && !el.second.isLarge)
            res += ( Node::count_routes2(nodes.at("start"),el.first) - to_sub );
    }

    return res;

}

uint64_t d13t1(){
    std::ifstream file;
    file.open("/Users/peterivony/Documents/VSCode Projects/AdventOfCode/inputs/day13.txt");
    std::vector<std::string> vec = read_from_file(file);

    vec.erase(std::remove_if(vec.begin(),vec.end(),[](std::string str){return str == "fold" || str == "along";}),vec.end());

    std::vector<Point> points;
    std::vector<std::string> folds;

    for (const auto& str : vec){
        if ( (str.at(0) == 'x' || str.at(0) == 'y') && folds.empty()){
            folds.push_back(str);
        } else if ( str.at(0) != 'x' && str.at(0) != 'y') {
            size_t index;
            for (size_t i{0}; i < str.size(); ++i){
                if (str.at(i) == ',')
                    index = i;
            }
            points.emplace_back(std::stoi(str.substr(0,index)),std::stoi(str.substr(index+1,std::string::npos)));
        }
    }

    return day13solver(points,folds);

}
uint64_t d13t2() {

    std::ifstream file;
    file.open("/Users/peterivony/Documents/VSCode Projects/AdventOfCode/inputs/day13.txt");
    std::vector<std::string> vec = read_from_file(file);

    vec.erase(std::remove_if(vec.begin(), vec.end(), [](std::string str) { return str == "fold" || str == "along"; }),
              vec.end());

    std::vector<Point> points;
    std::vector<std::string> folds;

    for (const auto &str: vec) {
        if (str.at(0) == 'x' || str.at(0) == 'y') {
            folds.push_back(str);
        } else {
            size_t index;
            for (size_t i{0}; i < str.size(); ++i) {
                if (str.at(i) == ',')
                    index = i;
            }
            points.emplace_back(std::stoi(str.substr(0, index)), std::stoi(str.substr(index + 1, std::string::npos)));
        }
    }

    return day13solver(points,folds);
}

uint64_t d14(size_t loops){

    std::ifstream file;
    file.open("/Users/peterivony/Documents/VSCode Projects/AdventOfCode/inputs/day14.txt");
    std::vector<std::string> vec = read_from_file(file);

    std::string temp = vec.at(0);

    std::map<std::string,char> rules;
    std::map<std::string,int64_t> amount_of_pairs;

    for (size_t i{1}; i < vec.size(); i+=3){
        rules.insert(std::pair<std::string,char>(vec.at(i),vec.at(i+2)[0] ));
        amount_of_pairs.insert(std::pair<std::string,int64_t>(vec.at(i), 0));
    }

    for (size_t i{0}; i < temp.size(); ++i){
        std::string as = std::string(1, temp[i]) + std::string(1, temp[i+1]);
        if (amount_of_pairs.contains(as))
            amount_of_pairs.at(as)++;
    }

    std::map<std::string,int64_t> changes;
    for (const auto& el : amount_of_pairs){
        changes.insert(std::pair<std::string,int64_t>(el.first,0));
    }

    for (size_t i{0}; i < loops; ++i) {

        // Reset changes
        for (auto& el : changes)
            el.second = 0;


        for (auto& el : amount_of_pairs) {
            std::string first = std::string(1,el.first[0]),
                        last = std::string(1,el.first[1]),
                        mid = std::string(1,rules.at(el.first));
            int64_t a = amount_of_pairs.at(first+last);

            changes.at(first+last) -= a;
            changes.at(first+mid) += a;
            changes.at(mid+last) += a;
        }

        // Commit changes
        for (const auto& el : changes)
            amount_of_pairs.at(el.first) += el.second;

    }

    std::map<char,uint64_t> amount;
    for (const auto& el : amount_of_pairs){
        if (!amount.contains(el.first[0]))
            amount.insert(std::pair<char,uint64_t>(el.first[0],el.second));
        else
            amount.at(el.first[0]) += el.second;
        if (!amount.contains(el.first[1]))
            amount.insert(std::pair<char,uint64_t>(el.first[1],el.second));
        else
            amount.at(el.first[1])+=el.second;

    }

    uint64_t max=0, min=INT64_MAX;
    for (const auto& el : amount){
        if (el.second > max)
            max = el.second;
        if (el.second < min)
            min = el.second;
    }

    return (max-min-1)/2;

}

uint64_t d15t1(){
    std::ifstream file;
    file.open("/Users/peterivony/Documents/VSCode Projects/AdventOfCode/inputs/day15.txt");
    std::vector<std::string> vec = read_from_file(file);

    std::array<std::array<size_t,100>,100> map;
    for (size_t i{0}; i < vec.size(); ++i){
        for (size_t j{0}; j < vec.at(i).size(); ++j){
            map[i][j] = vec[i][j] - 48;
        }
    }

    std::array<std::array<size_t,100>,100> algomap;
    for (size_t i{0}; i < 100; ++i){
        for (size_t j{0}; j < 100; ++j){
            algomap[i][j] = SIZE_T_MAX;
        }
    }
    algomap[0][0] = 0;

    for (size_t k{0}; k < 3; k++) { // Not proud of this one, but it works XD
        for (size_t i{0}; i < 100; ++i) {
            for (size_t j{0}; j < 100; ++j) {
                if (i < 99)
                    if (algomap[i][j] + map[i + 1][j] < algomap[i + 1][j])
                        algomap[i + 1][j] = algomap[i][j] + map[i + 1][j];
                if (i > 0)
                    if (algomap[i][j] + map[i - 1][j] < algomap[i - 1][j])
                        algomap[i - 1][j] = algomap[i][j] + map[i - 1][j];
                if (j < 99)
                    if (algomap[i][j] + map[i][j + 1] < algomap[i][j + 1])
                        algomap[i][j + 1] = algomap[i][j] + map[i][j + 1];
                if (j > 0)
                    if (algomap[i][j] + map[i][j - 1] < algomap[i][j - 1])
                        algomap[i][j - 1] = algomap[i][j] + map[i][j - 1];
            }
        }
    }

    return algomap[99][99];

}
uint64_t d15t2(){
    std::ifstream file;
    file.open("/Users/peterivony/Documents/VSCode Projects/AdventOfCode/inputs/day15.txt");
    std::vector<std::string> vec = read_from_file(file);

    std::array<std::array<size_t,100>,100> map_old;
    for (size_t i{0}; i < vec.size(); ++i){
        for (size_t j{0}; j < vec.at(i).size(); ++j){
            map_old[i][j] = vec[i][j] - 48;
        }
    }

    // Create bigger map
    std::array<std::array<size_t,500>,500> map;
    for (size_t i{0}; i < 100; ++i){
        for (size_t j{0}; j < 100; ++j){

            std::array<std::array<size_t,5>,5> ij;
            for (size_t k{0}; k < 5; ++k){
                for (size_t l{0}; l < 5; ++l){
                    if (k == 0 && l == 0)
                        ij[k][l] = map_old[i][j];
                    else if (k > 0)
                        ij[k][l] = (ij[k-1][l] + 1 == 10) ? 1 : ij[k-1][l] + 1;
                    else if (l > 0)
                        ij[k][l] = (ij[k][l-1] + 1 == 10) ? 1 : ij[k][l-1] + 1;
                }
            }

            for (size_t k{0}; k < 5; ++k)
                for (size_t l{0}; l < 5; ++l)
                    map[k*100+i][l*100+j] = ij[k][l];

        }
    }

    std::array<std::array<size_t,500>,500> algomap;
    for (size_t i{0}; i < 500; ++i){
        for (size_t j{0}; j < 500; ++j){
            algomap[i][j] = SIZE_T_MAX;
        }
    }
    algomap[0][0] = 0;

    for (size_t k{0}; k < 3; k++) { // Not proud of this one, but it works XD
        for (size_t i{0}; i < 500; ++i)
            for (size_t j{0}; j < 500; ++j){
                if (i < 499)
                    if (algomap[i][j] + map[i+1][j] < algomap[i+1][j])
                        algomap[i+1][j] = algomap[i][j] + map[i+1][j];
                if (i > 0)
                    if (algomap[i][j] + map[i-1][j] < algomap[i-1][j])
                        algomap[i-1][j] = algomap[i][j] + map[i-1][j];
                if (j < 499)
                    if (algomap[i][j] + map[i][j+1] < algomap[i][j+1])
                        algomap[i][j+1] = algomap[i][j] + map[i][j+1];
                if (j > 0)
                    if (algomap[i][j] + map[i][j-1] < algomap[i][j-1])
                        algomap[i][j-1] = algomap[i][j] + map[i][j-1];
            }
    }

    return algomap[499][499];

}

uint64_t d16t1(){

    std::ifstream file;
    file.open("/Users/peterivony/Documents/VSCode Projects/AdventOfCode/inputs/day16.txt");
    std::vector<std::string> vec = read_from_file(file);

    std::string bin;
    for (const char& ch : vec.at(0)){
        int n;
        std::istringstream(std::string(1,ch)) >> std::hex >> n;
        auto a = std::bitset<4>(n);
        for (size_t i{4}; i > 0; --i){
            if (a[i-1])
                bin += '1';
            else
                bin += '0';
        }
    }

    int cnt = 0;
    std::vector<uint64_t> version_nums;
    parse_packet(bin, cnt, version_nums);

    uint64_t ret = 0;
    std::for_each(version_nums.begin(), version_nums.end(), [&ret](const auto& item){ret += item;});
    return ret;

}
uint64_t d16t2(){

    std::ifstream file;
    file.open("/Users/peterivony/Documents/VSCode Projects/AdventOfCode/inputs/day16.txt");
    std::vector<std::string> vec = read_from_file(file);

    std::string bin;
    for (const char& ch : vec.at(0)){
        int n;
        std::istringstream(std::string(1,ch)) >> std::hex >> n;
        auto a = std::bitset<4>(n);
        for (size_t i{4}; i > 0; --i){
            if (a[i-1])
                bin += '1';
            else
                bin += '0';
        }
    }

    int cnt = 0;
    std::vector<uint64_t> nums;

    return parse_packet(bin, cnt, nums);

}

int main() {

    uint64_t res;
    std::chrono::time_point<std::chrono::system_clock> start,end;
    std::chrono::duration<double> elapsed_seconds;

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
    // Day 11
    {
        std::cout << "================== Day 11 ==================" << std::endl;
        std::cout << "Task 1:" << std::endl;
        start = std::chrono::system_clock::now();
        res = d11t1();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << res << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
        std::cout << "Task 2:" << std::endl;
        start = std::chrono::system_clock::now();
        res = d11t2();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << res << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
    }
    // Day 12
    {
        std::cout << "================== Day 12 ==================" << std::endl;
        std::cout << "Task 1:" << std::endl;
        start = std::chrono::system_clock::now();
        res = d12t1();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << res << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
        std::cout << "Task 2:" << std::endl;
        start = std::chrono::system_clock::now();
        res = d12t2();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << res << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
    }
    // Day 13
    {
        std::cout << "================== Day 13 ==================" << std::endl;
        std::cout << "Task 1:" << std::endl;
        start = std::chrono::system_clock::now();
        res = d13t1();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << res << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
        std::cout << "Task 2:" << std::endl;
        start = std::chrono::system_clock::now();
        res = d13t2();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << "EFJKZLBL (in outputs/day13.txt)" << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
    }
    // Day 14
    {
        std::cout << "================== Day 14 ==================" << std::endl;
        std::cout << "Task 1:" << std::endl;
        start = std::chrono::system_clock::now();
        res = d14(10);
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << res << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
        std::cout << "Task 2:" << std::endl;
        start = std::chrono::system_clock::now();
        res = d14(40);
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << res << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
    }
    // Day 15
    {
        std::cout << "================== Day 15 ==================" << std::endl;
        std::cout << "Task 1:" << std::endl;
        start = std::chrono::system_clock::now();
        res = d15t1();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << res << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
        std::cout << "Task 2:" << std::endl;
        start = std::chrono::system_clock::now();
        res = d15t2();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << res << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
    }
    // Day 16
    {
        std::cout << "================== Day 16 ==================" << std::endl;
        std::cout << "Task 1:" << std::endl;
        start = std::chrono::system_clock::now();
        res = d16t1();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << res << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
        std::cout << "Task 2:" << std::endl;
        start = std::chrono::system_clock::now();
        res = d16t2();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << res << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
    }

    return 0;
}