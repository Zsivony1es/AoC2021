//
// Created by Peter Ivony on 17.12.21.
//

#include "Structures.h"

Structures::Node::Node(std::string val){
    this->val = val;
    isLarge = val.at(0) >= 'A' && val.at(0) <= 'Z';
}
uint64_t Structures::Node::count_routes1(Node& node){
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
uint64_t Structures::Node::count_routes2(Node& node, const std::string& twice_name){
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

Structures::BingoTable::BingoTable(std::vector<int> contents){
    if (contents.size() != pow(TABLE_SIZE,2))
        throw std::runtime_error("Invalid vector size!");
    for (size_t i{0}; i < TABLE_SIZE; ++i){
        for (size_t j{0}; j < TABLE_SIZE; ++j){
            table[i][j].val = contents.at(i*TABLE_SIZE + j);
            table[i][j].called = false;
        }
    }
}
void Structures::BingoTable::numberCalled(int num){
    for (size_t i{0}; i < TABLE_SIZE; ++i) {
        for (size_t j{0}; j < TABLE_SIZE; ++j) {
            if (table[i][j].val == num)
                table[i][j].called = true;
        }
    }
}
bool Structures::BingoTable::checkBingo(){
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
int Structures::BingoTable::sum_of_not_called(){
    int sum{0};
    for (size_t i{0}; i < TABLE_SIZE; ++i) {
        for (size_t j{0}; j < TABLE_SIZE; ++j) {
            if (!table[i][j].called)
                sum += table[i][j].val;
        }
    }
    return sum;
}
std::string Structures::BingoTable::to_string(){
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
bool Structures::BingoTable::operator==(BingoTable ro){
    if (this->to_string() == ro.to_string())
        return true;
    return false;
}

Structures::Point::Point(int x,int y){
    this->x = x;
    this->y = y;
}
Structures::Point::Point(const Structures::Point& p){
    this->x = p.x;
    this->y = p.y;
}
std::string Structures::Point::to_string() const{
    return reinterpret_cast<const char *>('(' + x + ',' + y + ')');
}
bool Structures::Point::operator==(const Structures::Point& p) const{return this->x == p.x && this->y == p.y;}
std::ostream& operator<<(std::ostream& os, const Structures::Point& p){
    return os << '(' << p.x << ',' << p.y << ')';
}

Structures::Line::Line(const Structures::Point& begin, const Structures::Point& end){
    this->begin = Structures::Point(begin.x, begin.y);
    this->end = Structures::Point(end.x, end.y);
}
Structures::Line::Line(int x1, int y1, int x2, int y2){
    this->begin = Structures::Point(x1,y1);
    this->end = Structures::Point(x2, y2);
}
std::vector<Structures::Point> Structures::Line::getAllPoints() const {
    std::vector<Structures::Point> ret;
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
std::ostream& operator<<(std::ostream& os, const Structures::Line& l){
    return os << l.begin << " -> " << l.end;
}