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
                deque<pair<int, int>> q;
                q.push_back({i, j});
                int type = content[i][j];
                vector<string> new_content(content);
                map<pair<int, int>, vector<int>> pers;

                while (!q.empty())
                {
                    int row = q.front().first;
                    int column = q.front().second;
                    q.pop_front();
                    if (new_content[row][column] == '0')
                        continue;
                    area++;
                    int up = 0, down = 0, right = 0, left = 0;

                    if (row < content.size() - 1 && new_content[row + 1][column] == type)
                        q.push_back({row + 1, column});
                    else if (row == content.size() - 1 || new_content[row + 1][column] != '0')
                        down++;
                    if (row > 0 && new_content[row - 1][column] == type)
                        q.push_front({row - 1, column});
                    else if (row == 0 || new_content[row - 1][column] != '0')
                        up++;
                    if (column > 0 && new_content[row][column - 1] == type)
                        q.push_front({row, column - 1});
                    else if (column == 0 || new_content[row][column - 1] != '0')
                        left++;
                    if (column < content[i].size() - 1 && new_content[row][column + 1] == type)
                        q.push_front({row, column + 1});
                    else if (column == content[i].size() - 1 || new_content[row][column + 1] != '0')
                        right++;

                    if (pers.contains({row - 1, column}))
                    {
                        if (right && pers[{row - 1, column}][3] != 0)
                            right = -1;
                        if (left && pers[{row - 1, column}][1] != 0)
                            left = -1;
                    }
                    if (pers.contains({row, column - 1}))
                    {
                        if (up && pers[{row, column - 1}][0] != 0)
                            up = -1;
                        if (down && pers[{row, column - 1}][2] != 0)
                            down = -1;
                    }
                    if (pers.contains({row + 1, column}))
                    {
                        if (right && pers[{row + 1, column}][3] != 0)
                            right = -1;
                        if (left && pers[{row + 1, column}][1] != 0)
                            left = -1;
                    }
                    if (pers.contains({row, column + 1}))
                    {
                        if (up && pers[{row, column + 1}][0] != 0)
                            up = -1;
                        if (down && pers[{row, column + 1}][2] != 0)
                            down = -1;
                    }

                    pers[{row, column}] = {up, left, down, right};
                    new_content[row][column] = '0';
                    mod_content[row][column] = '0';
                }
                for (auto &k : pers)
                {
                    if (k.second[0] == 1)
                        perimeter++;
                    if (k.second[1] == 1)
                        perimeter++;
                    if (k.second[2] == 1)
                        perimeter++;
                    if (k.second[3] == 1)
                        perimeter++;
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