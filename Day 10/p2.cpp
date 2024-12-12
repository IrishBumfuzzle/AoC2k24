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
    vector<string> content;

    ifstream f;
    f.open("input.txt");
    string buffer;
    while (getline(f, buffer))
    {
        content.push_back(buffer);
    }

    vector<vector<int>> ZeroList;
    for (int i = 0; i < content.size(); i++)
    {
        for (int j = 0; j < content[i].size(); j++)
        {
            if (content[i][j] == 0 + '0')
            {
                ZeroList.push_back({i, j, 0});
            }
        }
    }

    for (auto &zero : ZeroList)
    {
        queue<vector<int>> list;
        list.push({0, zero[0], zero[1]});
        while (!list.empty())
        {
            vector<int> entry = list.front();
            if (entry[0] == 9)
            {
                zero[2]++;
                list.pop();
                continue;
            }
            int i = entry[1];
            int j = entry[2];
            if (i > 0 && content[i - 1][j] == entry[0] + 1 + '0')
            {
                list.push({entry[0] + 1, i - 1, j});
            }
            if (j > 0 && content[i][j - 1] == entry[0] + 1 + '0')
            {
                list.push({entry[0] + 1, i, j - 1});
            }
            if (i < content.size() - 1 && content[i + 1][j] == entry[0] + 1 + '0')
            {
                list.push({entry[0] + 1, i + 1, j});
            }
            if (j < content[i].size() - 1 && content[i][j + 1] == entry[0] + 1 + '0')
            {
                list.push({entry[0] + 1, i, j + 1});
            }
            list.pop();
        }
    }

    int sum = 0;
    for (auto &i : ZeroList)
    {
        sum += i[2];
    }
    cout << sum;
}
