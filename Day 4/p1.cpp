#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <regex>
#define ll long long int
using namespace std;

vector<string> content;

int main()
{
    ifstream f;
    f.open("input.txt");

    string buffer;
    while (getline(f, buffer))
    {
        content.push_back(buffer);
    }
    int count = 0;

    int NumLines = content.size();
    for (auto i = 0; i < NumLines; i++)
    {
        int LineLength = content[i].length();
        for (auto j = 0; j < LineLength; j++)
        {
            if (content[i][j] == 'X')
            {
                // right
                if (j < LineLength - 3 && content[i][j + 1] == 'M' && content[i][j + 2] == 'A' && content[i][j + 3] == 'S')
                    count++;
                // left
                if (j > 2 && content[i][j - 1] == 'M' && content[i][j - 2] == 'A' && content[i][j - 3] == 'S')
                    count++;
                // down
                if (i < NumLines - 3 && content[i + 1][j] == 'M' && content[i + 2][j] == 'A' && content[i + 3][j] == 'S')
                    count++;
                // up
                if (i > 2 && content[i - 1][j] == 'M' && content[i - 2][j] == 'A' && content[i - 3][j] == 'S')
                    count++;
                // down-right
                if (j < LineLength - 3 && i < NumLines - 3 && content[i + 1][j + 1] == 'M' && content[i + 2][j + 2] == 'A' && content[i + 3][j + 3] == 'S')
                    count++;
                // down-left
                if (j > 2 && i < NumLines - 3 && content[i + 1][j - 1] == 'M' && content[i + 2][j - 2] == 'A' && content[i + 3][j - 3] == 'S')
                    count++;
                // up-left
                if (j > 2 && i > 2 && content[i - 1][j - 1] == 'M' && content[i - 2][j - 2] == 'A' && content[i - 3][j - 3] == 'S')
                    count++;
                // up-right
                if (j < LineLength - 3 && i > 2 && content[i - 1][j + 1] == 'M' && content[i - 2][j + 2] == 'A' && content[i - 3][j + 3] == 'S')
                    count++;
            }
        }
    }
    cout << count;
}