//
//  day_nine.cpp
//  advent_of_code_2022_cpp
//
//  Created by Maksym Kostynskyi on 24.12.2022.
//

#include "day_nine.hpp"
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

long count_tail_positions(vector<string> headHistory)
{
    char direction;
    int steps;
    
    int xS = 1000;
    int yS = 1000;
    
    int yH = yS;
    int xH = xS;
    int yHprev = yS;
    int xHprev = xS;
    int yT = yS;
    int xT = xS;
    int yTempComp = yS;
    int xTempComp = xS;
    int yTempPrev = yS;
    int xTempPrev = xS;
    int ySub = yS;
    int xSub = xS;
    
    set<string> positions;
    
//    positions.insert(to_string(yS) + " " + to_string(xS));
    // Create a vector of pairs of integers
    std::vector<std::pair<int, int>> vecOfPairs;
    for (int i = 0; i < 8; i++) {
        vecOfPairs.push_back(make_pair(yS, xS));
    }
    cout << endl;
    for (const std::string& str : headHistory) {
        std::istringstream iss(str);
        iss >> direction >> steps;
        cout << "Direction: " << direction << " Steps: " << steps <<  endl;

        for (int i = 0; i < steps; i++) {
            yHprev = yH;
            xHprev = xH;
            if (direction == 'U') {
                yH--;
            }
            if (direction == 'R') {
                xH++;
            }
            if (direction == 'L') {
                xH--;
            }
            if (direction == 'D') {
                yH++;
            }
            yTempComp = yH;
            xTempComp = xH;
            yTempPrev = yHprev;
            xTempPrev = xHprev;
            if (abs(yTempComp - yT) > 1 || abs(xTempComp-xT) > 1) {
                yT = yTempPrev;
                xT = xTempPrev;
            }
            yTempComp = yT;
            xTempComp = xT;
            
            for (int f = 0; f < vecOfPairs.size(); f++) {
                ySub = vecOfPairs[f].first;
                xSub = vecOfPairs[f].second;
//                bool found = false;
//                cout << endl;
//
//                for (int q = 0; q < 21; q++) {
//                    for (int j = 0; j < 26; j++) {
//                        if ((q == yH) && (j == xH)) {
//                            cout << "H";
//                            continue;
//                        }
//                        if ((q == yT) && (j == xT)) {
//                            cout << "1";
//                            continue;
//                        }
//                        found = false;
//                        for (int k = 0; k < vecOfPairs.size(); k++) {
//                            if (vecOfPairs[k].first == q && vecOfPairs[k].second == j) {
//                                cout << k + 2;
//                                found = true;
//                                break;
//                            }
//                        }
//                        if (!found) {
//                            cout << ".";
//                        }
//                    }
//                    cout << endl;
//                }
                if (steps == 8 && direction == 'L' && i == 3 && f == 3) {
                    xSub = vecOfPairs[f].second;
                }
                if ((abs(yTempComp - ySub) + abs(xTempComp-xSub)) > 2) {
                    if (yTempComp != ySub) {
                        if (yTempComp > ySub) {
                            ySub++;
                        } else {
                            ySub--;
                        }
                    }
                    if (xTempComp != xSub) {
                        if (xTempComp > xSub) {
                            xSub++;
                        } else {
                            xSub--;
                        }
                    }
//                    if (direction == 'U') {
//                        ySub--;
//                        xSub++;
//                    }
//                    if (direction == 'R') {
//                        if (yTempComp > ySub) {
//                            ySub++;
//                        } else {
//                            ySub--;
//                        }
//                        xSub++;
//                    }
//                    if (direction == 'L') {
//                        if (yTempComp > ySub) {
//                            ySub++;
//                        } else {
//                            ySub--;
//                        }
//                        
//                        xSub--;
//                        
//                    }
//                    if (direction == 'D') {
//                        ySub++;
//                        xSub--;
//                    }
                } else if (abs(yTempComp - ySub) > 1 || abs(xTempComp - xSub) > 1) {
                    if (abs(yTempComp - ySub) > 1) {
                        if (yTempComp > ySub) {
                            ySub++;
                        } else {
                            ySub--;
                        }
                    }
                    if (abs(xTempComp - xSub) > 1) {
                        if (xTempComp > xSub) {
                            xSub++;
                        } else {
                            xSub--;
                        }
                    }
                }
                
                vecOfPairs[f].first = ySub;
                vecOfPairs[f].second = xSub;
                yTempComp = ySub;
                xTempComp = xSub;
            }
            positions.insert(to_string(vecOfPairs[7].first) + to_string(vecOfPairs[7].second));
//            bool found = false;
//            for (int q = 0; q < 21; q++) {
//                for (int j = 0; j < 26; j++) {
//                    if ((q == yH) && (j == xH)) {
//                        cout << "H";
//                        continue;
//                    }
//                    if ((q == yT) && (j == xT)) {
//                        cout << "1";
//                        continue;
//                    }
//                    found = false;
//                    for (int k = 0; k < vecOfPairs.size(); k++) {
//                        if (vecOfPairs[k].first == q && vecOfPairs[k].second == j) {
//                            cout << k + 2;
//                            found = true;
//                            break;
//                        }
//                    }
//                    if (!found) {
//                        cout << ".";
//                    }
//                }
//                cout << endl;
//            }
//            cout << endl;

        }
    }
//    cout << endl;

    
    return positions.size();
}


// wrong -> 5987
