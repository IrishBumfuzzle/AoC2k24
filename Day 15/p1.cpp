#include <bits/stdc++.h>
#define ll long long int
using namespace std;

int main()
{
    ifstream f;
    f.open("input.txt");
    string buffer;

    vector<string> grid;
    while (getline(f, buffer) && buffer != "")
    {
        grid.push_back(buffer);
    }

    string moves;
    while (getline(f, buffer))
    {
        moves += buffer;
    }

    pair<int, int> location;
    for (auto i = 1; i < grid.size() - 1; i++)
        for (int j = 1; j < grid[0].size() - 1; j++)
            if (grid[i][j] == '@')
                location = {i, j};
    grid[location.first][location.second] = '.';

    for (auto &move : moves)
    {
        stack<pair<int, int>> changes;

        switch (move)
        {
        case '^':
            changes.push({location.first - 1, location.second});
            break;

        case 'v':
            changes.push({location.first + 1, location.second});
            break;

        case '<':
            changes.push({location.first, location.second - 1});
            break;

        case '>':
            changes.push({location.first, location.second + 1});
            break;
        }

        int row = location.first;
        int column = location.second;

        while (grid[changes.top().first][changes.top().second] != '.' && grid[changes.top().first][changes.top().second] != '#')
        {
            switch (move)
            {
            case '^':
                changes.push({row - 1, column});
                break;

            case 'v':
                changes.push({row + 1, column});
                break;

            case '<':
                changes.push({row, column - 1});
                break;

            case '>':
                changes.push({row, column + 1});
                break;
            }
            row = changes.top().first;
            column = changes.top().second;
        }

        if (grid[changes.top().first][changes.top().second] == '.')
        {
            while (!changes.empty())
            {
                pair<int, int> change = changes.top();
                if (changes.size() == 1)
                {
                    location.first = change.first;
                    location.second = change.second;
                    grid[change.first][change.second] = '.';
                }

                else
                {
                    grid[change.first][change.second] = 'O';
                }

                changes.pop();
            }
        }
    }

    ll sum = 0;
    for (int i = 1; i < grid.size() - 1; i++)
    {
        for (int j = 1; j < grid[0].size() - 1; j++)
        {
            if (grid[i][j] == 'O')
                sum += i * 100 + j;
        }
    }

    cout << sum << endl;
}