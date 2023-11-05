//
//  day_eight.cpp
//  advent_of_code_2022_cpp
//
//  Created by Maksym Kostynskyi on 09.12.2022.
//

#include "day_eight.hpp"
#include <vector>
#include <set>
#include <string>
#include <iostream>
#include <map>
#include <iterator>
#include <algorithm>
#include <array>

using namespace std;

bool is_tree_visible(int row, int column, vector<vector<int>> trees_heights)
{
    bool is_visible = false;
    // look from row start
    for (long i = 0; i < column; i++)
    {
        is_visible = trees_heights[row][i] < trees_heights[row][column];
        if (!is_visible)
        {
            break;
        }
    }
    
    if (is_visible)
    {
        return true;
    }
    
    // look from row end
    for (long i = trees_heights.size() - 1; i > column; i--)
    {
        is_visible = trees_heights[row][i] < trees_heights[row][column];
        if (!is_visible)
        {
            break;
        }
    }
    
    if (is_visible)
    {
        return true;
    }
    
    // look from column start
    for (long i = 0; i < row; i++)
    {
        is_visible = trees_heights[i][column] < trees_heights[row][column];
        if (!is_visible)
        {
            break;
        }
    }
    
    if (is_visible)
    {
        return true;
    }
    
    // look from column end
    for (long i = trees_heights.size() - 1; i > row; i--)
    {
        is_visible = trees_heights[i][column] < trees_heights[row][column];
        if (!is_visible)
        {
            break;
        }
    }
    
    if (is_visible)
    {
        return true;
    }
    
    return false;
}

long get_scienic_score(int row, int column, vector<vector<int>> trees_heights)
{
    long scienic_score = 1;
    long temp_scienic_score = 0;
    bool is_visible = false;
    // look to row start
    for (long i = column - 1; i >= 0; i--)
    {
        is_visible = trees_heights[row][i] < trees_heights[row][column];
        temp_scienic_score++;
        if (!is_visible)
        {
            break;
        }
    }
    
    if (temp_scienic_score > 0) {
        scienic_score *= temp_scienic_score;
    }
    temp_scienic_score = 0;
    
    // look to row end
    for (long i = column + 1; i < trees_heights.size(); i++)
    {
        is_visible = trees_heights[row][i] < trees_heights[row][column];
        temp_scienic_score++;
        if (!is_visible)
        {
            break;
        }
    }
    
    if (temp_scienic_score > 0) {
        scienic_score *= temp_scienic_score;
    }
    temp_scienic_score = 0;
    
    // look from column start
    for (long i = row - 1; i >= 0; i--)
    {
        is_visible = trees_heights[i][column] < trees_heights[row][column];
        temp_scienic_score++;
        if (!is_visible)
        {
            break;
        }
    }
    
    if (temp_scienic_score > 0) {
        scienic_score *= temp_scienic_score;
    }
    temp_scienic_score = 0;
    
    // look from column end
    for (long i = row + 1; i < trees_heights.size(); i++)
    {
        is_visible = trees_heights[i][column] < trees_heights[row][column];
        temp_scienic_score++;
        if (!is_visible)
        {
            break;
        }
    }
    
    if (temp_scienic_score > 0) {
        scienic_score *= temp_scienic_score;
    }
    temp_scienic_score = 0;
    
    return scienic_score;
}

int calculate_visible_trees(vector<string> treesMap)
{
    vector<vector<int>> trees_heights;
    
    vector<int> temp_vector;
    long visible_trees_count = 0;
    
    for (auto s: treesMap)
    {
        for (auto c: s)
        {
            temp_vector.push_back(c - '0');
        }
        trees_heights.push_back(temp_vector);
        temp_vector.clear();
    }
    
    cout<<endl;
    
    long max_scienic_score = 0;
    long temp_scienic_score = 0;
    int max_scienic_row = 0;
    int max_scienic_column = 0;
    
    for (int i = 0; i < trees_heights.size(); i++)
    {
        for (int j = 0; j < trees_heights[i].size(); j++)
        {
            if (i == 0 || j == 0 || i == trees_heights.size() - 1 || j == trees_heights[i].size() - 1)
            {
                continue;
            }
            
            if (i == 3 && j == 2) {
                cout << endl;
            }
            
            temp_scienic_score = get_scienic_score(i, j, trees_heights);
            
            if (temp_scienic_score > max_scienic_score)
            {
                max_scienic_score = temp_scienic_score;
                max_scienic_row = i;
                max_scienic_column = j;
            }
            
        }
    }
    
    for (int i = 0; i < trees_heights.size(); i++)
    {
        for (int j = 0; j < trees_heights[i].size(); j++)
        {
            if (i == 0 || j == 0 || i == trees_heights.size() - 1 || j == trees_heights[i].size() - 1)
            {
                cout << " " << trees_heights[i][j] << " ";
                continue;
            }
            
            if (i == max_scienic_row && j == max_scienic_column) {
                visible_trees_count++;
                cout << "(" << trees_heights[i][j] << ")";
            } else {
                cout << " " << trees_heights[i][j] << " ";
            }
        }
        cout<<endl;
    }
    
    return (int)max_scienic_score;
}
