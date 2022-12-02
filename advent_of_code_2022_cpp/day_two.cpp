//
//  day_two.cpp
//  advent_of_code_2022_cpp
//
//  Created by Maksym Kostynskyi on 02.12.2022.
//

#include "day_two.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <iterator>

using namespace std;

int get_score(char elvesShape, char myShape)
{
    int score = 0;
    static map<char, int> shapesMap;
    shapesMap.insert(pair<char, int>('A', 1));
    shapesMap.insert(pair<char, int>('B', 2));
    shapesMap.insert(pair<char, int>('C', 3));
    shapesMap.insert(pair<char, int>('X', 1));
    shapesMap.insert(pair<char, int>('Y', 2));
    shapesMap.insert(pair<char, int>('Z', 3));
    
    score += shapesMap[myShape];
    
    if (shapesMap[elvesShape] == shapesMap[myShape])
    {
        score += 3;
        
        return score;
    }

    string bothShapes{elvesShape, myShape};
    
   if (bothShapes == "AY" || bothShapes == "BZ" || bothShapes == "CX")
   {
       score += 6;
   }
    
    return score;
}

char get_shape_by_strategy(char elvesShape, char myStrategy)
{
    map<char, char> shapes;
    
    shapes.insert(pair<char, char>('A', 'X'));
    shapes.insert(pair<char, char>('B', 'Y'));
    shapes.insert(pair<char, char>('C', 'Z'));
    
    map<char, char> loseShapes;
    
    loseShapes.insert(pair<char, char>('A', 'Z'));
    loseShapes.insert(pair<char, char>('B', 'X'));
    loseShapes.insert(pair<char, char>('C', 'Y'));
    
    map<char, char> winShapes;
    
    winShapes.insert(pair<char, char>('A', 'Y'));
    winShapes.insert(pair<char, char>('B', 'Z'));
    winShapes.insert(pair<char, char>('C', 'X'));
    if (myStrategy == 'Y') {
        return shapes[elvesShape];
    }
    
    if (myStrategy == 'X') {
        return loseShapes[elvesShape];
    }
    
    
    return winShapes[elvesShape];
}

int calculate_strategy_score(vector<string> inputStrategy)
{
    int score = 0;
    
    const char* tempStr;
    
    for (int i = 0; i < inputStrategy.size(); i++)
    {
        tempStr = inputStrategy[i].c_str();
        
        score += get_score(tempStr[0], get_shape_by_strategy(tempStr[0], tempStr[2]));
    }
    
    return score;
}
