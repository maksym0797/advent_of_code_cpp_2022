//
//  day_three.cpp
//  advent_of_code_2022_cpp
//
//  Created by Maksym Kostynskyi on 03.12.2022.
//

#include "day_three.hpp"
#include <vector>
#include <set>
#include <string>
#include <iostream>
#include <map>
#include <iterator>
#include <algorithm>

using namespace std;

set<int> get_intersect_set(string tempStr)
{
    set<char> first_compartment;
    set<char> second_compartment;
    for (int j = 0; j < tempStr.length(); j++)
    {
        if (j < tempStr.length() / 2) {
            first_compartment.insert(tempStr[j]);
        } else {
            second_compartment.insert(tempStr[j]);
        }
    }

    set<int> intersect;
    set_intersection(first_compartment.begin(), first_compartment.end(), second_compartment.begin(), second_compartment.end(),
                     inserter(intersect, intersect.begin()));
    
    return intersect;
}

set<int> fill_set_from_string(string rucksack)
{
    set<int> result_set;
    for (auto s: rucksack)
    {
        result_set.insert((char)s);
    }
    
    return result_set;
}

set<int> get_intersect_of_three(set<int> first_elf, set<int> second_elf, set<int> third_elf)
{
    set<int> intersect_of_two;
    set<int> intersect_of_three;
    
    set_intersection(first_elf.begin(), first_elf.end(), second_elf.begin(), second_elf.end(),
                     inserter(intersect_of_two, intersect_of_two.begin()));
    
    set_intersection(third_elf.begin(), third_elf.end(), intersect_of_two.begin(), intersect_of_two.end(),
                     inserter(intersect_of_three, intersect_of_three.begin()));
    
    return intersect_of_three;
}


int count_intersect_types(vector<string> rucksacks)
{
    int prioties_sum = 0;
    for (int i = 0; i < rucksacks.size(); i+=3)
    {
       
//        set<int> intersect = get_intersect_set(rucksacks[i]);
        set<int> first_elf = fill_set_from_string(rucksacks[i]);
        set<int> second_elf = fill_set_from_string(rucksacks[i+1]);
        set<int> third_elf = fill_set_from_string(rucksacks[i+2]);
        set<int> intersect = get_intersect_of_three(first_elf, second_elf, third_elf);
        for (auto it: intersect)
        {
            prioties_sum += (it > 'Z' ? it - 'a' + 1 : it - 'A' + 1 + 26);
        }
    }
    return prioties_sum;
}

