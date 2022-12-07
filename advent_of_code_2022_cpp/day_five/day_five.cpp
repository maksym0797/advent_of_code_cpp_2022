//
//  day_five.cpp
//  advent_of_code_2022_cpp
//
//  Created by Maksym Kostynskyi on 05.12.2022.
//

#include "day_five.hpp"
#include <vector>
#include <set>
#include <string>
#include <iostream>
#include <map>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <regex>
#include <array>

using namespace std;

vector<char> fill_tower_with_chars(vector<string> inputCrates, int separator_str_index, int tower_index)
{
    vector<char> tower;
    
    for (int i = separator_str_index - 2; i >= 0; i--)
    {
        if (inputCrates[i][tower_index] == '\0' || inputCrates[i][tower_index] == ' ')
        {
            break;
        }
        
        tower.push_back(inputCrates[i][tower_index]);
    }
    
    for (int i = 0; i < tower.size(); i++)
    {
        cout << tower[i];
    }
    
    return tower;
}

array<int, 3> get_action_numbers(string str)
{
    array<int, 3> actions;
    int i = 0;
    stringstream ss;
     
    /* Storing the whole string into string stream */
    ss << str;
     
        /* Running loop till the end of the stream */
        string temp;
        int found;
        while (!ss.eof()) {
     
            /* extracting word by word from stream */
            ss >> temp;
     
            /* Checking the given word is integer or not */
            if (stringstream(temp) >> found){
                actions[i++] = found;
            }
     
            /* To save from space at the end of string */
            temp = "";
        }
    
    return actions;
}

map<char,vector<char>> modify_towers(map<char,vector<char>> towers, char move_from_tower, char move_to_tower, int amount_to_move)
{
    for (int i = 0; i < amount_to_move; i++)
    {
        towers[move_to_tower].push_back(towers[move_from_tower].back());
        towers[move_from_tower].pop_back();
    }
    
    return towers;
}

map<char,vector<char>> modify_towers_by_stacks(map<char,vector<char>> towers, char move_from_tower, char move_to_tower, int amount_to_move)
{
    for (int i = (int)towers[move_from_tower].size() - amount_to_move; i < towers[move_from_tower].size(); i++)
    {
        towers[move_to_tower].push_back(towers[move_from_tower][i]);
    }
    for (int i = 0; i < amount_to_move; i++)
    {
//        towers[move_to_tower].push_back(towers[move_from_tower].back());
        towers[move_from_tower].pop_back();
    }
    
    return towers;
}

string get_crate_message(vector<string> inputCrates)
{
    auto it = find(inputCrates.begin(), inputCrates.end(), "");
    int separator_str_index = (int)(it - inputCrates.begin());
    string tower_numbers = inputCrates[separator_str_index-1];
    map<char,vector<char>> towers;
    string message;
    cout << endl;
    
    for (int i = 0; i < tower_numbers.length(); i++)
    {
        if (tower_numbers[i] == ' ')
        {
            continue;
        }
        
        towers[tower_numbers[i]] = fill_tower_with_chars(inputCrates, separator_str_index, i);
        cout << endl;
    }
    
    
    for (int i = separator_str_index + 1; i < inputCrates.size(); i++)
    {
        array<int, 3> actions = get_action_numbers(inputCrates[i]);
        int amount_to_move = actions[0];
        char from_tower = to_string(actions[1])[0];
        char to_tower = to_string(actions[2])[0];
        towers = modify_towers_by_stacks(towers, from_tower, to_tower, amount_to_move);
    }
    
    for (auto const& [key, val] : towers)
    {
        cout << key << " ";
        for (auto const& n: val)
        {
            cout << n;
        }
        cout << endl;
        message += val.back();
    }
    
    
    

    return message;
}
