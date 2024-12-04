#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <regex>
#define ll long long int
using namespace std;

int main()
{
    ifstream f;
    f.open("input.txt");
    vector<string> content;
    string buffer;
    while (getline(f, buffer))
    {
        content.push_back(buffer);
    }
    int count = 0;

    int NumLines = content.size();
    for (int i = 1; i < NumLines - 1; i++)
    {
        int LineLength = content[i].length();
        for (int j = 1; j < LineLength - 1; j++)
        {
            if (content[i][j] == 'A')
            {
                int check = 0;
                if (content[i - 1][j - 1] == 'M' && content[i + 1][j + 1] == 'S')
                    check++;
                if (content[i - 1][j - 1] == 'S' && content[i + 1][j + 1] == 'M')
                    check++;
                if (content[i + 1][j - 1] == 'M' && content[i - 1][j + 1] == 'S')
                    check++;
                if (content[i + 1][j - 1] == 'S' && content[i - 1][j + 1] == 'M')
                    check++;
                if (check == 2)
                    count++;
            }
        }
    }
    cout << count;
}