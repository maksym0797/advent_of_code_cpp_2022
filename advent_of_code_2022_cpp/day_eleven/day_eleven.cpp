//
//  day_eleven.cpp
//  advent_of_code_2022_cpp
//
//  Created by Maksym Kostynskyi on 08.11.2023.
//

#include "day_eleven.hpp"
#include <vector>
#include <set>
#include <string>
#include <iostream>
#include <map>
#include <iterator>
#include <algorithm>
#include <array>
#include <sstream>


using namespace std;

struct Monkey {
    vector<long long> items;
    long long monkey_buisness = 0;
    char operator_type;
    long second_value;
    int divisible;
    int positive_test_index;
    int negative_test_index;
    long long operate(long divider)
    {
        if (items.size() == 0) {
            return 0;
        }
        long long old = items[0] % divider;
        long long second = second_value;

        if (second_value == 0) {
            second = old;
        }
        items.erase(items.begin());
        switch (operator_type) {
            case '+':
                return old + second;
//            case '-':
//                return old - second_value;
            case '*':
                return old * second;
//            case '/':
//                return old / second_value;
            default:
                return 0;
        }
        return 0;
    }
    int test(long long value)
    {
        return value % divisible == 0 ? positive_test_index : negative_test_index;
    }
    
};

bool canBeConvertedToInt(const std::string& str) {
    std::istringstream iss(str);
    int num;
    iss >> num;

    // Check if input succeeded and we reached the end of the string
    return iss.eof() && !iss.fail();
}

// Comparison function
bool compareByBuisness(const Monkey& a, const Monkey& b) {
    return a.monkey_buisness > b.monkey_buisness;
}

long calculate_monkey_buisness(vector<string> input)
{
    vector<Monkey> monkeys;
    
    for (int i = 0; i < input.size(); i+=6)
    {
        string skip;
        Monkey monkey;
        string items_str = input[i+1];

        // Erase the "removed" characters
        items_str.erase(std::remove(items_str.begin(), items_str.end(), ','), items_str.end());
        std::istringstream iss(items_str);
        iss >> skip >> skip;
        int item;
        while (iss >> item) {
            monkey.items.push_back(item);
        }
        iss.clear();
        string operation = input[i+2];
        iss.str(operation);
        
        iss >> skip >> skip >> skip >> skip >> monkey.operator_type >> skip;
        
        if (canBeConvertedToInt(skip)) {
            monkey.second_value = stoi(skip);
        } else {
            monkey.second_value = 0;
        }
        
        iss.clear();
        string test_str = input[i+3];
        iss.str(test_str);
        iss >> skip >> skip >> skip >> monkey.divisible;
        
        iss.clear();
        string positive_str = input[i+4];
        iss.str(positive_str);
        iss >> skip >> skip >> skip >> skip >> skip >> monkey.positive_test_index;
        
        iss.clear();
        string negative_str = input[i+5];
        iss.str(negative_str);
        iss >> skip >> skip >> skip >> skip >> skip >> monkey.negative_test_index;
        
        monkeys.push_back(monkey);
    }
    cout << endl;
    
    for (const Monkey& monkey: monkeys)
    {
        cout << "Operator: " << monkey.operator_type << " " << monkey.second_value << " " << monkey.divisible << " " <<monkey.positive_test_index<< " "<<monkey.negative_test_index<< " -> | ";
        for (const long long& item: monkey.items) {
            cout << item << " ";
        }
        cout << "|" << endl;
    }
    long divider = 1;
    
    for (const Monkey& monkey: monkeys)
    {
        divider = monkey.divisible * divider;
    }
    
    for (int r = 0; r < 10000; r++) {
        for (int i = 0; i < monkeys.size(); i++)
        {
            long long worry_level;
            
            long long count = monkeys[i].items.size();
            monkeys[i].monkey_buisness += count;
            for (int l = 0; l < count; l++) {
                worry_level = monkeys[i].operate(divider);
//                worry_level /= 3;
                int test = monkeys[i].test(worry_level);
                monkeys[test].items.push_back(worry_level);
            }
        }
        cout << "Round: " << r + 1 << endl;
        for (int i = 0; i < monkeys.size(); i++)
        {
            cout << "Monkey " << i << ": " << monkeys[i].monkey_buisness << " times -> | " ;
            for (const long long& item: monkeys[i].items) {
                cout << item << " ";
            }
            cout << "|" << endl;
        }
        cout << endl;
    }
    cout << "|" << endl;
    
    std::sort(std::begin(monkeys), std::end(monkeys), compareByBuisness);

    for (int i = 0; i < monkeys.size(); i++)
    {
        cout << "Monkey " << i << ": " << monkeys[i].monkey_buisness << " times" << endl;
    }
    
    return monkeys[0].monkey_buisness * monkeys[1].monkey_buisness;
}
