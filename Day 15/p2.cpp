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
        string line = "";
        for (auto &i : buffer)
        {
            if (i == '.')
                line += "..";
            else if (i == '#')
                line += "##";
            else if (i == 'O')
                line += "[]";
            else if (i == '@')
                line += "@.";
        }
        grid.push_back(line);
    }

    string moves;
    while (getline(f, buffer))
    {
        moves += buffer;
    }

    pair<int, int> location;
    vector<pair<int, int>> boxes;
    for (auto i = 1; i < grid.size() - 1; i++)
        for (int j = 1; j < grid[0].size() - 1; j++)
        {
            if (grid[i][j] == '@')
                location = {i, j};
            else if (grid[i][j] == '[')
                boxes.push_back({i, j});
        }
    grid[location.first][location.second] = '.';

    for (auto &move : moves)
    {
        stack<pair<int, int>> safeCheck;
        set<int> changes;

        switch (move)
        {
        case '^':
            safeCheck.push({location.first - 1, location.second});
            break;

        case 'v':
            safeCheck.push({location.first + 1, location.second});
            break;

        case '<':
            safeCheck.push({location.first, location.second - 1});
            break;

        case '>':
            safeCheck.push({location.first, location.second + 1});
            break;
        }

        int row = location.first;
        int column = location.second;
        int safe = 1;

        while (safeCheck.size())
        {

            row = safeCheck.top().first;
            column = safeCheck.top().second;
            safeCheck.pop();

            if (grid[row][column] == '#')
            {
                safe = 0;
                break;
            }
            else if (grid[row][column] == '[')
            {
                switch (move)
                {
                case '^':
                    safeCheck.push({row - 1, column});
                    break;

                case 'v':
                    safeCheck.push({row + 1, column});
                    break;

                case '<':
                    safeCheck.push({row, column - 1});
                    break;

                    // case '>':
                    //     safeCheck.push({row, column + 1});
                    //     break;
                }
                // if (safeCheck.top().first != row || safeCheck.top().second != column + 1)
                safeCheck.push({row, column + 1});
                for (int i = 0; i < boxes.size(); i++)
                    if (boxes[i].first == row && boxes[i].second == column)
                    {
                        changes.insert(i);
                        break;
                    }
            }
            else if (grid[row][column] == ']')
            {
                int place = -1;
                for (int i = 0; i < boxes.size(); i++)
                    if (boxes[i].first == row && boxes[i].second == column - 1)
                    {
                        place = i;
                        break;
                    }
                switch (move)
                {
                case '^':
                    safeCheck.push({row - 1, column});
                    break;

                case 'v':
                    safeCheck.push({row + 1, column});
                    break;

                    // case '<':
                    //     safeCheck.push({row, column - 1});
                    //     break;

                case '>':
                    safeCheck.push({row, column + 1});
                    break;
                }
                if (!changes.contains(place))
                    safeCheck.push({row, column - 1});
            }
            else
            {
                // safeCheck.pop();
                continue;
            }
        }

        if (safe)
        {
            for (auto &i : changes)
            {
                grid[boxes[i].first][boxes[i].second] = '.';
                grid[boxes[i].first][boxes[i].second + 1] = '.';
                switch (move)
                {
                case '^':

                    boxes[i].first--;
                    break;

                case 'v':
                    boxes[i].first++;
                    break;

                case '<':
                    boxes[i].second--;
                    break;

                case '>':
                    boxes[i].second++;
                    break;
                }
            }
            for (auto &i : changes)
            {
                grid[boxes[i].first][boxes[i].second] = '[';
                grid[boxes[i].first][boxes[i].second + 1] = ']';
            }

            switch (move)
            {
            case '^':

                location.first--;
                break;

            case 'v':
                location.first++;
                break;

            case '<':
                location.second--;
                break;

            case '>':
                location.second++;
                break;
            }
        }
    }

    ll sum = 0;
    for (auto &i : boxes)
        sum += i.first * 100 + i.second;

    cout << sum << endl;
}