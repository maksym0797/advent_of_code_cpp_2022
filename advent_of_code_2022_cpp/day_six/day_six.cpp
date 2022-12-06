//
//  day_six.cpp
//  advent_of_code_2022_cpp
//
//  Created by Maksym Kostynskyi on 06.12.2022.
//

#include "day_six.hpp"
#include <vector>
#include <set>
#include <string>
#include <iostream>
#include <map>
#include <iterator>
#include <algorithm>
#include <array>

using namespace std;

bool is_unique(string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        if (count(str.begin(), str.end(), str[i]) > 1)
        {
            return false;
        }
    }
    return true;
}

long get_unique_marker(string str)
{
    string s = str;
    
    for (long i = 0; i < str.length() - 14; i++)
    {
        if (is_unique(str.substr(i, 14)))
        {
            return i + 14;
        }
    }
    
    return str.length();
}

long find_marker_start(vector<string> inputStreams)
{
    return get_unique_marker(inputStreams[0]);
}
