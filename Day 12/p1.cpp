#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <set>
#include <regex>
#include <queue>
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

    vector<pair<int, int>> regions;
    vector<string> mod_content(content);
    for (int i = 0; i < content.size(); i++)
    {
        for (int j = 0; j < content[i].size(); j++)
        {
            if (mod_content[i][j] != '0')
            {
                int area = 0, perimeter = 0;
                queue<pair<int, int>> q;
                q.push({i, j});
                int type = content[i][j];
                vector<string> new_content(content);

                while (!q.empty())
                {
                    int row = q.front().first;
                    int column = q.front().second;
                    q.pop();
                    if (new_content[row][column] == '0')
                        continue;
                    area++;

                    if (row > 0 && new_content[row - 1][column] == type)
                        q.push({row - 1, column});
                    else if (row == 0 || new_content[row - 1][column] != '0')
                        perimeter++;
                    if (column > 0 && new_content[row][column - 1] == type)
                        q.push({row, column - 1});
                    else if (column == 0 || new_content[row][column - 1] != '0')
                        perimeter++;
                    if (row < content.size() - 1 && new_content[row + 1][column] == type)
                        q.push({row + 1, column});
                    else if (row == content.size() - 1 || new_content[row + 1][column] != '0')
                        perimeter++;
                    if (column < content.size() - 1 && new_content[row][column + 1] == type)
                        q.push({row, column + 1});
                    else if (column == content.size() - 1 || new_content[row][column + 1] != '0')
                        perimeter++;
                    new_content[row][column] = '0';
                    mod_content[row][column] = '0';
                }
                regions.push_back({area, perimeter});
            }
        }
    }

    ll sum = 0;
    for (auto &i : regions)
    {
        sum += i.first * i.second;
    }
    cout << sum << '\n';
}