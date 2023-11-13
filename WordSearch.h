#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <array>

const int MAX_ROWS = 10;
const int MAX_COLS = 10;

void PrintGrid(char grid[][MAX_COLS]);

bool CanPlaceWord(char grid[][MAX_COLS], std::string word, int row,
                  int col, int dRow, int dCol);

void PlaceWord(char grid[][MAX_COLS], const std::string& word, 
               std::vector<std::pair<std::pair<int, int>, 
               std::pair<int, int>>>& usedCoords, bool upper = false);

