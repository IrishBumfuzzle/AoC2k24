#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <regex>
#define ll long long int
using namespace std;

vector<vector<int>> AllWays;

int ObstacleInFront(vector<string> &grid, int row, int column, int dir)
{
    switch (dir)
    {
    case 0:
        row--;
        break;
    case 1:
        column++;
        break;
    case 2:
        row++;
        break;
    case 3:
        column--;
        break;
    default:
        break;
    }

    if (row < grid.size() && column < grid[row].size() && grid[row][column] == '#')
        return 1;
    return 0;
}

int PathfindArea(vector<string> grid, int row, int column, int dir, int PreviousPositions[][130])
{
    int row_new = row, col_new = column;
    switch (dir)
    {
    case 0:
        row_new--;
        break;
    case 1:
        col_new++;
        break;
    case 2:
        row_new++;
        break;
    case 3:
        col_new--;
        break;
    default:
        break;
    }
    if (row_new < grid.size() && col_new < grid[row].size() && PreviousPositions[row_new][col_new] == -1)
        grid[row_new][col_new] = '#';
    else
        return 0;

    dir = dir == 3 ? 0 : dir + 1;
    int NewPositions[130][130];
    for (int i = 0; i < 130; i++)
    {
        for (int j = 0; j < 130; j++)
        {
            NewPositions[i][j] = PreviousPositions[i][j];
        }
    }

    while (row < grid.size() && column < grid[row].size())
    {
        if (ObstacleInFront(grid, row, column, dir))
        {
            dir = dir == 3 ? 0 : dir + 1;
            continue;
        }
        if (NewPositions[row][column] % (dir + 4) == 0)
            return 1;

        if (NewPositions[row][column] == -1)
            NewPositions[row][column] = dir + 4;
        else
            NewPositions[row][column] *= dir + 4;

        switch (dir)
        {
        case 0:
            row--;
            break;
        case 1:
            column++;
            break;
        case 2:
            row++;
            break;
        case 3:
            column--;
            break;
        default:
            break;
        }
    }
    return 0;
}

int main()
{
    ifstream f;
    f.open("input.txt");
    string buffer;
    vector<string> grid;
    while (getline(f, buffer))
    {
        grid.push_back(buffer);
    }

    int row, column;
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            if (grid[i][j] == '^')
            {
                grid[i][j] = '.';
                row = i;
                column = j;
                AllWays.push_back({row, column});
                break;
            }
        }
    }

    int dir = 0;
    int PreviousPositions[130][130];
    for (int i = 0; i < 130; i++)
    {
        for (int j = 0; j < 130; j++)
        {
            PreviousPositions[i][j] = -1;
        }
    }
    while (row < grid.size() && column < grid[row].size())
    {
        if (ObstacleInFront(grid, row, column, dir))
        {
            dir = dir == 3 ? 0 : dir + 1;
        }
        else
        {
            int found = 0;
            if (PathfindArea(grid, row, column, dir, PreviousPositions))
                found = 1;

            if (PreviousPositions[row][column] == -1)
                PreviousPositions[row][column] = dir + 4;
            else
                PreviousPositions[row][column] *= dir + 4;

            switch (dir)
            {
            case 0:
                row--;
                break;
            case 1:
                column++;
                break;
            case 2:
                row++;
                break;
            case 3:
                column--;
                break;
            default:
                break;
            }
            if (found == 1)
            {
                int unique = 1;
                for (auto &i : AllWays)
                    if (i[0] == row && i[1] == column)
                        unique = 0;

                if (unique)
                    AllWays.push_back({row, column});
            }
        }
    }

    cout << AllWays.size() - 1 << '\n';
}
