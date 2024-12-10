#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <regex>
#include <queue>
#define ll long long int
using namespace std;

int main()
{
    vector<vector<int>> Antennas;
    vector<string> content;

    ifstream f;
    f.open("input.txt");
    string buffer;
    while (getline(f, buffer))
    {
        content.push_back(buffer);
    }

    for (int i = 0; i < content.size(); i++)
    {
        for (int j = 0; j < content[i].size(); j++)
        {
            if (content[i][j] != '.')
                Antennas.push_back({i, j, content[i][j]});
        }
    }

    int Antinodes[content.size()][content[0].size()] = {};
    int count = 0;
    for (auto &i : Antennas)
    {
        for (auto &j : Antennas)
        {
            if (i[2] == j[2] && i != j)
            {
                for (int k = 1; k < 100; k++)
                {
                    int row = k * i[0] - (k - 1) * j[0];
                    int column = k * i[1] - (k - 1) * j[1];
                    if (row >= 0 && column >= 0 && row < content.size() && column < content[row].size() && Antinodes[row][column] == 0)
                    {
                        Antinodes[row][column] = 1;
                        count++;
                    }
                }
            }
        }
    }

    cout << count;
}