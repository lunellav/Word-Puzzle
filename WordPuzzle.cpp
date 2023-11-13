#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>
#include <cstdlib>
#include <array>
#include <cctype>
#include "WordSearch.h"

using namespace std;

int main()
{
    short beg_row, beg_col, end_row, end_col;
    char br1, br2, comma;

    srand(static_cast<unsigned>(time(nullptr)));

    const int MAX_WORDS = 5;
    char grid[MAX_ROWS][MAX_COLS] = { {'\0'} };

    ifstream data_file;

    data_file.open("Words.text");

    data_file.seekg(0, ios::end);
    streampos filesize = data_file.tellg();

    cerr << "File size is " << filesize << '\n';

    array <string,MAX_WORDS> words;

    int num_words = 0;

    while (num_words < MAX_WORDS) //while array is not full
    {
        data_file.seekg(rand() % filesize);

        while (filesize != 0 && !isspace(data_file.peek()))
        {
            data_file.seekg(-1, ios::cur); // move the pointer backwards
        }

        if (words[num_words] == words[i]) //make sure no same words
        {
            data_file >> words[num_words];
            num_words++;
        }
        else
        {
            num_words++;
        }
    }

    cout << "\nHello, Welcome to the WordSearch Puzzle !\n"
            "\nThe words you will need to find are : \n";

    size_t arr_size = size(words);
    for (size_t a = 0; a < arr_size; a++)
    {
        cout << words[a] << " ";
    }
    cout << "\n\n";

    cerr << "Words selected\n";

    // place each word in the grid
    vector<pair<pair<int, int>,pair<int, int>>> UsedCoords;

    for (int i = 0; i < MAX_WORDS; i++)
    {
        string word(words[i]); // convert the row to a string
        PlaceWord(grid, word, UsedCoords); // pass the vector as an argument
    }

    cerr<<"Words placed\n";

    // initialize grid with random letters
    for (int i = 0; i < MAX_ROWS; i++)
    {
        for (int j = 0; j < MAX_COLS; j++)
        {
            if (grid[i][j] == '\0')
            {
                grid[i][j] = static_cast<char>('a' + rand() % 26);
            }
        }
    }
    cerr<<"Rest of grid filled\n\n";
    // print the grid

    int count = 0;

    do
    {
        PrintGrid(grid);

        cout << "\nEnter the coordinates of the word you found :\n"
                "\n1. Where does it begin? (row, column) : ";

        cin >> br1 >> beg_row >> comma >> ws >> beg_col >> br2;

        cout << "2. Where does it end? (row, column) : ";

        cin >> br1 >> end_row >> comma >> ws >> end_col >> br2;

        bool FoundWords = false;

        for (int i = 0; i < MAX_WORDS; i++)
        {
            pair<int, int> start = UsedCoords[i].first;
            pair<int, int> end = UsedCoords[i].second;

            int start_word_row = (start.first + 1),
                start_word_col = (start.second + 1),
                end_word_row = (end.first + 1),
                end_word_col = (end.second + 1);

            bool upper = false;

            if (beg_row == start_word_row && beg_col == start_word_col 
                && end_row == end_word_row && end_col == end_word_col)
            {
                upper = true;
                PlaceWord(grid, words[i], UsedCoords, upper);
                FoundWords = true;
                count++;
                cout << "\nCongrats!! You found the word " 
                     << words[i] << "\n\n";
            }
        }
        if (!FoundWords)
        {
            cout << "\nSorry you didn't find an actual word...\n\n";
        }
    } while (count != MAX_WORDS);

    PrintGrid(grid);

    cout << "\nWow! You found everything! You are made "
            "for wordsearch puzzles user!\n";

    return 0;
}
