//
//  main.cpp
//  advent_of_code_2022_cpp
//
//  Created by Maksym Kostynskyi on 01.12.2022.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "day_one.hpp"
#include "day_two.hpp"
#include "day_three.hpp"
#include "day_four.hpp"
#include "day_five.hpp"
#include "day_six.hpp"
#include "day_seven.hpp"
#include "day_eight.hpp"
#include "day_nine.hpp"
#include "day_ten.hpp"
#include "day_eleven.hpp"
#include "day_twelve.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    fstream inputFile;
    inputFile.open("/Users/Maksym_Kostynskyi/Code/playground/advent_of_code_2022_cpp/advent_of_code_2022_cpp/input.txt", ios::in);
    if (inputFile.is_open()) {
        string tempStr;
        vector<string> inputList;
        while (getline(inputFile, tempStr)) {
            inputList.push_back(tempStr);
        }
        cout << "Result is:" << find_least_steps(inputList) << endl;
    } else {
        cout << "Error, cannot open input file" << endl;
    }
    
    return 0;
}
