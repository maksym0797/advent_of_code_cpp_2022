//
//  day_ten.cpp
//  advent_of_code_2022_cpp
//
//  Created by Maksym Kostynskyi on 05.11.2023.
//

#include "day_ten.hpp"
#include <stdio.h>
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


int calculate_signal_strength(vector<string> commands)
{
    int registerX = 1;
    int signalStrength = registerX;
    int cycleNumber = 1;
    int cyclesToChange = 1;
    string command = "";
    int commandValue = 0;
    int strengthSum = 0;
    
    char display[6][40];
    
    for (int i = 0; i < 6; i++) {
        for(int j = 0; j < 40; j++) {
            display[i][j] = '.';
        }
    }
    cout << endl;

    for (const string& str: commands) {
        std::istringstream iss(str);
        iss >> command >> commandValue;
        if (command == "noop") {
            commandValue = 0;
            cyclesToChange = 1;
        }
        if (command == "addx") {
            cyclesToChange = 2;
        }
        
        for (int i = 0; i < cyclesToChange; i++) {
//            signalStrength = registerX * cycleNumber;
            int index = cycleNumber % 40 - 1;
            if ((registerX - 1) == index || index == (registerX + 1) || index == registerX) {
//                cout << cycleNumber << " -> " <<(cycleNumber / 40) << "|" <<cycleNumber % 40 << endl;
                display[(cycleNumber / 40)][index] = '#';
            }
            cycleNumber++;
            
        }
        registerX += commandValue;

    }
    
    for (int i = 0; i < 6; i++) {
        for(int j = 0; j < 40; j++) {
            cout << display[i][j];
        }
        cout << endl;
    }
    
    return strengthSum;
}
/*
 if (cycleNumber == 20) {
     cout << "Command: " << command << " strengthSum: " << strengthSum << " Register: " << registerX << " Cycle: " << cycleNumber << endl;
     strengthSum += signalStrength;
 }
 if (cycleNumber == 60) {
     cout << "Command: " << command << " strengthSum: " << strengthSum << " Register: " << registerX << " Cycle: " << cycleNumber << endl;
     strengthSum += signalStrength;
 }
 if (cycleNumber == 100) {
     cout << "Command: " << command << " strengthSum: " << strengthSum << " Register: " << registerX << " Cycle: " << cycleNumber << endl;
     strengthSum += signalStrength;
 }
 if (cycleNumber == 140) {
     cout << "Command: " << command << " strengthSum: " << strengthSum << " Register: " << registerX << " Cycle: " << cycleNumber << endl;
     strengthSum += signalStrength;
 }
 if (cycleNumber == 180) {
     cout << "Command: " << command << " strengthSum: " << strengthSum << " Register: " << registerX << " Cycle: " << cycleNumber << endl;
     strengthSum += signalStrength;
 }
 if (cycleNumber == 220) {
     cout << "Command: " << command << " strengthSum: " << strengthSum << " Register: " << registerX << " Cycle: " << cycleNumber << endl;
     strengthSum += signalStrength;
 }
 */
