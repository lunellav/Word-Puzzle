#include "WordSearch.h"
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <cctype>

using namespace std;

void PrintGrid(char grid[][MAX_COLS]) //can i just put it as int?
{
    for (int i = 0; i < MAX_ROWS; i++)
    {
        for (int j = 0; j < MAX_COLS; j++)
        {
            char c = grid[i][j];
            cout << c << " ";
        }
        cout << endl;
    }
}

bool CanPlaceWord(char grid[][MAX_COLS], string word, 
                 int row, int col, int dRow, int dCol)
{
    
    // check if word fits in the grid in this direction
    if (row + (word.length() - 1) * dRow >= MAX_ROWS ||
        col + (word.length() - 1) * dCol >= MAX_COLS)

    {
        return false;
    }

    // check if word overlaps with existing letters
    for (string::size_type i = 0; i < word.length(); i++)
    {
        string::size_type r, c;
        r = row + i * dRow;
        c = col + i * dCol;

        if (tolower(word[i]) != tolower(grid[r][c]) &&
            grid[r][c] != '\0')
        {
            return false;
        }
    }

    return true;
}

void PlaceWord(char grid[][MAX_COLS], const string& word,
               vector<pair<pair<int, int>,pair<int, int>>>
               &UsedCoords, bool upper)
{
    bool placed = false;

    while (!placed)
    {
        // pick a random beginning position and direction
        int row = rand() % MAX_ROWS;
        int col = rand() % MAX_COLS;
        int dRow = rand() % 3 - 1; // -1, 0, or 1
        int dCol = rand() % 3 - 1; // -1, 0, or 1

        // don't allow zero direction
        if (dRow == 0 && dCol == 0)
        {
            continue;
        }

        if (CanPlaceWord(grid, word, row, col, dRow, dCol))
        {
            string::size_type r, c;
            // place the word
            for (string::size_type i = 0; i < word.length(); i++)
            {
                r = row + i * dRow;
                c = col + i * dCol;
                if (upper)
                {
                    grid[r][c] = static_cast<char>(toupper (word[i]));
                }
                else
                {
                    grid[r][c] = word[i];
                }
            }
            UsedCoords.push_back({{row,col},{r, c}});

            placed = true;
        }
    }
}
