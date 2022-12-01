//
//  day_one.cpp
//  advent_of_code_2022_cpp
//
//  Created by Maksym Kostynskyi on 01.12.2022.
//

#include "day_one.hpp"
#include <vector>
#include <string>
#include <iostream>

int findMaxCalories(std::vector<std::string> inputList)
{
    int maxCalories = 0;
    int tempCalories = 0;
    for (int i = 0; i < inputList.size(); i++) {
        
        if (inputList[i] == "") {
            if (tempCalories > maxCalories) {
                maxCalories = tempCalories;
            }
            tempCalories = 0;
            continue;
        }
        
        tempCalories += std::stoi(inputList[i]);
    }
    return maxCalories;
}

int findTopThreeMaxCalories(std::vector<std::string> inputList)
{
    int tempCalories = 0;
    std::vector<int> elvesCalories;
    for (int i = 0; i < inputList.size(); i++) {
        
        if (inputList[i] == "") {
            elvesCalories.push_back(tempCalories);
            tempCalories = 0;
            continue;
        }
        
        tempCalories += std::stoi(inputList[i]);
    }
    
    std::sort(elvesCalories.begin(), elvesCalories.end(), std::greater<int>());

    return elvesCalories[0] + elvesCalories[1] + elvesCalories[2];
}
