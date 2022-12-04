//
//  day_four.cpp
//  advent_of_code_2022_cpp
//
//  Created by Maksym Kostynskyi on 04.12.2022.
//

#include "day_four.hpp"
#include <vector>
#include <set>
#include <string>
#include <iostream>
#include <map>
#include <iterator>
#include <algorithm>
#include <sstream>

using namespace std;

vector<string> get_splited_strins_by_delimiter(string input, char delimiter)
{
    stringstream input_stream(input);
    string segment;
    vector<string> seglist;

    while(std::getline(input_stream, segment, delimiter))
    {
       seglist.push_back(segment);
    }
    
    return seglist;
}

vector<int> get_ranges_starts_ends(string pairs)
{
    vector<int> result;
    
    vector<string> splited_pairs = get_splited_strins_by_delimiter(pairs, ',');
    vector<string> pair_range;
    for (int i = 0; i < splited_pairs.size(); i++)
    {
        pair_range = get_splited_strins_by_delimiter(splited_pairs[i], '-');
        result.push_back(stoi(pair_range[0]));
        result.push_back(stoi(pair_range[1]));
    }
    
    return result;
}

int calculate_in_range_pairs(vector<string> inputPairs)
{
    int result = 0;
    
    vector<int> range;
    for (auto s: inputPairs)
    {
        range = get_ranges_starts_ends(s);
        
        // check if ranges does not overlap at all
        if ((range[0] < range[2] && range[1] < range[2]) || (range[2] < range[0] && range[3] < range[0])) {
            result++;
        }
    }
    
    return inputPairs.size() - result;
}
