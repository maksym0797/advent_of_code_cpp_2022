//
//  day_seven.cpp
//  advent_of_code_2022_cpp
//
//  Created by Maksym Kostynskyi on 07.12.2022.
//

#include "day_seven.hpp"
#include "day_four.hpp"
#include <vector>
#include <set>
#include <string>
#include <iostream>
#include <map>
#include <iterator>
#include <algorithm>
#include <array>

using namespace std;

bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(),
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

long calculate_sum_of_dir_sizes_part1(vector<string> commands)
{
    long sum_of_total = 0;
    string tempStr = "";
    map<string, long> directories_sum;
    vector<string> splited_command;
    vector<string> directories_tree;

    for (int i = 0; i < commands.size(); i++)
    {
        tempStr = commands[i];
        if (tempStr.substr(0, 3) == "dir")
        {
            continue;
        }
        if (tempStr.substr(0, 4) == "$ ls")
        {
            continue;
        }
        if (tempStr.substr(0, 4) == "$ cd")
        {
            string dir = tempStr.substr(5, tempStr.length() - 5);
            if (dir == "..")
            {
                directories_tree.pop_back();
            } else {
                directories_tree.push_back(dir);
            }
            continue;
        }
        splited_command = get_splited_strings_by_delimiter(tempStr, ' ');
        if (is_number(splited_command[0]))
        {
            long size = stol(splited_command[0]);
            string path = "";
            for (int j = 0; j < directories_tree.size(); j++)
            {
                path += directories_tree[j];
                directories_sum[path] += size;
            }
        }
    }

    for (auto const& [key, val] : directories_sum)
    {
        if (val <= 100000)
        {
            sum_of_total += val;
        }
    }
    
    return sum_of_total; // last 1211472 -> 1367870
}

long calculate_sum_of_dir_sizes(vector<string> commands)
{
    string tempStr = "";
    map<string, long> directories_sum;
    vector<string> splited_command;
    vector<string> directories_tree;

    for (int i = 0; i < commands.size(); i++)
    {
        tempStr = commands[i];
        if (tempStr.substr(0, 3) == "dir")
        {
            continue;
        }
        if (tempStr.substr(0, 4) == "$ ls")
        {
            continue;
        }
        if (tempStr.substr(0, 4) == "$ cd")
        {
            string dir = tempStr.substr(5, tempStr.length() - 5);
            if (dir == "..")
            {
                directories_tree.pop_back();
            } else {
                directories_tree.push_back(dir);
            }
            continue;
        }
        splited_command = get_splited_strings_by_delimiter(tempStr, ' ');
        if (is_number(splited_command[0]))
        {
            long size = stol(splited_command[0]);
            string path = "";
            for (int j = 0; j < directories_tree.size(); j++)
            {
                path += directories_tree[j] + "/";
                directories_sum[path] += size;
            }
        }
    }

    long min_size = LONG_MAX;

    for (auto const& [key, val] : directories_sum)
    {
        cout << key << "->" << val << endl;
        if (val >= (30000000 - (70000000 - directories_sum["//"])))
        {
            if (min_size > val)
            {
                min_size = val;
            }
        }
    }
    
    return min_size; // -> 549173
}
